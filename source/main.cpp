/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Flip It (https://www.maus-games.at)   |//
//*-----------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "main.h"

STATIC_MEMORY(CField, g_pField)
STATIC_MEMORY(CGame,  g_pGame)


// ****************************************************************
// init the application
void CoreApp::Init()
{
    Core::Graphics->SetCamera(CAMERA_POSITION, CAMERA_DIRECTION, CAMERA_ORIENTATION);
    Core::Graphics->SetView(Core::System->GetResolution(), DEG_TO_RAD(45.0f), 50.0f, 500.0f, 0.0f);

    Core::System->SetWindowAll(Core::System->GetDisplayIndex(), coreVector2(1100.0f,800.0f), CORE_SYSTEM_MODE_WINDOWED);

    STATIC_NEW(g_pField)
    STATIC_NEW(g_pGame)
}


// ****************************************************************
// exit the application
void CoreApp::Exit()
{
    STATIC_DELETE(g_pGame)
    STATIC_DELETE(g_pField)
}


// ****************************************************************
// render the application
void CoreApp::Render()
{
    g_pField->Render();
    g_pGame ->Render();
}


// ****************************************************************
// move the application
void CoreApp::Move()
{
    if(Core::System->GetWinSizeChanged())
    {
        Core::Reshape();
    }

    if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(SPACE), CORE_INPUT_PRESS))
    {
        STATIC_DELETE(g_pGame)
        STATIC_DELETE(g_pField)

        STATIC_NEW(g_pField)
        STATIC_NEW(g_pGame)
    }

    g_pField->Move();
    g_pGame ->Move();
}