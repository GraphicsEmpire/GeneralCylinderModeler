#include "glattribs.h"
#include "glselect.h"

using namespace nb::opengl;
using namespace gl;

GLAttribDepthTest::GLAttribDepthTest()
{
    gl::GLboolean b;
    gl::glGetBooleanv(GL_DEPTH_TEST, &b);
    mFlag = (bool)b;
}

void GLAttribDepthTest::Enable()
{
    glEnable(GL_DEPTH_TEST);
    mFlag = true;
}

void GLAttribDepthTest::Disable()
{
    glDisable(GL_DEPTH_TEST);
    mFlag = false;
}

///////////////////////////////////////////////
GLStoreAllAttributes::GLStoreAllAttributes()
{
    mStored = false;
}

void GLStoreAllAttributes::Enable()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    mStored = true;
}

void GLStoreAllAttributes::Disable()
{
    if(!mStored) {
        //nbLogError("The opengl attributes are not stored. Did you forget to make a call to enable?");
        return;
    }
    glPopAttrib();
    mStored = false;
}

///////////////////////////////////////////////
GLScopedAttributeStorage::GLScopedAttributeStorage():GLStoreAllAttributes()
{
    Enable();
}

GLScopedAttributeStorage::~GLScopedAttributeStorage()
{
    Disable();
}
