#ifndef COLLIDER_H
#define COLLIDER_H

#include <SDL.h>
#include "Mathematics.h"
class Collider
{
    public:

        inline SDL_Rect Get() {return m_Box;}
        inline void SetBuffer(int x,int y,int w,int h) { m_Buffer = { x,y,w,h };}
//        void SetPolygon(Vector2D* pos,double angle,bool overlap = false,bool PolygonCollider = true)
//        {
//            Vector2D vec = {pos->X,pos->Y};
//            m_Polygon.pos = vec;
//            m_Polygon.angle = angle;
//            m_Polygon.overlap = overlap;
//            m_HasPolygonCollider = PolygonCollider;
//        }
//        void PushInPolygonProjectVector(Vector2D vect)
//        {
//            m_Polygon.p.push_back(vect);
//        }
//        void PushInPolygonModelVector(Vector2D vect)
//        {
//            m_Polygon.o.push_back(vect);
//        }
//        void PushInPolygonProjectVectorByPos(Vector2D vect,int pos)
//        {
//            m_Polygon.p[pos] = vect;
//        }
//        void PushInPolygonModelVectorByPos(Vector2D vect,int pos)
//        {
//            m_Polygon.o[pos] = vect;
//        }
//        void ResizePolygonProject(int amount) { m_Polygon.p.resize(amount); }
//        void ResizePolygonModel(int amount) { m_Polygon.o.resize(amount); }

        //Polygon* GetPolygon() { return &m_Polygon;}
        Collider& operator= ( const Collider& coll)
        {
            return *this;
        }
        //inline bool PolygonCollider(){ return m_HasPolygonCollider;}

        void Set (int x,int y,int w,int h)
        {
            m_Box = {
                x - m_Buffer.x,
                y - m_Buffer.y,
                w - m_Buffer.w,
                h - m_Buffer.h
            };
        }
        Circle m_Circle;
        Polygon m_Polygon;
        bool m_HasPolygonCollider = false;
        bool m_HasCircleCollider = false;
private:
        SDL_Rect m_Box;
        SDL_Rect m_Buffer;


};

#endif // COLLIDER_H
