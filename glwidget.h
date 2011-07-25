//-------------------------------------------------------------------------------------------
//  University of Victoria Computer Science Department
//	FrameWork for OpenGL application under QT
//  Course title: Computer Graphics CSC305
//-------------------------------------------------------------------------------------------
//These two lines are header guiardians against multiple includes
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "CCylinder.h"
#include "PS_ArcBallCamera.h"

using namespace PS::MATH;
using namespace PS::MODELING;
typedef enum DragDirection {ddNone, ddLeft, ddRight};


//This is our OpenGL Component we built it on top of QGLWidget
class GLWidget : public QGLWidget
{
    Q_OBJECT

public slots:
    void reset();
    void setView(bool bPers);
    void setSectors(int sectors);
    void setStacks(int stacks);
    void setRadiusStart(double r1);
    void setRadiusEnd(double r2);
    void setDrawCrossSections(bool bDraw);
    void setDrawWireFrame(bool bDraw);
    void setDrawSurface(bool bDraw);
    void setDrawNormals(bool bDraw);

    void closeCurve();
    void exportModel();

public:
    //Constructor for GLWidget
    GLWidget(QWidget *parent = 0);

    //Destructor for GLWidget
    ~GLWidget();

protected:
    //Initialize the OpenGL Graphics Engine
    void initializeGL();

    //All our painting stuff are here
    void paintGL();

    //When user resizes main window, the scrollArea will be resized and it will call this function from
    //its attached GLWidget
    void resizeGL(int width, int height);

    //Handle mouse press event in scrollArea
    void mousePressEvent(QMouseEvent *event);

    //Handle Mouse Move Event
    void mouseMoveEvent(QMouseEvent *event);

    //Handle mouse release event
    void mouseReleaseEvent(QMouseEvent *event);

    //Get Object ID for selection
    int hitObjects(int x, int y, const int nMaxObjectsHit = 8);
    int getObjectID(int x, int y);
private:
    void drawCurve();

    bool m_bDrawCrossSections;

    bool m_bDrawWireFrame;

    bool m_bDrawSurface;

    bool m_bDrawNormals;

    bool m_bPerspective;

    DragDirection m_dragdir;

    PS::CArcBallCamera m_camera;

    CCylinder m_cylinder;

    QPoint m_lastPos;
};


#endif
