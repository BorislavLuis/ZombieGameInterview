#ifndef ZOMBIEL5_H
#define ZOMBIEL5_H
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
#include "Claw.h"
#include "Arm.h"
#include <math.h>

#define PI 3.14159265
class ZombieL5 : public GameObject
{
    public:
        ZombieL5(Transform* tf,int path);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        inline Collider* GetCollider() { return m_Collider; }
        void ReciveDamage(int damage);
        virtual bool IsDead() { return m_IsDeath; }
        virtual GetObjectNumber() { return m_ObjNum;}

        virtual void HandlePatrolState();
        virtual void CreatePaths();

        virtual ~ZombieL5();
    private:
        void AnimationState();
        void ApplyForceX(float a,float b);
        void ApplyForceY(float a,float b);
        void CalculateFlameCollider();

        int m_ObjNum;
        int m_DyingTime;
        int m_NextAttack1Time;
        int m_NextAttack2Time;
        int m_NextAttack3Time;
        int m_NextAttack4Time;

        int m_CurrentPath;
        int m_CurrentWaypoint;
        float EPSILON = 5.0f;

        double m_Angle;
        bool m_Attack1;
        bool m_Attack2;
        bool m_Attack3;
        bool m_Attack4;
        bool m_FrameForAttack2;
        bool m_FrameForAttack3;
        bool m_FrameForAttack4;
        bool m_DamageDeledAttack2;
        bool m_IsDeath;
        bool m_IsDying;
        Uint32 m_CurrentTicks;
        bool m_IsCalled;

        Collider* m_Collider;
        Collider* m_FlamesCollider;
        RigidBody* m_RigidBody;
        SpriteAnimation* m_Animation;
        SeqAnimation* m_SeqAnimation;

        Vector2D m_LastSafePosition;
        Vector2D m_LastCoord;
        Vector2D m_LastForPathCalc;
        Vector2D m_LastForBackTrackCalc;

        Health m_Health;
        std::string m_TextureIdle;
        std::vector<std::vector<Vector2D>> m_SPaths;
        std::stack<Vector2D> m_BackTrack;
        std::stack<Vector2D> m_ReturnToPathInit;
        std::vector<Claw*> m_Claws;
        std::vector<Arm*> m_Arms;
        enum STATES { PATROL , INATTACK };
        STATES m_CurrentState;
};

#endif // ZOMBIEL5_H
