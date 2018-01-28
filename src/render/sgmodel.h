#ifndef SGMODEL_H
#define SGMODEL_H

#include <vector>
#include <memory>
#include <unordered_map>
#include "opengl/gltypes.h"
#include "sgrenderinterface.h"

using namespace std;

namespace nb {
namespace render {

class SGModelImplementation;

/*!
 * SGModel represents a geometry storage to create 3D models programmatically
 */
class SGModel : public SGRenderInterface {
public:
    SGModel();
    virtual ~SGModel();

    void Begin(const nb::opengl::GLFaceType& ftype);
    void End();

    void AddFace(U32* faces, U32 count);
    void AddFace(const std::vector<U32>& indices);
    void AddVertex( const std::vector<float>&)

    void Render(const nb::linalg::mat4 &modelview,
                const nb::linalg::mat4 &projection) override;

protected:
    void SyncDeviceBuffers();
    void Cleanup();

protected:
    std::vector<U32> mIndices;
    std::unordered_map<nb::opengl::GLVertexAttributeIndex, std::vector<float> > mVertexAttribs;
    std::unique_ptr<SGModelImplementation> mImpl;
};

}
}

#endif // SGMODEL_H
