#include "CCylinder.h"

namespace PS{
namespace MODELING{

void CCylinder::calc()
{
    if(m_axisCurve.getCtrlPointsCount() < 4)
        return;
    m_axisCurve.populateTable();
    if(m_lstStacks.size() > 0)
    {
        for(size_t i=0; i< m_lstStacks.size(); i++)
            m_lstStacks[i].removeAllPoints();
        m_lstStacks.clear();
    }

    vec3f xAxis(1.0f, 0.0f, 0.0f);
    vec3f yAxis(0.0f, 1.0f, 0.0f);
    vec3f zAxis(0.0f, 0.0f, 1.0f);

    float t = 0.0f;
    //Current Position + Frenet Frame
    vec3f T, N, B, P;

    //Previous Frenet Frame
    vec3f prevN, prevB;

    vec3f A;

    float deltaRadius = (m_radiusEnd - m_radiusStart) / static_cast<float>(m_stacks);
    float radius = m_radiusStart;

    for (int i=0; i < m_stacks; i++)
    {
        radius = m_radiusStart + i * deltaRadius;

        t = static_cast<float>(i)/ static_cast<float>(m_stacks - 1);

        P = m_axisCurve.position(t);

        T = m_axisCurve.tangent(t);
        T.normalize();

        if(i == 0)
        {
            A = m_axisCurve.acceleration(t);

            if(A.length() < EPSILON)
                A = T.cross(yAxis);
            A.normalize();

            //N = normalized(VxQxV)
            N = T.cross(A.cross(T)); //v = u*w
            N.normalize();

            //B = TxN
            B = T.cross(N);
            B.normalize();
        }
        else
        {
            N = prevB.cross(T);
            B = T.cross(N);
        }

        //Save for Next Iteration
        prevN = N;
        prevB = B;

        //At this point we have the frenet frame
        CCylinderBase base;
        base.setRadius(radius);
        base.setSectors(m_sectors);
        base.setPosition(P);
        base.setFrenetFrame(T, N, B);
        base.calc();


        m_lstStacks.push_back(base);
    }
}

bool CCylinder::closeCurve()
{
    int ctCtrlPoints = (int)m_axisCurve.getCtrlPointsCount();
    if(ctCtrlPoints < MIN_CTRL_POINTS_COUNT)
        return false;

    vec3f v0 = m_axisCurve.position(0.0f);
    vec3f t0 = m_axisCurve.tangent(0.0f);
    vec3f last = m_axisCurve.position(1.0f);
    if(last == v0)
        return false;

    t0.normalize();
    float halfDist = last.distance(v0) * 0.5f;
    m_axisCurve.addPoint(v0 - halfDist * t0);
    m_axisCurve.addPoint(v0);
    m_axisCurve.addPoint(v0);

    this->calc();

    return true;
}

}
}



