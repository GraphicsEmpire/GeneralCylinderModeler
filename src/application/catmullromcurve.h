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
#include <array>
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
        virtual ~CatmullRomCurve();

        /*!
         * Copies the curve data from another instance
         * @param rhs
         */
        void CopyFrom(const CatmullRomCurve& rhs);

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
        void Cleanup();

        /*!
         * Computes which local spline should be processed using the global curve parameter t.
         * Outputs the local spline parameter and the associated list of control points
         * @param globalT the global curve parameter
         * @param splineT the local spline parameter
         * @param cp the associated list of control points
         * @return true when the correct spline is selected
         */
        bool ExtractLocalSpline(float globalT, float& splineT, std::array<Vec3<float>, 4>& cp);

        /*!
         * Computes a point on the spline at normalized parameter t using the 4 control
         * points supplied.
         * @param ts local spline normalized parameter
         * @param cp input control points
         * @return a 3D point on the spline curve
         */
        static Vec3<float> ComputeSplinePosition(float ts, const std::array<Vec3<float>, 4>& cp);

    protected:
        std::vector<float> mRegularPoints;
        std::vector<float> mCtrlPoints;
        OnCurveDataChanged mFOnCurveDataChanged;
    };

}
}

#endif
