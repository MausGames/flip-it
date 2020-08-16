/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Flip It (https://www.maus-games.at)   |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _FLI_GUARD_FIELD_H_
#define _FLI_GUARD_FIELD_H_


// ****************************************************************
class cField final : public coreObject3D
{
private:
    coreBatchList m_TileList;
    coreObject3D  m_aTile[SIZE_TOTAL_EXT];

    coreFlow   m_afTurnTime [SIZE_TOTAL_EXT];
    coreUint32 m_aiTurnColor[SIZE_TOTAL_EXT];
    coreUint8  m_aiTurnType [SIZE_TOTAL_EXT];
    coreBool   m_abTurnState[SIZE_TOTAL_EXT];

    coreBool m_bExtended;


public:
    cField()noexcept;

    DISABLE_COPY(cField)

    void Render()final;
    void Move  ()final;

    void TurnTile(const coreUintW iIndex, const coreVector3& vNewColor, const coreUint8 iNewType, const coreFloat fDelay = 0.0f);

    void Extend();
    coreBool        SkipExtendedTile(const coreUintW iIndex)const;
    static coreBool IsExtendedTile  (const coreUintW iIndex);

    coreUint32 CalcCount  (const coreUint8 iType)const;
    coreFloat  CalcPercent(const coreUint8 iType)const;

    inline coreObject3D*   GetTile    (const coreUintW iIndex) {ASSERT(iIndex < SIZE_TOTAL_EXT) return &m_aTile[iIndex];}
    inline const coreBool& GetExtended()const                  {return m_bExtended;}
};


#endif // _FLI_GUARD_FIELD_H_