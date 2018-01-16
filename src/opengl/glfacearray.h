#ifndef GLFACEARRAY_H
#define GLFACEARRAY_H

#include <vector>
#include "utils/bindableinterface.h"
#include "gltypes.h"
#include "linalg/base.h"

using namespace std;

namespace nb {
namespace opengl {


class GLFaceArray : public nb::utils::BindableInterface
{
public:
    GLFaceArray();
    virtual ~GLFaceArray();


    bool Import(const vector<U32> &indices, GLFaceType ftype = ftTriangles);

    void Bind() override;
    void Unbind() override;

protected:
    void clear();

protected:
    U32 m_ebo;
    U32 m_count;
    GLFaceType m_ftype;
    bool m_ready;
};


}
}

#endif // GLFACEARRAY_H
