//////////////////////////////////////////////////////////////////////////////////
//*----------------------------------------------------------------------------*//
//| Flip It v1.0.0 (https://www.maus-games.at)                                 |//
//*----------------------------------------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics                                        |//
//|                                                                            |//
//| This software is provided 'as-is', without any express or implied          |//
//| warranty. In no event will the authors be held liable for any damages      |//
//| arising from the use of this software.                                     |//
//|                                                                            |//
//| Permission is granted to anyone to use this software for any purpose,      |//
//| including commercial applications, and to alter it and redistribute it     |//
//| freely, subject to the following restrictions:                             |//
//|                                                                            |//
//| 1. The origin of this software must not be misrepresented; you must not    |//
//|    claim that you wrote the original software. If you use this software    |//
//|    in a product, an acknowledgment in the product documentation would be   |//
//|    appreciated but is not required.                                        |//
//|                                                                            |//
//| 2. Altered source versions must be plainly marked as such, and must not be |//
//|    misrepresented as being the original software.                          |//
//|                                                                            |//
//| 3. This notice may not be removed or altered from any source distribution. |//
//*----------------------------------------------------------------------------*//
//////////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef _FLI_GUARD_MAIN_H_
#define _FLI_GUARD_MAIN_H_


// ****************************************************************
// engine headers
#include "Core.h"


// ****************************************************************
// general definitions
#define PLAYERS             (2u)

#define SIZE_X              (24u)
#define SIZE_Y              (20u)
#define SIZE_TOTAL          (SIZE_X * SIZE_Y)
#define SIZE_X_EXT          (48u)
#define SIZE_Y_EXT          (28u)
#define SIZE_TOTAL_EXT      (SIZE_X_EXT * SIZE_Y_EXT)

#define FIELD_POSITION      (coreVector2(0.0f,7.0f))

#define TILE_SIZE           (2.5f)

#define BAR_LENGTH          (0.65f)

#define PLAYER_SIZE         (2.5f)
#define PLAYER_RANGE        (2.5f)
#define PLAYER_SPEED_SLOW   (6.0f)
#define PLAYER_SPEED_FAST   (18.0f)
#define PLAYER_ACCELERATION (200.0f)
#define PLAYER_BRAKE        (16.0f)

#define ITEM_SIZE           (5.0f)
#define ITEM_DELAY          (5.0f)
#define ITEM_SPEED_TIME     (3.0f)
#define ITEM_SIDE_RANGE     (7.0f)
#define ITEM_EXPL_RANGE     (30.0f)

#define GAME_WAIT           (1.0f)
#define GAME_COUNTDOWN      (3.0f)
#define GAME_TIME           (50.0f)
#define GAME_DELAY          (2.0f)
#define GAME_EXTEND         (30.0f)

#define COLOR_PLAYER_1      (COLOR_YELLOW)
#define COLOR_PLAYER_2      (COLOR_BLUE)
#define COLOR_DEFAULT       (coreVector3(1.0f,1.0f,1.0f) * 0.9f)

#define CAMERA_POSITION     (coreVector3(0.0f, 0.0f, 110.0f))
#define CAMERA_DIRECTION    (coreVector3(0.0f, 0.0f,  -1.0f))
#define CAMERA_ORIENTATION  (coreVector3(0.0f, 1.0f,   0.0f))


// ****************************************************************
// game headers
#include "Field.h"
#include "Player.h"
#include "Item.h"
#include "Interface.h"
#include "Game.h"


// ****************************************************************
// global variables
extern CField* const g_pField;
extern CGame*  const g_pGame;


#endif // _FLI_GUARD_MAIN_H_