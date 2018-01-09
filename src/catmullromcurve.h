#ifndef CATMULLROM_CURVE_H
#define CATMULLROM_CURVE_H

#include <vector>
#include "linalg/vec.h"

using namespace std;
using namespace nb::linalg;

class CatmullRomCurve {
public:
  CatmullRomCurve();
  CatmullRomCurve(const CatmullRomCurve& rhs);

  void AddCtrlPoint(const nb::linalg::Vec3<float>& p);  
  U32 CountCtrlPoints() const;
  void ComputeCurvePoints();

  Vec3<float> GetPosition(float t);
  Vec3<float> GetTangent(float t);
  Vec3<float> GetAcceleration(float t);

protected:
  vector<float> mRegularPoints;
  vector<float> mCtrlPoints;
};

#endif
