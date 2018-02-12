//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#include "catmullromcurve.h"
#include <linalg/interval.h>
#include <utils/logger.h>

using namespace nb::utils;

namespace nb {
    namespace render {

        CatmullRomCurve::CatmullRomCurve() {

        }

        CatmullRomCurve::CatmullRomCurve(const CatmullRomCurve &rhs) {
            CopyFrom(rhs);
        }

        CatmullRomCurve::~CatmullRomCurve() {
            Clear();
        }


        void CatmullRomCurve::AddCtrlPoint(const nb::linalg::Vec3<float> &p) {
            mCtrlPoints.push_back(p.x);
            mCtrlPoints.push_back(p.y);
            mCtrlPoints.push_back(p.z);

            //if we got enough control points
            if(CountCtrlPoints() >= 4) {
                ComputeNormalizedDistancesBetweenKnots();
                ComputeCurvePoints();
            }

            if (mFOnCurveDataChanged)
                mFOnCurveDataChanged();
        }

        bool CatmullRomCurve::ComputeNormalizedDistancesBetweenKnots() {
            mKnotsLengthNormalized.resize(0);
            U32 count_ctrlpoints = CountCtrlPoints();
            if(count_ctrlpoints < 4)
                return false;

            U32 count_splines = count_ctrlpoints - 3;
            mKnotsLengthNormalized.resize(count_splines);

            Vec3<float> p1(&mCtrlPoints[1 * 3]);
            Vec3<float> p2;
            float accumulator = 0.0f;
            for(U32 i=0; i < count_splines; i++) {
                p2.Load(&mCtrlPoints[(i + 2) * 3]);
                float d = Vec3<float>::Distance(p1, p2);
                mKnotsLengthNormalized[i] = d;
                accumulator += d;

                p1 = p2;
            }

            //normalize all distances
            if(accumulator > 0.0) {
                for (U32 i = 0; i < count_splines; i++) {
                    mKnotsLengthNormalized[i] /= accumulator;
                }
            }

            return true;
        }

        U32 CatmullRomCurve::CountCurveProfilePoints() const {
            return mCurveProfilePoints.size() / 3;
        }

        U32 CatmullRomCurve::CountCtrlPoints() const {
            return mCtrlPoints.size() / 3;
        }

        U32 CatmullRomCurve::CountSplines() const {
            U32 ctrl_points_count = CountCtrlPoints();
            if(ctrl_points_count < 4)
                return 0;
            return ctrl_points_count - 3;
        }

        void CatmullRomCurve::ComputeCurvePoints() {
            if(CountSplines() == 0) {
                nbLogError("Not enough control points yet to make a spline");
                return;
            }

            if(mKnotsLengthNormalized.size() != CountSplines()) {
                nbLogError("Provide normalized distances between knots to make this algorithm to work.");
                return;
            }

            //Fixed step-size over the curve parameter
            const U32 num_curve_points = 1000;
            const float delta = 1.0f / static_cast<float>(num_curve_points);

            //removes all previous curve points
            mCurveProfilePoints.resize((num_curve_points + 1) * 3);

            for(U32 i=0; i <= num_curve_points; i++) {
                float t = static_cast<float>(i) * delta;
                Vec3<float> p = GetPosition(t);

                mCurveProfilePoints[i * 3 + 0] = p.x;
                mCurveProfilePoints[i * 3 + 1] = p.y;
                mCurveProfilePoints[i * 3 + 2] = p.z;
            }
        }

        Vec3<float> CatmullRomCurve::GetPosition(float t) {
            float splineT;
            std::array< Vec3<float>, 4> splineCtrlPoints;
            if(ExtractLocalSpline(t, splineT, splineCtrlPoints))
                return ComputeSplinePosition(splineT, splineCtrlPoints);
            else
                return Vec3<float>(0.0f);
        }

        Vec3<float> CatmullRomCurve::GetTangent(float t) {
            float splineT;
            std::array< Vec3<float>, 4> splineCtrlPoints;
            if(ExtractLocalSpline(t, splineT, splineCtrlPoints))
                return ComputeSplineTangent(splineT, splineCtrlPoints);
            else
                return Vec3<float>(0.0f);
        }

        Vec3<float> CatmullRomCurve::GetAcceleration(float t) {
            float splineT;
            std::array< Vec3<float>, 4> splineCtrlPoints;
            if(ExtractLocalSpline(t, splineT, splineCtrlPoints))
                return ComputeSplineAcceleration(splineT, splineCtrlPoints);
            else
                return Vec3<float>(0.0f);
        }

        void CatmullRomCurve::RegisterOnCurveDataChangedCallBack(OnCurveDataChanged cb) {
            mFOnCurveDataChanged = cb;
        }

        void CatmullRomCurve::Clear() {
            mCtrlPoints.resize(0);
            mCurveProfilePoints.resize(0);
            mKnotsLengthNormalized.resize(0);
            mAccumulatedArcLength.resize(0);
        }

        const vector<float> CatmullRomCurve::GetCtrlPoints() const {
            return mCtrlPoints;
        }

        const std::vector<float> CatmullRomCurve::GetCurveProfilePoints() const {
            return mCurveProfilePoints;
        }


        void CatmullRomCurve::CopyFrom(const CatmullRomCurve &rhs) {
            mCtrlPoints.assign(rhs.mCtrlPoints.begin(), rhs.mCtrlPoints.end());
            mCurveProfilePoints.assign(rhs.mCurveProfilePoints.begin(), rhs.mCurveProfilePoints.end());
            mFOnCurveDataChanged = rhs.mFOnCurveDataChanged;

            ComputeNormalizedDistancesBetweenKnots();
            ComputeCurvePoints();
        }

        void CatmullRomCurve::Cleanup() {
            mCtrlPoints.resize(0);
            mCurveProfilePoints.resize(0);
            mAccumulatedArcLength.resize(0);
            mKnotsLengthNormalized.resize(0);
            mFOnCurveDataChanged = nullptr;
        }


        bool CatmullRomCurve::ExtractLocalSpline(float globalT,
                                                 float &splineT,
                                                 std::array<Vec3<float>, 4> &splineCtrlPoints) {
            U32 nsplines = CountSplines();
            if(nsplines == 0)
                return false;

            //make sure global T is between 0 and 1
            Clamp<float>(globalT, 0.0f, 1.0f);

            float accumulator = 0.0;
            nb::linalg::Interval<float> spline_param_domain(0.0, 1.0);
            for(int i=0; i < nsplines; i++) {
                float d = mKnotsLengthNormalized[i];

                //if not the last spline use normalized knot length
                if(i < nsplines - 1)
                    spline_param_domain.Set(accumulator, accumulator + d);
                else
                    spline_param_domain.Set(accumulator, 1.0f);

                if(spline_param_domain.Contains(globalT)) {
                    int selected_spline = i;
                    splineT = (globalT - accumulator) / d;

                    //assign control points
                    for(int j = 0; j < 4; j++) {
                        int ctrlpoint_index = selected_spline + j;
                        Vec3<float> p(&mCtrlPoints[ctrlpoint_index * 3]);
                        splineCtrlPoints[j] = p;
                    }

                    return true;
                }

                //add up distances
                accumulator += d;
            }

            return false;
        }


        Vec3<float> CatmullRomCurve::ComputeSplinePosition(float splineT, const std::array<Vec3<float>, 4> &splineCtrlPoints) {
            //p(u) = U^T * M * B
            //U = [u^3 u^2 u^1 1]
            //M Matrix =0.5 * [-1 3 -3  1]
            //                [2 -5  4 -1]
            //				  [-1 0  1  0]
            //                [0  2  0  0]
            //B = [Pi-1 pi pi+1 pi+2]
            float ts2 = splineT * splineT;
            float ts3 = ts2 * splineT;

            float b0 = float(0.5 * (-ts3 + 2*ts2 - splineT));
            float b1 = float(0.5 * (3*ts3 -5*ts2 + 2));
            float b2 = float(0.5 * (-3*ts3 + 4*ts2 + splineT));
            float b3 = float(0.5 * (ts3 - ts2));

            Vec3<float> p = Vec3<float>::Mul(b0, splineCtrlPoints[0]) + Vec3<float>::Mul(b1, splineCtrlPoints[1]) +
                            Vec3<float>::Mul(b2, splineCtrlPoints[2]) + Vec3<float>::Mul(b3, splineCtrlPoints[3]);
            return p;
        }

        Vec3<float>
        CatmullRomCurve::ComputeSplineTangent(float splineT, const std::array<Vec3<float>, 4> &splineCtrlPoints) {
            //p(u) = U`^T * M * B
            //U`^T = [3u^2 2*u 1 0]
            //M Matrix =0.5 * [-1 3 -3  1]
            //                [2 -5  4 -1]
            //				  [-1 0  1  0]
            //                [0  2  0  0]
            //B = [Pi-1 pi pi+1 pi+2]
            float ts2 = splineT * splineT;

            float b0 = float(0.5 * (-3*ts2 + 4*splineT - 1));
            float b1 = float(0.5 * (9*ts2 -10*splineT));
            float b2 = float(0.5 * (-9*ts2 + 8*splineT + 1));
            float b3 = float(0.5 * (3*ts2 - 2*splineT));

            Vec3<float> tangent = Vec3<float>::Mul(b0, splineCtrlPoints[0]) + Vec3<float>::Mul(b1, splineCtrlPoints[1]) +
                            Vec3<float>::Mul(b2, splineCtrlPoints[2]) + Vec3<float>::Mul(b3, splineCtrlPoints[3]);
            return tangent;
        }

        Vec3<float>
        CatmullRomCurve::ComputeSplineAcceleration(float splineT, const std::array<Vec3<float>, 4> &splineCtrlPoints) {
            //p(u) = U``^T * M * B
            //U``^T = [6u 2 0 0]
            //M Matrix =0.5 * [-1 3 -3  1]
            //                [2 -5  4 -1]
            //				  [-1 0  1  0]
            //                [0  2  0  0]
            //B = [Pi-1 pi pi+1 pi+2]

            float b0 = float(0.5 * (-6*splineT + 4));
            float b1 = float(0.5 * (18*splineT - 10));
            float b2 = float(0.5 * (-18*splineT + 8));
            float b3 = float(0.5 * (6*splineT - 2));

            Vec3<float> acc = Vec3<float>::Mul(b0, splineCtrlPoints[0]) + Vec3<float>::Mul(b1, splineCtrlPoints[1]) +
                                  Vec3<float>::Mul(b2, splineCtrlPoints[2]) + Vec3<float>::Mul(b3, splineCtrlPoints[3]);
            return acc;
        }



    }
}
