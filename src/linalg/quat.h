#ifndef QUATERNION_H
#define QUATERNION_H

#include <math.h>
#include "vec.h"

namespace nb {
namespace linalg {

/*!
 * Quaternions are used for defining rotational chains. It helps to avoid the gymball-lock phenomenon.
 */
template <typename T>
class Quaternion
{
public:
    Quaternion() { Identity();}
    Quaternion(const Quaternion& rhs):x(rhs.x),y(rhs.y),z(rhs.z), w(rhs.w) {}
    Quaternion(T x_, T y_, T z_, T w_):x(x_),y(y_),z(z_), w(w_) {}

    Quaternion(const Vec3< T >& q_, T w_):x(q_.x),y(q_.y),z(q_.z), w(w_) {}
    Quaternion(const Vec4< T >& q_):x(q_.x),y(q_.y),z(q_.z), w(q_.w) {}

	void Identity() {
        x = y = z = 0.0;
		w = 1;
	}

	//As Vec3
	Vec3<T> ToVec3() const {
		return Vec3<T>(x, y, z);
	}

	//As Vec4
	Vec4<T> ToVec4() const {
		return Vec4<T>(x, y, z, w);
	}

    //Normalize Quaternion
    void Normalize();

	//transform
    Vec3<T> TransformPoint(const Vec3 <T> &p) const;
    Vec3<T> TransformPoint(const Quaternion &inv, const Vec3 <T> &p) const;

    //Convert To/From Euler
    void FromEuler(T roll, T pitch, T yaw);
    void ToEuler(T &roll, T &pitch, T &yaw) const;

    // Convert axis/angle
    void FromAxisAngle(const Vec3 <T> &axis, T deg);
    void ToAxisAngle(Vec3 <T> &axis, T &deg) const;

    // Taking the reciprocal of a quaternion makes its rotation go the other way
    void Reciprocate();
    void Invert();
    Quaternion GetInverted() const;

    //Ops
    Quaternion Mul(const Quaternion &b) const;
    static Quaternion Mul(const Quaternion &a, const Quaternion &b);


    //overloads
    Quaternion& operator =(const Quaternion& rhs);
    bool operator==(const Quaternion &rhs) const;
    Quaternion operator*(const Quaternion& rhs) const;
    inline T& operator[](int index);
    inline const T& operator[](int index) const;
public:
    //x/y/z/w components of quaternion.
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

template <typename T>
void Quaternion<T>::Normalize()
{
    T	dist, square;

    square = x * x + y * y + z * z + w * w;
    if (square > 0.0f)
        dist = (T)(1.0f / sqrt(square));
    else
        dist = 1;

    x *= dist;
    y *= dist;
    z *= dist;
    w *= dist;
}

template <typename T>
Vec3<T> Quaternion<T>::TransformPoint(const Vec3 <T> &p) const
{
    Quaternion input(p, 0.0f);
    Quaternion inv = GetInverted();

    Quaternion res = Mul(input);
    return res.Mul(inv).ToVec3();
}

template <typename T>
Vec3<T> Quaternion<T>::TransformPoint(const Quaternion &inv, const Vec3 <T> &p) const
{
    Quaternion input(p, 0.0);
    Quaternion res = Mul(input);
    return res.Mul(inv).ToVec3();
}

// build quaternion based on euler angles
template <typename T>
void Quaternion<T>::FromEuler(T roll, T pitch, T yaw)
{
    roll  *= 0.5f;
    pitch *= 0.5f;
    yaw   *= 0.5f;

    T cr = (T)cos(roll);
    T cp = (T)cos(pitch);
    T cy = (T)cos(yaw);

    T sr = (T)sin(roll);
    T sp = (T)sin(pitch);
    T sy = (T)sin(yaw);

    T cpcy = cp * cy;
    T spsy = sp * sy;
    T spcy = sp * cy;
    T cpsy = cp * sy;

    w = cr * cpcy + sr * spsy;
    x = sr * cpcy - cr * spsy;
    y = cr * spcy + sr * cpsy;
    z = cr * cpsy - sr * spcy;
}

template <typename T>
void Quaternion<T>::ToEuler(T &roll, T &pitch, T &yaw) const
{
    T sint		= (2.0f * w * y) - (2.0f * x * z);
    T cost_temp = 1.0f - (sint * sint);
    T cost		= 0;

    if ( (T)fabs(cost_temp) > 0.001f )
    {
        cost = sqrt( cost_temp );
    }

    T sinv, cosv, sinf, cosf;
    if ( (T)fabs(cost) > 0.001f )
    {
        sinv = ((2.0f * y * z) + (2.0f * w * x)) / cost;
        cosv = (1.0f - (2.0f * x * x) - (2.0f * y * y)) / cost;
        sinf = ((2.0f * x * y) + (2.0f * w * z)) / cost;
        cosf = (1.0f - (2.0f * y * y) - (2.0f * z * z)) / cost;
    }
    else
    {
        sinv = (2.0f * w * x) - (2.0f * y * z);
        cosv = 1.0f - (2.0f * x * x) - (2.0f * z * z);
        sinf = 0;
        cosf = 1.0f;
    }

    // compute output rotations
    roll	= atan2( sinv, cosv );
    pitch	= atan2( sint, cost );
    yaw		= atan2( sinf, cosf );
}

template <typename T>
void Quaternion<T>::FromAxisAngle(const Vec3 <T> &axis, T deg)
{
    T halftheta    = DEGTORAD(deg) * 0.5;
    T sinHalfTheta = (T)sin( halftheta );
    T cosHalfTheta = (T)cos( halftheta );

    x = axis.x*sinHalfTheta;
    y = axis.y*sinHalfTheta;
    z = axis.z*sinHalfTheta;
    w = cosHalfTheta;
}

template <typename T>
void Quaternion<T>::ToAxisAngle(Vec3 <T> &axis, T &deg) const
{
    deg = RADTODEG(acos(w) * 2.0);
    T sa = sqrt(1.0f - w*w);
    if (sa)
        axis = Vec3<T>(x/sa, y/sa, z/sa);
    else
        axis = Vec3<T>(1,0,0);
}


template <typename T>
void Quaternion<T>::Reciprocate()
{
    x = -x;
    y = -y;
    z = -z;
}

template <typename T>
void Quaternion<T>::Invert()
{
    T square = x * x + y * y + z * z + w * w;
    if(square == 0.0)
        square = 1.0;
    T coeff = 1.0/square;
    x = x * (- coeff);
    y = y * (- coeff);
    z = z * (- coeff);
    w = w * coeff;
}

template <typename T>
Quaternion<T> Quaternion<T>::GetInverted() const
{
    Quaternion res = *this;
    res.Invert();
    return res;
}

template <typename T>
Quaternion<T> Quaternion<T>::Mul(const Quaternion &b) const {
	return Mul(*this, b);
}

template <typename T>
Quaternion<T> Quaternion<T>::Mul(const Quaternion &a, const Quaternion &b)
{
    Quaternion res;
    res.x = b.w * a.x + b.x * a.w + b.y * a.z - b.z * a.y;
    res.y = b.w * a.y + b.y * a.w + b.z * a.x - b.x * a.z;
    res.z = b.w * a.z + b.z * a.w + b.x * a.y - b.y * a.x;
    res.w = b.w * a.w - b.x * a.x - b.y * a.y - b.z * a.z;
    res.Normalize();
    return res;
}

template <typename T>
Quaternion<T>& Quaternion<T>::operator=(const Quaternion& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return(*this);
}

template <typename T>
bool Quaternion<T>::operator==(const Quaternion &rhs) const
{
    return ( rhs.x == x && rhs.y == y && rhs.z == z && rhs.w == w );
}

template <typename T>
Quaternion<T> Quaternion<T>::operator*(const Quaternion& rhs) const
{
	return Mul(*this, rhs);
}

template<typename T>
T& Quaternion<T>::operator[](int index) {
	return e[index];
}

template<typename T>
const T& Quaternion<T>::operator[](int index) const {
	return e[index];
}

typedef Quaternion<nbReal> quat;

}
}
#endif
