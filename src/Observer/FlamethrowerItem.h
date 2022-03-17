#ifndef FLAMETHROWERITEM_H
#define FLAMETHROWERITEM_H

#include "Subject.h"
#include "Flamethrower.h"

class FlamethrowerItem: public Observer
{
    public:
        FlamethrowerItem(Transform* tf, Collider* coll, SpriteAnimation* sp);

        virtual SDL_Rect GetCollider() { return m_Collider->Get();}
        inline Transform* GetTransform() { return m_Tf; }
        virtual void OnNotify(Soldier* player) override;
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        virtual Observer& operator = (const Observer &obs) { return *this;}
        virtual ~FlamethrowerItem();

    protected:
        Transform* m_Tf;
        Collider* m_Collider;
        SpriteAnimation* m_Anim;
};

#endif // FLAMETHROWERITEM_H
