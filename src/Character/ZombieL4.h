#ifndef ZOMBIEL4_H
#define ZOMBIEL4_H
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
#include <math.h>

#define PI 3.14159265
class ZombieL4 : public GameObject
{
    public:
        ZombieL4(Transform* tf,int path);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        inline Collider* GetCollider() { return m_Collider; }
        void ReciveDamage(int damage);
        virtual bool IsDead() { return m_IsDeath; }
        virtual GetObjectNumber() { return m_ObjNum;}
        virtual void ParseColliderCoord(std::string source);

        virtual void HandlePatrolState();
        virtual void CreatePaths();

        virtual ~ZombieL4();
        Collider m_ColliderBullet;
    private:
        void AnimationState();
        void ApplyForceX(float a,float b);
        void ApplyForceY(float a,float b);

        int m_ObjNum;
        int m_DyingTime;
        int m_NextAttack1Time;
        int m_NextAttack2Time;
        bool m_FrameForAttac2;

        int m_CurrentPath;
        int m_CurrentWaypoint;
        float EPSILON = 5.0f;

        double m_Angle;
        bool m_Attack1;
        bool m_Attack2;
        bool m_IsDeath;
        bool m_IsDying;
        Uint32 m_CurrentTicks;
        bool m_IsCalled;
        bool m_FrameForAttack2;

        Collider* m_Collider;
        RigidBody* m_RigidBody;
        SpriteAnimation* m_Animation;
        SeqAnimation* m_SeqAnimation;


        Vector2D m_LastSafePosition;
        Vector2D m_LastCoord;
        Vector2D m_LastForPathCalc;
        Vector2D m_LastForBackTrackCalc;

        Health m_Health;
        std::string m_TextureIdle;
        //static std::vector<Collider> m_Colliders;
        std::vector<std::vector<Vector2D>> m_SPaths;
        std::stack<Vector2D> m_BackTrack;
        std::stack<Vector2D> m_ReturnToPathInit;
        enum STATES { PATROL , INATTACK };
        STATES m_CurrentState;
};

#endif // ZOMBIEL4_H
