#ifndef BAT_H
#define BAT_H

#include "Weapon.h"
#include "Soldier.h"
#include <math.h>
class Soldier;
class Bat: public Weapons
{
    public:
        Bat(Soldier* player,int bullets,int damage,int reloadTime);
        virtual void Attack();
        virtual void Reload();
        virtual int DealDamage();
        Collider* GetBatCollider(){return m_BatCollider;}
        virtual ~Bat(){}

        Transform* m_Tf;
    private:
        Soldier* m_PlayerImage;
        Collider* m_BatCollider;

};

#endif // BAT_H
