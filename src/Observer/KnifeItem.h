#ifndef KNIFEITEM_H
#define KNIFEITEM_H

#include "Subject.h"

class KnifeItem: public Observer
{
    public:
        KnifeItem(Transform* tf, Collider* coll, SpriteAnimation* sp);

        virtual SDL_Rect GetCollider() { return m_Collider->Get();}
        inline Transform* GetTransform() { return m_Tf; }
        virtual void OnNotify(Soldier* player) override;
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        virtual Observer& operator = (const Observer &obs) { return *this;}
        virtual ~KnifeItem();

    protected:
        Transform* m_Tf;
        Collider* m_Collider;
        SpriteAnimation* m_Anim;
};

#endif // KNIFEITEM_H
