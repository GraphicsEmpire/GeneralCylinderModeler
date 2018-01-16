#include "gltransform.h"
#include "glselect.h"

using namespace gl;

namespace nb {
namespace opengl {

GLTransform::GLTransform()
{
    mMode = mmModelView;
    mMatrix.SetIdentity();
}

GLTransform::GLTransform(GLMatrixMode mode, const mat4 &matrix)
{
    mMode = mode;
    mMatrix = matrix;
}

GLTransform::~GLTransform()
{

}

void GLTransform::Set(GLTransform::GLMatrixMode mode, const mat4 &matrix)
{
    mMode = mode;
    mMatrix = matrix;
}

void GLTransform::Bind()
{
    switch(mMode) {
    case(mmModelView):
        glMatrixMode(GL_MODELVIEW);
        break;
    case(mmProjection):
        glMatrixMode(GL_PROJECTION);
        break;
    case(mmColor):
        glMatrixMode(GL_COLOR);
        break;
    case(mmTexture):
        glMatrixMode(GL_TEXTURE);
        break;
    }

    glPushMatrix();
    glMultMatrixf(mMatrix.GetConstData());
}

void GLTransform::Unbind()
{
    switch(mMode) {
        case(mmModelView):
            glMatrixMode(GL_MODELVIEW);
            break;
        case(mmProjection):
            glMatrixMode(GL_PROJECTION);
            break;
        case(mmColor):
            glMatrixMode(GL_COLOR);
            break;
        case(mmTexture):
            glMatrixMode(GL_TEXTURE);
            break;
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void GLTransform::LoadIdentity() {
    switch(mMode) {
        case(mmModelView):
            glMatrixMode(GL_MODELVIEW);
            break;
        case(mmProjection):
            glMatrixMode(GL_PROJECTION);
            break;
        case(mmColor):
            glMatrixMode(GL_COLOR);
            break;
        case(mmTexture):
            glMatrixMode(GL_TEXTURE);
            break;
    }
    glLoadIdentity();
}


}
}
