#ifndef ZOMBIEL3_H
#define ZOMBIEL3_H

#include "Collider.h"
#include "CollisionHandler.h"
#include "Vector2D.h"
#include "RigidBody.h"
#include "SpriteAnimation.h"
#include "SeqAnimation.h"
#include "Camera.h"
#include "Soldier.h"
#include "Health.h"
#include "GameObject.h"
#include "Play.h"
#include "Puddle.h"
#include "Snot.h"

#include <math.h>
#include <stack>

#define PI 3.14159265
class ZombieL3 : public GameObject
{
    public:
        ZombieL3(Transform* tf,int path);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        inline Collider* GetCollider() { return m_Collider; }
        void ReciveDamage(int damage);
        virtual bool IsDead() { return m_IsDeath; }
        virtual GetObjectNumber() { return m_ObjNum;}

        virtual void HandlePatrolState();
        virtual void CreatePaths();

        virtual ~ZombieL3();
        static std::vector<Puddle*> GetPuddles() { return m_Puddles;}
        Collider m_ColliderBullet;
    private:
        void AnimationState();
        void ApplyForceX(float a,float b);
        void ApplyForceY(float a,float b);
        void SetState();

        int m_ObjNum;
        int m_DyingTime;
        int m_NextAttack1Time;
        int m_NextAttack2Time;
        int m_NextAttack3Time;

        int m_CurrentPath;
        int m_CurrentWaypoint;
        float EPSILON = 5.0f;

        double m_Angle;
        bool m_Attack1;
        bool m_Attack2;
        bool m_Attack3;
        bool m_IsDeath;
        bool m_IsDying;
        Uint32 m_CurrentTicks;
        bool m_IsCalled;

        bool m_FrameForAttack3; /// EXPERIMENT
        bool m_FrameForAttack2;

        Collider* m_Collider;
        RigidBody* m_RigidBody;
        SpriteAnimation* m_Animation;
        SeqAnimation* m_SeqAnimation;

        Collider m_ColliderMug;

        Vector2D m_LastSafePosition;
        Vector2D m_LastCoord;
        Vector2D m_LastForPathCalc;
        Vector2D m_LastForBackTrackCalc;

        Health m_Health;
        std::string m_TextureIdle;
        std::vector<std::vector<Vector2D>> m_SPaths;
        std::vector<Snot*> m_Snots;
        static std::vector<Puddle*> m_Puddles;

        std::stack<Vector2D> m_BackTrack;
        std::stack<Vector2D> m_ReturnToPathInit;

        enum STATES { IDLE, WALK , ATTACK1 , ATTACK2 , ATTACK3, DEAD };
        STATES m_CurrentState;
};
#endif // ZOMBIEL3_H
