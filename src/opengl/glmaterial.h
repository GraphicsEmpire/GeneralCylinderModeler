#ifndef GLMATERIAL_H
#define GLMATERIAL_H

#include "utils/bindableinterface.h"
#include "linalg/material.h"

using namespace nb::linalg;

namespace nb {
namespace opengl {

/*!
 * \brief The GLMaterial class represents the mesh material properties
 */
class GLMaterial : public nb::utils::BindableInterface
{
public:
    GLMaterial();
    GLMaterial(const Material& mtrl);
    virtual ~GLMaterial();

    void Bind() override;
    void Unbind() override;

    void Set(const Material &mtrl);
protected:
    Material mMaterial;
};

}
}

#endif // GLMATERIAL_H
