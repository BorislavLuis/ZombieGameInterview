#include "GunItem.h"

GunItem::GunItem(Transform* tf, Collider* coll, SpriteAnimation* sp):m_Tf(tf),m_Collider(coll),m_Anim(sp)
{
    m_Collider->Set(m_Tf->X,m_Tf->Y+25,100,50);
    m_Anim->SetProps(1,4,500);
}


void GunItem::OnNotify(Soldier* player)
{
    player->AddWeapon(new Gun(player,20,100,15),GUN);
}

void GunItem::Draw()
{
    m_Anim->Draw(m_Tf);
//    SDL_Rect box = m_Collider->Get();
//    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
}

void GunItem::Update(float dt)
{
    m_Anim->Update();
}

void GunItem::Clean()
{
    delete m_Tf;
    delete m_Anim;
    delete m_Collider;
    m_Tf = nullptr;
    m_Anim = nullptr;
    m_Collider = nullptr;
}

GunItem::~GunItem()
{
    //dtor
}
