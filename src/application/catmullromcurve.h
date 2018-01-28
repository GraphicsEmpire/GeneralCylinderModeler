//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#ifndef CATMULLROM_CURVE_H
#define CATMULLROM_CURVE_H

#include <vector>
#include <functional>
#include "linalg/vec.h"

using namespace std;
using namespace nb::linalg;

namespace nb {
  namespace render {

    typedef std::function<void(void)> OnCurveDataChanged;

    /*!
     * Represents the data storage for a Catmull-Rom curve
     */
    class CatmullRomCurve {
    public:
        CatmullRomCurve();
        CatmullRomCurve(const CatmullRomCurve& rhs);

        void Clear();
        void AddCtrlPoint(const nb::linalg::Vec3<float>& p);
        U32 CountCtrlPoints() const;
        void ComputeCurvePoints();

        Vec3<float> GetPosition(float t);
        Vec3<float> GetTangent(float t);
        Vec3<float> GetAcceleration(float t);

        const std::vector<float> GetCtrlPoints() const;

        void RegisterOnCurveDataChangedCallBack(OnCurveDataChanged cb);
    protected:
        std::vector<float> mRegularPoints;
        std::vector<float> mCtrlPoints;
        OnCurveDataChanged mFOnCurveDataChanged;
    };

}
}

#endif
