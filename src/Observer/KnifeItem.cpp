#include "KnifeItem.h"

KnifeItem::KnifeItem(Transform* tf, Collider* coll, SpriteAnimation* sp):m_Tf(tf),m_Collider(coll),m_Anim(sp)
{
    m_Collider->Set(m_Tf->X,m_Tf->Y,62,80);
    m_Anim->SetProps(1,4,500);
}

void KnifeItem::OnNotify(Soldier* player)
{
    player->AddWeapon(new Knife(player,20,100,15),KNIFE);
}

void KnifeItem::Draw()
{
    m_Anim->Draw(m_Tf);
    SDL_Rect box = m_Collider->Get();
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&box);
}

void KnifeItem::Update(float dt)
{
    m_Anim->Update();
}

void KnifeItem::Clean()
{
    delete m_Tf;
    delete m_Anim;
    delete m_Collider;
    m_Tf = nullptr;
    m_Anim = nullptr;
    m_Collider = nullptr;
}

KnifeItem::~KnifeItem()
{
    Clean();
}
