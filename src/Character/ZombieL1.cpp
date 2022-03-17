#include "ZombieL1.h"
#include "Engine.h"

extern Soldier* player;
//std::vector<std::vector<Vector2D>> ZombieL1::m_SPaths;
ZombieL1::ZombieL1(Transform* tf, int path): GameObject(tf)
{
    m_RigidBody = new RigidBody();
    m_Collider = new Collider();
    m_Animation = new SpriteAnimation();
    m_Animation->SetProps(1,1,200);
    m_TextureIdle = tf->m_TextureID;
    m_NextAttackTime = 100;
    m_Attack = false;
    m_IsDeath = false;
    m_IsDying = false;
    m_IsCalled = false;
    m_CurrentPath = path;
    m_CurrentWaypoint = 0;
    m_CurrentState = PATROL;
    m_LastCoord.X = tf->X;
    m_LastCoord.Y = tf->Y;
    m_LastForBackTrackCalc.X = tf->X;
    m_LastForBackTrackCalc.Y = tf->Y;
    CreatePaths();
    m_DyingTime = 0;
    m_Angle = 0;
    m_Health.SetHealth(100);
    m_ObjectNumber++;
    m_ObjNum = m_ObjectNumber;
    m_Collider->m_Circle.x = (int)m_Tf->X + m_Tf->m_Width/2;
    m_Collider->m_Circle.y = (int)m_Tf->Y + m_Tf->m_Height/2;
    m_Collider->m_Circle.r = 50;
    m_Collider->m_HasCircleCollider = true;
}

void ZombieL1::Draw()
{
    if(!m_IsDying)  ///m_DyingTime <= 80)
    {
        m_Animation->Draw(m_Tf);
    }
    else if (!SDL_TICKS_PASSED(SDL_GetTicks(),m_CurrentTicks))
    {
        m_Animation->Draw(m_Tf);
    }
    else
    {
        m_IsDeath = true;
    }

    Vector2D cam = Camera::GetInstance()->GetPosition();

    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;

    SDL_Rect colliderposition = m_Collider->Get();

    SDL_Rect healtbar = {box.x - 20,box.y + colliderposition.h+30,m_Health.GetHealth(),5};


    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&healtbar);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRender(),255,0,0,0);
    SDL_RenderFillRect(Engine::GetInstance()->GetRender(),&healtbar);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRender(),152,251,152,255);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRender(),255,255,0,SDL_ALPHA_OPAQUE);


    for(int i = 0;i < 360;i++)
    {
        SDL_RenderDrawPoint(Engine::GetInstance()->GetRender(),m_Collider->m_Circle.x + cos(i*(3.1415/180))*m_Collider->m_Circle.r,m_Collider->m_Circle.y + sin(i*(3.1415/180))*m_Collider->m_Circle.r);
    }
//    //SDL_Log("8888888888888888888888888888888888888888888888888888-----------------%d", m_SPaths[m_CurrentPath].size());
//    for(int i = 0 ; i < m_SPaths[m_CurrentPath].size();i++)
//    {
//        //SDL_Log("-----------------------------XXXXXXXXXXXXXXXXXXXXXXXXX-----------------------------%f",m_SPaths[m_CurrentPath][i].X);
//        //SDL_Log("-----------------------------YYYYYYYYYYYYYYYYYYYYYYYYY-----------------------------%f",m_SPaths[m_CurrentPath][i].Y);
//        ///SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),m_SPaths[m_CurrentPath][i].X,m_SPaths[m_CurrentPath][i].Y,m_SPaths[m_CurrentPath][i+1].X,m_SPaths[m_CurrentPath][i+1].Y);
//    }
//    SDL_Point p[m_SPaths[m_CurrentPath].size()];
//    for(int i = 0 ; i < m_SPaths[m_CurrentPath].size()-1;i++)
//    {
//        //SDL_Log("----------------------------------------------------------%d",i);
//        p[i].x = m_SPaths[m_CurrentPath][i].X;
//        p[i].y = m_SPaths[m_CurrentPath][i].Y;
//    }
//
//    SDL_RenderDrawLines(Engine::GetInstance()->GetRender(),p,m_SPaths[m_CurrentPath].size()-2);

}

void ZombieL1::Update(float dt)
{
    if(Camera::GetInstance()->IsInViewPort(m_Tf))
    {
        if(m_Health.GetHealth() <= 0)
        {
            m_DyingTime++;
            m_IsDying = true;
        }
        if(!m_IsDying || !m_Attack)
        {
            m_Tf->m_TextureID = m_TextureIdle + "Idle";
            m_Animation->SetProps(1,1,200);
        }
        if(!m_IsCalled && m_IsDying )
        {
            m_IsCalled = true;
            m_CurrentTicks = SDL_GetTicks()+2000;
        }

        m_RigidBody->Update(0.5);
        m_LastSafePosition.X = m_Tf->X;
        m_Tf->X += m_RigidBody->Position().X;
        m_Collider->m_Circle.x = (int)m_Tf->X + m_Tf->m_Width/2;
        m_Collider->Set(m_Tf->X + ((m_Tf->m_Width/2) - (m_Collider->Get().w/2)),m_Tf->Y+(m_Tf->m_Height/2-m_Collider->Get().h/2),50,50);

        if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()) ||
           CollisionHandler::GetInstance()->CheckPlayerEnemyCollision(player,Engine::GetInstance()->GetObjects()) ||
           CollisionHandler::GetInstance()->CheckEnemyToEnemyCollision(this))
        {
            m_Tf->X = m_LastSafePosition.X;
        }

        m_RigidBody->Update(0.5);
        m_LastSafePosition.Y = m_Tf->Y;
        m_Tf->Y += m_RigidBody->Position().Y;
        m_Collider->m_Circle.y = (int)m_Tf->Y + m_Tf->m_Height/2;
        m_Collider->Set(m_Tf->X+(m_Tf->m_Width/2-m_Collider->Get().w/2),m_Tf->Y+(m_Tf->m_Height/2-m_Collider->Get().h/2),50,50);

        if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()) ||
           CollisionHandler::GetInstance()->CheckPlayerEnemyCollision(player,Engine::GetInstance()->GetObjects()) ||
           CollisionHandler::GetInstance()->CheckEnemyToEnemyCollision(this))
        {
            m_Tf->Y = m_LastSafePosition.Y;
        }

        float distance = m_Tf->m_Origin->Lenght(player->GetOrigin()->X,player->GetOrigin()->Y);
        distance = abs(distance);

        if(distance < 300)
        {
            m_Tf->m_Angle = atan2(player->GetOrigin()->Y - m_Tf->m_Origin->Y, player->GetOrigin()->X - m_Tf->m_Origin->X) * 180/PI;
            if(distance > 90)
            {
                m_Attack = false;

                ApplyForceX(m_Tf->m_Origin->X,player->GetOrigin()->X);
                ApplyForceY(m_Tf->m_Origin->Y,player->GetOrigin()->Y);

                m_Tf->m_TextureID = m_TextureIdle + "Walk";
                m_Animation->SetProps(1,6,200);

                if(m_LastCoord.X != m_Tf->X || m_LastCoord.Y != m_Tf->Y)
                {
                    m_LastCoord.X = m_Tf->X ;
                    m_LastCoord.Y = m_Tf->Y ;
                    m_BackTrack.push(m_LastCoord);
                }
            }
            else
            {
                m_RigidBody->UnsetForce();
                m_Attack = true;
            }
        }
        else
        {
            if(m_BackTrack.empty())
            {

                Vector2D v1,v2,res;
                v1 = m_SPaths[m_CurrentPath][m_CurrentWaypoint];
                v2.X = m_Tf->m_Origin->X;
                v2.Y = m_Tf->m_Origin->Y;
                res = v1.Normalized() - m_LastForPathCalc.Normalized();

                if(m_CurrentWaypoint < m_SPaths[m_CurrentPath].size())
                {
                    if((v1 - v2).MagnitudeSqr() < EPSILON)
                    {
                        m_CurrentWaypoint++;
                    }

                    if(m_LastForPathCalc.X != v1.X && m_LastForPathCalc.Y != v1.Y)
                    {
                        m_Tf->m_Angle = atan2(res.Y ,res.X) * 180/PI;
                        m_LastForPathCalc = v1;
                    }

                    ApplyForceX(m_Tf->m_Origin->X , v1.X);
                    ApplyForceY(m_Tf->m_Origin->Y , v1.Y);

                    m_Tf->m_TextureID = m_TextureIdle + "Walk";
                    m_Animation->SetProps(1,6,200);
                }
                else
                {

                    v1 = m_SPaths[m_CurrentPath][0];
                    v2.X = m_Tf->m_Origin->X;
                    v2.Y = m_Tf->m_Origin->Y;
                    if((int)v1.X == (int)v2.X && (int)v1.Y == (int)v2.Y )
                    {
                        m_CurrentWaypoint=0;
                    }
                    res = v1.Normalized() - v2.Normalized();
                    m_Tf->m_Angle = atan2(res.Y ,res.X) * 180/PI;

                    m_Tf->m_TextureID = m_TextureIdle + "Walk";
                    m_Animation->SetProps(1,6,200);
                    ApplyForceX(m_Tf->m_Origin->X , v1.X);
                    ApplyForceY(m_Tf->m_Origin->Y , v1.Y);
                }
            }
            else
            {
                m_LastCoord = m_BackTrack.top();
                Vector2D result;

                result = m_LastCoord - m_LastForBackTrackCalc ;
                result = result.Normalized();

                m_Tf->m_Angle = atan2(result.Y , result.X ) * 180/PI ;

                m_Tf->m_TextureID = m_TextureIdle + "Walk";
                m_Animation->SetProps(1,6,200);
                m_BackTrack.pop();

                m_LastForBackTrackCalc.X = m_Tf->X;
                m_LastForBackTrackCalc.Y = m_Tf->Y;

                m_Tf->SetCoord(m_LastCoord);
            }
        }
        m_Tf->m_Origin->X = m_Tf->X + m_Tf->m_Width/2;
        m_Tf->m_Origin->Y = m_Tf->Y + m_Tf->m_Height/2;

        AnimationState();
        m_Animation->Update();
    }

}

void ZombieL1::AnimationState()
{
    if(m_Attack && !m_IsDying)
    {
        m_Tf->m_TextureID = m_TextureIdle + "Attack";
        m_Animation->SetProps(1,7,200);
        if(m_NextAttackTime == 0)
        {
            player->ReciveDamage(10);
            m_NextAttackTime = 100;
        }
        else
        {
           m_NextAttackTime--;
        }
        m_Animation->Update();
    }
    if(m_IsDying)
    {
        m_Tf->m_TextureID = m_TextureIdle + "Dead";
        m_Animation->SetProps(1,5,500);
    }
}

void ZombieL1::Clean()
{
    delete m_RigidBody;
    delete m_Animation;
    delete m_Collider;
    m_RigidBody = nullptr;
    m_Animation = nullptr;
    m_Collider = nullptr;
}
void ZombieL1::ReciveDamage(int damage)
{
    if(m_Health.GetHealth() - damage > 0 )
    {
        m_Health.DealDamage(damage);
    }
    else
    {
        m_Health.SetHealth(0);
    }
}
ZombieL1::~ZombieL1()
{
    if((m_RigidBody != nullptr) && (m_Animation != nullptr) && (m_Collider != nullptr))
    {
        Clean();
    }
}
void ZombieL1::HandlePatrolState()
{
    //if(m_SPaths[m_CurrentPath][m_CurrentWaypoint]-)
    //m_CurrentWaypoint++;
}
void ZombieL1::CreatePaths()
{
    float screenMidPoint = SCREEN_WIDTH * 0.4f;
    int currentPath = 0;
    BezierPaths* path = new BezierPaths();
    float Xcenter,Ycenter;
    Xcenter = m_Tf->m_Origin->X;
    Ycenter = m_Tf->m_Origin->Y;
    //path->AddCurve({Vector2D(Xcenter,Ycenter),Vector2D(Xcenter+15.0f,Ycenter-20.0f),Vector2D(Xcenter+30.0f,Ycenter-30.0f),Vector2D(Xcenter+65.0f,Ycenter-30.0f)},200);
//    path->AddCurve({Vector2D(Xcenter,Ycenter),Vector2D(Xcenter+20,Ycenter-45),Vector2D(Xcenter+40,Ycenter-45),Vector2D(Xcenter+75,Ycenter-53)},100);
//    path->AddCurve({Vector2D(Xcenter+75,Ycenter-53),Vector2D(Xcenter+93.0f,Ycenter-50.0f),Vector2D(Xcenter+108.0f,Ycenter-42.0f),Vector2D(Xcenter+113.0f,Ycenter-33.0f)},100);
//    path->AddCurve({Vector2D(Xcenter+113.0f,Ycenter-33.0f),Vector2D(Xcenter+118.0f,Ycenter-20.0f),Vector2D(Xcenter+113.0f,Ycenter),Vector2D(Xcenter+98.0f,Ycenter+3.0f)},100);
//    path->AddCurve({Vector2D(Xcenter+98.0f,Ycenter+3.0f),Vector2D(Xcenter+93.0f,Ycenter+55.0f),Vector2D(Xcenter+70.0f,Ycenter+97.0f),Vector2D(Xcenter+30.0f,Ycenter+148.0f)},100);
//    path->AddCurve({Vector2D(Xcenter+30.0f,Ycenter+148.0f),Vector2D(Xcenter-5.0f,Ycenter+182.0f),Vector2D(Xcenter-50.0f,Ycenter+184.0f),Vector2D(Xcenter-90.0f,Ycenter+194.0f)},100);
//    path->AddCurve({Vector2D(Xcenter-90.0f,Ycenter+194.0f),Vector2D(Xcenter-125.0f,Ycenter+182.0f),Vector2D(Xcenter-125.0f,Ycenter+139.0f),Vector2D(Xcenter-100.0f,Ycenter+119.0f)},100);
//    path->AddCurve({Vector2D(Xcenter-100.0f,Ycenter+119.0f),Vector2D(Xcenter-80.0f,Ycenter+107.0f),Vector2D(Xcenter-65.0f,Ycenter+97.0f),Vector2D(Xcenter,Ycenter)},100);
// ----------------------------------- PATH 1 -------------------------------
    path->AddCurve({Vector2D(Xcenter,Ycenter),Vector2D(Xcenter-18,Ycenter+20),Vector2D(Xcenter-33,Ycenter+95),Vector2D(Xcenter-48,Ycenter+125)},100);
    path->AddCurve({Vector2D(Xcenter-48,Ycenter+125),Vector2D(Xcenter-58,Ycenter+155),Vector2D(Xcenter-93,Ycenter+230),Vector2D(Xcenter-108,Ycenter+265)},100);
    path->AddCurve({Vector2D(Xcenter-108,Ycenter+265),Vector2D(Xcenter-130,Ycenter+300),Vector2D(Xcenter-130,Ycenter+340),Vector2D(Xcenter-170,Ycenter+370)},100);
    m_SPaths.push_back(std::vector<Vector2D>());
    path->Sample(&m_SPaths[currentPath]);
    currentPath++;
    delete path;
    path = new BezierPaths();
// ----------------------------------- PATH 2 -------------------------------
    path->AddCurve({Vector2D(Xcenter,Ycenter),Vector2D(Xcenter-18,Ycenter+20),Vector2D(Xcenter-33,Ycenter+95),Vector2D(Xcenter-48,Ycenter+125)},100);
    path->AddCurve({Vector2D(Xcenter-48,Ycenter+125),Vector2D(Xcenter-58,Ycenter+155),Vector2D(Xcenter-93,Ycenter+230),Vector2D(Xcenter-108,Ycenter+265)},100);
    path->AddCurve({Vector2D(Xcenter-108,Ycenter+265),Vector2D(Xcenter-130,Ycenter+340),Vector2D(Xcenter-93,Ycenter+370),Vector2D(Xcenter,Ycenter+370)},100);
    path->AddCurve({Vector2D(Xcenter,Ycenter+370),Vector2D(Xcenter,Ycenter+370),Vector2D(Xcenter+100,Ycenter+370),Vector2D(Xcenter+100,Ycenter+370)},100);
    path->AddCurve({Vector2D(Xcenter+100,Ycenter+370),Vector2D(Xcenter+100,Ycenter+377),Vector2D(Xcenter+20,Ycenter+377),Vector2D(Xcenter,Ycenter+377)},100);
    path->AddCurve({Vector2D(Xcenter,Ycenter+377),Vector2D(Xcenter-93,Ycenter+370),Vector2D(Xcenter-130,Ycenter+370),Vector2D(Xcenter-130,Ycenter+265)},100);
    path->AddCurve({Vector2D(Xcenter-130,Ycenter+265),Vector2D(Xcenter-108,Ycenter+230),Vector2D(Xcenter-93,Ycenter+155),Vector2D(Xcenter-58,Ycenter+125)},100);
    path->AddCurve({Vector2D(Xcenter-58,Ycenter+125),Vector2D(Xcenter-33,Ycenter+20),Vector2D(Xcenter-18,Ycenter),Vector2D(Xcenter,Ycenter)},100);
    m_SPaths.push_back(std::vector<Vector2D>());
    path->Sample(&m_SPaths[currentPath]);
    delete path;
}
void ZombieL1::ApplyForceX(float a,float b)
{
    if(a < b)
    {
        m_RigidBody->ApplyForceX(3*FORWARD);
    }
    if(a > b)
    {
        m_RigidBody->ApplyForceX(3*BACKWARD);
    }
}
void ZombieL1::ApplyForceY(float a,float b)
{
    if(a < b)
    {
        m_RigidBody->ApplyForceY(3*DOWNWARD);
    }
    if(a > b)
    {
        m_RigidBody->ApplyForceY(3*UPWARD);
    }
}
