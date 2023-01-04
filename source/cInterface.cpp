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
cInterface::cInterface()noexcept
{
    for(coreUintW i = 0u; i < PLAYERS; ++i)
    {
        m_Identifier[i].DefineTexture(0u, "tile.png");
        m_Identifier[i].DefineProgram("default_2d_program");

        m_Identifier[i].SetSize   (coreVector2(0.1f,0.1f));
        m_Identifier[i].SetTexSize(coreVector2(0.5f,1.0f));
    }

    m_Identifier[0].SetPosition (coreVector2(-0.43f,-0.4f));
    m_Identifier[0].SetTexOffset(coreVector2(0.0f,0.0f));

    m_Identifier[1].SetPosition (coreVector2(0.43f,-0.4f));
    m_Identifier[1].SetTexOffset(coreVector2(0.5f,0.0f));

    for(coreUintW i = 0u; i < PLAYERS; ++i)
    {
        m_Bar[i].DefineTexture(0u, "default_white.png");
        m_Bar[i].DefineProgram("default_2d_program");

        m_Bar[i].SetPosition(coreVector2((BAR_LENGTH * 0.5f) + 0.003f, m_Identifier[0].GetPosition().y) * coreVector2(SIGN(m_Identifier[i].GetPosition().x), 1.0f));
        m_Bar[i].SetSize    (coreVector2(0.3f,0.07f));
    }

    m_Bar[0].SetAlignment(coreVector2( 1.0f,0.0f));
    m_Bar[1].SetAlignment(coreVector2(-1.0f,0.0f));

    m_Title.Construct  ("default.ttf", 200u, 2u);
    m_Title.SetPosition(coreVector2(0.0f,0.08f));
    m_Title.SetText    ("FLIP IT");

    m_Time.Construct  ("default.ttf", 40u, 2u);
    m_Time.SetPosition(coreVector2(0.0f,-0.4f));

    m_Countdown.Construct  ("default.ttf", 90u, 2u);
    m_Countdown.SetPosition(coreVector2(0.0f,0.08f));
}


// ****************************************************************
void cInterface::Render()
{
    for(coreUintW i = 0u; i < PLAYERS; ++i)
        m_Identifier[i].Render();

    for(coreUintW i = 0u; i < PLAYERS; ++i)
        m_Bar[i].Render();

    m_Time     .Render();
    m_Countdown.Render();
    m_Title    .Render();
}


// ****************************************************************
void cInterface::Move()
{
    for(coreUintW i = 0u; i < PLAYERS; ++i)
    {
        const coreFloat fPercent = g_pField->CalcPercent(i);

        m_Bar[i].SetSize(coreVector2(BAR_LENGTH * fPercent, m_Bar[i].GetSize().y));

        m_Identifier[i].Move();
        m_Bar       [i].Move();
    }

    const coreFloat fTitle     = MAX0(GAME_WAIT - (g_pGame->GetTime() - GAME_TIME - GAME_COUNTDOWN));
    const coreFloat fTime      = CEIL(MIN(g_pGame->GetTime(), GAME_TIME));
    const coreFloat fCountdown = CEIL(g_pGame->GetTime() - GAME_TIME);

         if(fCountdown >  3.0f) m_Countdown.SetText("");
    else if(fCountdown >  0.0f) m_Countdown.SetText(PRINT("%.0f", fCountdown));
    else if(fCountdown > -1.0f) m_Countdown.SetText("GO!");
    else if(fTime <= -GAME_DELAY)
    {
        coreUintW  iWinIndex = 0u;
        coreUint32 iWinCount = g_pField->CalcCount(0u);
        coreUint8  iSame     = 1u;

        for(coreUintW i = 1u; i < PLAYERS; ++i)
        {
            const coreUint32 fNewCount = g_pField->CalcCount(i);
            if(fNewCount > iWinCount)
            {
                iWinIndex = i;
                iWinCount = fNewCount;
            }
            else if(fNewCount == iWinCount)
            {
                iSame += 1u;
            }
        }

        if(iSame == PLAYERS) m_Countdown.SetText("DRAW!");
                        else m_Countdown.SetText(PRINT("PLAYER %zu WINS!", iWinIndex + 1u));

        m_Time.SetText(PRINT("%.0f%%", 100.0f * (I_TO_F(iWinCount) / I_TO_F(SIZE_TOTAL_EXT))));
    }
    else if(fTime <= 0.0f) m_Countdown.SetText("TIME UP!");
    else if(fTime <= 3.0f) m_Countdown.SetText(PRINT("%.0f", fTime));
    else                   m_Countdown.SetText("");

    if(fTime > -GAME_DELAY) m_Time.SetText(PRINT("%.0f", MAX0(fTime)));

    m_Title.SetDirection(coreVector2::Direction((fTitle * 4.0f - 0.05f) * PI));
    m_Title.SetPosition (coreVector2(m_Title.GetPosition().x, 0.08f + fTitle * 2.0f));

    m_Title    .Move();
    m_Time     .Move();
    m_Countdown.Move();
}


// ****************************************************************
void cInterface::SetColor(const coreUintW iIndex, const coreVector3 vColor)
{
    ASSERT(iIndex < PLAYERS)

    m_Identifier[iIndex].SetColor3(vColor);
    m_Bar       [iIndex].SetColor3(vColor);
}