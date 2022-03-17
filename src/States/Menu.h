#ifndef MENU_H
#define MENU_H

#include "GameState.h"
#include "StateMgr.h"
#include "GameObject.h"
#include "Button.h"
#include "Play.h"
#include "Pause.h"
#include "Settings.h"
#include <SDL.h>
#include <string>
#include <vector>

class Menu : public GameState
{
    public:
        Menu();
        virtual bool Init();
        virtual bool Exit();

        virtual void Update();
        virtual void Render();
        virtual ~Menu();
        virtual void Events();
        virtual std::string GetStateID() const { return m_MenuID; }


    private:

        static void StartGame();
        static void Resume();
        static void Stop();
        static void Setting();
        static void Editor();
        static void ChosePlayerWoman();
        static void ChosePlayerMan();
        static void Quit();
        static const std::string m_MenuID;
        static bool m_PlayerTypeChosed;
        std::vector<GameObject* > m_GameObjects;

};

#endif // MENU_H
