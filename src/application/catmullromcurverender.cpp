#include "catmullromcurverender.h"
#include "catmullromcurve.h"
#include "opengl/glmeshbuffer.h"

using namespace nb::opengl;

class CatmullRomCurveRenderImpl {
public:
    CatmullRomCurveRenderImpl() {
    }

    virtual ~CatmullRomCurveRenderImpl() {
        mCtrlPointsMeshBuffer.Clear();
    }

    /*!
     * \brief Sync mesh buffer from the geometry data
     * \param cdata reference of geometry data
     */
    void Sync(CatmullRomCurve& cdata) {

    }

protected:
    GLMeshBuffer mCtrlPointsMeshBuffer;
};

/////////////////////////////////////////////////
CatmullRomCurveRender::CatmullRomCurveRender(const std::shared_ptr<CatmullRomCurve> &cdata):
    mCurveData(cdata), mDrawCtrlPoints(true), mDrawCurve(false)
{
    mImpl.reset(new CatmullRomCurveRenderImpl());
}

CatmullRomCurveRender::~CatmullRomCurveRender()
{

}

void CatmullRomCurveRender::render(const nb::linalg::mat4 &modelview, const nb::linalg::mat4 &projection)
{
    if(mDrawCtrlPoints) {

    }
}
