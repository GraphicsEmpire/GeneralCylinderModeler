#ifndef GLMESHBUFFER_H
#define GLMESHBUFFER_H

#include <memory>
#include <vector>
#include "utils/bindableinterface.h"
#include "glvertexarray.h"
#include "glfacearray.h"
//#include "gltexture.h"

using namespace std;

namespace nb {
namespace opengl {

enum GLPolygonMode {glRenderModePointCloud = 0x1B00, glRenderModeLine = 0x1B01, glRenderModeFill = 0x1B02};

/*!
 * \brief The GLMeshBuffer class
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

#endif // GLMESHBUFFER_H
