#include "glmaterial.h"
#include "glselect.h"

using namespace gl;

namespace nb {
namespace opengl {


GLMaterial::GLMaterial()
{
    mMaterial = Material::PredefinedJade();
}

GLMaterial::GLMaterial(const Material &mtrl)
{
    mMaterial = mtrl;
}

GLMaterial::~GLMaterial()
{

}

void GLMaterial::Bind()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mMaterial.ambient.GetConstData());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mMaterial.diffuse.GetConstData());
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mMaterial.specular.GetConstData());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mMaterial.shininess);
}

void GLMaterial::Unbind()
{

}

void GLMaterial::Set(const Material &mtrl)
{
    mMaterial = mtrl;
}

}
}
