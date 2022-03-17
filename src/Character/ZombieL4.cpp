#include "ZombieL4.h"
#include "Mathematics.h"
extern Soldier* player;

//std::vector<Collider> ZombieL4::m_Colliders;
ZombieL4::ZombieL4(Transform* tf,int path):GameObject(tf)
{
    m_RigidBody = new RigidBody();
    m_Collider = new Collider();
    m_Animation = new SpriteAnimation();
    m_Animation->SetProps(1,1,200);
    m_TextureIdle = tf->m_TextureID;
    m_NextAttack1Time = 100;
    m_NextAttack2Time = 200;
    m_Attack1 = false;
    m_Attack2 = false;
    m_IsDeath = false;
    m_IsDying = false;
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
    m_Health.SetHealth(500);
    m_ObjectNumber++;
    m_ObjNum = m_ObjectNumber;

    m_SeqAnimation = new SeqAnimation(true);
    m_SeqAnimation->Parse("assets/Zombies/SeqAnim/AnimationLvl4Boss.tml");
    m_SeqAnimation->SetCurrentSeq(tf->m_TextureID + "Idle");

//    m_Collider->SetPolygon(m_Tf->m_Origin,m_Tf->m_Angle);
//    Vector2D coord = {-27,-63};
//    m_Collider->PushInPolygonModelVector(coord);
//    coord = {-36,-59};
//    m_Collider->PushInPolygonModelVector(coord);
//    coord = {-43,-50};
//    m_Collider->PushInPolygonModelVector(coord);
//    coord = {-50,-35};
//    m_Collider->PushInPolygonModelVector(coord);
//    coord = {-56,-9};
//    m_Collider->PushInPolygonModelVector(coord);
//    coord = {-50,17};
//    m_Collider->PushInPolygonModelVector(coord);
//    coord = {-37,39};
//    m_Collider->PushInPolygonModelVector(coord);
//    coord = {-24,44};
//    m_Collider->PushInPolygonModelVector(coord);
//    coord = {26,51};
//    m_Collider->PushInPolygonModelVector(coord);
//    coord = {98,56};
//    m_Collider->PushInPolygonModelVector(coord);
//    coord = {111,38};
//    m_Collider->PushInPolygonModelVector(coord);
//    coord = {111,-66};
//    m_Collider->PushInPolygonModelVector(coord);
//    coord = {101,-82};
//    m_Collider->PushInPolygonModelVector(coord);
//    coord = {-27,-63};
//    m_Collider->PushInPolygonModelVector(coord);
    m_Collider->m_Polygon.pos.X = m_Tf->m_Origin->X;
    m_Collider->m_Polygon.pos.Y = m_Tf->m_Origin->Y;
    m_Collider->m_Polygon.angle = m_Tf->m_Angle;
    m_Collider->m_Polygon.o.push_back({-27,-63});
    m_Collider->m_Polygon.o.push_back({-36,-59});
    m_Collider->m_Polygon.o.push_back({-43,-50});
    m_Collider->m_Polygon.o.push_back({-50,-35});
    m_Collider->m_Polygon.o.push_back({-56,-9});
    m_Collider->m_Polygon.o.push_back({-50,17});
    m_Collider->m_Polygon.o.push_back({-37,39});
    m_Collider->m_Polygon.o.push_back({-24,44});
    m_Collider->m_Polygon.o.push_back({26,51});
    m_Collider->m_Polygon.o.push_back({98,56});
    m_Collider->m_Polygon.o.push_back({111,38});
    m_Collider->m_Polygon.o.push_back({111,-66});
    m_Collider->m_Polygon.o.push_back({101,-82});
    m_Collider->m_Polygon.o.push_back({-27,-63});

    m_Collider->m_Polygon.p.push_back({-27,-63});
    m_Collider->m_Polygon.p.push_back({-36,-59});
    m_Collider->m_Polygon.p.push_back({-43,-50});
    m_Collider->m_Polygon.p.push_back({-50,-35});
    m_Collider->m_Polygon.p.push_back({-56,-9});
    m_Collider->m_Polygon.p.push_back({-50,17});
    m_Collider->m_Polygon.p.push_back({-37,39});
    m_Collider->m_Polygon.p.push_back({-24,44});
    m_Collider->m_Polygon.p.push_back({26,51});
    m_Collider->m_Polygon.p.push_back({98,56});
    m_Collider->m_Polygon.p.push_back({111,38});
    m_Collider->m_Polygon.p.push_back({111,-66});
    m_Collider->m_Polygon.p.push_back({101,-82});
    m_Collider->m_Polygon.p.push_back({-27,-63});
//    m_Polygon.o.push_back({-55,-54});
//    m_Polygon.o.push_back({-67,-47});
//    m_Polygon.o.push_back({-79,-27});
//    m_Polygon.o.push_back({-84,-2});
//    m_Polygon.o.push_back({-78,25});
//    m_Polygon.o.push_back({-67,47});
//    m_Polygon.o.push_back({-54,52});
//    m_Polygon.o.push_back({-7,60});
//    m_Polygon.o.push_back({72,125});
//    m_Polygon.o.push_back({83,48});
//    m_Polygon.o.push_back({85,-56});
//    m_Polygon.o.push_back({79,-68});
//    m_Polygon.o.push_back({71,-74});
//    m_Polygon.o.push_back({-55,-54});
    m_Collider->m_HasPolygonCollider = true;
    m_Collider->m_Polygon.overlap = false;
    m_Collider->m_HasCircleCollider = true;
    m_Collider->m_Circle.r = 65;
    m_Collider->m_Circle.x = (int)m_Tf->X + m_Tf->m_Width/2 + 5;
    m_Collider->m_Circle.y = (int)m_Tf->Y + m_Tf->m_Height/2 - 10;
}

void ZombieL4::Draw()
{
    if(!m_IsDying)  ///m_DyingTime <= 80)
    {
        m_SeqAnimation->Update();
        m_SeqAnimation->DrawFrame(m_Tf);
        //m_Animation->Draw(m_Tf);
    }
    else if (!SDL_TICKS_PASSED(SDL_GetTicks(),m_CurrentTicks))
    {
        m_SeqAnimation->DrawFrame(m_Tf);
        //m_Animation->Draw(m_Tf);
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
    int HealthScalled = Scaling(m_Health.GetHealth(),0,500,0,100);
    SDL_Rect healtbar = {box.x - 20,box.y + colliderposition.h+30,HealthScalled,5};


    //SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&healtbar);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRender(),255,0,0,0);
    SDL_RenderFillRect(Engine::GetInstance()->GetRender(),&healtbar);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRender(),152,251,152,255);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRender(),255,255,0,SDL_ALPHA_OPAQUE);

    for(int i = 0;i < 360;i++)
    {
        SDL_RenderDrawPoint(Engine::GetInstance()->GetRender(),m_Collider->m_Circle.x + cos(i*(3.1415/180))*m_Collider->m_Circle.r,m_Collider->m_Circle.y + sin(i*(3.1415/180))*m_Collider->m_Circle.r);
    }
//    for(int i = 0; i < m_Collider->m_Polygon.p.size();i++)
//    {
//        //SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),(int)m_Collider->GetPolygon()->p[i].X,(int)m_Collider->GetPolygon()->p[i].Y,(int)m_Collider->GetPolygon()->p[(i+1)%m_Collider->GetPolygon()->p.size()].X,(int)m_Collider->GetPolygon()->p[(i+1)%m_Collider->GetPolygon()->p.size()].Y);
//        SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),(int)m_Collider->m_Polygon.p[i].X,(int)m_Collider->m_Polygon.p[i].Y,(int)m_Collider->m_Polygon.p[(i+1)%m_Collider->m_Polygon.p.size()].X,(int)m_Collider->m_Polygon.p[(i+1)%m_Collider->m_Polygon.p.size()].Y);
//    }
}

void ZombieL4::Update(float dt)
{
    if(Camera::GetInstance()->IsInViewPort(m_Tf))
    {
        if(m_Health.GetHealth() <= 0)
        {
            m_DyingTime++;
            m_IsDying = true;
        }
        if(!m_IsDying || !m_Attack1 || !m_Attack2)
        {
            m_Tf->m_TextureID = m_TextureIdle + "Idle";
            m_SeqAnimation->SetCurrentSeq(m_Tf->m_TextureID);
            //m_Animation->SetProps(1,1,200);
        }
        if(!m_IsCalled && m_IsDying )
        {
            m_IsCalled = true;
            m_CurrentTicks = SDL_GetTicks()+2000;
        }

        m_RigidBody->Update(0.5);
        m_LastSafePosition.X = m_Tf->X;
        m_Tf->X += m_RigidBody->Position().X;


        m_Collider->m_Circle.x = (int)m_Tf->X + m_Tf->m_Width/2 + 5;




        m_Collider->Set(m_Tf->X + ((m_Tf->m_Width/2) - (m_Collider->Get().w/2)),m_Tf->Y+(m_Tf->m_Height/2-m_Collider->Get().h/2),70,70);

        if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()) ||
           CollisionHandler::GetInstance()->CheckPlayerEnemyCollision(player,Engine::GetInstance()->GetObjects()) ||
           CollisionHandler::GetInstance()->CheckEnemyToEnemyCollision(this))
        {
            //m_RigidBody->UnsetForce();
            //m_Tf->X -= m_RigidBody->Position().X + 5;// + 10;
            m_Tf->X = m_LastSafePosition.X;
        }

        m_RigidBody->Update(0.5);
        m_LastSafePosition.Y = m_Tf->Y;
        m_Tf->Y += m_RigidBody->Position().Y;
        m_Collider->m_Circle.y = (int)m_Tf->Y + m_Tf->m_Height/2 - 10;
        m_Collider->Set(m_Tf->X+(m_Tf->m_Width/2-m_Collider->Get().w/2),m_Tf->Y+(m_Tf->m_Height/2-m_Collider->Get().h/2),70,70);

        if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()) ||
           CollisionHandler::GetInstance()->CheckPlayerEnemyCollision(player,Engine::GetInstance()->GetObjects()) ||
           CollisionHandler::GetInstance()->CheckEnemyToEnemyCollision(this))
        {
            //m_RigidBody->UnsetForce();
            //m_Tf->Y -= m_RigidBody->Position().Y + 5;// + 10;
            m_Tf->Y = m_LastSafePosition.Y;
        }

        float distance = m_Tf->m_Origin->Lenght(player->GetOrigin()->X,player->GetOrigin()->Y);
        distance = abs(distance);

        if(distance < 300)
        {
            m_Tf->m_Angle = atan2(player->GetOrigin()->Y - m_Tf->m_Origin->Y, player->GetOrigin()->X - m_Tf->m_Origin->X) * 180/PI;
            if(distance > 110 && !m_Attack2)
            {
                m_Attack1 = false;

                ApplyForceX(m_Tf->m_Origin->X,player->GetOrigin()->X);
                ApplyForceY(m_Tf->m_Origin->Y,player->GetOrigin()->Y);

                m_Tf->m_TextureID = m_TextureIdle + "Walk";
                m_SeqAnimation->SetCurrentSeq(m_Tf->m_TextureID);
                //m_Animation->SetProps(1,6,200);

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
                m_Attack1 = true;
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
                    m_SeqAnimation->SetCurrentSeq(m_Tf->m_TextureID);
                    //m_Animation->SetProps(1,6,200);
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
                    m_SeqAnimation->SetCurrentSeq(m_Tf->m_TextureID);
                    //m_Animation->SetProps(1,6,200);
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

                if(m_Tf->m_Angle > m_Angle + 180 && m_Tf->m_Angle > m_Angle - 180)
                {
                    m_Tf->m_Angle = m_Angle;
                }
                m_Tf->m_TextureID = m_TextureIdle + "Walk";
                m_SeqAnimation->SetCurrentSeq(m_Tf->m_TextureID);
                //m_Animation->SetProps(1,6,200);
                m_BackTrack.pop();

                m_LastForBackTrackCalc.X = m_Tf->X;
                m_LastForBackTrackCalc.Y = m_Tf->Y;

                m_Tf->SetCoord(m_LastCoord);
            }
        }
        m_Tf->m_Origin->X = m_Tf->X + m_Tf->m_Width/2;
        m_Tf->m_Origin->Y = m_Tf->Y + m_Tf->m_Height/2;

        m_NextAttack2Time--;
        if(m_NextAttack2Time <= 0)
        {
            m_Attack2 = true;
            m_NextAttack2Time = 200;
        }
        AnimationState();
        m_SeqAnimation->Update();
        //m_Collider->SetPolygon(m_Tf->m_Origin,m_Tf->m_Angle);
//        m_Collider->m_Polygon.pos.X = m_Tf->m_Origin->X ; //m_RigidBody->Position().X;
//        m_Collider->m_Polygon.pos.Y = m_Tf->m_Origin->Y; //m_RigidBody->Position().Y;
//        m_Collider->m_Polygon.angle = m_Tf->m_Angle;
//        for(int i = 0; i < m_Collider->m_Polygon.o.size();i++)
//        {
////            Vector2D vect = {
////                              (m_Collider->GetPolygon()->o[i].X * cos(m_Tf->m_Angle*(3.1415/180)) - m_Collider->GetPolygon()->o[i].Y * sin(m_Tf->m_Angle*(3.1415/180))) + m_Collider->GetPolygon()->pos.X,
////                              (m_Collider->GetPolygon()->o[i].X * sin(m_Tf->m_Angle*(3.1415/180)) + m_Collider->GetPolygon()->o[i].Y * cos(m_Tf->m_Angle*(3.1415/180))) + m_Collider->GetPolygon()->pos.Y
////                             };
////            m_Collider->PushInPolygonProjectVectorByPos(vect,i);
//            m_Collider->m_Polygon.p[i] = {
//                              (m_Collider->m_Polygon.o[i].X * cos(m_Tf->m_Angle*(3.1415/180)) - m_Collider->m_Polygon.o[i].Y * sin(m_Tf->m_Angle*(3.1415/180))) + m_Collider->m_Polygon.pos.X,
//                              (m_Collider->m_Polygon.o[i].X * sin(m_Tf->m_Angle*(3.1415/180)) + m_Collider->m_Polygon.o[i].Y * cos(m_Tf->m_Angle*(3.1415/180))) + m_Collider->m_Polygon.pos.Y
//                             };
//        }
        //m_Animation->Update();
    }
}

void ZombieL4::AnimationState()
{
    if(m_Attack1 && !m_IsDying)
    {
        m_Tf->m_TextureID = m_TextureIdle + "Attack1";
        m_SeqAnimation->SetCurrentSeq(m_Tf->m_TextureID);
        //m_Animation->SetProps(1,9,200);
        if(m_NextAttack1Time == 0)
        {
            player->ReciveDamage(40);
            m_NextAttack1Time = 100;
        }
        else
        {
           m_NextAttack1Time--;
        }
        m_SeqAnimation->Update();
        //m_Animation->Update();
    }
    if(m_Attack2 && !m_IsDying)
    {
        m_Tf->m_TextureID = m_TextureIdle + "Attack2";
        m_SeqAnimation->SetCurrentSeq(m_Tf->m_TextureID);
        if(m_SeqAnimation->GetCurrentFrame() == 10)
        {
            m_Attack2 = false;
        }

        if(m_SeqAnimation->GetCurrentFrame() == 8 && m_FrameForAttack2)
        {
            //m_FrameForAttack3 = false;
            m_ColliderBullet.SetBuffer(0,0,0,0);
            int x,y;
            x = m_Tf->m_Origin->X + cos(m_Tf->m_Angle)*100;
            y = m_Tf->m_Origin->Y + sin(m_Tf->m_Angle)*50;
            //m_ColliderBullet.Set((int)m_Tf->m_Origin->X,(int)m_Tf->m_Origin->Y,40,40);
            m_ColliderBullet.Set(x,y,40,40);
            Bullet* bl = new Bullet(m_Tf->m_Origin,Vector2D(0.1,0.1),m_ColliderBullet,{m_TextureIdle+"Meat_0",m_TextureIdle+"Meat_1"});
            bl->SetCoordinate(x,y,m_Tf->m_Angle);
            BulletHandler::GetInstance()->AddEnemyBullet(bl);///new Bullet(m_Tf->m_Origin,Vector2D(5,5),col,{"Puddle","Puddle2"}));
            m_FrameForAttack2 = false;
        }
        if(m_SeqAnimation->GetCurrentFrame() != 8)
        {
            m_FrameForAttack2 = true;
        }
        m_SeqAnimation->Update();
        //m_Animation->SetProps(1,9,200);
//        if(m_NextAttack2Time == 0)
//        {
//            player->ReciveDamage(40);
//            m_NextAttack2Time = 100;
//        }
//        else
//        {
//           m_NextAttack2Time--;
//        }
        //m_SeqAnimation->Update();
        //m_Animation->Update();
    }
    if(m_IsDying)
    {
        m_Tf->m_TextureID = m_TextureIdle + "Dead";
        m_SeqAnimation->SetCurrentSeq(m_Tf->m_TextureID);
        //m_Animation->SetProps(1,6,300);
    }
}

void ZombieL4::Clean()
{

    delete m_RigidBody;
    delete m_Animation;
    delete m_Collider;
    m_RigidBody = nullptr;
    m_Animation = nullptr;
    m_Collider = nullptr;

}

void ZombieL4::ReciveDamage(int damage)
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

ZombieL4::~ZombieL4()
{
    if((m_RigidBody != nullptr) && (m_Animation != nullptr) && (m_Collider != nullptr))
    {
        Clean();
    }
}
void ZombieL4::HandlePatrolState()
{

}

void ZombieL4::CreatePaths()
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

void ZombieL4::ApplyForceX(float a, float b)
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

void ZombieL4::ApplyForceY(float a, float b)
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

void ZombieL4::ParseColliderCoord(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error())
    {
        SDL_Log("Failed to load Puddle collider coordinate file!");
    }
    TiXmlElement* root = xml.RootElement();
    int i = 1;
    int row;
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        std::string s;
        s = e->Value();
        s = s.substr(1,s.size()-1);
        row = stoi(s);
        if(row == i)
        {
            Collider col;
            col.SetBuffer(0,0,0,0);
            int w,h,indent;
            e->Attribute("W",&w);
            e->Attribute("H",&h);
            e->Attribute("INDENT",&indent);
            col.Set((int)m_Tf->X,(int)m_Tf->Y,w,h);
            //m_Colliders.push_back(col);
            //m_Indent.push_back(indent);
            i++;
        }
    }

}
