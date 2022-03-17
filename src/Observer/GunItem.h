#ifndef GUNITEM_H
#define GUNITEM_H
#include "Subject.h"

class GunItem: public Observer
{
    public:
        GunItem(Transform* tf, Collider* coll, SpriteAnimation* sp);

        virtual SDL_Rect GetCollider() { return m_Collider->Get();}
        inline Transform* GetTransform() { return m_Tf; }
        virtual void OnNotify(Soldier* player) override;
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        virtual Observer& operator = (const Observer &obs) { return *this;}
        virtual ~GunItem();

    protected:
        Transform* m_Tf;
        Collider* m_Collider;
        SpriteAnimation* m_Anim;
};

#endif // GUNITEM_H
