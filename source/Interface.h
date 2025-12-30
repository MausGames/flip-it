/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Flip It (https://www.maus-games.at)   |//
//*-----------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _FLI_GUARD_INTERFACE_H_
#define _FLI_GUARD_INTERFACE_H_


// ****************************************************************
class CInterface final
{
private:
    coreObject2D m_Identifier[PLAYERS];
    coreObject2D m_Bar       [PLAYERS];

    coreLabel m_Title;
    coreLabel m_Time;
    coreLabel m_Countdown;


public:
    CInterface()noexcept;

    DISABLE_COPY(CInterface)

    void Render();
    void Move();

    void SetColor(const coreUintW iIndex, const coreVector3 vColor);
};


#endif // _FLI_GUARD_INTERFACE_H_