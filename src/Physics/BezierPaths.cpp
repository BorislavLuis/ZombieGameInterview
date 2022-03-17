#include "BezierPaths.h"

BezierPaths::BezierPaths()
{

}

BezierPaths::~BezierPaths()
{

}
void BezierPaths::AddCurve(BezierCurve curve, int samples)
{
    m_Curves.push_back(curve);
    m_Samples.push_back(samples);
}

void BezierPaths::Sample(std::vector<Vector2D>* samplePath)
{
    for(int i = 0; i < m_Curves.size(); i++)
    {
        for(float t = 0.0f ; t <= 1.0f ; t += 1.0f/ m_Samples[i])
        {
            samplePath->push_back(m_Curves[i].CalculateCurvePoint(t));
        }
    }
}
