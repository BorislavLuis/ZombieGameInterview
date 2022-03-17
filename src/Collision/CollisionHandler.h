#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <SDL.h>
#include "TileLayer.h"
#include "GameMap.h"
#include "GameObject.h"
#include "Soldier.h"
#include "Bullet.h"
#include "Mathematics.h"
#include <vector>

class Soldier;
class GameObject;
class Bullet;
class CollisionHandler
{
    public:

        bool CheckPlayerEnemyBulletCollision(Soldier* soldier,Bullet* bull);
        bool CheckEnemyAttackOnPlayer(Soldier* player,const std::vector<GameObject*>& enemies);
        bool CheckPlayerEnemyCollision(Soldier* soldier,const std::vector<GameObject*>& enemies);
        bool CheckEnemyPlayerBulletCollision();
        bool CheckEnemyToEnemyCollision(GameObject* enemy,const std::vector<GameObject*>& enemies);
        bool CheckEnemyToEnemyCollision(GameObject* enemy);
        bool CheckCollision(SDL_Rect a,SDL_Rect b);
        bool CheckBoxCircleCollision(Circle a,SDL_Rect b);
        bool CheckCirclesCollision(Circle a,Circle b);
        bool CheckEnemyHitByPlayerBat(SDL_Rect& bat);
        bool MapCollision(SDL_Rect a);
        bool CheckCollisionBySAT(Polygon& r1,Polygon& r2);
        bool CheckAproximation(SDL_Rect rect1,SDL_Rect rect2);
        bool IsOutsideScreen(SDL_Rect rect1);

        void SetCollisionLayers();
        void ResolveCollision(GameObject* a,GameObject* b);

        inline static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr)? s_Instance : new CollisionHandler();}

    private:
        CollisionHandler();
        TileMap m_CollisionTilemap1;
        TileMap m_CollisionTilemap2;
        TileLayer* m_CollisionLayer1;
        TileLayer* m_CollisionLayer2;
        static CollisionHandler* s_Instance;
};

#endif // COLLISIONHANDLER_H
