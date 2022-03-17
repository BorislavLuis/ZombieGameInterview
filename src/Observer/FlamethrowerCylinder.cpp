#include "FlamethrowerCylinder.h"

FlamethrowerCylinder::FlamethrowerCylinder(Transform* tf, Collider* coll, SpriteAnimation* sp):m_Tf(tf),m_Collider(coll),m_Anim(sp)
{
    m_Collider->Set(m_Tf->X,m_Tf->Y+5,70,90);
    m_Anim->SetProps(1,2,500);
}


void FlamethrowerCylinder::OnNotify(Soldier* player)
{

}

void FlamethrowerCylinder::Draw()
{
    m_Anim->Draw(m_Tf);
//    SDL_Rect box = m_Collider->Get();
//    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
}

void FlamethrowerCylinder::Update(float dt)
{
    m_Anim->Update();
}

void FlamethrowerCylinder::Clean()
{
    delete m_Tf;
    delete m_Anim;
    delete m_Collider;
    m_Tf = nullptr;
    m_Anim = nullptr;
    m_Collider = nullptr;
}

FlamethrowerCylinder::~FlamethrowerCylinder()
{

}
