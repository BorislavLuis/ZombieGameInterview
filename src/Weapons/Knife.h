#ifndef KNIFE_H
#define KNIFE_H
#include "Weapon.h"
#include "Soldier.h"


class Soldier;
class Knife: public Weapons
{
    public:
        Knife(Soldier* player,int bullets,int damage,int reloadTime);

        virtual void Attack();
        virtual void Reload();
        virtual int DealDamage();
        bool IsRecharging() { return m_Recharging; }

    private:
        Soldier* m_PlayerImage;

};

#endif // KNIFE_H
