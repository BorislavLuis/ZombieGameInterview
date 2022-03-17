#include "Camera.h"

Camera* Camera::s_Instance = nullptr;

void Camera::Update(float dt)
{
    MapProps* ptr;
    if(LevelMgr::GetInstance()->GetCurrentLevel() == "")
    {
        ptr = MapParser::GetInstance()->GetMapProps("level1");
    }
    else
    {
        ptr = MapParser::GetInstance()->GetMapProps(LevelMgr::GetInstance()->GetCurrentLevel());
    }

    if(m_Target != nullptr)
    {
        m_ViewPort.x = (int)m_Target->X - (SCREEN_WIDTH/2);
        m_ViewPort.y = (int)m_Target->Y - (SCREEN_HEIGHT/2);
        m_ViewPort.w = SCREEN_WIDTH; //(ptr->ColCount*ptr->TileSize)/2;
        m_ViewPort.h = SCREEN_HEIGHT; //(ptr->RowCount*ptr->TileSize)/2;

        if(m_ViewPort.x < 0)
        {
            m_ViewPort.x = 0;
        }
        if(m_ViewPort.y < 0)
        {
            m_ViewPort.y = 0;
        }
        if(m_ViewPort.x > ((ptr->ColCount*ptr->TileSize)) - m_ViewPort.w)
        {
            m_ViewPort.x = (((ptr->ColCount*ptr->TileSize)) - m_ViewPort.w);
        }
        if(m_ViewPort.y > (((ptr->RowCount*ptr->TileSize)) - m_ViewPort.h))
        {
            m_ViewPort.y = (((ptr->RowCount*ptr->TileSize)) - m_ViewPort.h);
        }

//        if(m_ViewPort.x > (2*SCREEN_WIDTH - m_ViewPort.w))
//        {
//            m_ViewPort.x = (2*SCREEN_WIDTH - m_ViewPort.w);
//        }
//        if(m_ViewPort.y > (4*SCREEN_HEIGHT - m_ViewPort.h))
//        {
//            m_ViewPort.y = (4*SCREEN_HEIGHT - m_ViewPort.h);
//        }
        m_Position = Vector2D(m_ViewPort.x,m_ViewPort.y);
    }

}
bool Camera::IsInViewPort(Transform* tf)
{
    return ((tf->X + tf->m_Width > m_Position.X)&&(tf->X < m_Position.X + SCREEN_WIDTH)) && ((tf->Y + tf->m_Height > m_Position.Y)&&(tf->Y < m_Position.Y + SCREEN_HEIGHT));
}
