#include "MachineGunItem.h"

MachineGunItem::MachineGunItem(Transform* tf, Collider* coll, SpriteAnimation* sp):m_Tf(tf),m_Collider(coll),m_Anim(sp)
{
    m_Collider->Set(m_Tf->X+5,m_Tf->Y+20,300,60);
    m_Anim->SetProps(1,2,500);
}

void MachineGunItem::OnNotify(Soldier* player)
{
    player->AddWeapon(new MachineGun(player,7,100,15),MACHINEGUN);
}

void MachineGunItem::Draw()
{
    m_Anim->Draw(m_Tf);
//    SDL_Rect box = m_Collider->Get();
//    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
}

void MachineGunItem::Update(float dt)
{
    m_Anim->Update();
}

void MachineGunItem::Clean()
{
    delete m_Tf;
    delete m_Anim;
    delete m_Collider;
    m_Tf = nullptr;
    m_Anim = nullptr;
    m_Collider = nullptr;
}
MachineGunItem::~MachineGunItem()
{

}
