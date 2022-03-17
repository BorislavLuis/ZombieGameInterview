#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(bool repeat):Animation(repeat){}

void SpriteAnimation::Update()
{
    m_CurrentFrame = (SDL_GetTicks()/m_AnimSpeed)%m_FrameCount;
}

void SpriteAnimation::Draw(Transform* tf)
{
    TextureMgr::GetInstance()->DrawFrame(tf,m_SpriteRow,m_CurrentFrame);
}

void SpriteAnimation::SetProps(int spriteRow, int frame, int animSpeed)
{
    m_SpriteRow = spriteRow;
    m_FrameCount = frame;
    m_AnimSpeed = animSpeed;
}
