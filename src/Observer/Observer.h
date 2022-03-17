#ifndef OBSERVER_H
#define OBSERVER_H
#include "Soldier.h"

class Soldier;

class Observer
{
    public:
        virtual void OnNotify(Soldier* player) = 0;
        virtual SDL_Rect GetCollider() = 0;
        virtual void Draw() = 0;
        virtual void Update(float dt) = 0;
        virtual void Clean() = 0;
        virtual Observer& operator = (const Observer &obs) = 0;
        virtual ~Observer(){}

};

#endif // OBSERVER_H
