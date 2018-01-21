#ifndef CATMULLROMCURVERENDER_H
#define CATMULLROMCURVERENDER_H

#include <memory>
#include "linalg/matrix.h"

using namespace std;

namespace nb {
  namespace render {

class CatmullRomCurve;
class CatmullRomCurveRenderImpl;

class CatmullRomCurveRender {
public:
    CatmullRomCurveRender(const std::shared_ptr<CatmullRomCurve>& cdata);
    virtual ~CatmullRomCurveRender();

    void Render(const nb::linalg::mat4 &modelview,
                const nb::linalg::mat4 &projection);

    void Sync();

protected:
    std::shared_ptr<CatmullRomCurve> mCurveData;
    std::unique_ptr<CatmullRomCurveRenderImpl> mImpl;
    bool mDrawCtrlPoints;
    bool mDrawCurveProfile;
};

}
}

#endif // CATMULLROMCURVERENDER_H
