/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Flip It (https://www.maus-games.at)   |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "main.h"

STATIC_MEMORY(cField, g_pField)
STATIC_MEMORY(cGame,  g_pGame)


// ****************************************************************
// init the application
void CoreApp::Init()
{
    Core::Graphics->SetCamera(CAMERA_POSITION, CAMERA_DIRECTION, CAMERA_ORIENTATION);
    Core::Graphics->SetView(Core::System->GetResolution(), DEG_TO_RAD(45.0f), 50.0f, 500.0f);

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