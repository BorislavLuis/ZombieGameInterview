#ifndef WEAPON_H
#define WEAPON_H
#include "Collider.h"
#include "Transform.h"
class Weapons
{
    public:

        virtual void Attack() = 0;
        virtual void Reload() = 0;
        virtual int DealDamage() = 0;
        Transform* GetTransform() { return m_Transform;}
        virtual ~Weapons() { delete m_Transform; m_Transform = nullptr;}

    protected:

        int m_BulletCount;
        int m_FireTime;
        int m_ReloadTime;
        int m_Damage;
        bool m_Recharging;
        bool m_StartRecharge;
        Transform* m_Transform;

};

#endif // WEAPON_H
