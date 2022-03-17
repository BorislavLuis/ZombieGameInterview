#ifndef ZOMBIEL2_H
#define ZOMBIEL2_H
#include "Collider.h"
#include "CollisionHandler.h"
#include "Vector2D.h"
#include "RigidBody.h"
#include "SpriteAnimation.h"
#include "Camera.h"
#include "Soldier.h"
#include "Health.h"
#include "GameObject.h"
#include "Play.h"
#include <math.h>
#include <stack>

#define PI 3.14159265
class ZombieL2 : public GameObject
{
    public:
        ZombieL2(Transform* tf,int path);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        inline Collider* GetCollider() { return m_Collider; }
        void ReciveDamage(int damage);
        virtual bool IsDead() { return m_IsDeath; }
        virtual GetObjectNumber() { return m_ObjNum;}

        virtual void HandlePatrolState();
        virtual void CreatePaths();

        virtual ~ZombieL2();
    private:
        void AnimationState();
        void ApplyForceX(float a,float b);
        void ApplyForceY(float a,float b);

        int m_ObjNum;
        int m_DyingTime;
        int m_NextAttackTime;

        int m_CurrentPath;
        int m_CurrentWaypoint;
        float EPSILON = 5.0f;

        double m_Angle;
        bool m_Attack;
        bool m_IsDeath;
        bool m_IsDying;
        Uint32 m_CurrentTicks;
        bool m_IsCalled;

        Collider* m_Collider;
        RigidBody* m_RigidBody;
        SpriteAnimation* m_Animation;
        Vector2D m_LastSafePosition;
        Vector2D m_LastCoord;
        Vector2D m_LastForPathCalc;
        Vector2D m_LastForBackTrackCalc;

        Health m_Health;
        std::string m_TextureIdle;

        std::vector<std::vector<Vector2D>> m_SPaths;
        std::stack<Vector2D> m_BackTrack;
        std::stack<Vector2D> m_ReturnToPathInit;
        enum STATES { PATROL , INATTACK };
        STATES m_CurrentState;
};

#endif // ZOMBIEL2_H
