#include "Snot.h"
#include <chrono>
auto tt1 = std::chrono::system_clock::now();
auto tt2 = std::chrono::system_clock::now();
Snot::Snot(float x, float y, double angle)
{
    m_Tf = new Transform("Snot",x,y,200,200,angle);
    m_Animation = new SeqAnimation(true);
    m_Animation->Parse("assets/Weapons/SnotAnim.tml");
    m_Animation->SetCurrentSeq("Snot");
    m_Animation->SetCurrentFrame(0);
    m_Collider = new Collider();
    m_Collider->SetBuffer(0,0,0,0);
    m_Collider->Set(x,y,16,16);
    m_InitX = x;
    m_InitY = y;
    m_ElapsedTime = 0.0f;
    m_TimeFrame2 = 300;
    m_TimeFrame3 = 300;
    m_Delete = false;
}

void Snot::Update(Soldier* soldier)
{


    double sinN=sin(m_Tf->m_Angle*(3.1415/180))*32;
    double cosN=cos(m_Tf->m_Angle*(3.1415/180))*32;
    switch(m_Animation->GetCurrentFrame())
    {
        case 0:
            if(m_Tf->X > m_InitX + 100 || m_Tf->X  < m_InitX - 100 || m_Tf->Y > m_InitY + 100 || m_Tf->Y < m_InitY - 100)
            {
                m_Animation->SetCurrentFrame(1);
            }
            m_ColCenter.x = int((m_Tf->X + m_Tf->m_Width/2) + cosN);
            m_ColCenter.y = int((m_Tf->Y + m_Tf->m_Height/2) + sinN);
            m_Collider->Set(m_ColCenter.x - 8,m_ColCenter.y - 8,16,16);
            Move();

        break;
        case 1:
            if( CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()) || CollisionHandler::GetInstance()->IsOutsideScreen(m_Collider->Get()))
            {
                m_Animation->SetCurrentFrame(2);
            }
            if(CollisionHandler::GetInstance()->CheckCollision(soldier->GetCollider()->Get(),m_Collider->Get()))
            {
                soldier->ReciveDamage(20);
                m_Animation->SetCurrentFrame(2);
            }
            else
            {
                m_Collider->Set((int)(m_Tf->X + m_Tf->m_Width/2) - 10,(int)(m_Tf->Y + m_Tf->m_Height/2) - 10,20,20);
                Move();
            }

            break;
        case 2:
            {
                tt2 = std::chrono::system_clock::now();
                std::chrono::duration<float> elapsedTime = tt2 - tt1;
                tt1 = tt2;
                m_ElapsedTime += elapsedTime.count();
                if(m_ElapsedTime >= 0.5)
                {
                    m_ElapsedTime = 0.0f;
                    m_Animation->SetCurrentFrame(3);
                }
            }
            break;
        case 3:
            {
                tt2 = std::chrono::system_clock::now();
                std::chrono::duration<float> elapsedTime = tt2 - tt1;
                tt1 = tt2;
                m_ElapsedTime += elapsedTime.count();
                if(m_ElapsedTime >= 0.5)
                {
                    m_ElapsedTime = 0.0f;
                    m_Delete = true;
                }
            }
            //m_TimeFrame3--;
            break;
    }
}

void Snot::Draw()
{
    m_Animation->DrawFrame(m_Tf);
//    SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),(int)m_Tf->m_Origin->X,(int)m_Tf->m_Origin->Y,m_ColCenter.x,m_ColCenter.y);
//    SDL_Rect coll = m_Collider->Get();
//    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&coll);
}

void Snot::Move()
{

    m_Tf->X+=cos(m_Tf->m_Angle*(3.1415/180))*10;
    m_Tf->Y+=sin(m_Tf->m_Angle*(3.1415/180))*10;
}

Snot::~Snot()
{
    delete m_Tf;
    delete m_Animation;
    delete m_Collider;
    m_Tf = nullptr;
    m_Animation = nullptr;
    m_Collider = nullptr;
}
