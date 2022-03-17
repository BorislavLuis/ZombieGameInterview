#ifndef PLAY_H
#define PLAY_H

#include <iostream>
#include "StateMgr.h"
#include "Menu.h"
#include "Pause.h"
#include "GameMap.h"
#include "GameObject.h"
#include "GameState.h"
#include "Soldier.h"
#include "Timer.h"
#include "Input.h"
#include "Camera.h"
#include "MapParser.h"
#include "TileLayer.h"
#include "ObjectFactory.h"
#include "TextureMgr.h"
#include "CollisionHandler.h"


class Play : public GameState
{
    public:
        Play();

        virtual bool Init();
        virtual bool Exit();

        virtual void Update();
        virtual void Render();
        virtual void Events();

        //inline GameMap* GetMap() { return m_LevelMap; }
        virtual std::string GetStateID() const { return m_PlayID; }

        virtual ~Play();

    private:
        static void OpenMenu();
        static void PauseGame();
        static const std::string m_PlayID;
        void ClearGameObjects();
        bool m_EditMode;
        bool m_NextLevel;
        GameMap* m_LevelMap;
        std::vector<GameObject*> m_GameObjects;

};

#endif // PLAY_H
