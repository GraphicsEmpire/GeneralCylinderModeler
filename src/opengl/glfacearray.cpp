#include "glfacearray.h"
#include "glselect.h"

namespace nb {
namespace opengl {

GLFaceArray::GLFaceArray()
{
    mInitialized = false;
    mIBO = 0;
}

GLFaceArray::~GLFaceArray() {
    clear();
}

bool GLFaceArray::Import(const vector<U32> &indices, GLFaceType ftype) {
    if(indices.size() == 0)
        return false;

    clear();

    glGenBuffers(1, &mIBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(U32), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //hold extra data
    mCount = indices.size();
    mFaceType = ftype;
    mInitialized = true;
    return true;
}

void GLFaceArray::Bind() {
    if(!mInitialized)
        return;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

    // Draw the faces
    glDrawElements(
        (GLenum)mFaceType,      // mode
        mCount,    // count
        GL_UNSIGNED_INT,   // type
        (void*)0           // element array buffer offset
    );
}

void GLFaceArray::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLFaceType GLFaceArray::GetFaceType() const
{
    return mFaceType;
}

void GLFaceArray::SetFaceType(const GLFaceType &ftype)
{
    mFaceType = ftype;
}

void GLFaceArray::clear()
{
    if(!mInitialized)
        return;
    if(glIsBuffer(mIBO))
        glDeleteBuffers(1, &mIBO);
}

}
}
