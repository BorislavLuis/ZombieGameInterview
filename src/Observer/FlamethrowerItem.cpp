#include "FlamethrowerItem.h"

FlamethrowerItem::FlamethrowerItem(Transform* tf, Collider* coll, SpriteAnimation* sp):m_Tf(tf),m_Collider(coll),m_Anim(sp)
{
    m_Collider->Set(m_Tf->X+25,m_Tf->Y+10,260,80);
    m_Anim->SetProps(1,2,500);
}


void FlamethrowerItem::OnNotify(Soldier* player)
{
    player->AddWeapon(new Flamethrower(player,7,100,15),FLAMETHROWER);
}

void FlamethrowerItem::Draw()
{
    m_Anim->Draw(m_Tf);
//    SDL_Rect box = m_Collider->Get();
//    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
}

void FlamethrowerItem::Update(float dt)
{
    m_Anim->Update();
}

void FlamethrowerItem::Clean()
{
    delete m_Tf;
    delete m_Anim;
    delete m_Collider;
    m_Tf = nullptr;
    m_Anim = nullptr;
    m_Collider = nullptr;
}

FlamethrowerItem::~FlamethrowerItem()
{

}
