#include "HealtBox.h"

HealtBox::HealtBox(Transform* tf, Collider* coll, SpriteAnimation* sp):m_Tf(tf),m_Collider(coll),m_Anim(sp)
{
    m_Collider->Set(m_Tf->X+25,m_Tf->Y+25,50,47);
    m_Anim->SetProps(1,4,500);
}


void HealtBox::OnNotify(Soldier* player)
{
    player->RegenerateHealt(25);
}

void HealtBox::Draw()
{
    m_Anim->Draw(m_Tf);
    SDL_Rect box = m_Collider->Get();
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
}

void HealtBox::Update(float dt)
{
    m_Anim->Update();
}

void HealtBox::Clean()
{
    delete m_Tf;
    delete m_Anim;
    delete m_Collider;
    m_Tf = nullptr;
    m_Anim = nullptr;
    m_Collider = nullptr;
}


HealtBox::~HealtBox()
{

}
