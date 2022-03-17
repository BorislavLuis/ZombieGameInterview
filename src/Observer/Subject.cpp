#include "Subject.h"
void Subject::AddObserver(Observer* obs)
{
    m_Observers.push_back(obs);
}

void Subject::RemoveObserver(Observer* obs)
{
    std::vector<Observer*>::iterator itr1;
    for(itr1 = m_Observers.begin();itr1 != m_Observers.end();itr1++)
    {
        if(*itr1 == obs)
        {
            obs->Clean();
            delete *itr1;
            itr1 = m_Observers.erase(itr1);
            itr1--;
        }
    }
}

void Subject::Notify(Soldier* player)
{

    for(auto ob:m_Observers)
    {
        if(ob != nullptr)
        {
            ob->Update(1);
            ob->Draw();
            if(CollisionHandler::GetInstance()->CheckCollision(ob->GetCollider(), player->GetCollider()->Get()))
            {
                ob->OnNotify(player);
                RemoveObserver(ob);
            }
        }
    }
}
void Subject::CleanAllObservers()
{
    for(auto ob:m_Observers)
    {
        ob->Clean();
    }
    std::vector<Observer*>::iterator itr;
    for(itr = m_Observers.begin(); itr != m_Observers.end();itr++)
    {
        delete *itr;
        *itr = nullptr;
    }
    m_Observers.clear();
}

Subject::~Subject()
{
    //dtor
}
