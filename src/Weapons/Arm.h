#ifndef ARM_H
#define ARM_H
#include "Soldier.h"

class Arm
{
    public:
        Arm(float x,float y, double angle);
        void Update(Soldier* player);
        void Draw();
        bool ForDelete() { return m_Delete;}
        virtual ~Arm();

    private:
        bool m_Delete;
        SDL_Point m_TestPoint;
        Collider* m_Collider;
        Transform* m_Tf;

};

#endif // ARM_H
