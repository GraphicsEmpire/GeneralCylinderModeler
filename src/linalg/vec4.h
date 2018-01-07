#ifndef VEC4_H
#define VEC4_H

#include "base.h"

namespace nb {
namespace linalg {

////////////////////////////////////////////////////////////////
/*!
  * 4D Vector arithmetic
  */
template<typename T>
class VecN<4, T> {
public:
    //Constructors
    VecN<4, T>() {}
    explicit VecN<4, T>(T a_):x(a_), y(a_), z(a_), w(a_) {}
    explicit VecN<4, T>(T x_, T y_, T z_, T w_ = 1.0f) :x(x_), y(y_), z(z_), w(w_) {}
    explicit VecN<4, T>(const Vec2<T>& vl2, const Vec2<T>& vr2):x(vl2.x), y(vl2.y), z(vr2.x), w(vr2.y) {}
    explicit VecN<4, T>(const Vec3<T>& v3, T w_):x(v3.x), y(v3.y), z(v3.z), w(w_) {}
    VecN<4, T>(const VecN<4, T>& rhs):x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}
    VecN<4, T>(const T* pValues) {
        Load(pValues);
    }

    static size_t GetElementsCount() { return 4;}

    //Load and Store
    void Load(const T *pValues) {
        x = pValues[0];
        y = pValues[1];
        z = pValues[2];
        w = pValues[3];
    }

    void Store(T *pValues) const {
        pValues[0] = x;
        pValues[1] = y;
        pValues[2] = z;
        pValues[3] = w;
    }

    //member overrides
    inline T GetElement(int i) const;
    inline void SetElement(int i, T v);

    /*!
      * Get the xyz part of the 4D vector
      */
    inline Vec3<T> GetXYZ() const;
    T* GetData() {return &e[0];}
    const T* GetConstData() const {return &e[0];}

    /*!
      * The dot product of two 4D vectors
      */
    static T Dot(const Vec4 <T> &a, const Vec4 <T> &b);
    static Vec4<T> GetMinPoint(const Vec4 <T> &a, const Vec4 <T> &b);
    static Vec4<T> GetMaxPoint(const Vec4 <T> &a, const Vec4 <T> &b);
    static Vec4<T> GetClamped(const Vec4 <T> &a, float aMin, float aMax);

    //Primary Operators
    static Vec4<T> Mul(const Vec4 <T> &a, const Vec4 <T> &b);
    static Vec4<T> Mul(T a, const Vec4 <T> &b);
    static Vec4<T> Div(const Vec4 <T> &a, const Vec4 <T> &b);
    static Vec4<T> Add(const Vec4 <T> &a, const Vec4 <T> &b);
    static Vec4<T> Sub(const Vec4 <T> &a, const Vec4 <T> &b);
    static bool IsEqual(const Vec4 <T> &a, const Vec4 <T> &b);


    //Operators
    inline Vec4<T>& operator=(const Vec4<T>& rhs);
    inline bool operator==(const Vec4<T>& rhs);
    inline Vec4<T> operator*(T s) const;
    inline Vec4<T> operator+(const Vec4<T>& rhs) const;
    inline Vec4<T> operator-(const Vec4<T>& rhs) const;
    inline T& operator[](int index);
    inline const T& operator[](int index) const;
public:
    union{
        struct{
            T x;
            T y;
            T z;
            T w;
        };
        T e[4];
    };
};

//Implementation
template<typename T>
Vec3<T> Vec4<T>::GetXYZ() const
{
    return Vec3<T>(this->x, this->y, this->z);
}

template<typename T>
T Vec4<T>::GetElement(int i) const
{
    assert(i >=0 && i < 4);
    return this->e[i];
}

template<typename T>
void Vec4<T>::SetElement(int i, T v)
{
    assert(i >=0 && i < 4);
    this->e[i] = v;
}


template<typename T>
T Vec4<T>::Dot(const Vec4 <T> &a, const Vec4 <T> &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<typename T>
Vec4<T> Vec4<T>::GetMinPoint(const Vec4 <T> &a, const Vec4 <T> &b) {
    Vec4<T> result;
    result.x = MATHMIN(a.x, b.x);
    result.y = MATHMIN(a.y, b.y);
    result.z = MATHMIN(a.z, b.z);
    result.w = MATHMIN(a.w, b.w);
    return result;
}

template<typename T>
Vec4<T> Vec4<T>::GetMaxPoint(const Vec4 <T> &a, const Vec4 <T> &b) {
    Vec4<T> result;
    result.x = MATHMAX(a.x, b.x);
    result.y = MATHMAX(a.y, b.y);
    result.z = MATHMAX(a.z, b.z);
    result.w = MATHMAX(a.w, b.w);
    return result;
}

template<typename T>
Vec4<T> Vec4<T>::Mul(const Vec4 <T> &a, const Vec4 <T> &b) {
    Vec4<T> result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    result.w = a.w * b.w;
    return result;
}

template<typename T>
Vec4<T> Vec4<T>::Mul(T a, const Vec4 <T> &b) {
    Vec4<T> result;
    result.x = a * b.x;
    result.y = a * b.y;
    result.z = a * b.z;
    result.w = a * b.w;
    return result;
}


template<typename T>
Vec4<T> Vec4<T>::Div(const Vec4 <T> &a, const Vec4 <T> &b) {
    Vec4<T> result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    result.z = a.z / b.z;
    result.w = a.w / b.w;
    return result;
}

template<typename T>
Vec4<T> Vec4<T>::Add(const Vec4 <T> &a, const Vec4 <T> &b) {
    Vec4<T> result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}

template<typename T>
Vec4<T> Vec4<T>::Sub(const Vec4 <T> &a, const Vec4 <T> &b) {
    Vec4<T> result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    return result;
}

template<typename T>
Vec4<T> Vec4<T>::GetClamped(const Vec4 <T> &a, float aMin, float aMax) {
        Vec4<T> result = a;
        Clamp<T>(result.x, aMin, aMax);
        Clamp<T>(result.y, aMin, aMax);
        Clamp<T>(result.z, aMin, aMax);
        Clamp<T>(result.w, aMin, aMax);
        return result;
}

template<typename T>
bool Vec4<T>::IsEqual(const Vec4 <T> &a, const Vec4 <T> &b) {
    return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}


template<typename T>
Vec4<T>& Vec4<T>::operator=(const Vec4<T>& rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    this->z = rhs.z;
    this->w = rhs.w;
    return (*this);
}

template<typename T>
bool Vec4<T>::operator==(const Vec4<T>& rhs) {
    return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->w == rhs.w);
}

template<typename T>
Vec4<T> Vec4<T>::operator*(T s) const
{
    Vec4<T> result;
    result.x = x * s;
    result.y = y * s;
    result.z = z * s;
    result.w = w * s;
    return result;
}

template<typename T>
Vec4<T> Vec4<T>::operator+(const Vec4<T>& rhs) const
{
    Vec4<T> result;
    result.x = x + rhs.x;
    result.y = y + rhs.y;
    result.z = z + rhs.z;
    result.w = w + rhs.w;
    return result;
}

template<typename T>
Vec4<T> Vec4<T>::operator-(const Vec4<T>& rhs) const
{
    Vec4<T> result;
    result.x = x - rhs.x;
    result.y = y - rhs.y;
    result.z = z - rhs.z;
    result.w = w - rhs.w;
    return result;
}

template<typename T>
T& Vec4<T>::operator[](int index) {
        return e[index];
}

template<typename T>
const T& Vec4<T>::operator[](int index) const {
        return e[index];
}

typedef Vec4<nbReal> vec4;
typedef Vec4<double> vec4d;
typedef Vec4<bool>   vec4b;

typedef Vec4<I32>   vec4i;
typedef Vec4<U32>	 vec4u;

typedef Vec4<I8>	vec4i8;
typedef Vec4<U8>	vec4u8;
typedef Vec4<I16>   vec4i16;
typedef Vec4<U16>	 vec4u16;
typedef Vec4<I32>   vec4i32;
typedef Vec4<U32>	 vec4u32;
typedef Vec4<I64>   vec4i64;
typedef Vec4<U64>	 vec4u64;


}
}

#endif // VEC4_H
