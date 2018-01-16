#ifndef CINTERVAL_H
#define CINTERVAL_H

#include <float.h>
#include "base.h"

namespace nb {
namespace linalg {

template <typename T>
class Interval
{

public:
    Interval():mLower(EPSILON), mUpper(FLT_MAX) {};

	Interval(T lower, T upper) {
		if (lower > upper) {
            mLower = upper;
            mUpper = lower;
		} else {
            mLower = lower;
            mUpper = upper;
		}
	}

	T GetLower() const { return mLower;}
	void SetLower(const T lower)
	{
        mLower = lower;
	}

	T GetUpper() const {return mUpper;}
	void SetUpper(const T max)
	{
        mUpper = max;
	}

	void Set(const T lower, const T upper)
	{
        mLower = lower;
        mUpper = upper;
	}

    T Length() { return (mUpper - mLower);}

    bool Contains(const T f) const { return ((f >= mLower)&&(f <= mUpper));}


    bool Overlaps(const Interval &a)
	{
        return (Contains(a.mLower))||(Contains(a.mUpper));
	}

    bool IsEqual(const Interval &a) const {
        return ((mLower == a.GetLower())&&(mUpper == a.GetUpper()));
    }

	Interval& operator=(const Interval& y)
	{
        this->mLower = y.mLower;
        this->mUpper = y.mUpper;
		return(*this);
	}

	bool operator==(const Interval& y) const
	{
        return ((this->mLower == y.mLower)&&(this->mUpper == y.mUpper));
	}

	bool operator!=(const Interval& y) const
	{
        return ((this->mLower != y.mLower)||(this->mUpper != y.mUpper));
	}

private:
    T mLower;
    T mUpper;
};

typedef Interval<nbReal> interval;

}
}

#endif
