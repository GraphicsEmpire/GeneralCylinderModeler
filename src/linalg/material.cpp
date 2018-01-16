#include "material.h"

namespace nb {
namespace linalg {

Material Material::PredefinedEmerald()
{
    Material result;
    result.ambient = vec4(0.0215f, 0.1745f, 0.0215f, 1.0f);
    result.diffuse = vec4(0.07568f, 0.61424f, 0.07568f, 1.0f);
    result.specular = vec4(0.633f, 0.727811f, 0.633f, 1.0f);
    result.shininess = 0.6f;
    return result;
}

Material Material::PredefinedJade()
{
    Material result;
    result.ambient = vec4(0.135f, 0.2225f, 0.1575f, 1.0f);
    result.diffuse = vec4(0.54f, 0.89f, 0.63f, 1.0f);
    result.specular = vec4(0.316228f, 0.316228f, 0.316228f, 1.0f);
    result.shininess = 0.1f;
    return result;
}

Material Material::PredefinedRuby()
{
    Material result;
    result.ambient = vec4(0.1745f, 0.01175f, 0.1175f, 1.0f);
    result.diffuse = vec4(0.61624f, 0.04136f, 0.04136f, 1.0f);
    result.specular = vec4(0.727811f, 0.626959f, 0.626959f, 1.0f);
    result.shininess = 0.6f;
    return result;
}

}
}
