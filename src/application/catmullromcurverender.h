//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#ifndef CATMULLROMCURVERENDER_H
#define CATMULLROMCURVERENDER_H

#include <memory>
#include "linalg/matrix.h"
#include "render/sgrenderinterface.h"

using namespace std;

namespace nb {
  namespace render {

class CatmullRomCurve;
class CatmullRomCurveRenderImpl;

class CatmullRomCurveRender : public SGRenderInterface {
public:
    CatmullRomCurveRender(const std::shared_ptr<CatmullRomCurve>& cdata);
    virtual ~CatmullRomCurveRender();

    void Render(const nb::linalg::mat4 &modelview,
                const nb::linalg::mat4 &projection) override;

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
