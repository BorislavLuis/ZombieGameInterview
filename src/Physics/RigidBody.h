#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"

#define UNI_MASS 1.0f
#define GRAVITY 9.8f
#define FORWARD 1
#define BACKWARD -1
#define UPWARD -1
#define DOWNWARD 1

class RigidBody
{
    public:
        RigidBody()
        {
            m_Mass = UNI_MASS;
            m_Gravity = GRAVITY;
            m_Angle = 0;
        }

        inline void SetMass(float mass){m_Mass = mass;}
        inline void SetGravity(float gravity){m_Gravity = gravity;}

        inline void ApplyForce(Vector2D force){m_Force = force;}
        inline void ApplyForceX(float fx){m_Force.X = fx;}
        inline void ApplyForceY(float fy){m_Force.Y = fy;}
        inline void UnsetForce(){m_Force = Vector2D(0,0);}

        inline void ApplyFriction(Vector2D fr){m_Friction = fr;}
        inline void UnsetFriction(){m_Friction = Vector2D(0,0);}

        inline float GetMass(){return m_Mass;}
        inline Vector2D Position(){return m_Position;}
        inline Vector2D Velocity(){return m_Velocity;}
        inline Vector2D Acceleration(){return m_Accelaration;}


        void Update(float dt)
        {
            m_Accelaration.X = (m_Force.X + m_Friction.X)/m_Mass;
            m_Accelaration.Y = (m_Force.Y + m_Friction.Y)/m_Mass;
            m_Velocity = m_Accelaration*dt;
            m_Position = m_Velocity*dt;
        }

        virtual ~RigidBody() {}

    private:
        float m_Mass;
        float m_Gravity;
        double m_Angle;

        Vector2D m_Force;
        Vector2D m_Friction;

        Vector2D m_Position;
        Vector2D m_Velocity;
        Vector2D m_Accelaration;

};

#endif // RIGIDBODY_H
