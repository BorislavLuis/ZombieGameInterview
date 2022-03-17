#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <SDL.h>
class Animation
{
    public:
        Animation(bool repeat = true):m_Repeat(repeat){ m_IsEnded = false; }
        virtual void Update() = 0;
        inline bool IsEnded(){return m_IsEnded;}
        inline int GetCurrentFrame() { return m_CurrentFrame;}
        virtual ~Animation(){};
    protected:
        bool m_Repeat;
        bool m_IsEnded;
        int m_CurrentFrame;
};

#endif // ANIMATION_H
