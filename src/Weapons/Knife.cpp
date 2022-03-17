#include "Knife.h"
#include "Mathematics.h"
Knife::Knife(Soldier* player, int bullets, int damage, int reloadTime)
{
    m_PlayerImage = player;
    m_Transform = new Transform("KnifeIcon",10,10,64,64);
}

void Knife::Attack()
{

    SDL_Point p, pReal;
    float EngValueX,EngValueY;
    float xd1 = m_PlayerImage->GetCollider()->Get().w/2;
    float yd1 = m_PlayerImage->GetCollider()->Get().h/2;
    float xd2 = 32;//m_PlayerImage->GetCollider()->Get().w;
    float yd2 = 32;//m_PlayerImage->GetCollider()->Get().h;
    float x1;// = (m_PlayerImage->GetCollider()->Get().x - Camera::GetInstance()->GetPosition().X );//  + m_PlayerImage->GetCollider()->Get().w;///2;
    float y1;// = (m_PlayerImage->GetCollider()->Get().y - Camera::GetInstance()->GetPosition().Y); //+ m_PlayerImage->GetCollider()->Get().h;///2;
    float distance = sqrt((xd1*xd1 + xd2*xd2) + (yd1*yd1 + yd2*yd2));

    double angle = atan2(Camera::GetInstance()->GetPosition().Y + Input::GetInstance()->GetMousePosition().Y - m_PlayerImage->GetOrigin()->Y, Camera::GetInstance()->GetPosition().X + Input::GetInstance()->GetMousePosition().X - m_PlayerImage->GetOrigin()->X);
    float x = cos(angle);
    float y = sin(angle);
    EngValueX = Scaling(x,0.0f,1.0f,0.0f,32.0f);
    EngValueY = Scaling(y,0.0f,1.0f,0.0f,32.0f);
    float Devider = Scaling(angle * 180/PI,0.0,90.0,0.0,32.0);
    SDL_Rect box;
    if(x >= 0 && y >= 0)
    {
        x1 = m_PlayerImage->GetCollider()->Get().x + xd1;
        y1 = m_PlayerImage->GetCollider()->Get().y + yd1;
        /* SHOW COLLIDER */
//        x1 = m_PlayerImage->GetCollider()->Get().x - Camera::GetInstance()->GetPosition().X ;
//        y1 = (m_PlayerImage->GetCollider()->Get().y - Camera::GetInstance()->GetPosition().Y ) + m_PlayerImage->GetCollider()->Get().h;
        p.x = x1 + (distance*x);
        p.y = y1 + (distance*y);
        //box = { p.x ,p.y - 32,32,32};

        box = { p.x - 32 ,p.y - Devider,32,32};
        SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),x1,y1,x1 + (distance*x),y1 + (distance*y));
    }
    else if(x < 0 && y >= 0)
    {
        x1 = m_PlayerImage->GetCollider()->Get().x + xd1;
        y1 = m_PlayerImage->GetCollider()->Get().y + yd1;
         /* SHOW COLLIDER */
//        x1 = m_PlayerImage->GetCollider()->Get().x - Camera::GetInstance()->GetPosition().X;
//        y1 = m_PlayerImage->GetCollider()->Get().y - Camera::GetInstance()->GetPosition().Y;
        p.x = x1 + (distance*x);
        p.y = y1 + (distance*y);

        Devider = Scaling(angle * 180/PI - 90,0.0,90.0,0.0,32.0);
        //SDL_Log("******************************************************************************* %f",Devider);
        box = { p.x ,p.y - Devider ,32,32 };
        SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),x1,y1,x1 + (distance*x),y1+(distance*y));
    }
    else if (x < 0 && y < 0)
    {
        x1 = /*Camera::GetInstance()->GetPosition().X + */m_PlayerImage->GetCollider()->Get().x + xd1;
        y1 = /*Camera::GetInstance()->GetPosition().Y + */m_PlayerImage->GetCollider()->Get().y + yd1;
         /* SHOW COLLIDER */
//        x1 = (m_PlayerImage->GetCollider()->Get().x - Camera::GetInstance()->GetPosition().X) + m_PlayerImage->GetCollider()->Get().w;
//        y1 = m_PlayerImage->GetCollider()->Get().y - Camera::GetInstance()->GetPosition().Y;
        p.x = x1 + (distance*x);
        p.y = y1 + (distance*y);
        Devider = Scaling(angle * 180/PI + 90,0.0,90.0,0.0,32.0);
        //SDL_Log("******************************************************************************* %f",Devider);
        box = { p.x + Devider ,p.y ,32,32 };
        SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),x1,y1,x1 + (distance*x),y1 + (distance*y));
    }
    else if (x >= 0 && y < 0)
    {
        x1 = m_PlayerImage->GetCollider()->Get().x + xd1;
        y1 = m_PlayerImage->GetCollider()->Get().y + yd1;
         /* SHOW COLLIDER */
//        x1 = (m_PlayerImage->GetCollider()->Get().x - Camera::GetInstance()->GetPosition().X ) + m_PlayerImage->GetCollider()->Get().w;
//        y1 = (m_PlayerImage->GetCollider()->Get().y - Camera::GetInstance()->GetPosition().Y ) + m_PlayerImage->GetCollider()->Get().h;
        p.x = x1 + (distance*x);
        p.y = y1 + (distance*y);
        Devider = Scaling(angle * 180/PI,0.0,90.0,0.0,32.0);
        box = { p.x + Devider ,p.y,32,32 };
        SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),x1,y1,x1 + (distance*x),y1 + (distance*y));
    }
    CollisionHandler::GetInstance()->CheckEnemyHitByPlayerBat(box);
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
}

void Knife::Reload()
{

}

int Knife::DealDamage()
{

}
