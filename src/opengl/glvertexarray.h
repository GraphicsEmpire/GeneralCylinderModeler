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

    enum VertexAttributeIndex : U32 { kPosition = 0x0, kNormal = 0x1, kTexture = 0x2, kColor = 0x3, kWeight = 0x4 };
    enum AttributeLayoutType { altSeparate, altSequentialBatch, altInterleave };


    //Attribute layout
    class GLVertexAttribute {
    public:
        GLVertexAttribute():mIndex(kPosition), mCount(0) {}
        GLVertexAttribute(VertexAttributeIndex index,
                          U32 count):mIndex(index), mCount(count) {}
    public:
        VertexAttributeIndex mIndex;
        U32 mCount;
    };


    //Complete buffer layout
    struct GLVertexBufferLayout {
        AttributeLayoutType layoutType;
        vector<GLVertexAttribute> attributes;
        vector<float> buffer;
    };

    /*!
     * Reads in a vertex data buffer to the gpu memory
     * @param count_vertices number of vertices to read in
     * @param layouts an array representing the buffer layout
     * @param count_layouts number of buffer layouts supplied
     * @return true when vertex data is imported successfully
     */
    bool Import(U32 count_vertices, const GLVertexBufferLayout *layouts, U32 count_layouts);


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
