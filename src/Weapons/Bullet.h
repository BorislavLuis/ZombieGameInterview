#ifndef BULLET_H
#define BULLET_H
#include "Vector2D.h"
#include "Transform.h"
#include "TextureMgr.h"
#include "Engine.h"
#include "Collider.h"
#include "CollisionHandler.h"
#include <string>

enum BulletState  { INPLAY = 0,EXPLODED = 1};

class Bullet
{
    public:
        Bullet(Vector2D* pos,Vector2D vel,Collider collider,std::vector<std::string> type);
        void Draw();
        void Move(float dt);
        void Explode();
        void SetCoordinate(float x,float y,double angle);

        bool IsOutsideScreen();
        bool CheckMapCollision();
        bool CheckPlayerEnemyBulletCollision();
        bool CheckEnemyPlayerBulletCollision();

        inline Collider GetCollider() { return m_Collider; }
        virtual ~Bullet() {}


    private:

        Vector2D m_Vel;
        Collider m_Collider;
        Transform m_Transform;
        std::vector<std::string> m_TextureID;
        bool m_Exploded;
};

#endif // BULLET_H
