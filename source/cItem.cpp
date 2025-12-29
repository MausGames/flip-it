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
IItem::IItem()noexcept
: m_iState (0u)
{
    this->DefineModel  ("cube.md3z");
    this->DefineTexture(0u, "item.webp");
    this->DefineProgram("object_program");

    this->SetSize   (coreVector3(1.0f,1.0f,1.0f) * ITEM_SIZE);
    this->SetTexSize(coreVector2(0.5f,0.5f));
}


// ****************************************************************
void IItem::Render()
{
    this->coreObject3D::Render();
}


// ****************************************************************
void IItem::Move()
{
    this->MoveEffect();
    this->coreObject3D::Move();
}


// ****************************************************************
CSideItem::CSideItem(const coreVector2 vDir)noexcept
{
    this->SetDirection(coreVector3(vDir, 0.0f));
    this->SetColor3   (COLOR_ORANGE * 0.9f);
    this->SetTexOffset(coreVector2(0.5f,0.0f));
}


// ****************************************************************
void CSideItem::ApplyEffect(CPlayer* OUTPUT pPlayer)
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
CExplosionItem::CExplosionItem()noexcept
{
    this->SetColor3   (COLOR_RED * 0.9f);
    this->SetTexOffset(coreVector2(0.0f,0.0f));
}


// ****************************************************************
void CExplosionItem::ApplyEffect(CPlayer* OUTPUT pPlayer)
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
CSpeedItem::CSpeedItem()noexcept
: m_pPlayer (NULL)
, m_fTime   (0.0f)
{
    this->SetColor3   (COLOR_PURPLE * 0.9f);
    this->SetTexOffset(coreVector2(0.0f,0.5f));
}


// ****************************************************************
void CSpeedItem::MoveEffect()
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
void CSpeedItem::ApplyEffect(CPlayer* OUTPUT pPlayer)
{
    this->SetEnabled(CORE_OBJECT_ENABLE_MOVE);

    m_iState = 1u;

    m_pPlayer = pPlayer;
    m_pPlayer->IncreaseSpeed();
}