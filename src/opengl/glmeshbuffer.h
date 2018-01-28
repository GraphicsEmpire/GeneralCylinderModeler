//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#ifndef LIBUMF_OPENGL_GLMESHBUFFER_H
#define LIBUMF_OPENGL_GLMESHBUFFER_H

#include <memory>
#include <vector>
#include "utils/bindableinterface.h"
#include "glvertexarray.h"
#include "glfacearray.h"
#include "gltexture.h"

using namespace std;

namespace nb {
namespace opengl {

enum GLPolygonMode {glRenderModePointCloud = 0x1B00, glRenderModeLine = 0x1B01, glRenderModeFill = 0x1B02};

/*!
 * \brief The GLMeshPartBuffer class
 */
class GLMeshBuffer : public nb::utils::BindableInterface {
public:
    GLMeshBuffer();
    virtual ~GLMeshBuffer();

    typedef shared_ptr<GLVertexArray> GLVertexArrayPtrType;
    typedef shared_ptr<GLFaceArray> GLFaceArrayPtrType;    

    void Bind() override;
    void Unbind() override;

    void Clear();

    GLVertexArrayPtrType AddVertexAttribArray();
    GLVertexArrayPtrType GetVertexAttribArray(U32 index);
    U32 CountVertexAttribArrays() const;

    GLFaceArrayPtrType AddFaceArray();
    GLFaceArrayPtrType GetFaceArray(U32 index);
    U32 CountFaceArrays() const;

    void SetPolygonRenderMode(GLPolygonMode mode);



protected:
    void Setup();
    bool IsVertexAttribArrayIndex(U32 index) const;
    bool IsFaceArrayIndex(U32 index) const;

protected:
    vector<GLVertexArrayPtrType> mVertexAttribs;
    vector<GLFaceArrayPtrType> mFaceArrays;
    GLPolygonMode mPolygonRenderMode;

};

typedef nb::utils::BindableCollection<GLMeshBuffer> GLMeshBufferCollection;

}
}

#endif // LIBUMF_OPENGL_GLMESHBUFFER_H
