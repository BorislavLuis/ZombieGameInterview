#include <iostream>
#include <SDL.h>
#include "Engine.h"
#include "Timer.h"
#include "StateMgr.h"
int main(int argv, char** args)
{
    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunning())
    {
        Engine::GetInstance()->Events();
        StateMgr::GetInstance()->Render();
        StateMgr::GetInstance()->Update();
        //SDL_Delay(10000);
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();


    return 0;
}
