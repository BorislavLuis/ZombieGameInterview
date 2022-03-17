#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"
#include "Transform.h"
#include "Vector2D.h"
#include "TextureMgr.h"
#include "Collider.h"
#include <iostream>
#include <string>
#include <SDL.h>


class GameObject : public IObject
{
    public:
        GameObject(Transform* tf):m_Tf(tf){}

        inline Vector2D* GetOrigin() { return m_Tf->m_Origin;}
        inline Transform* GetTransform() { return m_Tf; }
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        virtual Collider* GetCollider();
        virtual void ReciveDamage(int damage){};
        virtual bool IsDead(){return false;};
        //virtual bool ForRemove(){return false;}
        //virtual void Remove(){};
        virtual int GetObjectNumber(){};
        virtual ~GameObject();

    protected:
        Transform* m_Tf;
        static int m_ObjectNumber;

};

#endif // GAMEOBJECT_H
