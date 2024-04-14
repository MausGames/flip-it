/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Flip It (https://www.maus-games.at)   |//
//*-----------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "main.h"


// ****************************************************************
cGame::cGame()noexcept
: m_fItemDelay    (ITEM_DELAY)
, m_iItemLastPos  (0u)
, m_iItemLastType (0u)
, m_fTime         (GAME_TIME + GAME_COUNTDOWN + GAME_WAIT)
, m_bStarted      (false)
{
    m_aPlayer[0].SetPosition   (coreVector3(coreVector2(-20.0f,0.0f) + FIELD_POSITION, 0.0f));
    m_aPlayer[0].SetColor3     (COLOR_PLAYER_1);
    m_aPlayer[0].SetTileType   (0u);
    m_aPlayer[0].SetControlType(0u);

    m_aPlayer[1].SetPosition   (m_aPlayer[0].GetPosition().InvertedX());
    m_aPlayer[1].SetColor3     (COLOR_PLAYER_2);
    m_aPlayer[1].SetTileType   (1u);
    m_aPlayer[1].SetControlType(1u);

    m_apItem.reserve(16u);

    m_Interface.SetColor(0u, COLOR_PLAYER_1);
    m_Interface.SetColor(1u, COLOR_PLAYER_2);
}


// ****************************************************************
cGame::~cGame()
{
    this->ClearItems();
}


// ****************************************************************
void cGame::Render()
{
    glDisable(GL_DEPTH_TEST);
    {
        for(coreUintW i = 0u; i < PLAYERS; ++i)
            m_aPlayer[i].Render();

        FOR_EACH(it, m_apItem)
            (*it)->Render();

        m_Interface.Render();
    }
    glEnable(GL_DEPTH_TEST);
}


// ****************************************************************
void cGame::Move()
{
    if(Core::Input->GetAnyButton(CORE_INPUT_PRESS) && !Core::Input->GetKeyboardButton(CORE_INPUT_KEY(SPACE), CORE_INPUT_PRESS))
    {
        m_bStarted = true;
    }

    if(m_bStarted)
    {
        m_fTime.Update(-1.0f);
        if(m_fTime < GAME_EXTEND) g_pField->Extend();
    }

    if((m_fTime <= GAME_TIME) && (m_fTime > 0.0f))
    {
        m_fItemDelay.Update(-1.0f);
        if(m_fItemDelay <= 0.0f)
        {
            const coreUint8 iNumPos = g_pField->GetExtended() ? 8u : 4u;
            m_iItemLastPos = (m_iItemLastPos + Core::Rand->Uint(1u, iNumPos-1u)) % iNumPos;

            coreVector2 vPosition;
            switch(m_iItemLastPos)
            {
            default: UNREACHABLE
            case 0: vPosition = coreVector2( 0.5f, 0.5f); break;
            case 1: vPosition = coreVector2( 0.5f,-0.5f); break;
            case 2: vPosition = coreVector2(-0.5f, 0.5f); break;
            case 3: vPosition = coreVector2(-0.5f,-0.5f); break;
            case 4: vPosition = coreVector2( 1.5f, 0.5f); break;
            case 5: vPosition = coreVector2( 1.5f,-0.5f); break;
            case 6: vPosition = coreVector2(-1.5f, 0.5f); break;
            case 7: vPosition = coreVector2(-1.5f,-0.5f); break;
            }
            vPosition *= 30.0f;
            vPosition += FIELD_POSITION;

            m_iItemLastType = (m_iItemLastType + Core::Rand->Uint(1u, 2u)) % 3u;

            switch(m_iItemLastType)
            {
            default: UNREACHABLE
            case 0: this->AddItem(new cSideItem     (Core::Rand->Bool() ? coreVector2(1.0f,0.0f) : coreVector2(0.0f,1.0f)), vPosition); break;
            case 1: this->AddItem(new cExplosionItem(),                                                                     vPosition); break;
            case 2: this->AddItem(new cSpeedItem    (),                                                                     vPosition); break;
            }

            m_fItemDelay = ITEM_DELAY;
        }
    }

    if((m_fTime <= GAME_TIME + GAME_COUNTDOWN) && (m_fTime > 0.0f))
    {
        for(coreUintW i = 0u; i < PLAYERS; ++i)
        {
            m_aPlayer[i].Move();

            for(coreUintW j = 0u; j < SIZE_TOTAL_EXT; ++j)
            {
                const coreVector2 vDiff = g_pField->GetTile(j)->GetPosition().xy() - m_aPlayer[i].GetPosition().xy();
                if((vDiff.x <=  PLAYER_RANGE) &&
                   (vDiff.x >= -PLAYER_RANGE) &&
                   (vDiff.y <=  PLAYER_RANGE) &&
                   (vDiff.y >= -PLAYER_RANGE))
                {
                    g_pField->TurnTile(j, m_aPlayer[i].GetColor3(), m_aPlayer[i].GetTileType());
                }
            }

            FOR_EACH(it, m_apItem)
            {
                if((*it)->GetState()) continue;

                coreVector3 vIntersection;
                if(Core::Manager::Object->TestCollision(*it, &m_aPlayer[i], &vIntersection))
                {
                    (*it)->ApplyEffect(&m_aPlayer[i]);
                }
            }
        }

        FOR_EACH_DYN(it, m_apItem)
        {
            if((*it)->GetState() == 2u)
            {
                SAFE_DELETE(*it)
                DYN_REMOVE(it, m_apItem)
            }
            else
            {
                (*it)->Move();
                DYN_KEEP(it, m_apItem)
            }
        }

        Core::Manager::Object->TestCollision(1, [](cPlayer* OUTPUT pPlayer1, cPlayer* OUTPUT pPlayer2, const coreVector3 vIntersection, const coreBool bFirstHit)
        {
            if(!bFirstHit) return;

            coreVector2 vDiff = (pPlayer1->GetPosition().xy() - pPlayer2->GetPosition().xy());
            if(vDiff.IsNull()) return;

            vDiff = vDiff.Normalized();

            const coreVector2 vVel1 = pPlayer1->GetVelocity();
            const coreVector2 vVel2 = pPlayer2->GetVelocity();

            pPlayer1->SetVelocity(coreVector2::Reflect(vVel1,  vDiff) + vVel2 * 0.5f +  vDiff * TIME);
            pPlayer2->SetVelocity(coreVector2::Reflect(vVel2, -vDiff) + vVel1 * 0.5f + -vDiff * TIME);
        });
    }

    m_Interface.Move();
}


// ****************************************************************
void cGame::AddItem(cItem* pItem, const coreVector2 vPosition)
{
    pItem->SetPosition(coreVector3(vPosition, 0.0f));
    m_apItem.push_back(pItem);
}


// ****************************************************************
void cGame::ClearItems()
{
    FOR_EACH(it, m_apItem)
        SAFE_DELETE(*it)

    m_apItem.clear();
}