#ifndef VECN_H
#define VECN_H

#include "base.h"
#include <math.h>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

namespace nb {
namespace linalg {

/*!
 * meta vector templated class
 */
template <U32 N, typename T>
class VecN;


/*!
 * base class for all vectors
 */
template <U32 N, typename T>
class VecN {
public:
    typedef T ELEMENT_TYPE;
    static const U32 ELEMENTS_COUNT = N;

    VecN() {}
    VecN(const VecN& rhs) {
        this->CopyFrom(rhs);
    }

    explicit VecN(const T* values) {
        for(U32 i=0; i < N; i++)
            this->e[i] = values[i];
    }

    explicit VecN(T value) {
        for(U32 i=0; i < N; i++)
            this->e[i] = value;
    }


    virtual ~VecN() {}

    inline void CopyFrom(const VecN &rhs) {
        for(U32 i=0; i < N; i++)
            this->e[i] = rhs.e[i];
    }

    //Load and Store
    void Load(const T *pValues) {
        for(U32 i=0; i < N; i++)
            this->e[i] = pValues[i];
    }

    void Store(T *pValues) const {
        for(U32 i=0; i < N; i++)
            pValues[i] = this->e[i];
    }

    T GetElement(int i) const {
        return e[i];
    }

    void SetElement(int i, T v) {
        e[i] = v;
    }

    inline T Length() const {
        return sqrt(Length2());
    }

    inline T Length2() const {
        T sum = 0;
        for(U32 i=0; i < N; i++)
            sum += this->e[i] * this->e[i];
        return sum;
    }

    static U32 GetElementsCount() { return N;}

    //shading
    static T Dot(const VecN &a, const VecN &b) {
        T sum = 0;
        for(U32 i=0; i < N; i++)
            sum += a.GetElement(i) * b.GetElement(i);
        return sum;
    }

    static T Distance(const VecN &a, const VecN &b) {
        return VecN::Sub(b, a).Length();
    }

    static VecN GetMinPoint(const VecN &a, const VecN &b) {
        VecN min_point;
        for(U32 i=0; i < N; i++) {
            min_point.e[i] = std::min<T>(a.GetElement(i), b.GetElement(i));
        }
        return min_point;
    }

    static VecN GetMaxPoint(const VecN &a, const VecN &b) {
        VecN max_point;
        for(U32 i=0; i < N; i++) {
            max_point.e[i] = std::max<T>(a.GetElement(i), b.GetElement(i));
        }
        return max_point;
    }

    //arithmetics
    static VecN Mul(const VecN &a, const VecN &b) {
        VecN result;
        for(U32 i=0; i < N; i++) {
            result.e[i] = a.GetElement(i) * b.GetElement(i);
        }
        return result;
    }

    static VecN Mul(T a, const VecN &b) {
        VecN result;
        for(U32 i=0; i < N; i++) {
            result.e[i] = a * b.GetElement(i);
        }
        return result;
    }

    static VecN Div(const VecN &a, const VecN &b) {
        VecN result;
        for(U32 i=0; i < N; i++) {
            result.e[i] = a.GetElement(i) / b.GetElement(i);
        }
        return result;
    }

    static VecN Add(const VecN &a, const VecN &b) {
        VecN result;
        for(U32 i=0; i < N; i++) {
            result.e[i] = a.GetElement(i) + b.GetElement(i);
        }
        return result;
    }

    static VecN Sub(const VecN &a, const VecN &b) {
        VecN result;
        for(U32 i=0; i < N; i++) {
            result.e[i] = a.GetElement(i) - b.GetElement(i);
        }
        return result;
    }

    T* GetData() {
        return &e[0];
    }

    const T* GetConstData() const {
        return &e[0];
    }

    inline T& operator[](int index) {
        return e[index];
    }

    inline const T& operator[](int index) const {
        return e[index];
    }

    template<U32 NN, typename TT>
    friend std::ostream & operator<<(std::ostream &os, const VecN<NN, TT>& v);

public:
    T e[N];
};

template<U32 N, typename T>
std::ostream & operator<<(std::ostream &os, const VecN<N, T>& v) {
    os << "[";
    for (int i = 0; i < N; ++i) {
      os << v.e[i];
      if ((i + 1) < N) {
        os << ", ";
      }
    }
    os << "]";
    return os;
}


//all paritial specializations
template<typename T>
using Vec2 = VecN<2, T>;

template<typename T>
using Vec3 = VecN<3, T>;

template<typename T>
using Vec4 = VecN<4, T>;

}
}

#endif // VECN_H
