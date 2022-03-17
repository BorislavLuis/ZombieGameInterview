#include "BatItem.h"

BatItem::BatItem(Transform* tf, Collider* coll, SpriteAnimation* sp):m_Tf(tf),m_Collider(coll),m_Anim(sp)
{
    m_Collider->Set(m_Tf->X+5,m_Tf->Y+5,20,130);
    m_Anim->SetProps(1,2,500);
}

void BatItem::OnNotify(Soldier* player)
{
    player->AddWeapon(new Bat(player,7,100,15),BAT);
}

void BatItem::Draw()
{
    m_Anim->Draw(m_Tf);
//    SDL_Rect box = m_Collider->Get();
//    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
}

void BatItem::Update(float dt)
{
    m_Anim->Update();
}

void BatItem::Clean()
{
    delete m_Tf;
    delete m_Anim;
    delete m_Collider;
    m_Tf = nullptr;
    m_Anim = nullptr;
    m_Collider = nullptr;
}

BatItem::~BatItem()
{

}

