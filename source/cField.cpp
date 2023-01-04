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
cField::cField()noexcept
: m_TileList    (SIZE_TOTAL_EXT)
, m_afTurnTime  {}
, m_aiTurnColor {}
, m_aiTurnType  {}
, m_abTurnState {}
, m_bExtended   (false)
{
    m_TileList.DefineProgram("tile_inst_program");

    for(coreUintW i = 0u; i < SIZE_TOTAL_EXT; ++i)
    {
        m_aTile[i].DefineModel  (Core::Manager::Object->GetLowQuad());
        m_aTile[i].DefineTexture(0u, "tile.png");
        m_aTile[i].DefineProgram("tile_program");

        const coreIntW X = i % SIZE_X_EXT;
        const coreIntW Y = i / SIZE_X_EXT;
        const coreVector2 vPos = coreVector2((I_TO_F(X)+0.5f) - I_TO_F(SIZE_X_EXT)*0.5f, (I_TO_F(Y)+0.5f) - I_TO_F(SIZE_Y_EXT)*0.5f);

        m_aTile[i].SetPosition (coreVector3(vPos * TILE_SIZE + FIELD_POSITION, 0.0f));
        m_aTile[i].SetSize     (coreVector3(1.0f,1.0f,1.0f) * (TILE_SIZE + 0.001f));
        m_aTile[i].SetColor3   (COLOR_DEFAULT * 0.8f);
        m_aTile[i].SetTexOffset(coreVector2(0.0f,0.0f));
        m_aTile[i].SetTexSize  (coreVector2(0.01f,0.01f));

        m_TileList.BindObject(&m_aTile[i]);
    }

    std::memset(m_aiTurnType, 0xFF, sizeof(m_aiTurnType));
}


// ****************************************************************
void cField::Render()
{
    for(coreUintW i = 0u; i < SIZE_TOTAL_EXT; ++i)
    {
        m_aTile[i].SetEnabled(this->SkipExtendedTile(i) ? CORE_OBJECT_ENABLE_MOVE : CORE_OBJECT_ENABLE_ALL);
    }
    m_TileList.Render();
}


// ****************************************************************
void cField::Move()
{
    for(coreUintW i = 0u; i < SIZE_TOTAL_EXT; ++i)
    {
        if(this->SkipExtendedTile(i))
            continue;

        if(m_abTurnState[i])
        {
            m_afTurnTime[i].Update(1.0f);
            m_afTurnTime[i] = MIN1(m_afTurnTime[i]);

            const coreVector2 vDir = coreVector2::Direction(MAX0(m_afTurnTime[i]) * PI);

            m_aTile[i].SetDirection  (coreVector3(vDir, 0.0f));
            m_aTile[i].SetOrientation(coreVector3(-vDir.x*vDir.y, vDir.x*vDir.x, vDir.y));

            const coreBool bFlip = (coreVector3::Dot(Core::Graphics->GetCamPosition() - m_aTile[i].GetPosition(), m_aTile[i].GetOrientation()) >= 0.0f) && (m_aiTurnType[i] != 2u);

            m_aTile[i].SetSize(coreVector3(m_aTile[i].GetSize().x, ABS(m_aTile[i].GetSize().y) * (bFlip ? 1.0f : -1.0f), m_aTile[i].GetSize().z));

            if(!bFlip)
            {
                m_aTile[i].SetColor3(coreVector4::UnpackUnorm4x8(m_aiTurnColor[i]).xyz());

                if(m_aiTurnType[i] == 0u)
                {
                    m_aTile[i].SetTexSize  (coreVector2(0.5f,1.0f));
                    m_aTile[i].SetTexOffset(coreVector2(0.0f,0.0f));
                }
                else if(m_aiTurnType[i] == 1u)
                {
                    m_aTile[i].SetTexSize  (coreVector2(0.5f,1.0f));
                    m_aTile[i].SetTexOffset(coreVector2(0.5f,0.0f));
                }
            }

            if(m_afTurnTime[i] >= 1.0f)
            {
                m_afTurnTime [i] = 0.0f;
                m_abTurnState[i] = false;
            }
        }
    }

    m_TileList.MoveNormal();
}


// ****************************************************************
void cField::TurnTile(const coreUintW iIndex, const coreVector3 vNewColor, const coreUint8 iNewType, const coreFloat fDelay)
{
    ASSERT(iIndex < SIZE_TOTAL_EXT)

    if(this->SkipExtendedTile(iIndex))
        return;

    if(m_abTurnState[iIndex])
        return;

    m_afTurnTime [iIndex] = -fDelay;
    m_aiTurnColor[iIndex] = coreVector4(vNewColor * 0.8f, 0.0f).PackUnorm4x8();
    m_aiTurnType [iIndex] = iNewType;
    m_abTurnState[iIndex] = true;
}


// ****************************************************************
void cField::Extend()
{
    if(m_bExtended) return;
    m_bExtended = true;

    for(coreUintW i = 0u; i < SIZE_TOTAL_EXT; ++i)
    {
        if(cField::IsExtendedTile(i))
        {
            const coreFloat fDelay = (m_aTile[i].GetPosition().xy() - FIELD_POSITION * 0.5f).Length() * 0.02f - 0.6f;

            this->TurnTile(i, COLOR_DEFAULT, 2u, fDelay);
            m_aTile[i].SetSize(m_aTile[i].GetSize() * coreVector3(1.0f,-1.0f,1.0f));
        }
    }
}


// ****************************************************************
coreBool cField::SkipExtendedTile(const coreUintW iIndex)const
{
    ASSERT(iIndex < SIZE_TOTAL_EXT)

    return !m_bExtended && cField::IsExtendedTile(iIndex);
}


// ****************************************************************
coreBool cField::IsExtendedTile(const coreUintW iIndex)
{
    ASSERT(iIndex < SIZE_TOTAL_EXT)

    const coreIntW X = iIndex % SIZE_X_EXT;
    const coreIntW Y = iIndex / SIZE_X_EXT;

    return !(X >= ((SIZE_X_EXT - SIZE_X) / 2u) && X < ((SIZE_X_EXT - SIZE_X) / 2u + SIZE_X) &&
             Y >= ((SIZE_Y_EXT - SIZE_Y) / 2u) && Y < ((SIZE_Y_EXT - SIZE_Y) / 2u + SIZE_Y));
}


// ****************************************************************
coreUint32 cField::CalcCount(const coreUint8 iType)const
{
    coreUint32 iCount = 0u;

    for(coreUintW i = 0u; i < SIZE_TOTAL_EXT; ++i)
    {
        if(this->SkipExtendedTile(i))
            continue;

        if(m_aiTurnType[i] == iType)
            iCount += 1u;
    }

    return iCount;
}


// ****************************************************************
coreFloat cField::CalcPercent(const coreUint8 iType)const
{
    return I_TO_F(this->CalcCount(iType)) / I_TO_F(m_bExtended ? SIZE_TOTAL_EXT : SIZE_TOTAL);
}