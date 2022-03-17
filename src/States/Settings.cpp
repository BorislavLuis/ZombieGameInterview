#include "Settings.h"
#include "Engine.h"

const std::string Settings::m_SettingsID = "SETTINGS";
Settings::Settings()
{
    m_Ctxt = Engine::GetInstance()->GetRender();
}

bool Settings::Init()
{
    m_BackToMainMenu = new Button(850,925,MainMenu,{"Resume_N","Resume_H","Resume_P"});
    m_Ctxt = Engine::GetInstance()->GetRender();
    TextureMgr::GetInstance()->Load("Key","assets/Buttons/Key.png");
    if(!TextureMgr::GetInstance()->Load("SettingsBackground","assets/SettingsBackground4.jpg"))
    {
        SDL_Log("%s","Cann't load background");
    }
    SDL_Log("%s","Init Settings");
}

bool Settings::Exit()
{

}

void Settings::Update()
{
    m_BackToMainMenu->Update(0.5);
    float dt = Timer::GetInstance()->GetDeltaTime();
    Vector2D zeropoint;
    zeropoint.X = 0;
    zeropoint.Y = 0;
    Camera::GetInstance()->SetTarget(&zeropoint);
    Camera::GetInstance()->Update(dt);
}

void Settings::Render()
{

    SDL_SetRenderDrawColor(m_Ctxt,152,251,152,255);
    SDL_RenderClear(m_Ctxt);
    Transform tf;
    SDL_Log("Render");
    tf.m_TextureID = "SettingsBackground";
    TextureMgr::GetInstance()->QueryTexture("SettingsBackground",&tf.m_Width,&tf.m_Height);
    TextureMgr::GetInstance()->Draw(&tf);
    SDL_Rect rect = {200,200,400,100};
    m_BackToMainMenu->Draw();
    SDL_SetTextInputRect(&rect);
    SDL_RenderDrawRect(m_Ctxt,&rect);
    SDL_RenderPresent(m_Ctxt);
}

void Settings::Events()
{

}
void Settings::MainMenu()
{
    StateMgr::GetInstance()->Update();
    StateMgr::GetInstance()->Render();
    StateMgr::GetInstance()->ChangeState(new Menu());
    SDL_Log("%s","Settings");
}

Settings::~Settings()
{

}
