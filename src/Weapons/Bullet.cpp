#include "Bullet.h"

extern Soldier* player;

Bullet::Bullet(Vector2D* pos,Vector2D vel,Collider collider,std::vector<std::string> type)
{
    m_Exploded = false;
    m_Vel = vel;
    m_Transform.X = pos->X;
    m_Transform.Y = pos->Y;
    m_TextureID = type;
    m_Transform.m_TextureID = m_TextureID[INPLAY];
    m_Collider.SetBuffer(0,0,0,0);
    m_Collider.Set(collider.Get().x,collider.Get().y,collider.Get().w,collider.Get().h);
    TextureMgr::GetInstance()->QueryTexture(m_Transform.m_TextureID,&m_Transform.m_Width,&m_Transform.m_Height);
}

void Bullet::Draw()
{
    TextureMgr::GetInstance()->Draw(&m_Transform);
    SDL_Rect dest = this->m_Collider.Get();
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&dest);
}

void Bullet::Move(float dt)
{
    double sinN=sin(m_Transform.m_Angle*(3.1415/180));
    double cosN=cos(m_Transform.m_Angle*(3.1415/180));
    if(m_Transform.m_Angle > 0 && m_Transform.m_Angle <= 90)
    {
        m_Transform.X+=cos(m_Transform.m_Angle*(3.1415/180))*2;//10;
        m_Transform.Y+=sin(m_Transform.m_Angle*(3.1415/180))*2;//10;
        //SDL_Log("XXXXX***%d YYYYYY***%d WWWWW***%d HHHHH***%d",m_Collider.Get().x,m_Collider.Get().y,m_Collider.Get().w,m_Collider.Get().h);
        //m_Collider.Set((int)m_Transform.X,(int)m_Transform.Y,5,5);
        m_Collider.Set((int)m_Transform.X,(int)m_Transform.Y,m_Collider.Get().w,m_Collider.Get().h);
        //m_Collider.Set((int)m_Transform.X,(int)m_Transform.Y,X,Y);
    }
    else if (m_Transform.m_Angle > 90 && m_Transform.m_Angle <= 180)
    {
        m_Transform.X+=cos(m_Transform.m_Angle*(3.1415/180))*2;//10;
        m_Transform.Y+=sin(m_Transform.m_Angle*(3.1415/180))*2;//10;
        //SDL_Log("XXXXX***%d YYYYYY***%d WWWWW***%d HHHHH***%d",m_Collider.Get().x,m_Collider.Get().y,m_Collider.Get().w,m_Collider.Get().h);
        m_Collider.Set((int)m_Transform.X,(int)m_Transform.Y,m_Collider.Get().w,m_Collider.Get().h);
    }
    else if (m_Transform.m_Angle > -180 && m_Transform.m_Angle <= -90)
    {
        m_Transform.X+=cos(m_Transform.m_Angle*(3.1415/180))*2;//10;
        m_Transform.Y+=sin(m_Transform.m_Angle*(3.1415/180))*2;//10;
        //SDL_Log("XXXXX***%d YYYYYY***%d WWWWW***%d HHHHH***%d",m_Collider.Get().x,m_Collider.Get().y,m_Collider.Get().w,m_Collider.Get().h);
        m_Collider.Set((int)m_Transform.X,(int)m_Transform.Y,m_Collider.Get().w,m_Collider.Get().h);
    }
    else if (m_Transform.m_Angle > -90 && m_Transform.m_Angle <= 0)
    {
        m_Transform.X+=cos(m_Transform.m_Angle*(3.1415/180))*2;//10;
        m_Transform.Y+=sin(m_Transform.m_Angle*(3.1415/180))*2;//10;
        //SDL_Log("XXXXX***%d YYYYYY***%d WWWWW***%d HHHHH***%d",m_Collider.Get().x,m_Collider.Get().y,m_Collider.Get().w,m_Collider.Get().h);
        m_Collider.Set((int)m_Transform.X,(int)m_Transform.Y,m_Collider.Get().w,m_Collider.Get().h);
    }

    //Explode();
}

bool Bullet::IsOutsideScreen()
{
    const SDL_Rect screen = Camera::GetInstance()->GetViewPort();
    if((m_Transform.X < screen.x) || (m_Transform.Y < screen.y) ||
        (m_Transform.X > screen.w+screen.x) || (m_Transform.Y > screen.h+screen.y))
    {
        m_Exploded = true;
        return true;
    }
    return false;
}
bool Bullet::CheckMapCollision()
{
    if(CollisionHandler::GetInstance()->MapCollision(m_Collider.Get()))
    {
        m_Exploded = true;
        return true;
    }
    return false;
}
bool Bullet::CheckPlayerEnemyBulletCollision()
{
    if(CollisionHandler::GetInstance()->CheckPlayerEnemyBulletCollision(player,this))
    {
        m_Exploded = true;
        Explode();
        Draw();
        return true;
    }
    return false;
}
bool Bullet::CheckEnemyPlayerBulletCollision()
{
    if(CollisionHandler::GetInstance()->CheckEnemyPlayerBulletCollision())
    {
        m_Exploded = true;
        Explode();
        Draw();
        return true;
    }
    return false;
}
void Bullet::Explode()
{
    if(m_Exploded)
    {
        m_Transform.m_TextureID = m_TextureID[EXPLODED];
    }
}
void Bullet::SetCoordinate(float x,float y,double angle)
{
    m_Transform.X = x;
    m_Transform.Y = y;
    m_Transform.m_Angle = angle;
}
