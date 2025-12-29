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
class INTERFACE IItem : public coreObject3D
{
protected:
    coreUint8 m_iState;


public:
    IItem()noexcept;
    virtual ~IItem()override = default;

    ENABLE_COPY(IItem)

    void Render()final;
    void Move  ()final;

    virtual void ApplyEffect(CPlayer* OUTPUT pPlayer) {}
    virtual void MoveEffect ()                        {}

    inline const coreUint8& GetState()const {return m_iState;}
};


// ****************************************************************
class CSideItem final : public IItem
{
public:
    CSideItem(const coreVector2 vDir)noexcept;

    ENABLE_COPY(CSideItem)

    void ApplyEffect(CPlayer* OUTPUT pPlayer)final;
};


// ****************************************************************
class CExplosionItem final : public IItem
{
public:
    CExplosionItem()noexcept;

    ENABLE_COPY(CExplosionItem)

    void ApplyEffect(CPlayer* OUTPUT pPlayer)final;
};


// ****************************************************************
class CSpeedItem final : public IItem
{
protected:
    CPlayer* m_pPlayer;
    coreFlow m_fTime;


public:
    CSpeedItem()noexcept;

    ENABLE_COPY(CSpeedItem)

    void ApplyEffect(CPlayer* OUTPUT pPlayer)final;
    void MoveEffect ()final;
};


#endif // _FLI_GUARD_ITEM_H_