#include "Bat.h"

Bat::Bat(Soldier* player, int bullets, int damage, int reloadTime)
{
    m_PlayerImage = player;
    m_Transform = new Transform("BatIcon",74,10,64,64);
}

void Bat::Attack()
{
    SDL_Point p, pReal;
    float xd1 = m_PlayerImage->GetCollider()->Get().w/2;
    float yd1 = m_PlayerImage->GetCollider()->Get().h/2;
    float xd2 = m_PlayerImage->GetCollider()->Get().w;
    float yd2 = m_PlayerImage->GetCollider()->Get().h;
    float x1 = (m_PlayerImage->GetCollider()->Get().x - Camera::GetInstance()->GetPosition().X )  + m_PlayerImage->GetCollider()->Get().w;///2;
    float y1 = (m_PlayerImage->GetCollider()->Get().y - Camera::GetInstance()->GetPosition().Y) + m_PlayerImage->GetCollider()->Get().h;///2;
    float distance = sqrt((xd1*xd1 + xd2*xd2) + (yd1*yd1 + yd2*yd2));
//    double angle = atan2(Camera::GetInstance()->GetPosition().Y + Input::GetInstance()->GetMousePosition().Y - y1, Camera::GetInstance()->GetPosition().X + Input::GetInstance()->GetMousePosition().X - x1);// * 180/PI;
    double angle = atan2(Camera::GetInstance()->GetPosition().Y + Input::GetInstance()->GetMousePosition().Y - m_PlayerImage->GetOrigin()->Y, Camera::GetInstance()->GetPosition().X + Input::GetInstance()->GetMousePosition().X - m_PlayerImage->GetOrigin()->X);
    float x = cos(angle);
    float y = sin(angle);
    SDL_Rect box;
    if(x >= 0 && y >= 0)
    {
        x1 = m_PlayerImage->GetCollider()->Get().x;
        y1 = m_PlayerImage->GetCollider()->Get().y;
        /* SHOW COLLIDER */
//        x1 = m_PlayerImage->GetCollider()->Get().x - Camera::GetInstance()->GetPosition().X ;
//        y1 = (m_PlayerImage->GetCollider()->Get().y - Camera::GetInstance()->GetPosition().Y ) + m_PlayerImage->GetCollider()->Get().h;
        p.x = x1 + (distance*x);
        p.y = y1 + (distance*y);
        //box = { p.x,p.y,20,30 };
//        realBox = { pReal.x,pReal.y,32,32 };
        box = { p.x ,p.y,32,32};
        SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),x1,y1,x1 + (distance*x),y1 + (distance*y));
    }
    else if(x < 0 && y >= 0)
    {
        x1 = /*Camera::GetInstance()->GetPosition().X + */m_PlayerImage->GetCollider()->Get().x;
        y1 = /*Camera::GetInstance()->GetPosition().Y + */m_PlayerImage->GetCollider()->Get().y;
         /* SHOW COLLIDER */
//        x1 = m_PlayerImage->GetCollider()->Get().x - Camera::GetInstance()->GetPosition().X;
//        y1 = m_PlayerImage->GetCollider()->Get().y - Camera::GetInstance()->GetPosition().Y;
        p.x = x1 + (distance*x);
        p.y = y1 + (distance*y);
        //box = { p.x - 20,p.y,20,30 };
        box = { p.x - 32,p.y,32,32 };
        SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),x1,y1,x1 + (distance*x),y1+(distance*y));
    }
    else if (x < 0 && y < 0)
    {
        x1 = /*Camera::GetInstance()->GetPosition().X + */m_PlayerImage->GetCollider()->Get().x;
        y1 = /*Camera::GetInstance()->GetPosition().Y + */m_PlayerImage->GetCollider()->Get().y;
         /* SHOW COLLIDER */
//        x1 = (m_PlayerImage->GetCollider()->Get().x - Camera::GetInstance()->GetPosition().X) + m_PlayerImage->GetCollider()->Get().w;
//        y1 = m_PlayerImage->GetCollider()->Get().y - Camera::GetInstance()->GetPosition().Y;
        p.x = x1 + (distance*x);
        p.y = y1 + (distance*y);
        //box = { p.x - 20,p.y - 30,20,30 };

        box = { p.x ,p.y - 32,32,32 };
        SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),x1,y1,x1 + (distance*x),y1 + (distance*y));
    }
    else if (x >= 0 && y < 0)
    {
        x1 = /*Camera::GetInstance()->GetPosition().X + */m_PlayerImage->GetCollider()->Get().x;
        y1 = /*Camera::GetInstance()->GetPosition().Y + */m_PlayerImage->GetCollider()->Get().y;
         /* SHOW COLLIDER */
//        x1 = (m_PlayerImage->GetCollider()->Get().x - Camera::GetInstance()->GetPosition().X ) + m_PlayerImage->GetCollider()->Get().w;
//        y1 = (m_PlayerImage->GetCollider()->Get().y - Camera::GetInstance()->GetPosition().Y ) + m_PlayerImage->GetCollider()->Get().h;
        p.x = x1 + (distance*x);
        p.y = y1 + (distance*y);
        //box = { p.x ,p.y - 30,20,30 };
        box = { p.x ,p.y,32,32 };
        SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),x1,y1,x1 + (distance*x),y1 + (distance*y));
    }
    CollisionHandler::GetInstance()->CheckEnemyHitByPlayerBat(box);
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
}

void Bat::Reload()
{

}

int Bat::DealDamage()
{

}
