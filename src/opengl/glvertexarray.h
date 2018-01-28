//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#ifndef LIBUMF_OPENGL_GLVERTEXARRAY_H
#define LIBUMF_OPENGL_GLVERTEXARRAY_H

#include <vector>
#include "utils/bindableinterface.h"
#include "linalg/base.h"
#include "gltypes.h"

using namespace std;

namespace nb {
namespace opengl {

/*!
 * GLVertexArray provides an opengl vertex buffer to store the vertex data on the GPU memory.
 */
class GLVertexArray : public nb::utils::BindableInterface {
public:
    GLVertexArray();
    virtual ~GLVertexArray();




    //Attribute layout
    class GLVertexAttribute {
    public:
        GLVertexAttribute():mIndex(kPosition), mCount(0) {}
        GLVertexAttribute(GLVertexAttributeIndex index,
                          U32 count):mIndex(index), mCount(count) {}

        U32 GetCount() const { return mCount; }
        GLVertexAttributeIndex  GetVertexAttributeIndex() const { return mIndex; }
    protected:
        GLVertexAttributeIndex mIndex;
        U32 mCount;
    };

    /*!
     *
     * @param attribs array of vertex attributes
     * @param vdata the vertex data to be imported into video memory
     * @param layout the type of layout
     * @return true when vertices are loaded successfully
     */
    bool Import(const vector<GLVertexAttribute>& attribs,
                const vector<float>& vdata,
                GLVertexAttributeLayoutType layout = kSeparate);

    void Bind() override;
    void Unbind() override;

protected:
    void clear();

protected:
    vector<U32> mVertexBufferObjects;
    U32 mVertexArrayObject;
    bool mValid;
};

}
}
#endif
