#include "Claw.h"

Claw::Claw(float x, float y, double angle)
{
//    if(angle > 0 && angle <= 90)
//    {
//        m_Tf = new Transform("Claws",x+200,y+200,400,400,angle);
//    }
//    else if (angle > 90 && angle <= 180)
//    {
//        m_Tf = new Transform("Claws",x,y+200,400,400,angle);
//    }
//    else if (angle > -180 && angle <= -90)
//    {
//        m_Tf = new Transform("Claws",x-200,y,400,400,angle);
//    }
//    else if (angle > -90 && angle <= 0)
//    {
//        m_Tf = new Transform("Claws",x,y-200,400,400,angle);
//    }
    m_Tf = new Transform("Claws",x,y,400,400,angle);
    m_Collider1 = new Collider();
    m_Collider2 = new Collider();
    m_Collider1->SetBuffer(0,0,0,0);
    m_Collider2->SetBuffer(0,0,0,0);
    m_ForDelete = false;


    double sinN=sin((m_Tf->m_Angle-90)*(3.1415/180))*60;
    double cosN=cos((m_Tf->m_Angle-90)*(3.1415/180))*60;
    m_Collider1->m_HasCircleCollider = true;
    m_Collider2->m_HasCircleCollider = true;
    m_Collider1->m_Circle.x = m_Tf->m_Origin->X + cosN;
    m_Collider1->m_Circle.y = m_Tf->m_Origin->Y + sinN;
    m_Collider1->Set((m_Tf->m_Origin->X - 17) + cosN,(m_Tf->m_Origin->Y-17) + sinN,34,34);
    sinN=sin((m_Tf->m_Angle+90)*(3.1415/180))*60;
    cosN=cos((m_Tf->m_Angle+90)*(3.1415/180))*60;
    m_Collider2->m_Circle.x = m_Tf->m_Origin->X + cosN;
    m_Collider2->m_Circle.y = m_Tf->m_Origin->Y + sinN;
    m_Collider2->Set((m_Tf->m_Origin->X - 17) + cosN,(m_Tf->m_Origin->Y-17) + sinN,34,34);
    m_Collider1->m_Circle.r = 25;
    m_Collider2->m_Circle.r = 25;
}

void Claw::Update(Soldier* player)
{
    m_Tf->X+=cos(m_Tf->m_Angle*(3.1415/180))*2;//10;
    m_Tf->Y+=sin(m_Tf->m_Angle*(3.1415/180))*2;//10;
    double sinN=sin((m_Tf->m_Angle-90)*(3.1415/180))*60;
    double cosN=cos((m_Tf->m_Angle-90)*(3.1415/180))*60;
    m_Collider1->m_Circle.x = m_Tf->X + m_Tf->m_Width/2 + cosN;
    m_Collider1->m_Circle.y = m_Tf->Y + m_Tf->m_Height/2 + sinN;
    m_Collider1->Set((m_Tf->X + m_Tf->m_Width/2 - 17) + cosN,(m_Tf->Y + m_Tf->m_Height/2-17) + sinN,34,34);
    sinN=sin((m_Tf->m_Angle+90)*(3.1415/180))*60;
    cosN=cos((m_Tf->m_Angle+90)*(3.1415/180))*60;
    m_Collider2->m_Circle.x = m_Tf->X + m_Tf->m_Width/2 + cosN;
    m_Collider2->m_Circle.y = m_Tf->Y + m_Tf->m_Height/2 + sinN;
    m_Collider2->Set((m_Tf->X + m_Tf->m_Width/2 - 17) + cosN,(m_Tf->Y + m_Tf->m_Height/2-17) + sinN,34,34);

    if(CollisionHandler::GetInstance()->CheckBoxCircleCollision(m_Collider1->m_Circle,player->GetCollider()->Get()) ||
       CollisionHandler::GetInstance()->CheckBoxCircleCollision(m_Collider2->m_Circle,player->GetCollider()->Get()))
    {
        player->ReciveDamage(40);
        m_ForDelete = true;
    }
    if(CollisionHandler::GetInstance()->MapCollision(m_Collider1->Get()) || CollisionHandler::GetInstance()->MapCollision(m_Collider2->Get())
       || CollisionHandler::GetInstance()->IsOutsideScreen(m_Collider1->Get()) || CollisionHandler::GetInstance()->IsOutsideScreen(m_Collider2->Get()))
    {
        m_ForDelete = true;
    }
}

void Claw::Draw()
{
    TextureMgr::GetInstance()->Draw(m_Tf);
    //SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),(int)m_Tf->m_Origin->X,(int)m_Tf->m_Origin->Y,m_ColCenter.x,m_ColCenter.y);
    for(int i = 0;i < 360;i++)
    {
        SDL_RenderDrawPoint(Engine::GetInstance()->GetRender(),m_Collider1->m_Circle.x + cos(i*(3.1415/180))*m_Collider1->m_Circle.r,m_Collider1->m_Circle.y + sin(i*(3.1415/180))*m_Collider1->m_Circle.r);
        SDL_RenderDrawPoint(Engine::GetInstance()->GetRender(),m_Collider2->m_Circle.x + cos(i*(3.1415/180))*m_Collider2->m_Circle.r,m_Collider2->m_Circle.y + sin(i*(3.1415/180))*m_Collider2->m_Circle.r);
    }
    SDL_Rect coll1 = m_Collider1->Get();
    SDL_Rect coll2 = m_Collider2->Get();
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&coll1);
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&coll2);
}

Claw::~Claw()
{
    delete m_Collider1;
    delete m_Collider2;
    delete m_Tf;
    m_Collider1 = nullptr;
    m_Collider2 = nullptr;
    m_Tf = nullptr;
}
