#ifndef BEZIERPATHS_H
#define BEZIERPATHS_H
#include "Mathematics.h"
#include <vector>
class BezierPaths
{
    public:
        BezierPaths();
        virtual ~BezierPaths();
        void AddCurve(BezierCurve curve, int samples);
        void Sample(std::vector<Vector2D>* samplePath);

    private:
        std::vector<BezierCurve> m_Curves;
        std::vector<int> m_Samples;
};

#endif // BEZIERPATHS_H
