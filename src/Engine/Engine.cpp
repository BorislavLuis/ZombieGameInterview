#include <iostream>
#include "Engine.h"
#include "TextureMgr.h"
#include "Transform.h"
#include "Soldier.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"
#include "StateMgr.h"
#include "GameState.h"
#include "Menu.h"
#include "Play.h"
#include "Pause.h"
#include "Button.h"
Engine* Engine::s_Instance = nullptr;
Soldier* player = nullptr;

bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)!= 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0 )
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }
    SDL_WindowFlags w_flags = (SDL_WindowFlags)(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_Window = SDL_CreateWindow("Zombie Mania",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,w_flags);
    if(m_Window == nullptr)
    {
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer == nullptr)
    {
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;
    }

    player = new Soldier(new Transform("KnifeIdleWoman",200,0,400,200));
    m_Player = player;
    SDL_Cursor* cursor;
    cursor = SDL_GetCursor();
    SDL_Surface* crosshair;
    crosshair = IMG_Load("assets/reticle2.png");

    cursor = SDL_CreateColorCursor(crosshair,10,10);
    SDL_SetCursor(cursor);
    SDL_ShowCursor(SDL_ENABLE);
    if(!MapParser::GetInstance()->Load())
    {
        std::cout << "Failed to load map" << std::endl;
        return false;
    }
    m_LevelMap = MapParser::GetInstance()->GetMaps("level1");
    StateMgr::GetInstance()->ChangeState(new Menu());
    //TextureMgr::GetInstance()->ParseTextures("assets/textures.tml");
    return m_IsRunning = true;
}

void Engine::Clean()
{
//    player->Clean();
//    zombie1->Clean();
//    zombie2->Clean();
//    delete player;
//    player = nullptr;
//    delete zombie1;
//    delete zombie2;
//
//    zombie1 = nullptr;
//    zombie2 = nullptr;

    TextureMgr::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_IsRunning = false;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    //StateMgr::GetInstance()->Update();
//    player->Update(dt);
//    zombie1->Update(dt);
//    zombie2->Update(dt);
//    m_LevelMap->Update();
//    Camera::GetInstance()->Update(dt);

}

void Engine::Render()
{

    SDL_SetRenderDrawColor(m_Renderer,152,251,152,255);
    SDL_RenderClear(m_Renderer);
    //TextureMgr::GetInstance()->Draw("Flor1",100,100,423,408);
    //StateMgr::GetInstance()->Render();
//    m_LevelMap->Render();
//    player->Draw();
//    zombie1->Draw();
//    zombie2->Draw();

    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
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
void Engine::RemoveGameObject(GameObject* obj)
{
    SDL_Log("%s will die",obj->GetTransform()->m_TextureID.c_str());
    //SDL_Log("%d",obj->GetObjectNumber());
    std::vector<GameObject*>::iterator itr;
    for(itr = m_Objects.begin();itr != m_Objects.end();itr++)
    {
        if(*itr == obj)
        {
            delete *itr;
            *itr = nullptr;
            itr = m_Objects.erase(itr);
            itr--;
        }
    }
}
