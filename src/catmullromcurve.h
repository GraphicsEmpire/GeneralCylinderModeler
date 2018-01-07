#ifndef CATMULLROM_CURVE_H
#define CATMULLROM_CURVE_H

#include <vector>
#include "linalg/vec.h"

using namespace std;
using namespace nb;

class CatmullRomCurve {
public:
  CatmullRomCurve();
  CatmullRomCurve(const CatmullRomCurve& rhs);

  void AddCtrlPoint(const nb::vec3& p);
protected:
  vector<float> mRegularPoints;
  vector<float> mCtrlPoints;
};

#endif
