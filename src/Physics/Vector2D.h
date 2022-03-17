#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>
#include <math.h>

class Vector2D
{
    public:
        float X,Y;
        Vector2D(float x = 0,float y = 0):X(x),Y(y) {}
    public:
        inline Vector2D operator+ (const  Vector2D& v2) const
        {
            return Vector2D(X+v2.X,Y+v2.Y);
        }
        inline Vector2D operator- (const  Vector2D& v2) const
        {
            return Vector2D(X-v2.X,Y-v2.Y);
        }
        inline Vector2D operator- (const float f) const
        {
            return Vector2D(X-f,Y-f);
        }
        inline Vector2D operator* (const float scalar) const
        {
            return Vector2D(X*scalar,Y*scalar);
        }
        inline float Lenght(float x,float y) { return sqrt(((x-X)*(x-X))+((y-Y)*(y-Y)));}

        inline float MagnitudeSqr()
        {
            return X*X + Y*Y;
        }
        inline float Magnitude()
        {
            return (float)sqrt(X*X + Y*Y);
        }
        Vector2D Normalized()
        {
            float mag = Magnitude();
            return Vector2D(X/mag,Y/mag);
        }
        void Log(std::string msg="")
        {
            std::cout << msg <<" (X Y) = ("<< X << " " << Y << ")"<< std::endl;
        }

};

#endif // VECTOR2D_H
