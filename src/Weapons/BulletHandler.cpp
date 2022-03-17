#include "BulletHandler.h"

BulletHandler* BulletHandler::s_Instance = nullptr;

void BulletHandler::AddPlayerBullet(Bullet* bullet)
{
    m_PlayerBullets.push_back(bullet);
}

void BulletHandler::AddEnemyBullet(Bullet* bullet)
{
    m_EnemyBullets.push_back(bullet);
}

void BulletHandler::UpdatePlayerBullet()
{
    bool result = false;
    float dt = Timer::GetInstance()->GetDeltaTime();
    std::vector<Bullet*>::iterator itr;
    for(itr = m_PlayerBullets.begin();itr != m_PlayerBullets.end(); ++itr)
    {
        Bullet* bl = *itr;
        if(bl != nullptr)
        {
            //SDL_Log("%d",bl->IsOutsideScreen());
            //SDL_Log("%d",bl->CheckMapCollision());
            //SDL_Log("%d",bl->CheckEnemyPlayerBulletCollision());
            if(bl->IsOutsideScreen() || bl->CheckMapCollision() || bl->CheckEnemyPlayerBulletCollision())
            {
                SDL_Log("%s","Yes");
                delete *itr;
                *itr = nullptr;
            }
            else
            {
                bl->Move(dt);
            }
        }
    }
}
void BulletHandler::UpdateEnemyBullet()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    std::vector<Bullet*>::iterator itr;
    //SDL_Log("SIZEEEEE BULLET************** %d",m_EnemyBullets.size());
    if(m_EnemyBullets.size()>0)
    {
        for(itr = m_EnemyBullets.begin();itr != m_EnemyBullets.end(); ++itr)
        {
            Bullet* bl = *itr;
            if(bl != nullptr)
            {
                if(bl->IsOutsideScreen() || bl->CheckMapCollision() || bl->CheckPlayerEnemyBulletCollision())
                {

                    delete *itr;
                    *itr = nullptr;
                }
                else
                {
                    bl->Move(dt);
                }
            }
        }
    }
}

void BulletHandler::DrawPlayerBullet()
{
    //int m = m_PlayerBullets.size();
    //SDL_Log("%d",m);
    for(unsigned int i = 0; i < m_PlayerBullets.size();i++)
    {
        if(m_PlayerBullets[i] != nullptr)
        {
            m_PlayerBullets[i]->Draw();
        }
    }
}
void BulletHandler::DrawEnemyBullet()
{
    //SDL_Log("Drawwwwwwwwwwwwwww");
    for(unsigned int i = 0; i < m_EnemyBullets.size();i++)
    {
        if(m_EnemyBullets[i] != nullptr)
        {
            m_EnemyBullets[i]->Draw();
        }
    }
}

void BulletHandler::Clear()
{
    m_EnemyBullets.clear();
    m_PlayerBullets.clear();
}

BulletHandler::BulletHandler()
{

}
