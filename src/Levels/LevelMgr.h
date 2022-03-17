#ifndef LEVELMGR_H
#define LEVELMGR_H

#include "GameMap.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "ZombieL1.h"
#include "ZombieL2.h"
#include "ZombieL3.h"
#include "ZombieL4.h"
#include "ZombieL5.h"
#include "Soldier.h"
#include <sstream>
#include <fstream>

#define LEVELNUMBERS 10
#define ENEMIESTYPES

class LevelMgr
{
    public:

        bool LevelPassed();
        GameMap* LoadNextLevel();
        std::vector<GameObject*> LoadEnemies(Soldier* player);
        void LoadItems(Soldier* player);
        std::string GetCurrentLevel();
        static int GetLevelNumber();
        //std::vector<GameObject*> GetEnemy(){return m_CurrentLevelEnemies;}
        static LevelMgr* GetInstance() { return s_Instance = (s_Instance != nullptr)? s_Instance : new LevelMgr(); }
        static GameMap* GetCurrentMap() { return m_CurrentMap;}

    private:
        LevelMgr(){};
        void Clean();
        virtual ~LevelMgr() { if (s_Instance != nullptr) delete s_Instance;}
        static LevelMgr* s_Instance;
        static int m_CurrentLevel;
        static bool m_PassedLevels[LEVELNUMBERS];
        static GameMap* m_CurrentMap;
        std::vector<GameObject*> m_CurrentLevelEnemies;
        //SpawnerFor<Zombie> m_ObjectSpawner;

};


#endif // LEVELMGR_H
