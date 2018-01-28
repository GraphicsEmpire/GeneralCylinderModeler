//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#ifndef LIBUMF_OPENGL_GLFACEARRAY_H
#define LIBUMF_OPENGL_GLFACEARRAY_H

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

#endif // LIBUMF_OPENGL_GLFACEARRAY_H
