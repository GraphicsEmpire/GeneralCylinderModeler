#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec.h"

namespace nb {
namespace linalg {

/*!
 * \brief The Material class represents the shading material properties of a surface.
 * The interaction of the light source with the surface is defined in terms of the ambient,
 * diffuse, specular and shininess power.
 */
class Material {
public:
    Material() {}
    Material(const Material& rhs) {
        CopyFrom(rhs);
    }

    static const U32 MaterialDataArrayLength=13;
    using PacketType=VecN<MaterialDataArrayLength, float>;

    explicit Material(const vec4& ambient_and_diffuse) {
        ambient = ambient_and_diffuse;
        diffuse = ambient_and_diffuse;
        specular = vec4(1.0f);
        shininess = 1.0f;
    }

    explicit Material(const vec4& amb, const vec4& dif, const vec4& spec, float shininess_power) {
        this->ambient = amb;
        this->diffuse = dif;
        this->specular = spec;
        this->shininess = shininess_power;
    }

    explicit Material(const float data[MaterialDataArrayLength]) {
        CopyFrom(data);
    }

    explicit Material(const PacketType& packet) {
        CopyFrom(packet);
    }


    void CopyFrom(const Material &rhs) {
        this->ambient = rhs.ambient;
        this->diffuse = rhs.diffuse;
        this->specular = rhs.specular;
        this->shininess = rhs.shininess;
    }

    void CopyFrom(const PacketType &packet) {
        this->ambient.Load(&packet.e[0]);
        this->diffuse.Load(&packet.e[4]);
        this->specular.Load(&packet.e[8]);
        this->shininess = packet.e[12];
    }

    void CopyFrom(const float *data) {
        this->ambient.Load(&data[0]);
        this->diffuse.Load(&data[4]);
        this->specular.Load(&data[8]);
        this->shininess = data[12];
    }

    PacketType ToPacket() const {
        PacketType packet;
        ambient.Store(&packet.e[0]);
        diffuse.Store(&packet.e[4]);
        specular.Store(&packet.e[8]);
        packet.e[12] = shininess;
        return packet;
    }

    const Material& operator=(const Material& rhs) {
        this->CopyFrom(rhs);
        return *this;
    }

    //All Materials
    static Material PredefinedEmerald();
    static Material PredefinedJade();
    static Material PredefinedRuby();
public:
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

}
}

#endif
