#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SDL.h>
#include "Vector2D.h"

class Transform
{
    public:

        Transform(std::string textureID="",float x=0,float y=0,int width=0,int height=0,
                  double angle=0,int currentFrame=0,int currentRow=0,SDL_RendererFlip flip = SDL_FLIP_NONE)
        {
            X = x;
            Y = y;
            m_Width = width;
            m_Height = height;
            m_Angle = angle;
            m_CurrentFrame = currentFrame;
            m_CurrentRow = currentRow;
            m_TextureID = textureID;
            m_Flip = flip;
            m_Origin = new Vector2D((X+m_Width/2) , (Y+m_Height/2));
        }

        void Log(std::string msg="")
        {
            std::cout << msg <<" (X Y) = ("<< X << " " << Y << ")"<< std::endl;
        }

        inline void TranslateX(float x) { X += x;}
        inline void TranslateY(float y) { Y += y;}
        inline void Translate(Vector2D vect){ X += vect.X; Y += vect.Y; };
        inline void SetCoord(Vector2D vect) { X = vect.X; Y = vect.Y; }

        ~Transform(){delete m_Origin; m_Origin=nullptr;}
    public:
        float X,Y;
        int m_Width,m_Height;
        double m_Angle;
        int m_CurrentFrame;
        int m_CurrentRow;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;
        Vector2D* m_Origin;
};

#endif // TRANSFORM_H
