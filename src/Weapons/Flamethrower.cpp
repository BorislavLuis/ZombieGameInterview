#include "Flamethrower.h"
//#include "Mathematics.h"
Flamethrower::Flamethrower(Soldier* player,int bullets,int damage,int reloadTime)
{
    m_PlayerImage = player;
    m_Transform = new Transform("FlamethrowerIcon",202,10,64,64);
}

void Flamethrower::Attack()
{
    SDL_Point p, pReal;
    float xd1 = m_PlayerImage->GetCollider()->Get().w/2;
    float yd1 = m_PlayerImage->GetCollider()->Get().h/2;
    float xd2 = m_PlayerImage->GetCollider()->Get().w;
    float yd2 = m_PlayerImage->GetCollider()->Get().h;
    float x1 = (m_PlayerImage->GetCollider()->Get().x - Camera::GetInstance()->GetPosition().X )  + m_PlayerImage->GetCollider()->Get().w;///2;
    float y1 = (m_PlayerImage->GetCollider()->Get().y - Camera::GetInstance()->GetPosition().Y) + m_PlayerImage->GetCollider()->Get().h;///2;
    float distance = sqrt((xd1*xd1 + xd2*xd2) + (yd1*yd1 + yd2*yd2));

    double angle = atan2(Camera::GetInstance()->GetPosition().Y + Input::GetInstance()->GetMousePosition().Y - m_PlayerImage->GetOrigin()->Y, Camera::GetInstance()->GetPosition().X + Input::GetInstance()->GetMousePosition().X - m_PlayerImage->GetOrigin()->X);
    float x = cos(angle);
    float y = sin(angle);
    SDL_Rect box;
    if(x >= 0 && y >= 0)
    {
        x1 = m_PlayerImage->GetCollider()->Get().x  + xd1;
        y1 = m_PlayerImage->GetCollider()->Get().y  + yd1;
        /* SHOW COLLIDER */
//        x1 = (m_PlayerImage->GetCollider()->Get().x + xd1) - Camera::GetInstance()->GetPosition().X ;
//        y1 = (m_PlayerImage->GetCollider()->Get().y + yd1) - Camera::GetInstance()->GetPosition().Y ;// + m_PlayerImage->GetCollider()->Get().h;
        p.x = x1 + (distance*x) - ((64 - y*20)/2);
        p.y = y1 + (distance*y) - ((64 - x*20)/2);

        box = { p.x  , p.y  ,Scaling(x,0.0f,1.0f,45.0f,120.0f) , Scaling(y,0.0f,1.0f,45.0f,120.0f)};
        //SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),x1,y1,x1 + (distance*x),y1 + (distance*y));
    }
    else if(x < 0 && y >= 0)
    {
        x1 = m_PlayerImage->GetCollider()->Get().x + xd1;
        y1 = m_PlayerImage->GetCollider()->Get().y + yd1;
         /* SHOW COLLIDER */
//        x1 = (m_PlayerImage->GetCollider()->Get().x + xd1) - Camera::GetInstance()->GetPosition().X;
//        y1 = (m_PlayerImage->GetCollider()->Get().y + yd1) - Camera::GetInstance()->GetPosition().Y;
        p.x = x1 + (distance*x) + ((64 - y*20)/2);
        p.y = y1 + (distance*y) - ((64 + x*20)/2);

        //box = { p.x  , p.y ,-Scaling(x,0.0f,-1.0f,45.0f,120.0f),Scaling(y,0.0f,1.0f,45.0f,120.0f)};
        box = { p.x -Scaling(x,0.0f,-1.0f,45.0f,120.0f) , p.y ,Scaling(x,0.0f,-1.0f,45.0f,120.0f),Scaling(y,0.0f,1.0f,45.0f,120.0f)};
        //SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),x1,y1,x1 + (distance*x),y1+(distance*y));
    }
    else if (x < 0 && y < 0)
    {
        x1 = m_PlayerImage->GetCollider()->Get().x + xd1;
        y1 = m_PlayerImage->GetCollider()->Get().y + yd1;
         /* SHOW COLLIDER */
//        x1 = ((m_PlayerImage->GetCollider()->Get().x + xd1) - Camera::GetInstance()->GetPosition().X);/// + m_PlayerImage->GetCollider()->Get().w;
//        y1 = (m_PlayerImage->GetCollider()->Get().y + yd1) - Camera::GetInstance()->GetPosition().Y;
        p.x = x1 + (distance*x) + ((64 + y*20)/2);
        p.y = y1 + (distance*y) + ((64 + x*20)/2);

        //box = { p.x  ,p.y ,-Scaling(x,0.0f,-1.0f,45.0f,120.0f),-Scaling(y,0.0f,-1.0f,45.0f,120.0f)};
        box = { p.x - Scaling(x,0.0f,-1.0f,45.0f,120.0f)  ,p.y - Scaling(y,0.0f,-1.0f,45.0f,120.0f) ,Scaling(x,0.0f,-1.0f,45.0f,120.0f),Scaling(y,0.0f,-1.0f,45.0f,120.0f)};
        //SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),x1,y1,x1 + (distance*x),y1 + (distance*y));
    }
    else if (x >= 0 && y < 0)
    {
        x1 = m_PlayerImage->GetCollider()->Get().x + xd1;
        y1 = m_PlayerImage->GetCollider()->Get().y + yd1;
         /* SHOW COLLIDER */
//        x1 = (m_PlayerImage->GetCollider()->Get().x + xd1) - Camera::GetInstance()->GetPosition().X ;// + m_PlayerImage->GetCollider()->Get().w;
//        y1 = (m_PlayerImage->GetCollider()->Get().y + yd1) - Camera::GetInstance()->GetPosition().Y ;// + m_PlayerImage->GetCollider()->Get().h;
        p.x = x1 + (distance*x) - ((64 + y*20)/2);
        p.y = y1 + (distance*y) + ((64 - x*20)/2);

        box = { p.x ,p.y - Scaling(y,0.0f,-1.0f,45.0f,120.0f) ,Scaling(x,0.0f,1.0f,45.0f,120.0f),Scaling(y,0.0f,-1.0f,45.0f,120.0f) };
        //SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),x1,y1,x1 + (distance*x),y1 + (distance*y));
    }
    CollisionHandler::GetInstance()->CheckEnemyHitByPlayerBat(box);
    //SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
}

void Flamethrower::Reload()
{

}

int Flamethrower::DealDamage()
{

}

Flamethrower::~Flamethrower()
{

}
