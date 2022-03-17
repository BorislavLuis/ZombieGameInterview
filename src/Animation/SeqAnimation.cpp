#include "SeqAnimation.h"


SeqAnimation::SeqAnimation(bool repeat):Animation(repeat){}

void SeqAnimation::DrawFrame(Transform* tf)
{
    tf->m_TextureID = m_CurrentSeq.TextureIDs[m_CurrentFrame];
    tf->m_Width = m_CurrentSeq.Width;
    tf->m_Height = m_CurrentSeq.Height;

    TextureMgr::GetInstance()->Draw(tf);
}

void SeqAnimation::Update()
{
    if(m_Repeat || !m_IsEnded)
    {
        m_IsEnded = false;
        m_CurrentFrame = (SDL_GetTicks()/m_CurrentSeq.Speed)% m_CurrentSeq.FrameCount;
    }

    if(!m_Repeat && m_CurrentFrame == (m_CurrentSeq.FrameCount-1))
    {
        m_IsEnded = true;
        m_CurrentFrame = (m_CurrentSeq.FrameCount-1);
    }
}

void SeqAnimation::SetCurrentSeq(std::string seqID)
{
    if(m_SeqMap.count(seqID)>0)
    {
        m_CurrentSeq = m_SeqMap[seqID];
    }
    else
    {
        SDL_Log("%s","The given sequence animation not matching!");
    }
}

void SeqAnimation::Parse(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error())
    {
        SDL_Log("%s","Failed to load file");
    }

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e = root->FirstChildElement(); e!=nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("sequence"))
        {
            Sequence seq;
            std::string seqID = e->Attribute("id");
            e->Attribute("speed",&seq.Speed);
            e->Attribute("width",&seq.Width);
            e->Attribute("height",&seq.Height);
            e->Attribute("frameCount",&seq.FrameCount);
            for(TiXmlElement* frame=e->FirstChildElement();frame!=nullptr ;frame = frame->NextSiblingElement())
            {
                seq.TextureIDs.push_back(frame->Attribute("textureID"));
                m_SeqMap[seqID] = seq;
            }
        }
    }
}
void SeqAnimation::DrawFrameTranparency(Transform* tf,int TransparencyValue)
{
    tf->m_TextureID = m_CurrentSeq.TextureIDs[m_CurrentFrame];
    tf->m_Width = m_CurrentSeq.Width;
    tf->m_Height = m_CurrentSeq.Height;

    TextureMgr::GetInstance()->DrawWithTransparancy(tf,TransparencyValue);
}



