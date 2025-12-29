/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Flip It (https://www.maus-games.at)   |//
//*-----------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "main.h"


// ****************************************************************
CPlayer::CPlayer()noexcept
: coreObject3D   ()
, m_iTileType    (0u)
, m_iControlType (0u)
, m_vVelocity    (coreVector2(0.0f,0.0f))
, m_fSpeed       (PLAYER_SPEED_SLOW)
, m_iSpeedCount  (0u)
{
    this->DefineModel  ("default_sphere.md3z");
    this->DefineTexture(0u, "default_white.webp");
    this->DefineProgram("object_program");

    this->SetSize(coreVector3(1.0f,1.0f,1.0f) * PLAYER_SIZE);

    this->ChangeType(1);
}


// ****************************************************************
void CPlayer::Render()
{
    this->coreObject3D::Render();
}


// ****************************************************************
void CPlayer::Move()
{
    const coreFloat fTime = g_pGame->GetTime();
    if((fTime < GAME_TIME) && (fTime > 0.0f))
    {
        coreVector2 vMove = coreVector2(0.0f,0.0f);

        if(m_iControlType == 0u)
        {
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(D), CORE_INPUT_HOLD)) vMove.x += 1.0f;
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(A), CORE_INPUT_HOLD)) vMove.x -= 1.0f;
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(W), CORE_INPUT_HOLD)) vMove.y += 1.0f;
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(S), CORE_INPUT_HOLD)) vMove.y -= 1.0f;

            vMove += Core::Input->GetJoystickStickL(0u);
        }
        else if(m_iControlType == 1u)
        {
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(RIGHT), CORE_INPUT_HOLD)) vMove.x += 1.0f;
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(LEFT),  CORE_INPUT_HOLD)) vMove.x -= 1.0f;
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(UP),    CORE_INPUT_HOLD)) vMove.y += 1.0f;
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(DOWN),  CORE_INPUT_HOLD)) vMove.y -= 1.0f;

            vMove += Core::Input->GetJoystickStickL(1u);
        }

        if(!vMove.IsNull()) vMove = vMove.Normalized();

        m_vVelocity += vMove * (m_fSpeed * PLAYER_ACCELERATION * TIME);
        if(!m_vVelocity.IsNull()) m_vVelocity *= coreMath::Friction(PLAYER_BRAKE, TIME);

        constexpr coreVector2 vFieldSizeDef = coreVector2(I_TO_F(SIZE_X     - 2u)*0.5f + 0.5f, I_TO_F(SIZE_Y     - 2u)*0.5f + 0.5f) * TILE_SIZE;
        constexpr coreVector2 vFieldSizeExt = coreVector2(I_TO_F(SIZE_X_EXT - 2u)*0.5f + 0.5f, I_TO_F(SIZE_Y_EXT - 2u)*0.5f + 0.5f) * TILE_SIZE;
        const     coreVector2 vFieldSize    = g_pField->GetExtended() ? vFieldSizeExt : vFieldSizeDef;

        coreVector2 vNewPos = this->GetPosition().xy() + m_vVelocity * TIME;

             if(vNewPos.x >  vFieldSize.x + FIELD_POSITION.x && m_vVelocity.x > 0.0f) {vNewPos.x =  vFieldSize.x + FIELD_POSITION.x; m_vVelocity.x = -ABS(m_vVelocity.x);}
        else if(vNewPos.x < -vFieldSize.x + FIELD_POSITION.x && m_vVelocity.x < 0.0f) {vNewPos.x = -vFieldSize.x + FIELD_POSITION.x; m_vVelocity.x =  ABS(m_vVelocity.x);}
             if(vNewPos.y >  vFieldSize.y + FIELD_POSITION.y && m_vVelocity.y > 0.0f) {vNewPos.y =  vFieldSize.y + FIELD_POSITION.y; m_vVelocity.y = -ABS(m_vVelocity.y);}
        else if(vNewPos.y < -vFieldSize.y + FIELD_POSITION.y && m_vVelocity.y < 0.0f) {vNewPos.y = -vFieldSize.y + FIELD_POSITION.y; m_vVelocity.y =  ABS(m_vVelocity.y);}

        this->SetPosition(coreVector3(vNewPos, 0.0f));
    }

    this->coreObject3D::Move();
}


// ****************************************************************
void CPlayer::IncreaseSpeed()
{
    if(!m_iSpeedCount) m_fSpeed = PLAYER_SPEED_FAST;
    m_iSpeedCount += 1u;
}


// ****************************************************************
void CPlayer::DecreaseSpeed()
{
    m_iSpeedCount -= 1u;
    if(!m_iSpeedCount) m_fSpeed = PLAYER_SPEED_SLOW;
}