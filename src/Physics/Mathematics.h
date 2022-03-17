#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include <vector>
#include "Vector2D.h"
#include <math.h>
template <typename T>
T Scaling(T RawValue,T RawMin,T RawMax,T EngMin,T EngMax)
{
    T RawRange,EngRange,EngValue;
    RawRange = RawMax - RawMin;
    EngRange = EngMax - EngMin;
    EngValue = (((RawValue - RawMin)*EngRange)/RawRange) + EngMin;
    return EngValue;
}

struct BezierCurve
{
    Vector2D p0;
    Vector2D p1;
    Vector2D p2;
    Vector2D p3;

    Vector2D CalculateCurvePoint(float t)
    {
        float tt = t*t;
        float ttt = tt*t;
        float u = 1.0f - t;
        float uu = u*u;
        float uuu = uu*u;

        Vector2D point = (p0 * uuu) + (p1 *3.0f * uu * t) + ( p2 * 3.0f * u * tt ) + (p3 * ttt);
        point.X = round(point.X);
        point.Y = round(point.Y);
        return point;
    }
};
struct Polygon
{
    std::vector<Vector2D> p;
    Vector2D pos;
    double angle;
    std::vector<Vector2D> o;
    bool overlap = false;
};
struct Circle
{
    int x,y;
    int r;

    int DistanceSquared(int x1,int y1,int x2,int y2)
    {
        int deltaX = x2 - x1;
        int deltaY = y2 - y1;
        return deltaX*deltaX + deltaY*deltaY;
    }
};
#endif // MATHEMATICS_H
