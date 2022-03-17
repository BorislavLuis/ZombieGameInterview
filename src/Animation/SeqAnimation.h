#ifndef SEQANIMATION_H
#define SEQANIMATION_H

#include <vector>
#include <string>
#include <map>
#include "Animation.h"
#include "TextureMgr.h"
struct Sequence
{
    int Speed;
    int FrameCount;
    int Width,Height;
    std::vector<std::string> TextureIDs;
};

class SeqAnimation : public Animation
{
    public:
        SeqAnimation(bool repeat = true);

        virtual void Update();
        void Parse(std::string source);
        void SetCurrentSeq(std::string seqID);
        void SetRepeat(bool repeat) { m_Repeat = repeat; }
        void SetCurrentFrame(int frame) { m_CurrentFrame = frame;}
        void DrawFrame(Transform* tf);
        void DrawFrameTranparency(Transform* tf,int TransapencyValue);
        //virtual ~SeqAnimation();

    private:
        Sequence m_CurrentSeq;
        std::map<std::string, Sequence> m_SeqMap;

};

#endif // SEQANIMATION_H
