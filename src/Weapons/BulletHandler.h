#ifndef BULLETHANDLER_H
#define BULLETHANDLER_H

#include <vector>
#include "Bullet.h"
#include "Collider.h"
#include "Engine.h"
class Bullet;
class BulletHandler
{
    public:

        void AddPlayerBullet(Bullet* bullet);
        void AddEnemyBullet(Bullet* bullet);
        void UpdatePlayerBullet();
        void UpdateEnemyBullet();
        void DrawPlayerBullet();
        void DrawEnemyBullet();
        void Clear();
        const std::vector<Bullet*> GetEnemyBullets() { return m_EnemyBullets; }
        const std::vector<Bullet*> GetPlayerBullets() { return m_PlayerBullets; }
        static BulletHandler* GetInstance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new BulletHandler(); }

    private:
        BulletHandler();
        ~BulletHandler();
        static BulletHandler* s_Instance;
        std::vector<Bullet*> m_EnemyBullets;
        std::vector<Bullet*> m_PlayerBullets;
};

#endif // BULLETHANDLER_H
