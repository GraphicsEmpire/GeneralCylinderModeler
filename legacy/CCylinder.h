#ifndef CCYLINDER_H
#define CCYLINDER_H

#include "CCylinderBase.h"
#include "PS_SplineCatmullRom.h"

#define DEFAULT_STACKS 10

namespace PS{
namespace MODELING{


//Generalized Cylinder
class CCylinder
{
public:
    CCylinder(){
        m_radiusStart = DEFAULT_RADIUS;
        m_radiusEnd   = DEFAULT_RADIUS;
        m_sectors = DEFAULT_SECTORS;
        m_stacks = DEFAULT_STACKS;
    };

    ~CCylinder(){}

    void removeAll()
    {
        for(size_t i=0; i< m_lstStacks.size(); i++)
            m_lstStacks[i].removeAllPoints();
        m_lstStacks.clear();
        m_axisCurve.removeAll();
    }

    //Stacks
    void setStacks(int stacks) { m_stacks = stacks;}
    int getStacksCount() const {return m_stacks;}

    //Sectors
    void setSectors(int sectors) { m_sectors = sectors; }
    int getSectorsCount() const {return m_sectors;}

    //Start Radius
    void setRadiusStart(const float r1)    {  m_radiusStart = r1;  }
    float getRadiusStart() const { return m_radiusStart;}

    //End Radius
    void setRadiusEnd(const float r2)    {  m_radiusEnd = r2; }
    float getRadiusEnd() const { return m_radiusEnd;}

    /*!
     * Computes all cross sections across the profile curve.
     * Each cross section is oriented using a Frenet Frame.
     */
    void calc();

    void drawCurveControlPoints(bool bSelectMode = false)
    {
        vec3f p;
        glBegin(GL_POINTS);
        for(size_t i = 0; i< m_axisCurve.getCtrlPointsCount(); i++)
        {
            p = m_axisCurve.getPoint(i);

            if(bSelectMode)
                glPushName(i+1);

            glVertex3f(p.x, p.y, p.z);
            if(bSelectMode)
                glPopName();
        }
        glEnd();
    }

    void drawCurve()
    {
        //m_axisCurve.draw(GL_LINE_STRIP, 100);
        std::vector<ARCLENGTHPARAM> arc = m_axisCurve.getArcTable();
        if(arc.size() == 0)
            return;
        glBegin(GL_LINE_STRIP);
            for(size_t i=0;i<arc.size(); i++)
                glVertex3fv(arc[i].pt.ptr());
        glEnd();
    }

    void drawCrossSections()
    {
        size_t n = m_lstStacks.size();
        if(n == 0) return;
        for (size_t i=0; i< n; i++)
        {
            //m_lstStacks[i].calc();
            m_lstStacks[i].draw(GL_LINE_LOOP);
        }
    }

    void drawWireFrame()
    {
        if(m_lstStacks.size() < 2) return;

        size_t nPoints = m_lstStacks[0].getPointsCount();
        size_t nStacks = m_lstStacks.size();

        vec3f v1, v2;

        for (size_t i=0; i < nStacks - 1; i++)
        {
            //m_lstStacks[i].calc();
            //m_lstStacks[i + 1].calc();

            glBegin(GL_LINE_STRIP);
            for(size_t j=0; j < nPoints; j++)
            {
                v1 = m_lstStacks[i].getPoint(j);
                v2 = m_lstStacks[i + 1].getPoint(j);
                glVertex3f(v1.x, v1.y, v1.z);
                glVertex3f(v2.x, v2.y, v2.z);
            }
            v1 = m_lstStacks[i].getPoint(0);
            v2 = m_lstStacks[i + 1].getPoint(0);
            glVertex3f(v1.x, v1.y, v1.z);
            glVertex3f(v2.x, v2.y, v2.z);

            glEnd();
        }
    }

    void drawNormals()
    {
        if(m_lstStacks.size() < 2) return;

        size_t nPoints = m_lstStacks[0].getPointsCount();
        size_t nStacks = m_lstStacks.size();

        vec3f v1, v2;
        vec3f n1, n2;
        vec3f t;

        for (size_t i=0; i < nStacks - 1; i++)
        {
            //m_lstStacks[i].calc();
            //m_lstStacks[i + 1].calc();

            glBegin(GL_LINES);
            for(size_t j=0; j < nPoints; j++)
            {
                v1 = m_lstStacks[i].getPoint(j);
                n1 = m_lstStacks[i].getNormal(j);

                v2 = m_lstStacks[i + 1].getPoint(j);
                n2 = m_lstStacks[i + 1].getNormal(j);
                //glNormal3fv(n1.ptr());
                glVertex3fv(v1.ptr());
                t = v1 + 0.2f * n1;
                glVertex3fv(t.ptr());

                //glNormal3fv(n2.ptr());
                glVertex3fv(v2.ptr());
                t = v2 + 0.2f * n2;
                glVertex3fv(t.ptr());

            }
            v1 = m_lstStacks[i].getPoint(0);
            n1 = m_lstStacks[i].getNormal(0);
            v2 = m_lstStacks[i + 1].getPoint(0);
            n2 = m_lstStacks[i + 1].getNormal(0);

            //glNormal3fv(n1.ptr());
            glVertex3fv(v1.ptr());
            t = v1 + 0.2f * n1;
            glVertex3fv(t.ptr());


            //glNormal3fv(n2.ptr());
            glVertex3fv(v2.ptr());
            t = v2 + 0.2f * n2;
            glVertex3fv(t.ptr());


            glEnd();
        }

    }

    void drawSurface()
    {
        if(m_lstStacks.size() < 2) return;

        size_t nPoints = m_lstStacks[0].getPointsCount();
        size_t nStacks = m_lstStacks.size();

        vec3f v1, v2;
        vec3f n1, n2;

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        for (size_t i=0; i < nStacks - 1; i++)
        {
            //m_lstStacks[i].calc();
            //m_lstStacks[i + 1].calc();

            glBegin(GL_TRIANGLE_STRIP);
            for(size_t j=0; j < nPoints; j++)
            {
                v1 = m_lstStacks[i].getPoint(j);
                n1 = m_lstStacks[i].getNormal(j);

                v2 = m_lstStacks[i + 1].getPoint(j);
                n2 = m_lstStacks[i + 1].getNormal(j);
                glNormal3fv(n1.ptr());
                glVertex3fv(v1.ptr());

                glNormal3fv(n2.ptr());
                glVertex3fv(v2.ptr());
            }
            v1 = m_lstStacks[i].getPoint(0);
            n1 = m_lstStacks[i].getNormal(0);
            v2 = m_lstStacks[i + 1].getPoint(0);
            n2 = m_lstStacks[i + 1].getNormal(0);

            glNormal3fv(n1.ptr());
            glVertex3fv(v1.ptr());

            glNormal3fv(n2.ptr());
            glVertex3fv(v2.ptr());

            glEnd();
        }


    }

    CSplineCatmullRom& getProfileCurve() {return m_axisCurve;}
    bool closeCurve();

private:
    int m_stacks;
    int m_sectors;
    float m_radiusStart;
    float m_radiusEnd;

    //CSplineCatmullRom m_axisCurve;
    CSplineCatmullRom m_axisCurve;
    std::vector<CCylinderBase> m_lstStacks;
};

}
}

#endif
