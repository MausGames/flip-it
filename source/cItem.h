/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Flip It (https://www.maus-games.at)   |//
//*-----------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _FLI_GUARD_ITEM_H_
#define _FLI_GUARD_ITEM_H_


// ****************************************************************
class INTERFACE cItem : public coreObject3D
{
protected:
    coreUint8 m_iState;


public:
    cItem()noexcept;
    virtual ~cItem()override = default;

    ENABLE_COPY(cItem)

    void Render()final;
    void Move  ()final;

    virtual void ApplyEffect(cPlayer* OUTPUT pPlayer) {}
    virtual void MoveEffect ()                        {}

    inline const coreUint8& GetState()const {return m_iState;}
};


// ****************************************************************
class cSideItem final : public cItem
{
public:
    cSideItem(const coreVector2 vDir)noexcept;

    ENABLE_COPY(cSideItem)

    void ApplyEffect(cPlayer* OUTPUT pPlayer)final;
};


// ****************************************************************
class cExplosionItem final : public cItem
{
public:
    cExplosionItem()noexcept;

    ENABLE_COPY(cExplosionItem)

    void ApplyEffect(cPlayer* OUTPUT pPlayer)final;
};


// ****************************************************************
class cSpeedItem final : public cItem
{
protected:
    cPlayer* m_pPlayer;
    coreFlow m_fTime;


public:
    cSpeedItem()noexcept;

    ENABLE_COPY(cSpeedItem)

    void ApplyEffect(cPlayer* OUTPUT pPlayer)final;
    void MoveEffect ()final;
};


#endif // _FLI_GUARD_ITEM_H_