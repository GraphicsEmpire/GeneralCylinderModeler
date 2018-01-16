#ifndef GLTRANSFORM_H
#define GLTRANSFORM_H

#include "utils/bindableinterface.h"
#include "linalg/matrix.h"

using namespace nb::linalg;

namespace nb {
namespace opengl {

class GLTransform : public nb::utils::BindableInterface
{
public:
    enum GLMatrixMode {mmModelView, mmProjection, mmTexture, mmColor};

    GLTransform();
    GLTransform(GLMatrixMode mode, const mat4& matrix);
    virtual ~GLTransform();

    void Set(GLMatrixMode mode, const mat4 &matrix);
    void LoadIdentity();


    void Bind() override;
    void Unbind() override;

protected:
    GLMatrixMode mMode;
    mat4 mMatrix;
};

}
}

#endif // GLTRANSFORM_H
