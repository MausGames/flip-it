/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Flip It (https://www.maus-games.at)   |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _FLI_GUARD_INTERFACE_H_
#define _FLI_GUARD_INTERFACE_H_


// ****************************************************************
class cInterface final
{
private:
    coreObject2D m_Identifier[PLAYERS];
    coreObject2D m_Bar       [PLAYERS];

    coreLabel m_Title;
    coreLabel m_Time;
    coreLabel m_Countdown;


public:
    cInterface()noexcept;

    DISABLE_COPY(cInterface)

    void Render();
    void Move();

    void SetColor(const coreUintW iIndex, const coreVector3& vColor);
};


#endif // _FLI_GUARD_INTERFACE_H_