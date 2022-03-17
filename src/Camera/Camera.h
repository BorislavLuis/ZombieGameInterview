#ifndef CAMERA_H
#define CAMERA_H

#include "Engine.h"
#include "Vector2D.h"
#include "MapParser.h"
#include "LevelMgr.h"
#include <SDL.h>
class Camera
{
    public:

        void Update(float dt);
        inline static Camera* GetInstance() {return s_Instance = (s_Instance != nullptr)? s_Instance : new Camera();}
        inline SDL_Rect GetViewPort() { return m_ViewPort;}
        inline Vector2D GetPosition() { return m_Position;}
        inline void SetTarget(Vector2D* target) { m_Target = target; }
        bool IsInViewPort(Transform* tf);


    private:
        Camera(){m_ViewPort = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};}
        Vector2D* m_Target;
        Vector2D m_Position;
        SDL_Rect m_ViewPort;
        static Camera* s_Instance;

};

#endif // CAMERA_H
