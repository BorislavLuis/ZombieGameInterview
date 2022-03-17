#include "Gun.h"

Gun::Gun(Soldier* player,int bullets,int damage,int reloadTime)
{
    m_BulletCount = bullets;
    m_ReloadTime = reloadTime;
    m_Damage = damage;
    m_FireTime = 125;
    m_Recharging = false;
    m_StartRecharge = false;
    m_PlayerImage = player;
    Collider col;
    col.Set(5,5,5,5);
    BulletHandler::GetInstance()->Clear();
    m_Transform = new Transform("GunIcon",138,10,64,64);
    for(int i = 0; i < bullets;i++)
    {
        m_Filler.push_back(new Bullet(player->GetTransform()->m_Origin,Vector2D(5,5),col,{"InPlay","Exploded"}));
    }

}

void Gun::Attack()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    SDL_Rect rect = m_PlayerImage->GetCollider()->Get();
    m_Filler[m_BulletCount-1]->SetCoordinate(rect.x+rect.w/2,rect.y+rect.h/2 /*m_PlayerImage->GetOrigin()->X,m_PlayerImage->GetOrigin()->Y*/,m_PlayerImage->GetTransform()->m_Angle);
    if(m_FireTime == 125)
    {
        BulletHandler::GetInstance()->AddPlayerBullet(m_Filler[m_BulletCount-1]);
        if(m_BulletCount == 1)
        {
            m_BulletCount = m_Filler.size();
        }
        else
        {
            m_BulletCount--;
        }

        m_FireTime = 0;
    }
    //SDL_Log("%d",m_FireTime);
    m_FireTime++;
//    delete m_Filler[m_BulletCount];
//    m_Filler.erase(m_Filler.begin()+m_BulletCount);

}

void Gun::Reload()
{
    //if(m_Filler.size() )
}

int Gun::DealDamage()
{
    return m_Damage;
}
