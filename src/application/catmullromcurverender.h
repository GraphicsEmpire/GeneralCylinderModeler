#ifndef CATMULLROMCURVERENDER_H
#define CATMULLROMCURVERENDER_H

#include <memory>
#include "linalg/matrix.h"

using namespace std;

class CatmullRomCurve;
class CatmullRomCurveRenderImpl;

class CatmullRomCurveRender {
public:
    CatmullRomCurveRender(const std::shared_ptr<CatmullRomCurve>& cdata);
    virtual ~CatmullRomCurveRender();

    void render(const nb::linalg::mat4& modelview,
                const nb::linalg::mat4& projection);

protected:
    std::shared_ptr<CatmullRomCurve> mCurveData;
    std::unique_ptr<CatmullRomCurveRenderImpl> mImpl;
    bool mDrawCtrlPoints;
    bool mDrawCurve;
};

#endif // CATMULLROMCURVERENDER_H
