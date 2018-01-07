#ifndef VEC2_H
#define VEC2_H

#include "base.h"

namespace nb {
namespace linalg {

/*!
  * 2D Vector arithmetic
  */
template<typename T>
class VecN<2, T>  {
public:
    //Constructors
    VecN<2, T>() {}
    explicit VecN<2, T>(T a_):x(a_), y(a_) {}
    explicit VecN<2, T>(T x_, T y_):x(x_), y(y_) {}
    VecN<2, T>(const VecN<2, T>& rhs):x(rhs.x), y(rhs.y) {}
    VecN<2, T>(const T* pValues) {
        Load(pValues);
    }

    static size_t GetElementsCount() { return 2;}

    //Load and Store
    void Load(const T *pValues) {
        x = pValues[0];
        y = pValues[1];
    }

    void Store(const T *pValues) const {
        pValues[0] = x;
        pValues[1] = y;
    }


    //Public this functions
    inline void Normalize();
    inline Vec2<T> GetNormalized() const;
    inline T Length() const;
    inline T Length2() const;

    //Axis
    inline int LongestAxis() const;

    //access elements
    T  GetElement(int i) const;
    void SetElement(int i, T v);

    T* GetData() {return &e[0];}
    const T* GetConstData() const {return &e[0];}


    //Static Functions
    static T Dot(const Vec2 <T> &a, const Vec2 <T> &b);
    static T GetInnerAngleDegree(const Vec2 <T> &a, const Vec2 <T> &b);
    static Vec2<T> Reflect(const Vec2 <T> &a, const Vec2 <T> &n);
    static T Distance(const Vec2 <T> &a, const Vec2 <T> &b);
    static Vec2<T> GetMinPoint(const Vec2 <T> &a, const Vec2 <T> &b);
    static Vec2<T> GetMaxPoint(const Vec2 <T> &a, const Vec2 <T> &b);

    //Primary operators
    static Vec2<T> Mul(const Vec2 <T> &a, const Vec2 <T> &b);
    static Vec2<T> Mul(T a, const Vec2 <T> &b);
    static Vec2<T> Div(const Vec2 <T> &a, const Vec2 <T> &b);
    static Vec2<T> Add(const Vec2 <T> &a, const Vec2 <T> &b);
    static Vec2<T> Sub(const Vec2 <T> &a, const Vec2 <T> &b);
    static bool IsEqual(const Vec2 <T> &a, const Vec2 <T> &b);


    //Operators
    inline Vec2<T>& operator=(const Vec2<T>& rhs);
    inline Vec2<T> operator*(T s) const;
    inline Vec2<T> operator+(const Vec2<T>& rhs) const;
    inline Vec2<T> operator-(const Vec2<T>& rhs) const;
    inline bool operator==(const Vec2<T>& rhs) const;
    inline T& operator[](int index);
    inline const T& operator[](int index) const;
public:
    union{
        struct{
            T x;
            T y;
        };
        T e[2];
    };
};

template<typename T>
inline void Vec2<T>::Normalize(){
    T dInv = 1.0 / sqrt(x*x + y*y);
    x *= dInv;
    y *= dInv;
}

template<typename T>
inline Vec2<T> Vec2<T>::GetNormalized() const{
    Vec2<T> result = (*this);
    result.Normalize();
    return result;
}

template<typename T>
inline T Vec2<T>::Length() const{
    return sqrt(x*x + y*y);
}

template<typename T>
inline T Vec2<T>::Length2() const{
    return (x*x + y*y);
}

template<typename T>
inline int Vec2<T>::LongestAxis() const {
        return (x > y)? 0:1;
}

template<typename T>
T  Vec2<T>::GetElement(int i) const {
    return this->e[i];
}

template<typename T>
void Vec2<T>::SetElement(int i, T v) {
    this->e[i] = v;
}


template<typename T>
Vec2<T>& Vec2<T>::operator=(const Vec2<T>& rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    return (*this);
}

template<typename T>
Vec2<T> Vec2<T>::operator*(T s) const
{
    Vec2<T> result;
    result.x = x * s;
    result.y = y * s;
    return result;
}

template<typename T>
Vec2<T> Vec2<T>::operator+(const Vec2<T>& rhs) const
{
    Vec2<T> result;
    result.x = x + rhs.x;
    result.y = y + rhs.y;
    return result;
}

template<typename T>
Vec2<T> Vec2<T>::operator-(const Vec2<T>& rhs) const
{
    Vec2<T> result;
    result.x = x - rhs.x;
    result.y = y - rhs.y;
    return result;
}

template<typename T>
bool Vec2<T>::operator==(const Vec2<T>& rhs) const
{
    return (x == rhs.x && y == rhs.y);
}

template<typename T>
T& Vec2<T>::operator[](int index) {
        return e[index];
}

template<typename T>
const T& Vec2<T>::operator[](int index) const {
        return e[index];
}

template<typename T>
T Vec2<T>::Dot(const Vec2 <T> &a, const Vec2 <T> &b)
{
    return a.x * b.x + a.y * b.y;
}

template<typename T>
T Vec2<T>::GetInnerAngleDegree(const Vec2 <T> &a, const Vec2 <T> &b)
{
    Vec2<T> aN = a.GetNormalized();
    Vec2<T> bN = b.GetNormalized();
    return RADTODEG(acos(Dot(aN, bN)));
}

template<typename T>
Vec2<T> Vec2<T>::Reflect(const Vec2 <T> &a, const Vec2 <T> &n)
{
    Vec2<T> result = - a + 2.0 * Dot(a, n);
    return result;
}

template<typename T>
T Vec2<T>::Distance(const Vec2 <T> &a, const Vec2 <T> &b)
{
    return (b - a).length();
}

template<typename T>
Vec2<T> Vec2<T>::GetMinPoint(const Vec2 <T> &a, const Vec2 <T> &b)
{
    Vec2<T> result;
    result.x = MATHMIN(a.x, b.x);
    result.y = MATHMIN(a.y, b.y);
    return result;
}

template<typename T>
Vec2<T> Vec2<T>::GetMaxPoint(const Vec2 <T> &a, const Vec2 <T> &b)
{
    Vec2<T> result;
    result.x = MATHMAX(a.x, b.x);
    result.y = MATHMAX(a.y, b.y);
    return result;
}

template<typename T>
Vec2<T> Vec2<T>::Mul(const Vec2 <T> &a, const Vec2 <T> &b) {
    Vec2<T> result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    return result;
}

template<typename T>
Vec2<T> Vec2<T>::Mul(T a, const Vec2 <T> &b) {
    Vec2<T> result;
    result.x = a * b.x;
    result.y = a * b.y;
    return result;
}

template<typename T>
Vec2<T> Vec2<T>::Div(const Vec2 <T> &a, const Vec2 <T> &b) {
    Vec2<T> result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    return result;
}

template<typename T>
Vec2<T> Vec2<T>::Add(const Vec2 <T> &a, const Vec2 <T> &b) {
    Vec2<T> result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

template<typename T>
Vec2<T> Vec2<T>::Sub(const Vec2 <T> &a, const Vec2 <T> &b) {
    Vec2<T> result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

template<typename T>
bool Vec2<T>::IsEqual(const Vec2 <T> &a, const Vec2 <T> &b) {
    return (a.x == b.x && a.y == b.y);
}


typedef Vec2<nbReal> vec2;
typedef Vec2<double> vec2d;
typedef Vec2<bool> vec2b;

typedef Vec2<I32>   vec2i;
typedef Vec2<U32>	 vec2u;

typedef Vec2<I8>	vec2i8;
typedef Vec2<U8>	vec2u8;
typedef Vec2<I16>   vec2i16;
typedef Vec2<U16>	 vec2u16;
typedef Vec2<I32>   vec2i32;
typedef Vec2<U32>	 vec2u32;
typedef Vec2<I64>   vec2i64;
typedef Vec2<U64>	 vec2u64;



}
}
#endif // VEC2_H
