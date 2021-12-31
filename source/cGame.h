/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Flip It (https://www.maus-games.at)   |//
//*-----------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _FLI_GUARD_GAME_H_
#define _FLI_GUARD_GAME_H_


// ****************************************************************
class cGame final
{
private:
    cPlayer m_aPlayer[PLAYERS];

    coreList<cItem*> m_apItem;
    coreFlow  m_fItemDelay;
    coreUint8 m_iItemLastPos;
    coreUint8 m_iItemLastType;

    cInterface m_Interface;

    coreFlow m_fTime;
    coreBool m_bStarted;


public:
    cGame()noexcept;
    ~cGame();

    DISABLE_COPY(cGame)

    void Render();
    void Move();

    void AddItem(cItem* pItem, const coreVector2 vPosition);
    void ClearItems();

    inline const coreFloat& GetTime()const {return m_fTime;}
};


#endif // _FLI_GUARD_GAME_H_