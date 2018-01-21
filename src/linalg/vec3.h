#ifndef VEC3_H
#define VEC3_H

#include "base.h"

namespace nb {
namespace linalg {


////////////////////////////////////////////////////////////////
/*!
  * 3D Vector arithmetic
  */
template<typename T>
class VecN<3, T> {
public:
    //Constructors
    VecN<3, T>() {}
    explicit VecN<3, T>(T a_):x(a_), y(a_), z(a_) {}
    explicit VecN<3, T>(T x_, T y_, T z_):x(x_), y(y_), z(z_) {}
    VecN<3, T>(const VecN<3, T>& rhs):x(rhs.x), y(rhs.y), z(rhs.z) {}
    VecN<3, T>(const T* pValues) {
        Load(pValues);
    }

    static size_t GetElementsCount() { return 3;}

    //Load and Store
    void Load(const T *pValues) {
        x = pValues[0];
        y = pValues[1];
        z = pValues[2];
    }

    void Store(T *pValues) const {
        pValues[0] = x;
        pValues[1] = y;
        pValues[2] = z;
    }

    //Public this functions
    inline void Normalize();
    inline Vec3<T> GetNormalized() const;
    inline T Length() const;
    inline T Length2() const;

    //member overrides
    inline T GetElement(int i) const;
    inline void SetElement(int i, T v);

    //Axis Ops
    inline int LongestAxis() const;

    //Pointers
    T* GetData() {return &e[0];}
    const T* GetConstData() const {return &e[0];}

    //shading
    static T Dot(const Vec3 <T> &a, const Vec3 <T> &b);
    static Vec3<T> Cross(const Vec3 <T> &a, const Vec3 <T> &b);
    static T GetInnerAngleDegree(const Vec3 <T> &a, const Vec3 <T> &b);
    static Vec3<T> Reflect(const Vec3 <T> &a, const Vec3 <T> &n);
    static T Distance(const Vec3 <T> &a, const Vec3 <T> &b);
    static Vec3<T> GetMinPoint(const Vec3 <T> &a, const Vec3 <T> &b);
    static Vec3<T> GetMaxPoint(const Vec3 <T> &a, const Vec3 <T> &b);
    static T CubeSurface(const Vec3 <T> &lo, const Vec3 <T> &hi);

    //arithmetics
    static Vec3<T> Mul(const Vec3 <T> &a, const Vec3 <T> &b);
    static Vec3<T> Mul(T a, const Vec3 <T> &b);
    static Vec3<T> Div(const Vec3 <T> &a, const Vec3 <T> &b);
    static Vec3<T> Add(const Vec3 <T> &a, const Vec3 <T> &b);
    static Vec3<T> Sub(const Vec3 <T> &a, const Vec3 <T> &b);
    static bool IsEqual(const Vec3 <T> &a, const Vec3 <T> &b);


    //op overload
    inline Vec3<T>& operator=(const Vec3<T>& rhs);
    inline Vec3<T> operator*(T s) const;
    inline bool operator==(const Vec3<T>& rhs) const;
    inline Vec3<T> operator+(const Vec3<T>& rhs) const;
    inline Vec3<T> operator-(const Vec3<T>& rhs) const;
    inline T& operator[](int index);
    inline const T& operator[](int index) const;
public:
    union{
        struct{
            T x;
            T y;
            T z;
        };
        T e[3];
    };
};

template<typename T>
inline void Vec3<T>::Normalize(){
        T len = sqrt(x*x + y*y + z*z);
        if(len == 0.0)
                return;
    T dInv = (T)1.0 / len;
    x *= dInv;
    y *= dInv;
    z *= dInv;
}

template<typename T>
inline Vec3<T> Vec3<T>::GetNormalized() const {
    Vec3<T> result = (*this);
    result.Normalize();
    return result;
}

template<typename T>
inline T Vec3<T>::Length() const {
    return sqrt(x*x + y*y + z*z);
}

template<typename T>
inline T Vec3<T>::Length2() const {
        return (x*x + y*y + z*z);
}

template<typename T>
inline int Vec3<T>::LongestAxis() const {
        if(x > y && x > z)
                return 0;
        else if(y > z)
                return 1;
        else
                return 2;
}

template<typename T>
T  Vec3<T>::GetElement(int i) const {
    return this->e[i];
}

template<typename T>
void Vec3<T>::SetElement(int i, T v) {
    this->e[i] = v;
}

template<typename T>
Vec3<T>& Vec3<T>::operator=(const Vec3<T>& rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    this->z = rhs.z;
    return (*this);
}

template<typename T>
bool Vec3<T>::operator==(const Vec3<T>& rhs) const
{
    return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z);
}


template<typename T>
Vec3<T> Vec3<T>::operator*(T s) const
{
    Vec3<T> result;
    result.x = x * s;
    result.y = y * s;
    result.z = z * s;
    return result;
}



template<typename T>
Vec3<T> Vec3<T>::operator+(const Vec3<T>& rhs) const
{
    Vec3<T> result;
    result.x = x + rhs.x;
    result.y = y + rhs.y;
    result.z = z + rhs.z;
    return result;
}

template<typename T>
Vec3<T> Vec3<T>::operator-(const Vec3<T>& rhs) const
{
    Vec3<T> result;
    result.x = x - rhs.x;
    result.y = y - rhs.y;
    result.z = z - rhs.z;
    return result;
}

template<typename T>
T& Vec3<T>::operator[](int index) {
        return e[index];
}

template<typename T>
const T& Vec3<T>::operator[](int index) const {
        return e[index];
}

template<typename T>
T Vec3<T>::Dot(const Vec3 <T> &a, const Vec3 <T> &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<typename T>
Vec3<T> Vec3<T>::Cross(const Vec3 <T> &a, const Vec3 <T> &b)
{
    Vec3<T> result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

template<typename T>
T Vec3<T>::GetInnerAngleDegree(const Vec3 <T> &a, const Vec3 <T> &b)
{
    Vec3<T> aN = a.GetNormalized();
    Vec3<T> bN = b.GetNormalized();
    return RADTODEG(acos(Dot(aN, bN)));
}

template<typename T>
Vec3<T> Vec3<T>::Reflect(const Vec3 <T> &a, const Vec3 <T> &n)
{
    //Vec3<T> result = a * static_cast<T>(-1.0) + dot(a, n) * static_cast<T>(2.0);
    Vec3<T> result = a * (-1.0) + n * 2.0 * Dot(a, n);
    return result;
}

template<typename T>
T Vec3<T>::Distance(const Vec3 <T> &a, const Vec3 <T> &b)
{
    return (b - a).Length();
}

template<typename T>
Vec3<T> Vec3<T>::GetMinPoint(const Vec3 <T> &a, const Vec3 <T> &b)
{
    Vec3<T> result;
    result.x = MATHMIN(a.x, b.x);
    result.y = MATHMIN(a.y, b.y);
    result.z = MATHMIN(a.z, b.z);

    return result;
}

template<typename T>
Vec3<T> Vec3<T>::GetMaxPoint(const Vec3 <T> &a, const Vec3 <T> &b)
{
    Vec3<T> result;
    result.x = MATHMAX(a.x, b.x);
    result.y = MATHMAX(a.y, b.y);
    result.z = MATHMAX(a.z, b.z);

    return result;
}

template<typename T>
T Vec3<T>::CubeSurface(const Vec3 <T> &lo, const Vec3 <T> &hi)
{
    Vec3<T> d = Vec3<T>::Sub(hi, lo);
        return 2.0 * (d.x * d.y + d.y * d.z + d.x * d.z);
}

template<typename T>
Vec3<T> Vec3<T>::Mul(const Vec3 <T> &a, const Vec3 <T> &b) {
    Vec3<T> result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    return result;
}

template<typename T>
Vec3<T> Vec3<T>::Mul(T a, const Vec3 <T> &b) {
    Vec3<T> result;
    result.x = a * b.x;
    result.y = a * b.y;
    result.z = a * b.z;
    return result;
}

template<typename T>
Vec3<T> Vec3<T>::Div(const Vec3 <T> &a, const Vec3 <T> &b) {
    Vec3<T> result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    result.z = a.z / b.z;
    return result;
}

template<typename T>
Vec3<T> Vec3<T>::Add(const Vec3 <T> &a, const Vec3 <T> &b) {
    Vec3<T> result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

template<typename T>
Vec3<T> Vec3<T>::Sub(const Vec3 <T> &a, const Vec3 <T> &b) {
    Vec3<T> result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

template<typename T>
bool Vec3<T>::IsEqual(const Vec3 <T> &a, const Vec3 <T> &b) {
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}


typedef Vec3<nbReal> vec3;
typedef Vec3<double>  vec3d;
typedef Vec3<bool>  vec3b;

typedef Vec3<I32>   vec3i;
typedef Vec3<U32>	 vec3u;

typedef Vec3<I8>	vec3i8;
typedef Vec3<U8>	vec3u8;
typedef Vec3<I16>   vec3i16;
typedef Vec3<U16>	 vec3u16;
typedef Vec3<I32>   vec3i32;
typedef Vec3<U32>	 vec3u32;
typedef Vec3<I64>   vec3i64;
typedef Vec3<U64>	 vec3u64;

}
}

#endif // VEC3_H
