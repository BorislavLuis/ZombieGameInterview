#include "GameObject.h"

int GameObject:: m_ObjectNumber = 0;

void GameObject::Draw()
{
    TextureMgr::GetInstance()->Draw(m_Tf);
}

void GameObject::Update(float dt)
{
    m_Tf->m_Origin->X = m_Tf->X + m_Tf->m_Width/2;
    m_Tf->m_Origin->Y = m_Tf->Y + m_Tf->m_Height/2;
}

void GameObject::Clean()
{
    delete m_Tf;
    m_Tf = nullptr;
}
Collider* GameObject::GetCollider()
{

}
GameObject::~GameObject()
{
    if(m_Tf != nullptr)
    {
        Clean();
    }
}

