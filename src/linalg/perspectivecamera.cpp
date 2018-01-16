#include "perspectivecamera.h"

namespace nb {
namespace linalg {

PerspectiveCamera::PerspectiveCamera()
{
    Reset();
}

PerspectiveCamera::~PerspectiveCamera() {

}

void PerspectiveCamera::Reset()
{
    GenericRenderingCamera::Reset();

    //values to compute view
    //default target is 5 cm from the camera along z axis
    mCamLocation = vec3(0, 0, 0);
    mTarget = vec3(0, 0, DEFAULT_CAM_DISTANCE);
    mUpVector = vec3(0, 1, 0);

    //values to compute projection
    mAspectRatio = 1.0f;
    mDepthRange.Set(DEFAULT_NEAR_PLANE, DEFAULT_FAR_PLANE);
    mFovDeg = DEFAULT_FOVY_DEG;

    RecomputeProjection();
    RecomputeView();
}

Interval<nbReal> PerspectiveCamera::GetDepthRange() const {
    return mDepthRange;
}

void PerspectiveCamera::SetDepthRange(const Interval<nbReal> &depth_range) {
    if(!mDepthRange.IsEqual(depth_range)) {
        mDepthRange = depth_range;
        RecomputeProjection();
    }
}

nbReal PerspectiveCamera::GetFieldOfViewAngleDegrees() const {
    return mFovDeg;
}

void PerspectiveCamera::SetFieldOfViewAngleDegrees(nbReal deg) {
    if(mFovDeg != deg) {
        mFovDeg = deg;
        RecomputeProjection();
    }
}

nbReal PerspectiveCamera::GetAspectRatio() const {
    return mAspectRatio;
}

void PerspectiveCamera::SetAspectRatio(nbReal aspect_ratio) {
    if(mAspectRatio != aspect_ratio) {
        mAspectRatio = aspect_ratio;
        RecomputeProjection();
    }
}

vec3 PerspectiveCamera::GetCamLocation() const {
    return mCamLocation;
}

void PerspectiveCamera::SetCameraLocation(const vec3 &location) {
    mCamLocation = location;
    RecomputeView();
}

vec3 PerspectiveCamera::GetTarget() const {
    return mTarget;
}

void PerspectiveCamera::SetTarget(const vec3 &target) {
    mTarget = target;
    RecomputeView();
}

void PerspectiveCamera::RecomputeProjection() {
    mProjMatrices[0].Perspective(mFovDeg, mAspectRatio, mDepthRange.GetLower(), mDepthRange.GetUpper());

    if(mfOnCamUpdated)
        mfOnCamUpdated();
}

void PerspectiveCamera::RecomputeView() {
    mViewMatrices[0].LookAt(mCamLocation, mTarget, mUpVector);

    if(mfOnCamUpdated)
        mfOnCamUpdated();
}


}
}
