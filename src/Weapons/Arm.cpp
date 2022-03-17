#include "Arm.h"

Arm::Arm(float x, float y, double angle)
{
    m_Tf = new Transform("Arm",x,y,400,400,angle);
    m_Collider = new Collider();
    m_Collider->SetBuffer(0,0,0,0);
    m_Delete = false;
}

void Arm::Update(Soldier* player)
{
    m_Tf->X+=cos(m_Tf->m_Angle*(3.1415/180))*2;//10;
    m_Tf->Y+=sin(m_Tf->m_Angle*(3.1415/180))*2;//10;
    double sinN=sin(m_Tf->m_Angle*(3.1415/180))*155;
    double cosN=cos(m_Tf->m_Angle*(3.1415/180))*155;
    m_TestPoint.x = (int)(m_Tf->X + m_Tf->m_Width/2)+cosN;
    m_TestPoint.y = (int)(m_Tf->Y + m_Tf->m_Height/2)+sinN;
    m_Collider->SetBuffer(0,30,0,0);
    m_Collider->Set((m_Tf->X + m_Tf->m_Width/2)+(cosN-20),(m_Tf->Y + m_Tf->m_Height/2)+(sinN-20),40,40);

    if(CollisionHandler::GetInstance()->CheckCollision(m_Collider->Get(),player->GetCollider()->Get()))
    {
        player->ReciveDamage(40);
        m_Delete = true;
    }
    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())
       || CollisionHandler::GetInstance()->IsOutsideScreen(m_Collider->Get()))
    {
        m_Delete = true;
    }
}

void Arm::Draw()
{
    TextureMgr::GetInstance()->Draw(m_Tf);
    SDL_Rect coll = m_Collider->Get();
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&coll);
    SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),(int)m_Tf->X + m_Tf->m_Width/2,(int)m_Tf->Y + m_Tf->m_Height/2,m_TestPoint.x,m_TestPoint.y);
}

Arm::~Arm()
{
    delete m_Tf;
    delete m_Collider;
    m_Tf = nullptr;
    m_Collider = nullptr;
}
