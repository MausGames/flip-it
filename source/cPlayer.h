/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Flip It (https://www.maus-games.at)   |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _FLI_GUARD_PLAYER_H_
#define _FLI_GUARD_PLAYER_H_


// ****************************************************************
class cPlayer final : public coreObject3D
{
private:
    coreUint8 m_iTileType;
    coreUint8 m_iControlType;

    coreVector2 m_vVelocity;
    coreFloat   m_fSpeed;
    coreUint8   m_iSpeedCount;


public:
    cPlayer()noexcept;

    DISABLE_COPY(cPlayer)

    void Render()final;
    void Move  ()final;

    void IncreaseSpeed();
    void DecreaseSpeed();

    inline void SetTileType   (const coreUint8   iType)     {m_iTileType    = iType;}
    inline void SetControlType(const coreUint8   iType)     {m_iControlType = iType;}
    inline void SetVelocity   (const coreVector2 vVelocity) {m_vVelocity    = vVelocity;}

    inline const coreUint8&   GetTileType   ()const {return m_iTileType;}
    inline const coreUint8&   GetControlType()const {return m_iControlType;}
    inline const coreVector2& GetVelocity   ()const {return m_vVelocity;}
};


#endif // _FLI_GUARD_PLAYER_H_