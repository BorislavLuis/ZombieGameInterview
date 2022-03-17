#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include "Soldier.h"
#include "CollisionHandler.h"
#include "HealtBox.h"
#include "GunItem.h"
#include "KnifeItem.h"
#include "MachineGunItem.h"
#include "FlamethrowerItem.h"
#include "BatItem.h"
#include "GunMagazineItem.h"
#include "MachineGunMagazine.h"
#include "FlamethrowerCylinder.h"
#include "LevelEnd.h"

#include <vector>

class Observer;
class HealtBox;
class GunItem;
class FlamethrowerItem;
class Subject
{
    public:
        Subject(){}
        void AddObserver(Observer* obs);
        void RemoveObserver(Observer* obs);
        void Notify(Soldier* player);
        void CleanAllObservers();
        virtual ~Subject();

    private:
        std::vector<Observer*> m_Observers;

};

#endif // SUBJECT_H
