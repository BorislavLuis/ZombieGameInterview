#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <vector>
#include "Vector2D.h"

enum MouseButtons {LEFTB,MIDDLEB,RIGHTB};

class Input
{
    public:
        static Input* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance: new Input();
        }

        void Listen();
        bool GetKeyDown(SDL_Scancode key);
        bool GetKeyUp(SDL_Scancode key);
        inline Vector2D GetMousePosition() { return m_MousePosition; }
        inline Vector2D GetMouseLastPosition() { return m_MouseLastPosition; }
        inline bool GetMouseButtonDown(MouseButtons button) { return m_MouseButtonStates[button];}

    private:
        Input();
        void KeyUp();
        void KeyDown();
        void WindowEvent(SDL_Event event);

        void MouseMotion(SDL_Event event);
        void MouseButtonUp(SDL_Event event);
        void MouseButtonDown(SDL_Event event);

        const Uint8* m_KeyStates;
        static Input* s_Instance;
        Vector2D m_MousePosition;
        Vector2D m_MouseLastPosition;
        std::vector<bool> m_MouseButtonStates;

};

#endif // INPUT_H
