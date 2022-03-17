#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include "Animation.h"
#include <SDL.h>
#include "TextureMgr.h"
#include "Transform.h"
class SpriteAnimation: public Animation
{
    public:
        SpriteAnimation(bool repeat = true);

        virtual void Update();
        void Draw(Transform* tf);
        void SetProps(int spriteRow,int frame,int animSpeed);
        //virtual ~SpriteAnimation();

    private:

        int m_SpriteRow;
        int m_AnimSpeed;
        int m_FrameCount;
        int m_SpriteFrame;
};

#endif // SPRITEANIMATION_H
