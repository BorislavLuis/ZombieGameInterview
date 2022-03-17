#ifndef PUDDLE_H
#define PUDDLE_H
#include "Collider.h"
#include "SeqAnimation.h"
#include "Transform.h"
#include "Engine.h"
//#include "Soldier.h"
#include <sstream>
struct MapProps;
class Puddle
{
    public:
        Puddle(float x,float y,int destX,int destY,double angle);
        void Draw();
        void Update(Soldier* soldier);
        void ParseColliderCoord(std::string source);
        void ShiftCollider();
        void Move();
        void DirectionCheckByQuad(int DirX,int DirY,int frame);
        inline int GetTransparency() { return m_TransparencyValue;}
        inline bool MapCollision() { return m_MapCollision;}
        inline bool IsOutsideScreen() { return m_OutsideScreen;}
        virtual ~Puddle();

    private:
        bool m_MapCollision;
        bool m_OutsideScreen;
        int m_DestX,m_DestY;
        int m_BeforeX,m_BeforeY;
        int m_TransparencyValue;
        int m_FrameConsecutive;
        int m_ScallingFactorTransp;
        int m_FrameTime;
        enum Quads{ FIRST,SECOND,THIRD,FOURTH };
        Quads m_Quad;
        Collider* m_Collider;
        SeqAnimation* m_Animation;
        Transform* m_Tf;
        MapProps* m_MapPtr;
        std::vector<Collider*> m_Colliders;
        std::vector<int> m_Indent;
};

#endif // PUDDLE_H
