#ifndef GUN_H
#define GUN_H

#include "Weapon.h"
#include "Bullet.h"
#include "BulletHandler.h"
#include "Collider.h"
#include "Timer.h"
#include "Soldier.h"
#include <vector>
class Soldier;
class Bullet;
class Gun: public Weapons
{
    public:
        Gun(Soldier* player,int bullets,int damage,int reloadTime);

        virtual void Attack();
        virtual void Reload();
        virtual int DealDamage();
        bool IsRecharging() { return m_Recharging; }

    private:

        Soldier* m_PlayerImage;
        std::vector<Bullet*> m_Filler;

};

#endif // GUN_H
