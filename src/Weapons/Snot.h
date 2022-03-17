#ifndef SNOT_H
#define SNOT_H
#include "Collider.h"
#include "SeqAnimation.h"
#include "Soldier.h"
//#include "Transform.h"
//#include "Engine.h"
//#include "Mathematics.h"
class Snot
{
    public:
        Snot(float x,float y,double angle);
        void Update(Soldier* soldier);
        void Draw();
        void Move();
        bool ForDelete() {return m_Delete;}
        virtual ~Snot();
        //32

    private:
//        enum Quad {FIRST,SECOND,THIRD,FOURTH };
//        Quad m_Quad;
        int m_InitX,m_InitY;
        SDL_Point m_ColCenter;
        int m_TimeFrame2;
        int m_TimeFrame3;
        float m_ElapsedTime;
        bool m_Delete;
        Collider* m_Collider;
        SeqAnimation* m_Animation;
        Transform* m_Tf;
};

#endif // SNOT_H
