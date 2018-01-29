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


namespace nb {
    namespace render {

        CatmullRomCurve::CatmullRomCurve() {

        }

        CatmullRomCurve::CatmullRomCurve(const CatmullRomCurve &rhs) {
            CopyFrom(rhs);
        }

        CatmullRomCurve::~CatmullRomCurve() {

        }


        void CatmullRomCurve::AddCtrlPoint(const nb::linalg::Vec3<float> &p) {
            mCtrlPoints.push_back(p.x);
            mCtrlPoints.push_back(p.y);
            mCtrlPoints.push_back(p.z);

            if (mFOnCurveDataChanged)
                mFOnCurveDataChanged();
        }

        U32 CatmullRomCurve::CountCtrlPoints() const {
            return mCtrlPoints.size() / 3;
        }

        void CatmullRomCurve::ComputeCurvePoints() {


        }

        Vec3<float> CatmullRomCurve::GetPosition(float t) {
            return nb::linalg::Vec3<float>();
        }

        Vec3<float> CatmullRomCurve::GetTangent(float t) {
            return nb::linalg::Vec3<float>();
        }

        Vec3<float> CatmullRomCurve::GetAcceleration(float t) {
            return nb::linalg::Vec3<float>();
        }

        void CatmullRomCurve::RegisterOnCurveDataChangedCallBack(OnCurveDataChanged cb) {
            mFOnCurveDataChanged = cb;
        }

        void CatmullRomCurve::Clear() {
            mCtrlPoints.resize(0);
            mRegularPoints.resize(0);

            if (mFOnCurveDataChanged)
                mFOnCurveDataChanged();
        }

        const vector<float> CatmullRomCurve::GetCtrlPoints() const {
            return mCtrlPoints;
        }

        void CatmullRomCurve::CopyFrom(const CatmullRomCurve &rhs) {
            mCtrlPoints.assign(rhs.mCtrlPoints.begin(), rhs.mCtrlPoints.end());
            mRegularPoints.assign(rhs.mRegularPoints.begin(), rhs.mRegularPoints.end());
            mFOnCurveDataChanged = rhs.mFOnCurveDataChanged;
        }

        void CatmullRomCurve::Cleanup() {
            mRegularPoints.resize(0);
            mRegularPoints.resize(0);
            mFOnCurveDataChanged = nullptr;
        }


        bool CatmullRomCurve::ExtractLocalSpline(float globalT, float &splineT, std::array<Vec3<float>, 4> &cp) {
            U32 nslices = CountCtrlPoints() - 3;
        }


        Vec3<float> CatmullRomCurve::ComputeSplinePosition(float ts, const std::array<Vec3<float>, 4> &cp) {
            //p(u) = U^T * M * B
            //U = [u^3 u^2 u^1 1]
            //M Matrix =0.5 * [-1 3 -3  1]
            //                [2 -5  4 -1]
            //				  [-1 0  1  0]
            //                [0  2  0  0]
            //B = [Pi-1 pi pi+1 pi+2]
            float ts2 = ts * ts;
            float ts3 = ts2 * ts;

            float b0 = float(0.5 * (-ts3 + 2*ts2 - ts));
            float b1 = float(0.5 * (3*ts3 -5*ts2 + 2));
            float b2 = float(0.5 * (-3*ts3 + 4*ts2 + ts));
            float b3 = float(0.5 * (ts3 - ts2));

            Vec3<float> p = Vec3<float>::Mul(b0, cp[0]) + Vec3<float>::Mul(b1, cp[1]) +
                            Vec3<float>::Mul(b2, cp[2]) + Vec3<float>::Mul(b3, cp[3]);
            return p;
        }

    }
}
