#include "orthographiccamera.h"

namespace nb {
namespace linalg {

OrthographicCamera::OrthographicCamera()
{
    Reset();
}

OrthographicCamera::~OrthographicCamera() {

}

void OrthographicCamera::Reset()
{
    GenericRenderingCamera::Reset();
    SetPlanes(-1, 1, -1, 1, -1, 1);
}

void OrthographicCamera::SetPlanes(float left, float right, float bottom, float top, float znear, float zfar)
{
    mProjMatrices[0].Ortho(left, right, bottom, top, znear, zfar);
    mViewMatrices[0].SetIdentity();

    if(mfOnCamUpdated)
        mfOnCamUpdated();
}

}
}
