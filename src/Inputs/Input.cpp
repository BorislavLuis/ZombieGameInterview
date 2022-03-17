#include "Input.h"
#include "Engine.h"

Input* Input::s_Instance = nullptr;

Input::Input()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
    m_MouseButtonStates = {false,false,false};
}

void Input::Listen()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_WINDOWEVENT: WindowEvent(event); break;
            case SDL_QUIT: Engine::GetInstance()->Quit(); break;
            case SDL_MOUSEBUTTONDOWN: MouseButtonDown(event); break;
            case SDL_MOUSEBUTTONUP: MouseButtonUp(event); break;
            case SDL_MOUSEMOTION: MouseMotion(event); break;
            case SDL_KEYDOWN: KeyDown(); break;
            case SDL_KEYUP: KeyUp(); break;

        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    if(m_KeyStates[key] == 1)
    {
        return true;
    }
    return false;
}

bool Input::GetKeyUp(SDL_Scancode key)
{
    //m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyUp()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::MouseMotion(SDL_Event event)
{
    m_MouseLastPosition = m_MousePosition;
    m_MousePosition.X = event.motion.x;
    m_MousePosition.Y = event.motion.y;
}

void Input::MouseButtonUp(SDL_Event event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        m_MouseButtonStates[LEFTB] = false;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_MouseButtonStates[MIDDLEB] = false;
    }
    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        m_MouseButtonStates[RIGHTB] = false;
    }
}

void Input::MouseButtonDown(SDL_Event event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        m_MouseButtonStates[LEFTB] = true;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_MouseButtonStates[MIDDLEB] = true;
    }
    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        m_MouseButtonStates[RIGHTB] = true;
    }
}

void Input::WindowEvent(SDL_Event event)
{
    if(event.window.event == SDL_WINDOWEVENT_RESIZED)
    {
        const SDL_Rect viewport = { 0, 0, event.window.data1 , event.window.data2 };
        Engine::GetInstance()->SetViewPort(viewport);
        //Camera::GetInstance()->SetViewPort(viewport);
    }
}


