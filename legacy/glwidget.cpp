//-------------------------------------------------------------------------------------------
//  University of Victoria Computer Science Department
//	FrameWork for OpenGL application under QT
//  Course title: Computer Graphics CSC305
//-------------------------------------------------------------------------------------------
#include <QtGui>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"
#include "PS_Material.h"
#include "PS_AppConfig.h"
#include "GL/glu.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    m_bDrawCrossSections = true;
    m_bDrawWireFrame = true;
    m_bDrawSurface = false;
    m_bPerspective = false;
    m_bDrawNormals = false;
    m_dragdir = ddNone;
}

GLWidget::~GLWidget()
{    
    makeCurrent();

}

void GLWidget::reset()
{	
    m_cylinder.removeAll();
    updateGL();
}

void GLWidget::initializeGL()
{
    //Background color will be white
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);

    glPointSize(5.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void GLWidget::paintGL()
{
    //Clear target buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    // Set the camera position, orientation and target
    if(m_bPerspective)
    {
        glTranslated(0.0, 0.0, 1.0);
        vec3f p = m_camera.getCoordinates();
        gluLookAt(p.x, p.y, p.z, 0, 0, 0, 0, 1, 0);
    }
    else
    {
        //Draw the grid Map
    }


    //Draw Catmull-Rom Curve Control Points
    glDisable(GL_LIGHTING);

    glColor3f(0.0, 0.0, 0.0);
    m_cylinder.drawCurveControlPoints(false);

    //Draw Curve itself
    glColor3f(1.0, 0.0, 0.0);
    m_cylinder.drawCurve();

    if(m_bDrawSurface)
    {
        glEnable(GL_LIGHTING);
        //glColor3ub(255, 215, 0);
        //setMaterial(mtrlBrass);
        m_cylinder.drawSurface();

        glDisable(GL_LIGHTING);
    }

    if(m_bDrawNormals)
    {
        glColor3f(0.0f, 0.0f, 1.0f);
        m_cylinder.drawNormals();
    }

    if(m_bDrawCrossSections)
    {
        glColor3f(0.0, 0.0, 1.0);
        m_cylinder.drawCrossSections();
    }

    if(m_bDrawWireFrame)
    {
        glColor3f(0.0, 0.0, 0.0);
        m_cylinder.drawWireFrame();
    }

    
    glFlush();
}

void GLWidget::setDrawWireFrame(bool bDraw)
{
    if(m_bDrawWireFrame != bDraw)
    {
        m_bDrawWireFrame = bDraw;
        updateGL();
    }
}

void GLWidget::setDrawCrossSections(bool bDraw)
{
    if(m_bDrawCrossSections != bDraw)
    {
        m_bDrawCrossSections = bDraw;
        updateGL();
    }
}

void GLWidget::setDrawNormals(bool bDraw)
{
    if(m_bDrawNormals != bDraw)
    {
        m_bDrawNormals = bDraw;
        updateGL();
    }
}

void GLWidget::setDrawSurface(bool bDraw)
{
    if(m_bDrawSurface != bDraw)
    {
        m_bDrawSurface = bDraw;
        updateGL();
    }
}

void GLWidget::closeCurve()
{
    m_cylinder.closeCurve();
    updateGL();
}

void GLWidget::exportModel()
{

}

void GLWidget::setStacks(int stacks)
{
    m_cylinder.setStacks(stacks);
    m_cylinder.calc();

    updateGL();
}

void GLWidget::setSectors(int sectors)
{
    m_cylinder.setSectors(sectors);
    m_cylinder.calc();

    updateGL();
}

void GLWidget::setRadiusStart(double r1)
{
    if(r1 != m_cylinder.getRadiusStart())
    {
        m_cylinder.setRadiusStart((float)r1);
        m_cylinder.calc();

        updateGL();
    }
}

void GLWidget::setRadiusEnd(double r2)
{
    if(r2 != m_cylinder.getRadiusEnd())
    {
        m_cylinder.setRadiusEnd((float)r2);
        m_cylinder.calc();

        updateGL();
    }
}

void GLWidget::setView(bool bPers)
{
    if(m_bPerspective != bPers)
    {
        m_bPerspective = bPers;

        //Set projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        //Toggling Perspective View
        if(m_bPerspective)
        {
            GLfloat fov = 60.0f;
            gluPerspective(fov, (GLdouble)width()/height(), 0.5, 3000);
        }
        else
        {
            glOrtho(-1.0, +1.0, -1.0, 1.0, -1.0, 1.0);
        }

        //Return to ModelView Matrix
        glMatrixMode(GL_MODELVIEW);

        updateGL();
    }
}

void GLWidget::resizeGL(int width, int height)
{	
    //Correction for aspect ratio
    int side = qMin(width, height);
    //glViewport((width - side) / 2, (height - side) / 2, side, side);
    glViewport(0,0, width, height);

    //Set projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Toggling Perspective View
    if(m_bPerspective)
    {
        GLfloat fov = 60.0f;
        gluPerspective(fov, (GLdouble)width/height, 1, 3000);
    }
    else
    {
        glOrtho(-1.0, +1.0, -1.0, 1.0, -1.0, 1.0);
    }

    //Return to ModelView Matrix
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() & Qt::LeftButton)
    {
        float wx ,wy;
        int x = event->x();
        int y = event->y();
        int width = this->width();
        int height = this->height();

        if(getObjectID(x, y) > 0)
        {

        }
        else
        {
            wx = (2.0 * x) / (GLfloat)(width - 1) - 1.0;
            wy = (2.0 * (height - y)) / (GLfloat)(height) -1.0;

            vec3f p;
            p.x = wx; p.y = wy; p.z = 0.0f;
            m_cylinder.getProfileCurve().addPoint(p);
            m_cylinder.calc();
        }

        updateGL();
    }
    else if(event->buttons() & Qt::MidButton)
    {
        m_dragdir = ddLeft;
    }
    else if(event->button() & Qt::RightButton)
    {
        m_dragdir = ddRight;
    }

    m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_bPerspective) return;

    int x = event->x();
    int y = event->y();

    int dx = x - m_lastPos.x();
    int dy = m_lastPos.y() - y;

    if(m_dragdir == ddLeft)        
    {
        m_camera.setHorizontalAngle(m_camera.getHorizontalAngle() + (0.03 * dx));
        m_camera.setVerticalAngle(m_camera.getVerticalAngle() + (0.03 * dy));
    }
    else if(m_dragdir ==  ddRight)
    {
        m_camera.setZoom(m_camera.getCurrentZoom() + 0.1 * dy);
    }

    m_lastPos = event->pos();
    updateGL();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_dragdir = ddNone;
}

int GLWidget::getObjectID(int x, int y)
{
    // This will hold the amount of objects clicked
    int objectsFound = 0;

    // We need an array to hold our view port coordinates
    int	viewportCoords[4] = {0};

    // This will hold the ID's of the objects we click on.
    // We make it an arbitrary number of 32 because openGL also stores other information
    // that we don't care about.  There is about 4 slots of info for every object ID taken up.
    GLuint selectBuffer[32] = {0};

    // glSelectBuffer is what we register our selection buffer with.  The first parameter
    // is the size of our array.  The next parameter is the buffer to store the information found.
    // More information on the information that will be stored in selectBuffer is further below.
    // Setup our selection buffer to accept object ID's
    glSelectBuffer(32, selectBuffer);

    // This function returns information about many things in OpenGL.  We pass in GL_VIEWPORT
    // to get the view port coordinates.  It saves it like a RECT with {top, left, bottom, right}
    // Get the current view port coordinates
    glGetIntegerv(GL_VIEWPORT, viewportCoords);

    // Now we want to get out of our GL_MODELVIEW matrix and start effecting our
    // GL_PROJECTION matrix.  This allows us to check our X and Y coords against 3D space.
    // We now want to effect our projection matrix
    glMatrixMode(GL_PROJECTION);

    // We push on a new matrix so we don't effect our 3D projection
    glPushMatrix();

    // This makes it so it doesn't change the frame buffer if we render into it, instead,
    // a record of the names of primitives that would have been drawn if the render mode was
    // GL_RENDER are now stored in the selection array (selectBuffer).
    // Allows us to render the objects without changing framebuffer
    glRenderMode(GL_SELECT);

    // Reset our projection matrix
    glLoadIdentity();

    // gluPickMatrix allows us to create a projection matrix that is around our
    // cursor.  This basically only allows rendering in the region that we specify.
    // If an object is rendered into that region, then it saves that objects ID for us (The magic).
    // The first 2 parameters are the X and Y position to start from, then the next 2
    // are the width and height of the region from the starting point.  The last parameter is
    // of course our view port coordinates.  You will notice we subtract "y" from the
    // BOTTOM view port coordinate.  We do this to flip the Y coordinates around.  The 0 y
    // coordinate starts from the bottom, which is opposite to window's coordinates.
    // We also give a 2 by 2 region to look for an object in.  This can be changed to preference.
    gluPickMatrix(x, viewportCoords[3] - y, 2, 2, viewportCoords);

    // Next, we just call our normal gluPerspective() function, exactly as we did on startup.
    // This is to multiply the perspective matrix by the pick matrix we created up above.
    //Perspective view or Orthogonal View. Multiply by current projection matrix
    if(m_bPerspective)
    {
        GLfloat fov = 60.0f;
        gluPerspective(fov, (GLdouble)width()/height(), 1, 3000);
    }
    else
        glOrtho(-1.0, +1.0, -1.0, 1.0, -1.0, 1.0);


    // Go back into our model view matrix
    glMatrixMode(GL_MODELVIEW);

    m_cylinder.drawCurveControlPoints(true);

    // If we return to our normal render mode from select mode, glRenderMode returns
    // the number of objects that were found in our specified region (specified in gluPickMatrix())
    // Return to render mode and get the number of objects found
    objectsFound = glRenderMode(GL_RENDER);

    // Put our projection matrix back to normal.
    glMatrixMode(GL_PROJECTION);

    // Stop effecting our projection matrix
    glPopMatrix();

    // Go back to our normal model view matrix
    glMatrixMode(GL_MODELVIEW);

    if (objectsFound > 0)
    {
        // 1 is the first object's minimum Z value.
        // We use an unsigned int so we don't get a warning with selectBuffer below.
        unsigned int lowestDepth = selectBuffer[1];

        // Set the selected object to the first object to start it off.
        // 3 is the first object's object ID we passed into glLoadName().
        int selectedObject = selectBuffer[3];

        // Go through all of the objects found, but start at the second one
        for(int i = 1; i < objectsFound; i++)
        {
            // Check if the current objects depth is lower than the current lowest
            // Notice we times i by 4 (4 values for each object) and add 1 for the depth.
            if(selectBuffer[(i * 4) + 1] < lowestDepth)
            {
                // Set the current lowest depth
                lowestDepth = selectBuffer[(i * 4) + 1];

                // Set the current object ID
                selectedObject = selectBuffer[(i * 4) + 3];
            }
        }

        // Return the selected object
        return selectedObject;
    }

    // We didn't click on any objects so return nothing
    return -1;
}

int GLWidget::hitObjects(int x, int y, const int nMaxObjectsHit)
{
    int nFoundObjects = 0;
    int viewport[4] = {0};
    GLuint selectBuffer[32];
    int N = 6;

    glInitNames();
    glPushName(0);

    //Register selection buffer
    glSelectBuffer(32, selectBuffer);

    //Get Viewport from OpenGL. Can use this function to obtain many info
    glGetIntegerv(GL_VIEWPORT, viewport);

    //Need to change projection matrix
    glMatrixMode(GL_PROJECTION);

    //Save current projection matrix
    glPushMatrix();

    //load identity to top matrix
    glLoadIdentity();

    //Pick Matrix for receiving points
    gluPickMatrix((double)x, (double)(viewport[3] - y), N, N, viewport);

    //Perspective view or Orthogonal View. Multiply by current projection matrix
    if(m_bPerspective)
    {
        GLfloat fov = 60.0f;
        gluPerspective(fov, (GLdouble)width()/height(), 1, 3000);
    }
    else
        glOrtho(-1.0, +1.0, -1.0, 1.0, -1.0, 1.0);

    //Set render mode to select objects
    //glRenderMode(GL_SELECT);

    //Goto Model View to draw objects
    glMatrixMode(GL_MODELVIEW);

    //Draw with names
    m_cylinder.drawCurveControlPoints(true);

    //Revert to previous projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    nFoundObjects = glRenderMode(GL_RENDER);

    if(nFoundObjects > 0)
    {
        //Minimum Depth
        GLuint minDepth = selectBuffer[1];

        //Selection ID
        int selectID = selectBuffer[3];

        for(int i=1; i < nFoundObjects; i++)
        {
            if(selectBuffer[i*4 + 1] < minDepth)
            {
                minDepth = selectBuffer[i*4 + 1];
                selectID = selectBuffer[i*4 + 3];
            }
        }
        return selectID;
    }
    return -1;
}
