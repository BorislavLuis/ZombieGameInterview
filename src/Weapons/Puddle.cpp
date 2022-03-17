#include "Puddle.h"
#include "CollisionHandler.h"

Puddle::Puddle(float x,float y,int destX,int destY,double angle)
{
    m_Collider = new Collider();
    m_Tf = new Transform("Puddle",x,y,200,200,angle);
    m_Animation = new SeqAnimation(true);
    m_MapPtr = MapParser::GetInstance()->GetMapProps(LevelMgr::GetInstance()->GetCurrentLevel());
    m_Animation->Parse("assets/Zombies/SeqAnim/Puddle.tml");
    ParseColliderCoord("assets/Zombies/SeqAnim/PuddleColliderCoord.tml");
    m_Animation->SetCurrentSeq("Puddle");
    m_Animation->SetCurrentFrame(0);
    m_Collider->SetBuffer(0,0,0,0);
    m_Collider->Set((int)x + 100,(int)y + 100,95,150);
    m_ScallingFactorTransp = 2000;
    m_TransparencyValue = 255;
    m_MapCollision = false;
    m_OutsideScreen = false;
    m_FrameConsecutive = 0;
    m_FrameTime = 0;
    m_DestX = destX;
    m_DestY = destY;
    if(angle > 0 && angle <= 90)
    {
        m_Quad = FIRST;
        m_DestX = (int)m_Tf->X + m_DestX;
        m_DestY = (int)m_Tf->Y + m_DestY;
        m_BeforeX = m_DestX - 50;
        m_BeforeY = m_DestY - 50;
    }
    else if (angle > 90 && angle <= 180)
    {
        m_Quad = SECOND;
        m_DestX = (int)m_Tf->X - m_DestX;
        m_DestY = (int)m_Tf->Y + m_DestY;
        m_BeforeX = m_DestX + 50;
        m_BeforeY = m_DestY - 50;
    }
    else if (angle > -180 && angle <= -90)
    {
        m_Quad = THIRD;
        m_DestX = (int)m_Tf->X - m_DestX;
        m_DestY = (int)m_Tf->Y - m_DestY;
        m_BeforeX = m_DestX + 50;
        m_BeforeY = m_DestY + 50;
    }
    else if (angle > -90 && angle <= 0)
    {
        m_Quad = FOURTH;
        m_DestX = (int)m_Tf->X + m_DestX;
        m_DestY = (int)m_Tf->Y - m_DestY;
        m_BeforeX = m_DestX - 50;
        m_BeforeY = m_DestY + 50;
    }
    //SDL_Log("%d DEST---X *******  %d DEST---Y",m_DestX,m_DestY);
    //SDL_Log("%d BEF---XXX ******* %d BEF---YYY",m_BeforeX,m_BeforeY);
    //ShiftCollider();

}
void Puddle::Draw()
{
    m_Animation->DrawFrameTranparency(m_Tf,m_TransparencyValue);
//    SDL_Rect coll1 = m_Collider->Get();
//    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&coll1);
//    for(int i = 0; i < m_Colliders.size();i++)
//    {
//        SDL_Log("%d X---X *******  %d Y---Y  %d W---W   %d H---H",m_Colliders[i]->Get().x,m_Colliders[i]->Get().y,m_Colliders[i]->Get().w,m_Colliders[i]->Get().h);
//        SDL_Rect coll = m_Colliders[i]->Get();
//        SDL_RenderDrawRect(Engine::GetInstance()->GetRender(),&coll);
//    }
}

void Puddle::Update(Soldier* soldier)
{
    if(m_Collider->Get().x + m_Collider->Get().w > m_MapPtr->ColCount*m_MapPtr->TileSize || m_Collider->Get().x < 0 ||
       m_Collider->Get().y + m_Collider->Get().h > (m_MapPtr->RowCount*m_MapPtr->TileSize)-m_MapPtr->TileSize || m_Collider->Get().y < 0)
    {
        m_OutsideScreen = true;
    }
    switch (m_Animation->GetCurrentFrame())
    {
        case 0:
                m_Animation->SetCurrentFrame(0);
                Move();
                //SDL_Log("%d XXXXXXXXXXXXXX *******  %d YYYYYYYYYYYYYY",(int)m_Tf->X,(int)m_Tf->Y);
                //SDL_Log("%d BEFXXX *******  %d BEFYYY",m_BeforeX,m_BeforeY);
                DirectionCheckByQuad(m_BeforeX,m_BeforeY,1);
                m_Collider->Set((int)m_Tf->X + m_Tf->m_Width/2,(int)m_Tf->Y + m_Tf->m_Height/2,10,10);
            break;
        case 1:
                m_Animation->SetCurrentFrame(1);
                Move();
                //SDL_Log("XXXXXXXXXXXXXXXXXX***********%d       YYYYYYYYYYYYYYYYY***********%d",(int)m_Tf->X,(int)m_Tf->Y );
                //SDL_Log("XXXXXXXXXXXXXXXXXX***********%d       YYYYYYYYYYYYYYYYY***********%d",m_DestX,m_DestY );
                DirectionCheckByQuad(m_DestX,m_DestY,2);
                m_Collider->Set((int)m_Tf->X + m_Tf->m_Width/2,(int)m_Tf->Y + m_Tf->m_Height/2,10,10);
            break;
        case 2:
                m_FrameTime++;
                if(m_FrameTime == 100)
                {
                    m_FrameTime = 0;
                    m_Animation->SetCurrentFrame(3);
                }
            break;
        case 3:
                m_FrameTime++;
                if(m_FrameTime ==100)
                {
                    m_FrameTime = 0;
                    m_Animation->SetCurrentFrame(4);
                }
                SDL_Log("%d",m_Animation->GetCurrentFrame());
            break;
        case 4:
                m_FrameTime++;
                if(m_FrameTime == 100)
                {
                    m_FrameTime = 0;
                    m_Animation->SetCurrentFrame(5);
                }
            break;
        case 5:
                m_Tf->m_Angle = 0;
                m_Animation->SetRepeat(false);
                ShiftCollider();
                bool OnlyOne = false;
                for(int i = 0; i < m_Colliders.size();i++)
                {
                    if(CollisionHandler::GetInstance()->CheckCollision(soldier->GetCollider()->Get(),m_Colliders[i]->Get()) && !OnlyOne && m_ScallingFactorTransp > 1000)
                    {
                        soldier->ReciveDamage(1);
                        OnlyOne = true;
                    }
                    if(CollisionHandler::GetInstance()->MapCollision(m_Colliders[i]->Get()))
                    {
                        m_MapCollision = true;
                    }
                }
            break;
    }
    m_ScallingFactorTransp--;
    m_TransparencyValue = Scaling(m_ScallingFactorTransp,0,2000,0,255);
    //m_TransparencyValue--;


}
void Puddle::ShiftCollider()
{
    int r = 23;
    for(int i = 0 ; i < m_Colliders.size(); i++)
    {
        int X,Y;
        X = (int)m_Tf->X + (m_Tf->m_Width - m_Colliders[i]->Get().w)/2; + m_Indent[i];
        Y = (int)m_Tf->Y + r;
        r += m_Colliders[i]->Get().h;
        m_Colliders[i]->Set(X,Y,m_Colliders[i]->Get().w,m_Colliders[i]->Get().h);
    }


}


void Puddle::ParseColliderCoord(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error())
    {
        SDL_Log("Failed to load Puddle collider coordinate file!");
    }
    TiXmlElement* root = xml.RootElement();
    int i = 1;
    int row;
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        std::string s;
        s = e->Value();
        s = s.substr(1,s.size()-1);
        row = stoi(s);
        if(row == i)
        {
            Collider* col = new Collider();
            col->SetBuffer(0,0,0,0);
            int w,h,indent;
            e->Attribute("W",&w);
            e->Attribute("H",&h);
            e->Attribute("INDENT",&indent);
            col->Set((int)m_Tf->X,(int)m_Tf->Y,w,h);
            m_Colliders.push_back(col);
            m_Indent.push_back(indent);
            i++;
        }
    }

}
void Puddle::Move()
{
    double sinN=sin(m_Tf->m_Angle*(3.1415/180));
    double cosN=cos(m_Tf->m_Angle*(3.1415/180));
    if(m_Tf->m_Angle > 0 && m_Tf->m_Angle <= 90)
    {
        m_Tf->X+=cos(m_Tf->m_Angle*(3.1415/180))*5;//10;
        m_Tf->Y+=sin(m_Tf->m_Angle*(3.1415/180))*5;//10;
        //SDL_Log("XXXXX***%d YYYYYY***%d WWWWW***%d HHHHH***%d",m_Collider->Get().x,m_Collider->Get().y,m_Collider->Get().w,m_Collider->Get().h);
        //m_Collider->Set((int)m_Tf->X,(int)m_Tf->Y,5,5);
        m_Collider->Set((int)m_Tf->X,(int)m_Tf->Y,m_Collider->Get().w,m_Collider->Get().h);
        //m_Collider->Set((int)m_Tf->X,(int)m_Tf->Y,X,Y);
    }
    else if (m_Tf->m_Angle > 90 && m_Tf->m_Angle <= 180)
    {
        m_Tf->X+=cos(m_Tf->m_Angle*(3.1415/180))*5;//10;
        m_Tf->Y+=sin(m_Tf->m_Angle*(3.1415/180))*5;//10;
        //SDL_Log("XXXXX***%d YYYYYY***%d WWWWW***%d HHHHH***%d",m_Collider->Get().x,m_Collider->Get().y,m_Collider->Get().w,m_Collider->Get().h);
        m_Collider->Set((int)m_Tf->X,(int)m_Tf->Y,m_Collider->Get().w,m_Collider->Get().h);
    }
    else if (m_Tf->m_Angle > -180 && m_Tf->m_Angle <= -90)
    {
        m_Tf->X+=cos(m_Tf->m_Angle*(3.1415/180))*5;//10;
        m_Tf->Y+=sin(m_Tf->m_Angle*(3.1415/180))*5;//10;
        //SDL_Log("XXXXX***%d YYYYYY***%d WWWWW***%d HHHHH***%d",m_Collider->Get().x,m_Collider->Get().y,m_Collider->Get().w,m_Collider->Get().h);
        m_Collider->Set((int)m_Tf->X,(int)m_Tf->Y,m_Collider->Get().w,m_Collider->Get().h);
    }
    else if (m_Tf->m_Angle > -90 && m_Tf->m_Angle <= 0)
    {
        m_Tf->X+=cos(m_Tf->m_Angle*(3.1415/180))*5;//10;
        m_Tf->Y+=sin(m_Tf->m_Angle*(3.1415/180))*5;//10;
        //SDL_Log("XXXXX***%d YYYYYY***%d WWWWW***%d HHHHH***%d",m_Collider->Get().x,m_Collider->Get().y,m_Collider->Get().w,m_Collider->Get().h);
        m_Collider->Set((int)m_Tf->X,(int)m_Tf->Y,m_Collider->Get().w,m_Collider->Get().h);
    }
}
void Puddle::DirectionCheckByQuad(int DirX,int DirY,int frame)
{
    switch(m_Quad)
    {
        case FIRST:
                if( ((int)m_Tf->X >= DirX  || (int)m_Tf->Y >= DirY))// ||
                    //((int)m_Tf->X <= m_BeforeX  && (int)m_Tf->Y >= m_BeforeY) ||
                    //((int)m_Tf->X <= m_BeforeX  && (int)m_Tf->Y <= m_BeforeY) ||
                    //((int)m_Tf->X >= m_BeforeX  && (int)m_Tf->Y <= m_BeforeY) )
                {
                    m_Animation->SetCurrentFrame(frame);
                }
                //SDL_Log("Quadrant --- %d",m_Quad);
        break;
        case SECOND:
                if( ((int)m_Tf->X <= DirX  && (int)m_Tf->Y >= DirY))
                    //((int)m_Tf->X <= m_BeforeX  && (int)m_Tf->Y <= m_BeforeY) ||
                    //((int)m_Tf->X >= m_BeforeX  && (int)m_Tf->Y <= m_BeforeY) )
                {
                    m_Animation->SetCurrentFrame(frame);
                }
                //SDL_Log("Quadrant --- %d",m_Quad);
        break;
        case THIRD:
                if( ((int)m_Tf->X <= DirX  && (int)m_Tf->Y <= DirY))
                    //((int)m_Tf->X >= m_BeforeX  && (int)m_Tf->Y <= m_BeforeY) )
                {
                    m_Animation->SetCurrentFrame(frame);
                }
                //SDL_Log("Quadrant --- %d",m_Quad);
    break;
        case FOURTH:
                if(((int)m_Tf->X >= DirX  && (int)m_Tf->Y <= DirX) )
                {
                    m_Animation->SetCurrentFrame(frame);
                }
                //SDL_Log("Quadrant --- %d",m_Quad);
        break;
    }
}

Puddle::~Puddle()
{
    delete m_Collider;
    delete m_Animation;
    delete m_Tf;
    m_Tf = nullptr;
    m_Animation = nullptr;
    m_Collider = nullptr;
}
