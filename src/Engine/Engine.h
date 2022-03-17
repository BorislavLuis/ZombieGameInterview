#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include "GameMap.h"
#include "GameObject.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
class Soldier;
class Engine
{
    public:
        static Engine* GetInstance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();}
        bool Init();
        void Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        void LoadGameObjects(const std::vector<GameObject*> objects) { m_Objects = objects; }
        void RemoveGameObject(GameObject* obj);
        const std::vector<GameObject*> GetObjects() { return m_Objects; }
        inline SDL_Renderer* GetRender(){return m_Renderer;}
        inline SDL_Window* GetMainWindow() {return m_Window;}
        inline bool IsRunning(){return m_IsRunning;}
        inline GameMap* GetMap() { return m_LevelMap;}

        inline void SetViewPort(SDL_Rect viewport) { m_ScreenViewPort = viewport;}
        inline SDL_Rect GetViewPort() { return m_ScreenViewPort; }
    private:
        Engine(){}

        bool m_IsRunning;
        static Engine* s_Instance;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        SDL_Rect m_ScreenViewPort;
        GameMap* m_LevelMap;
        Soldier* m_Player;
        std::vector<GameObject*> m_Objects;
//        std::vector<GameState*> m_States;

};

#endif // ENGINE_H
