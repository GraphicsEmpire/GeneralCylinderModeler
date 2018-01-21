#include "catmullromcurve.h"


namespace nb {
  namespace render {

      CatmullRomCurve::CatmullRomCurve() {

      }

      CatmullRomCurve::CatmullRomCurve(const CatmullRomCurve& rhs) {

      }

      void CatmullRomCurve::AddCtrlPoint(const nb::linalg::Vec3<float>& p) {
        mCtrlPoints.push_back(p.x);
        mCtrlPoints.push_back(p.y);
        mCtrlPoints.push_back(p.z);

        if(mFOnCurveDataChanged)
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

          if(mFOnCurveDataChanged)
              mFOnCurveDataChanged();
      }

      const vector<float> CatmullRomCurve::GetCtrlPoints() const {
          return mCtrlPoints;
      }


  }
}
