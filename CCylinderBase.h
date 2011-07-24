#ifndef CCYLINDERBASE_H
#define CCYLINDERBASE_H

#include <QGLWidget>
#include "mathHelper.h"
#include "PS_Vector.h"


#define DEFAULT_SECTORS 3
#define DEFAULT_RADIUS 0.25f;

using namespace PS::MATH;
class CCylinderBase
{

public:
    CCylinderBase()
    {
        m_sectors = DEFAULT_SECTORS;
        m_radius = DEFAULT_RADIUS;
        m_position = vec3f(0.0f, 0.0f, 0.0f);
        m_normal = vec3f(0.0f, 0.0f, 0.0f);
        calc();
    }

    CCylinderBase(int nSectors, float radius)
    {
        m_sectors = nSectors;
        m_radius = radius;                
        m_position = vec3f(0.0f, 0.0f, 0.0f);
        m_normal = vec3f(0.0f, 0.0f, 0.0f);
        calc();
    }

    ~CCylinderBase() {
        removeAllPoints();
    }

    void removeAllPoints()
    {
        m_lstNormals.resize(0);
        m_lstPoints.resize(0);
    }


    void calc()
    {
        float angle = (float)(TwoPi /(float)m_sectors);

        m_lstPoints.resize(0);
        m_lstNormals.resize(0);

        vec3f C, pt, n;
        for(int i=0; i < m_sectors; i++)
        {
            //1.Point on 2D cross section
            C.x = m_radius * cos(i * angle);
            C.y = m_radius * sin(i * angle);
            C.z = 1.0f;

            //2.Point on cylinder
            pt.x = m_position.x + C.x * m_normal.x + C.y * m_binormal.x;
            pt.y = m_position.y + C.x * m_normal.y + C.y * m_binormal.y;
            pt.z = m_position.z + C.x * m_normal.z + C.y * m_binormal.z;

            //Compute Normal
            n = pt - m_position;
            n.normalize();

            m_lstPoints.push_back(pt);
            m_lstNormals.push_back(n);
        }
    }

    void setSectors(int sectors)
    {
        m_sectors = sectors;
    }

    void setRadius(const float radius)
    {
        m_radius = radius;
    }

    void setPosition(vec3f v)
    {
        m_position = v;
    }

    void setFrenetFrame(vec3f T, vec3f N, vec3f B)
    {
        m_tangent = T;
        m_normal = N;
        m_binormal = B;
    }

    void draw(int glArg = GL_POLYGON)
    {        
        glPushMatrix();
        glBegin(glArg);
        for(size_t i=0; i< m_lstPoints.size(); i++)
            glVertex3f(m_lstPoints[i].x, m_lstPoints[i].y, m_lstPoints[i].z);
        glEnd();
        glPopMatrix();
    }

    vec3f getBaseNormal() const
    {
        return m_normal;
    }

    vec3f getNormal(size_t i) const
    {
        return m_lstNormals[i];
    }

    vec3f getPoint(size_t i) const
    {
        return m_lstPoints[i];
    }

    size_t getPointsCount() const
    {
        return m_lstPoints.size();
    }

private:
    int m_sectors;
    float m_radius;
    vec3f m_position;

    vec3f m_tangent;
    vec3f m_normal;
    vec3f m_binormal;

    std::vector<vec3f> m_lstPoints;
    std::vector<vec3f> m_lstNormals;
};


#endif // CCYLINDERBASE_H
