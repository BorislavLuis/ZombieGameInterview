#include "Menu.h"
#include "Engine.h"

const std::string Menu::m_MenuID = "MENU";
extern Soldier* player;
bool Menu::m_PlayerTypeChosed = false;
bool Menu::Init()
{
    m_Ctxt = Engine::GetInstance()->GetRender();

    TextureMgr::GetInstance()->ParseTextures("assets/MenuTexture.tml");
    if(!TextureMgr::GetInstance()->Load("Background","assets/Background3.jpg"))
    {
        SDL_Log("%s","Cann't load background");
    }
    Button* start = new Button(100,100,StartGame,{"StartGame_N","StartGame_H","StartGame_P2"});
    Button* settings = new Button(100,170,Setting,{"Settings_N","Settings_H","Settings_P"});
    Button* resume = new Button(100,240,Resume,{"Resume_N","Resume_H","Resume_P"});
    Button* choseWoman = new Button(1200,100,ChosePlayerWoman,{"ChoseWoman_N","ChoseWoman_H","ChoseWoman_P"});
    Button* choseMan = new Button(1450,100,ChosePlayerMan,{"ChoseMan_N","ChoseMan_H","ChoseMan_P"});
    //Button* play = new Button(250,100,StartGame,{"Play_N","Play_H","Play_P"});
    //Button* pause = new Button(250,250,Stop,{"Pause_N","Pause_H","Pause_P"});
    Button* quit = new Button(100,310,Quit,{"Exit_N","Exit_H","Exit_P"});

    //Camera::GetInstance()->SetTarget(play->GetOrigin());

    m_GameObjects.push_back(start);
    m_GameObjects.push_back(settings);
    m_GameObjects.push_back(resume);
    m_GameObjects.push_back(choseWoman);
    m_GameObjects.push_back(choseMan);
    //m_GameObjects.push_back(play);
    //m_GameObjects.push_back(pause);
    m_GameObjects.push_back(quit);
    SDL_Log("%s","Init Menu");
    return true;
}

bool Menu::Exit()
{
//    m_GameObjects.clear();
//    TextureMgr::GetInstance()->Clean();
    SDL_Log("%s","Exit Menu");
    return true;
}

void Menu::Update()
{
    Events();
    float dt = Timer::GetInstance()->GetDeltaTime();
    Vector2D zeropoint;
    zeropoint.X = 0;
    zeropoint.Y = 0;
    Camera::GetInstance()->SetTarget(&zeropoint);
    for(auto object : m_GameObjects)
    {
        object->Update(0);
    }
    Camera::GetInstance()->Update(dt);
}

void Menu::Render()
{
    SDL_SetRenderDrawColor(m_Ctxt,152,251,152,255);
    SDL_RenderClear(m_Ctxt);
    Transform tff;
    tff.m_TextureID = "Background";
    TextureMgr::GetInstance()->QueryTexture("Background",&tff.m_Width,&tff.m_Height);
    TextureMgr::GetInstance()->Draw(&tff);
    switch (LevelMgr::GetInstance()->GetLevelNumber())
    {
        case 0: tff.m_TextureID = "LevelInitial"; break;
        case 1: tff.m_TextureID = "Level1Passed"; break;
        case 2: tff.m_TextureID = "Level2Passed"; break;
        case 3: tff.m_TextureID = "Level3Passed"; break;
        case 4: tff.m_TextureID = "Level4Passed"; break;
        case 5: tff.m_TextureID = "Level5Passed"; break;
        case 6: tff.m_TextureID = "Level6Passed"; break;
        case 7: tff.m_TextureID = "Level7Passed"; break;
        case 8: tff.m_TextureID = "Level8Passed"; break;
        case 9: tff.m_TextureID = "Level9Passed"; break;
        case 10: tff.m_TextureID = "Level10Passed"; break;

    }
    //tff.m_TextureID = "LevelInitial";
    tff.X = 1000;
    tff.Y = 400;
    TextureMgr::GetInstance()->QueryTexture("LevelInitial",&tff.m_Width,&tff.m_Height);
    TextureMgr::GetInstance()->Draw(&tff);
    for(auto object : m_GameObjects)
    {
        object->Draw();
    }
    SDL_RenderPresent(m_Ctxt);
}

void Menu::StartGame()
{
    if(m_PlayerTypeChosed)
    {
        StateMgr::GetInstance()->Update();
        StateMgr::GetInstance()->Render();
        StateMgr::GetInstance()->ChangeState(new Play());
        SDL_Log("%s","Start Game");
    }
    else
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Player type","Chose player type!",Engine::GetInstance()->GetMainWindow());
    }

}

void Menu::Setting()
{
    StateMgr::GetInstance()->Update();
    StateMgr::GetInstance()->Render();
    StateMgr::GetInstance()->ChangeState(new Settings());
    SDL_Log("%s","Settings");
}

void Menu::Editor()
{
    SDL_Log("%s","Editor");
}

void Menu::Quit()
{
    StateMgr::GetInstance()->Update();
    StateMgr::GetInstance()->Render();
    TextureMgr::GetInstance()->Clean();
    Engine::GetInstance()->Quit();
    SDL_Log("%s","Quit Game");
}
Menu::Menu()
{

}

Menu::~Menu()
{

    for(int i = 0;i < m_GameObjects.size();i++)
    {
        delete m_GameObjects[i];
        m_GameObjects[i] = nullptr;
    }
    m_GameObjects.clear();
}
void Menu::Stop()
{
    StateMgr::GetInstance()->Update();
    StateMgr::GetInstance()->Render();
    StateMgr::GetInstance()->PushState(new Pause());
    SDL_Log("%s","Pause");
}
void Menu::Resume()
{
    StateMgr::GetInstance()->Update();
    StateMgr::GetInstance()->Render();
    StateMgr::GetInstance()->PopState();
}
void Menu::Events()
{
    Input::GetInstance()->Listen();
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN))
    {
        StateMgr::GetInstance()->ChangeState(new Play());
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
    {
        StateMgr::GetInstance()->ChangeState(new Menu());
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_P))
    {
        StateMgr::GetInstance()->PushState(new Pause());
    }
}
void Menu::ChosePlayerWoman()
{
    std::string type = "Woman";
    m_PlayerTypeChosed = true;
    player->SetCharacterType(type);
}

void Menu::ChosePlayerMan()
{
    std::string type = "Man";
    m_PlayerTypeChosed = true;
    player->SetCharacterType(type);
}
