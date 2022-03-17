#ifndef MACHINEGUNMAGAZINE_H
#define MACHINEGUNMAGAZINE_H

#include "Subject.h"

class MachineGunMagazine: public Observer
{
    public:
        MachineGunMagazine(Transform* tf, Collider* coll, SpriteAnimation* sp);

        virtual SDL_Rect GetCollider() { return m_Collider->Get();}
        inline Transform* GetTransform() { return m_Tf; }
        virtual void OnNotify(Soldier* player) override;
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        virtual Observer& operator = (const Observer &obs) { return *this;}
        virtual ~MachineGunMagazine();

    protected:
        Transform* m_Tf;
        Collider* m_Collider;
        SpriteAnimation* m_Anim;
};

#endif // MACHINEGUNMAGAZINE_H
