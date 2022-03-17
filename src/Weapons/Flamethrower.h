#ifndef FLAMETHROWER_H
#define FLAMETHROWER_H

#include "Weapon.h"
#include "Soldier.h"
#include <math.h>
class Soldier;
class Flamethrower: public Weapons
{
    public:
        Flamethrower(Soldier* player,int bullets,int damage,int reloadTime);
        virtual void Attack();
        virtual void Reload();
        virtual int DealDamage();
        virtual ~Flamethrower();

    private:
        Soldier* m_PlayerImage;
};

#endif // FLAMETHROWER_H
