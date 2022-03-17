#ifndef CLAW_H
#define CLAW_H

#include "Collider.h"
#include "Transform.h"
#include "TextureMgr.h"
#include "Soldier.h"

class Claw
{
    public:
        Claw(float x,float y,double angle);
        void Update(Soldier* player);
        void Draw();
        bool ForDelete() { return m_ForDelete;}
        virtual ~Claw();

    private:
        bool m_ForDelete;
        SDL_Point m_CenterCol1;
        SDL_Point m_CenterCol2;
        enum Quads{ FIRST,SECOND,THIRD,FOURTH };
        Quads m_Quad;
        Collider* m_Collider1;
        Collider* m_Collider2;
        Transform* m_Tf;
};

#endif // CLAW_H
