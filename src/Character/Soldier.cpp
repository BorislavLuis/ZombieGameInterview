#include "Soldier.h"
#include "TextureMgr.h"
#include <SDL.h>
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "Engine.h"
#include "Mathematics.h"
#include <chrono>
auto t1 = std::chrono::system_clock::now();
auto t2 = std::chrono::system_clock::now();
int Soldier::m_BulletsInPlay = 0;
Soldier::Soldier(Transform* tf):GameObject(tf)
{
    m_Collider = new Collider();
    //m_Collider->SetBuffer(-70,-30,0,0);
    m_Collider->SetBuffer(-175,-75,0,0);
    m_RigidBody = new RigidBody();
    m_Animation = new SpriteAnimation();
    m_Animation->SetProps(1,6,200);
    m_BatAttack = false;
    m_Dir = RIGHT;
    m_Weapons.resize(5);
    m_HealthStatus = new Transform("HealthStatus",10,10,500,45);
    m_Health.SetHealth(100);
    m_Subject = new Subject();
    m_ObjectNumber++;
    m_ObjNum = m_ObjectNumber;

}

Soldier::~Soldier()
{
    delete m_Collider;
    delete m_Animation;
    delete m_RigidBody;
    delete m_Subject;
    m_Animation=nullptr;
    m_RigidBody=nullptr;
    m_Collider=nullptr;
    m_Subject=nullptr;
}

void Soldier::Draw()
{
    m_Animation->Draw(m_Tf);
    Vector2D cam = Camera::GetInstance()->GetPosition();
    //SDL_Rect dest2 = {this->GetOrigin()->X + Camera::GetInstance()->GetViewPort().x,this->GetOrigin()->Y + Camera::GetInstance()->GetViewPort().y,m_HealthStatus->m_Width,m_HealthStatus->m_Height};
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
    m_Subject->Notify(this);
    int HealthWidth = 0;
    HealthWidth = Scaling(m_Health.GetHealth(),0,100,0,m_HealthStatus->m_Width-20);

    SDL_Rect dest = {((int)m_HealthStatus->X + 10) - (int)cam.X,((int)m_HealthStatus->Y + 5) - (int)cam.Y ,HealthWidth/*-15*/,m_HealthStatus->m_Height-15};
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&dest);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRender(),255,0,0,0);
    SDL_RenderFillRect(Engine::GetInstance()->GetRender(),&dest);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRender(),152,251,152,255);

    CheckIntems(cam);

    TextureMgr::GetInstance()->Draw(m_HealthStatus);
//    if(m_UnderAttack )//&& m_Counter > 0)
//    {
//        TextureMgr::GetInstance()->Draw2("Blood");
//        //m_UnderAttack = false;
//        //SDL_Delay(1000);
//    }

}

void Soldier::Update(float dt)
{
    t2 = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsedTime = t2 - t1;
    t1 = t2;
    float fElapsedTime = elapsedTime.count();
    fElapsedTime = Scaling(fElapsedTime,0.0f,0.060f,0.7f,1.5f);
    m_Animation->SetProps(1,1,200);
    m_RigidBody->UnsetForce();
    m_HealthStatus->X = (SCREEN_WIDTH/4 + m_HealthStatus->m_Width/2) + Camera::GetInstance()->GetPosition().X;
    m_HealthStatus->Y = Camera::GetInstance()->GetPosition().Y + 10;
    m_Tf->m_Angle = atan2(Camera::GetInstance()->GetPosition().Y + Input::GetInstance()->GetMousePosition().Y - m_Tf->m_Origin->Y, Camera::GetInstance()->GetPosition().X + Input::GetInstance()->GetMousePosition().X - m_Tf->m_Origin->X) * 180/PI;

    //SDL_Log("%f,%f,%f,%f",m_Origin->Y,m_Origin->X,Camera::GetInstance()->GetPosition().Y+SCREEN_HEIGHT, Camera::GetInstance()->GetPosition().X + Input::GetInstance()->GetMousePosition().X );

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        WeaponChanger();
        m_RigidBody->ApplyForceX(5*BACKWARD);
        m_Animation->SetProps(1,6,200);
        m_Dir = LEFT;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        WeaponChanger();
        m_RigidBody->ApplyForceX(5*FORWARD);
        //m_Tf->m_TextureID = "BatWalk";
        m_Animation->SetProps(1,6,200);
        m_Dir = RIGHT;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
    {
        WeaponChanger();
        m_RigidBody->ApplyForceY(5*UPWARD);
        //m_Tf->m_TextureID = "BatWalk";
        m_Animation->SetProps(1,6,200);
        m_Dir = UP;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
    {
        WeaponChanger();
        m_RigidBody->ApplyForceY(5*DOWNWARD);
        //m_Tf->m_TextureID = "BatWalk";
        m_Animation->SetProps(1,6,200);
        m_Dir = DOWN;
    }
    switch(m_Weapon)
    {
        case KNIFE: if(Input::GetInstance()->GetMouseButtonDown(LEFTB) && m_Items[KNIFE]) { m_KnifeAttack = true; } else { m_KnifeAttack = false; } break;
        case BAT: if(Input::GetInstance()->GetMouseButtonDown(LEFTB) && m_Items[BAT]) { m_BatAttack = true; } else { m_BatAttack = false; } break;
        case GUN: if(Input::GetInstance()->GetMouseButtonDown(LEFTB) && m_Items[GUN] ) { m_GunShot = true; UpdateGunAttack(); } else { m_GunShot = false; UpdateGunAttack(); }  break;
        case MACHINEGUN: if(Input::GetInstance()->GetMouseButtonDown(LEFTB) && m_Items[MACHINEGUN] ) { m_MachineGunShot = true; } else { m_MachineGunShot = false; } break;
        case FLAMETHROWER: if(Input::GetInstance()->GetMouseButtonDown(LEFTB) && m_Items[FLAMETHROWER]) { m_FlamethrowerAttack = true; } else { m_FlamethrowerAttack = false; } break;
//        case KNIFE: if(Input::GetInstance()->GetMouseButtonDown(LEFTB) && m_Weapons[KNIFE] != NULL) { m_KnifeAttack = true; } else { m_KnifeAttack = false; } break;
//        case BAT: if(Input::GetInstance()->GetMouseButtonDown(LEFTB) && m_Weapons[BAT] != NULL) { m_BatAttack = true; } else { m_BatAttack = false; } break;
//        case GUN: if(Input::GetInstance()->GetMouseButtonDown(LEFTB) && m_Weapons[GUN] != NULL) { m_GunShot = true; } else { m_GunShot = false; }  break;
//        case MACHINEGUN: if(Input::GetInstance()->GetMouseButtonDown(LEFTB) && m_Weapons[MACHINEGUN] != NULL ) { m_MachineGunShot = true; } else { m_MachineGunShot = false; } break;
//        case FLAMETHROWER: if(Input::GetInstance()->GetMouseButtonDown(LEFTB) && m_Weapons[FLAMETHROWER] != NULL) { m_FlamethrowerAttack = true; } else { m_FlamethrowerAttack = false; } break;

    }
    MapProps* ptr = MapParser::GetInstance()->GetMapProps(LevelMgr::GetInstance()->GetCurrentLevel());
    m_RigidBody->Update(fElapsedTime/*0.7*/);

    m_LastSafePosition.X = m_Tf->X;
    m_Tf->X += m_RigidBody->Position().X;
    //m_Collider->Set(m_Tf->X+25,m_Tf->Y+10,30,30);
    m_Collider->Set(m_Tf->X,m_Tf->Y,52,52);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())||
       CollisionHandler::GetInstance()->CheckPlayerEnemyCollision(this,Engine::GetInstance()->GetObjects())||
       m_Collider->Get().x + m_Collider->Get().w > ptr->ColCount*ptr->TileSize ||
       m_Collider->Get().x < 0 )
    {
        m_Tf->X = m_LastSafePosition.X;
    }

    m_RigidBody->Update(fElapsedTime/*0.7*/);
    m_LastSafePosition.Y = m_Tf->Y;
    m_Tf->Y += m_RigidBody->Position().Y;
    //m_Collider->Set(m_Tf->X+25,m_Tf->Y+10,30,30);
    m_Collider->Set(m_Tf->X ,m_Tf->Y ,52,52);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()) ||
       CollisionHandler::GetInstance()->CheckPlayerEnemyCollision(this,Engine::GetInstance()->GetObjects())||
       m_Collider->Get().y + m_Collider->Get().h > (ptr->RowCount*ptr->TileSize)-ptr->TileSize ||
       m_Collider->Get().y < 0)
    {
        m_Tf->Y = m_LastSafePosition.Y;
    }

    m_Tf->m_Origin->X = m_Tf->X + m_Tf->m_Width/2;
    m_Tf->m_Origin->Y = m_Tf->Y + m_Tf->m_Height/2;
    if(m_BulletsInPlay > 0)
    {
        BulletHandler::GetInstance()->UpdatePlayerBullet();
        CollisionHandler::GetInstance()->CheckEnemyPlayerBulletCollision();
    }
    //SDL_Log("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX------%f, YYYYYYYYYYYYYYYYYYYYYYYYYYYYYY-------%f",m_Tf->m_Origin->X,m_Tf->m_Origin->Y);
    WeaponChanger();
    AnimationState();
    m_Animation->Update();

}

void Soldier::AnimationState()
{
    if(m_KnifeAttack)
    {
        m_Tf->m_TextureID = "KnifeAttack"+m_CharacterType;
        m_Animation->SetProps(1,7,80);
        m_Weapons[KNIFE]->Attack();
        for(int i = 0; i < 7; i++)
        {
           m_Animation->Update();
        }
    }

    if(m_BatAttack)
    {
        m_Tf->m_TextureID = "BatAttack"+m_CharacterType;
        m_Animation->SetProps(1,7,80);
        m_Weapons[BAT]->Attack();
//        for(int i = 0; i < 7; i++)
//        {
//            m_Animation->Update();
//        }
    }
    //int tim = 0;
    if(m_GunShot)
    {

        m_Tf->m_TextureID = "GunShot"+m_CharacterType;
        m_Animation->SetProps(1,5,150);
        m_Weapons[GUN]->Attack();
//        for(int i = 0; i < 5; i++)
//        {
//            m_Animation->Update();
//        }
    }

    if(m_MachineGunShot)
    {
        m_Tf->m_TextureID = "MachineGunShot"+m_CharacterType;
        m_Animation->SetProps(1,4,80);
        for(int i = 0; i < 7; i++)
        {
           m_Animation->Update();
        }
    }

    if(m_FlamethrowerAttack)
    {
        m_Tf->m_TextureID = "FlamethrowerAttack"+m_CharacterType;
        m_Animation->SetProps(1,5,80);
        m_Weapons[FLAMETHROWER]->Attack();
//        for(int i = 0; i < 7; i++)
//        {
//           m_Animation->Update();
//        }
    }
}

void Soldier::Clean()
{
    TextureMgr::GetInstance()->Drop(m_Tf->m_TextureID);

}
void Soldier::WeaponChanger()
{
    switch(m_Weapon)
    {
        case KNIFE: m_Tf->m_TextureID = "KnifeWalk"+m_CharacterType; break;
        case BAT: m_Tf->m_TextureID = "BatWalk"+m_CharacterType; break;
        case GUN: m_Tf->m_TextureID = "GunWalk"+m_CharacterType; break;
        case MACHINEGUN: m_Tf->m_TextureID = "MachineGunWalk"+m_CharacterType; break;
        case FLAMETHROWER: m_Tf->m_TextureID = "FlamethrowerWalk"+m_CharacterType; break;
    }
}
void Soldier::StopAttack()
{
    m_GunShot = false;
    m_KnifeAttack = false;
    m_MachineGunShot = false;
    m_BatAttack = false;
    m_FlamethrowerAttack = false;
}
void Soldier::ReciveDamage(int damage)
{
    if(m_Health.GetHealth() - damage > 0)
    {
        m_UnderAttack = true;
        m_Health.DealDamage(damage);
    }
    else
    {
        m_Health.SetHealth(0);
        m_Death = true;
    }

}
void Soldier::CheckIntems(Vector2D camera)
{
    for(unsigned int i = 0; i < m_Weapons.size();i++)
    {
        if(m_Weapons[i]!=NULL)
        {
            Transform* tf = m_Weapons[i]->GetTransform();
            tf->X = i*64 + camera.X ;
            tf->Y = 10 + camera.Y;
            TextureMgr::GetInstance()->Draw(tf);
            //Render Weapon Collider
//            if(i == FLAMETHROWER)
//            {
//                m_Weapons[i]->Attack();
//            }
        }
    }
}
void Soldier::AddWeapon(Weapons* arm,Weapon wep)
{
    if(m_Weapons[wep] != NULL)
    {
        delete m_Weapons[wep];
        m_Weapons[wep] = nullptr;
        m_Weapons[wep] = arm;
    }
    else
    {
       m_Weapons[wep] = arm;
    }
    m_Items[wep] = true;
}
void Soldier::RegenerateHealt(int health)
{
    if((health + m_Health.GetHealth()) > 100)
    {
        m_Health.SetHealth(100);
    }
    else
    {
        m_Health.RegenerateHealth(health);
    }
}
void Soldier::UpdateGunAttack()
{
    BulletHandler::GetInstance()->UpdatePlayerBullet();
    CollisionHandler::GetInstance()->CheckEnemyPlayerBulletCollision();
}
