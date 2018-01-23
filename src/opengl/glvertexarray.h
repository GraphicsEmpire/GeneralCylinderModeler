#ifndef GLVERTEXARRAY_H_
#define GLVERTEXARRAY_H_

#include <vector>
#include "utils/bindableinterface.h"
#include "linalg/base.h"

using namespace std;

namespace nb {
namespace opengl {


//enum VertexAttributeType {vatVertex, vatColor, vatNormal, vatTexCoord };


class GLVertexArray : public nb::utils::BindableInterface {
public:
    GLVertexArray();
    virtual ~GLVertexArray();

    enum VertexAttributeType { vatPosition, vatColor, vatNormal, vatTexCoord, vatGeneric };
    enum AttributeLayoutType { altSeparate, altSequentialBatch, altInterleave };


    //Attribute layout
    struct AttributeLayout {
        AttributeLayout() {}
        AttributeLayout(U32 dim_,
                        VertexAttributeType attrib_,
                        int gpu_attribute_layout_index_ = -1):dim(dim_), attrib(attrib_), gpuGenericVertexAttribArrayIndex(gpu_attribute_layout_index_) {}

        U32 dim;
        VertexAttributeType attrib;
        int gpuGenericVertexAttribArrayIndex;
    };

    //Complete buffer layout
    struct VertexBufferLayout {
        AttributeLayoutType layoutType;
        vector<AttributeLayout> attributes;
        vector<float> buffer;
    };

    bool Import(U32 count_vertices, const VertexBufferLayout *layouts, U32 count_layouts);


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
