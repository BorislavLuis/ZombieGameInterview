#ifndef MACHINEGUN_H
#define MACHINEGUN_H

#include "Weapon.h"
class Soldier;
class MachineGun: public Weapons
{
    public:
        MachineGun(Soldier* player,int bullets,int damage,int reloadTime);
        virtual void Attack();
        virtual void Reload();
        virtual int DealDamage();
        virtual ~MachineGun();

    private:
        Soldier* m_SoldierImage;
};

#endif // MACHINEGUN_H
