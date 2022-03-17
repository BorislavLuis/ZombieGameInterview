#include "LevelEnd.h"

LevelEnd::LevelEnd(Transform* tf, Collider* coll, SpriteAnimation* sp):m_Tf(tf),m_Collider(coll),m_Anim(sp)
{
    m_Collider->Set(m_Tf->X,m_Tf->Y,64,64);
    m_Anim->SetProps(1,2,500);
}

void LevelEnd::OnNotify(Soldier* player)
{
    player->SetLevelEnd(true);
}

void LevelEnd::Draw()
{
    m_Anim->Draw(m_Tf);
//    SDL_Rect box = m_Collider->Get();
//    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
}

void LevelEnd::Update(float dt)
{
    m_Anim->Update();
}

void LevelEnd::Clean()
{
    delete m_Tf;
    delete m_Anim;
    delete m_Collider;
    m_Tf = nullptr;
    m_Anim = nullptr;
    m_Collider = nullptr;
}
LevelEnd::~LevelEnd()
{

}
