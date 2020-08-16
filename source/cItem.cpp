/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Flip It (https://www.maus-games.at)   |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "main.h"


// ****************************************************************
cItem::cItem()noexcept
: m_iState (0u)
{
    this->DefineModel  ("default_cube.md3");
    this->DefineTexture(0u, "item.png");
    this->DefineProgram("object_program");

    this->SetSize   (coreVector3(1.0f,1.0f,1.0f) * ITEM_SIZE);
    this->SetTexSize(coreVector2(0.5f,0.5f));
}


// ****************************************************************
void cItem::Render()
{
    this->coreObject3D::Render();
}


// ****************************************************************
void cItem::Move()
{
    this->MoveEffect();
    this->coreObject3D::Move();
}


// ****************************************************************
cSideItem::cSideItem(const coreVector2& vDir)noexcept
{
    this->SetDirection(coreVector3(vDir, 0.0f));
    this->SetColor3   (COLOR_ORANGE * 0.9f);
    this->SetTexOffset(coreVector2(0.5f,0.0f));
}


// ****************************************************************
void cSideItem::ApplyEffect(cPlayer* OUTPUT pPlayer)
{
    const coreVector2 vArea = this->GetDirection().xy() * 1000.0f + this->GetDirection().yx() * ITEM_SIDE_RANGE;

    for(coreUintW i = 0u; i < SIZE_TOTAL_EXT; ++i)
    {
        const coreVector2 vDiff = this->GetPosition().xy() - g_pField->GetTile(i)->GetPosition().xy();

        if(ABS(vDiff.x) < vArea.x &&
           ABS(vDiff.y) < vArea.y)
        {
            const coreFloat fDist = vDiff.Length();
            const coreFloat fDelay = fDist * 0.02f;

            g_pField->TurnTile(i, pPlayer->GetColor3(), pPlayer->GetTileType(), fDelay);
        }
    }

    m_iState = 2u;
}


// ****************************************************************
cExplosionItem::cExplosionItem()noexcept
{
    this->SetColor3   (COLOR_RED * 0.9f);
    this->SetTexOffset(coreVector2(0.0f,0.0f));
}


// ****************************************************************
void cExplosionItem::ApplyEffect(cPlayer* OUTPUT pPlayer)
{
    for(coreUintW i = 0u; i < SIZE_TOTAL_EXT; ++i)
    {
        const coreFloat fDist = (this->GetPosition().xy() - g_pField->GetTile(i)->GetPosition().xy()).Length();

        if(fDist < ITEM_EXPL_RANGE)
        {
            const coreFloat fDelay = fDist * 0.02f;

            g_pField->TurnTile(i, pPlayer->GetColor3(), pPlayer->GetTileType(), fDelay);
        }
    }

    m_iState = 2u;
}


// ****************************************************************
cSpeedItem::cSpeedItem()noexcept
: m_pPlayer (NULL)
, m_fTime   (0.0f)
{
    this->SetColor3   (COLOR_PURPLE * 0.9f);
    this->SetTexOffset(coreVector2(0.0f,0.5f));
}


// ****************************************************************
void cSpeedItem::MoveEffect()
{
    if(m_iState)
    {
        m_fTime.Update(1.0f);

        if(m_fTime >= ITEM_SPEED_TIME)
        {
            m_pPlayer->DecreaseSpeed();
            m_iState = 2u;
        }
    }
}


// ****************************************************************
void cSpeedItem::ApplyEffect(cPlayer* OUTPUT pPlayer)
{
    this->SetEnabled(CORE_OBJECT_ENABLE_MOVE);

    m_iState = 1u;

    m_pPlayer = pPlayer;
    m_pPlayer->IncreaseSpeed();
}