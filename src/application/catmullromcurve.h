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
     * Represents the data storage for a Catmull-Rom curve.
     * The curve is built according to the following algorithm:
     *
     * 1. The curve is split into multiple splines. Number of splines is equal to
     *   the number of control point minus 3, so we need as least 4 control points to compute
     *   the first spline.
     *
     * 2. Starting from the first point, the position, tangent and acceleration are computed
     *   per each regular point.
     *
     * 3. The step size on the curve parameter is advanced according to the following equation:
     *   dt = distance(stop, start) / ns
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

        /*!
         * Clears all curve points and computed data for the curve along with the
         * control points
         */
        void Clear();

        /*!
         * Adds a new control point to the curve
         * @param p a 3D point
         */
        void AddCtrlPoint(const nb::linalg::Vec3<float>& p);

        /*!
         * Return the count of curve profile points
         * @return number of points on the curve
         */
        U32 CountCurveProfilePoints() const;
        U32 CountCtrlPoints() const;
        U32 CountSplines() const;

        Vec3<float> GetPosition(float t);
        Vec3<float> GetTangent(float t);
        Vec3<float> GetAcceleration(float t);

        /*!
         * Provides access to the control points of the curve
         * @return vector of control points
         */
        const std::vector<float> GetCtrlPoints() const;

        /*!
         * Provides access to the curve profile points
         * @return vector of curve points
         */
        const std::vector<float> GetCurveProfilePoints() const;

        void RegisterOnCurveDataChangedCallBack(OnCurveDataChanged cb);

    protected:
        void Cleanup();

        void ComputeCurvePoints();

        bool ComputeNormalizedDistancesBetweenKnots();

        /*!
         * Computes which local spline should be processed using the global curve parameter t.
         * Outputs the local spline parameter and the associated list of control points
         * @param globalT the global curve parameter
         * @param splineT the local spline parameter
         * @param splineCtrlPoints the associated list of control points
         * @return true when the correct spline is selected
         */
        bool ExtractLocalSpline(float globalT,
                                float& splineT,
                                std::array<Vec3<float>, 4>& splineCtrlPoints);

        /*!
         * Computes a point on the spline at normalized parameter t using the 4 control
         * points supplied.
         * @param splineT local spline normalized parameter
         * @param splineCtrlPoints input control points
         * @return a 3D point on the spline curve
         */
        static Vec3<float> ComputeSplinePosition(float splineT,
                                                 const std::array<Vec3<float>, 4>& splineCtrlPoints);


        static Vec3<float> ComputeSplineTangent(float splineT,
                                                 const std::array<Vec3<float>, 4>& splineCtrlPoints);

        static Vec3<float> ComputeSplineAcceleration(float splineT,
                                                     const std::array<Vec3<float>, 4>& splineCtrlPoints);

    protected:
        std::vector<float> mAccumulatedArcLength;
        std::vector<float> mKnotsLengthNormalized;

        std::vector<float> mCtrlPoints;
        std::vector<float> mCurveProfilePoints;
        OnCurveDataChanged mFOnCurveDataChanged;
    };

}
}

#endif
