//
// Project libumf: Unified Anisotropic Volume and Surface Mesh
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#ifndef LIBUMF_LINALG_COLOR_H
#define LIBUMF_LINALG_COLOR_H

#include "vec.h"

namespace nb {
namespace linalg {


class Color {
public:
	Color() {
        mColor = vec4(0,0,0,1);
	}

	explicit Color(U8 r, U8 g, U8 b, U8 a = 255) {
		FromRGBA(r, g, b, a);
	}

	explicit Color(const vec4u8& color) {
		FromRGBA(color);
	}

    explicit Color(const vec4& color) {
        mColor = color;
	}

	Color(const Color& other) {
        mColor = other.mColor;
	}

	void FromRGBA(const vec4u8 &color) {
		FromRGBA(color.x, color.y, color.z, color.w);
	}

	void FromRGBA(U8 r, U8 g, U8 b, U8 a = 255) {
		static const float fconv = 1.0f / 255.0f;
        mColor = vec4((float)r, (float)g, (float)b, (float)a) * fconv;
	}

    void FromRGBA(const vec4 &color) { mColor = color;}

    vec4 ToVec4() const { return mColor;}

	vec4u8 ToVec4u8() const {
        vec4u8 res((U8)(mColor.x * 255.0f), (U8)(mColor.y * 255.0f), (U8)(mColor.z * 255.0f), (U8)(mColor.w * 255.0f));
		return res;
	}

	Color& operator=(const Color& rhs) {
        mColor = rhs.mColor;
		return *this;
	}

	//sample colors
	static Color Red() { return Color(255, 0, 0);}
	static Color Green() { return Color(0, 255, 0);}
	static Color Blue() { return Color(0, 0, 255);}
	static Color Grey() { return Color(128, 128, 128);}
	static Color Black() { return Color(0, 0, 0);}
    static Color White() { return Color(255, 255, 255);}
	static Color Skin() { return Color(239, 208, 207);}

private:
    vec4 mColor;

};

}
}



#endif /* LIBUMF_LINALG_COLOR_H */
