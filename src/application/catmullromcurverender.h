#ifndef CATMULLROMCURVERENDER_H
#define CATMULLROMCURVERENDER_H

#include <memory>

using namespace std;

class CatmullRomCurve;

class CatmullRomCurveRender {
public:
    CatmullRomCurveRender(const std::shared_ptr<CatmullRomCurve>& cdata);
    virtual ~CatmullRomCurveRender();

protected:
    std::shared_ptr<CatmullRomCurve> mCurveData;
};

#endif // CATMULLROMCURVERENDER_H
