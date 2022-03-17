#include "Play.h"

const std::string Play::m_PlayID = "PLAY";
extern Soldier* player;
Play::Play()
{

}

bool Play::Init()
{
    m_EditMode = false;
    m_NextLevel = false;
    m_Ctxt = Engine::GetInstance()->GetRender();

    if(!MapParser::GetInstance()->Load())
    {
        std::cout << "Failed to load map" << std::endl;
        return false;
    }
    TextureMgr::GetInstance()->ParseTextures("assets/textures.tml");
    m_LevelMap = LevelMgr::GetInstance()->LoadNextLevel(); //MapParser::GetInstance()->GetMaps(LevelMgr::GetInstance()->GetCurrentLevel());
    CollisionHandler::GetInstance()->SetCollisionLayers();
    LevelMgr::GetInstance()->LoadItems(player);
    m_GameObjects = LevelMgr::GetInstance()->LoadEnemies(player);

    Engine::GetInstance()->LoadGameObjects(m_GameObjects);
    Camera::GetInstance()->SetTarget(player->GetOrigin());
    SDL_Log("%s","Play State");
    return true;
}

bool Play::Exit()
{
    m_GameObjects.clear();
    TextureMgr::GetInstance()->Clean();
    Vector2D zeropoint;
    zeropoint.X = 1280;
    zeropoint.Y = 800;
    Camera::GetInstance()->SetTarget(&zeropoint);
    SDL_Log("%s","Exit Play");
    return true;
}

void Play::Update()
{
    Events();
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_GameObjects = Engine::GetInstance()->GetObjects();
    int SizeBefore,SizeAfter;
    for(int i = 0; i < m_GameObjects.size();i++)
    {
        SizeBefore = m_GameObjects.size();
        //SDL_Log("%s",m_GameObjects[i]->GetTransform()->m_TextureID.c_str());
        m_GameObjects = Engine::GetInstance()->GetObjects();
        SizeAfter = m_GameObjects.size();
        i = i - (SizeBefore - SizeAfter);
        if(m_GameObjects[i] != nullptr)
        {
            m_GameObjects[i]->Update(dt);
        }
        m_GameObjects = Engine::GetInstance()->GetObjects();
    }

    Engine::GetInstance()->LoadGameObjects(m_GameObjects);
    m_LevelMap->Update();
    if(m_GameObjects.size() < 2)
    {
        m_NextLevel = true;
    }
    if(m_NextLevel && player->IsLevelEnd())
    {
        m_NextLevel = false;
        player->SetLevelEnd(false);
        m_GameObjects.clear();
        Init();
    }
//    BulletHandler::GetInstance()->UpdatePlayerBullet();
//    CollisionHandler::GetInstance()->CheckEnemyPlayerBulletCollision();

    BulletHandler::GetInstance()->UpdateEnemyBullet();
    Camera::GetInstance()->SetTarget(player->GetOrigin());
    Camera::GetInstance()->Update(dt);

}

void Play::Render()
{
    SDL_SetRenderDrawColor(m_Ctxt,255,0,0,255);
    //SDL_SetRenderDrawColor(m_Ctxt,112,128,144,255);
    SDL_RenderClear(m_Ctxt);
    //TextureMgr::GetInstance()->Draw("Flor1",100,100,423,408);
    //StateMgr::GetInstance()->Render();
    m_LevelMap->Render();
    m_GameObjects = Engine::GetInstance()->GetObjects();
    std::vector<Puddle*> pud = ZombieL3::GetPuddles();

    for(int i = 0; i < pud.size();i++)
    {
        if(pud[i] != nullptr)
        {
            pud[i]->Draw();
        }
    }
    for(int i = 1; i < m_GameObjects.size();i++)
    {
        if(m_GameObjects[i] != nullptr)
        {
            m_GameObjects[i]->Draw();
            if(m_GameObjects[i]->IsDead())
            {
                Engine::GetInstance()->RemoveGameObject(m_GameObjects[i]);
            }
        }
    }
    BulletHandler::GetInstance()->DrawEnemyBullet();
    m_GameObjects[0]->Draw();
//    for(auto object : m_GameObjects)
//    {
//        if(object != nullptr)
//        {
//            object->Draw();
//            if(object->IsDead())
//            {
//                Engine::GetInstance()->RemoveGameObject(object);
//            }
//        }
//    }
    BulletHandler::GetInstance()->DrawPlayerBullet();
    SDL_RenderPresent(m_Ctxt);
}

Play::~Play()
{

}

void Play::Events()
{
    Input::GetInstance()->Listen();

//    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
//    {
//        StateMgr::GetInstance()->ChangeState(new Menu());
//    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_P))
    {
        StateMgr::GetInstance()->PushState(new Pause());
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_1))
    {
        player->StopAttack();
        if(player->GetWeaponCollection()[KNIFE])
        {
           player->m_Weapon = KNIFE;
        }
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_2))
    {
        player->StopAttack();
        if(player->GetWeaponCollection()[BAT])
        {
            player->m_Weapon = BAT;
        }
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_3))
    {
        player->StopAttack();
        if(player->GetWeaponCollection()[GUN])
        {
            player->m_Weapon = GUN;
        }
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_4))
    {
        player->StopAttack();
        if(player->GetWeaponCollection()[MACHINEGUN])
        {
            player->m_Weapon = MACHINEGUN;
        }

    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_5))
    {
        player->StopAttack();
        if(player->GetWeaponCollection()[FLAMETHROWER])
        {
            player->m_Weapon = FLAMETHROWER;
        }
    }
}
void Play::ClearGameObjects()
{
    std::vector<GameObject*>::iterator itr;
    for(itr = m_GameObjects.begin();itr != m_GameObjects.end();itr++)
    {
        delete *itr;
        *itr = nullptr;
    }
}
