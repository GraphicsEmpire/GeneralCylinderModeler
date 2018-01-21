#include "glfacearray.h"
#include "glselect.h"

namespace nb {
namespace opengl {

GLFaceArray::GLFaceArray()
{
    m_ready = false;
    m_ebo = 0;
}

GLFaceArray::~GLFaceArray() {
    clear();
}

bool GLFaceArray::Import(const vector<U32> &indices, GLFaceType ftype) {
    if(indices.size() == 0)
        return false;

    clear();

    glGenBuffers(1, &m_ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(U32), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //hold extra data
    m_count = indices.size();
    m_ftype = ftype;
    m_ready = true;
    return true;
}

void GLFaceArray::Bind() {
    if(!m_ready)
        return;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

    // Draw the faces
    glDrawElements(
        (GLenum)m_ftype,      // mode
        m_count,    // count
        GL_UNSIGNED_INT,   // type
        (void*)0           // element array buffer offset
    );
}

void GLFaceArray::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLFaceArray::clear()
{
    if(!m_ready)
        return;
    if(glIsBuffer(m_ebo))
        glDeleteBuffers(1, &m_ebo);
}

}
}
