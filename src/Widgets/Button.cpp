#include "Button.h"

Button::Button(int x,int y,void (*callback)(),TextureIDList textrIDs):GameObject(new Transform())
{
    m_Tf->X = x;
    m_Tf->Y = y;
    m_Callback = callback;
    m_TextrIDs = textrIDs;
    m_Tf->m_TextureID = m_TextrIDs[NORMAL];
    TextureMgr::GetInstance()->QueryTexture(m_Tf->m_TextureID,&m_Tf->m_Width,&m_Tf->m_Height);
    m_Shape = { m_Tf->X,m_Tf->Y,m_Tf->m_Width,m_Tf->m_Height};
    m_IsReleased = true;
//    m_Tf->m_CurrentFrame = NORMAL;
//    m_Tf->m_CurrentRow = 1;
}

void Button::Update(float dt)
{
    Vector2D pMousePosition = Input::GetInstance()->GetMousePosition();
    SDL_Point point = {pMousePosition.X,pMousePosition.Y};

    if(SDL_PointInRect(&point,&m_Shape))
    {
        if(Input::GetInstance()->GetMouseButtonDown(LEFTB) && m_IsReleased)
        {
            m_Tf->m_TextureID = m_TextrIDs[PRESSED];
            m_IsReleased = false;
            m_Callback();

        }
        else if(!Input::GetInstance()->GetMouseButtonDown(LEFTB))
        {
            m_IsReleased = true;
            m_Tf->m_TextureID = m_TextrIDs[HOVER];
        }
    }
    else
    {
        m_Tf->m_TextureID = m_TextrIDs[NORMAL];
    }

}
void Button::Draw()
{
    TextureMgr::GetInstance()->DrawFrame(m_Tf,1,m_Tf->m_CurrentFrame);
}
void Button::Clean()
{

}
Button::~Button()
{
    GameObject::Clean();
}
