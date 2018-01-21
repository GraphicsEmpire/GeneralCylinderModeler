#include "arcballcamera.h"

namespace nb {
namespace linalg {

ArcBallCamera::ArcBallCamera()
{
    PerspectiveCamera::Reset();
    Setup();
}

ArcBallCamera::~ArcBallCamera() {

}

float ArcBallCamera::GetTiltAngleInDegrees() const
{
    return RADTODEG(mTilt);
}

void ArcBallCamera::SetTiltAngleInDegrees(float tiltInDegrees)
{
    Clamp<float>(tiltInDegrees, EPSILON, 180.0f - EPSILON);
    mTilt = DEGTORAD(tiltInDegrees);
    ComputeCameraLocation();
}

float ArcBallCamera::GetRollAngleInDegrees() const
{
    return RADTODEG(mRoll);
}

void ArcBallCamera::SetRollAngleInDegrees(float rollInDegrees)
{
//   if(rollInDegrees < 0)
//       rollInDegrees += 360.0f;
//   rollInDegrees = int(rollInDegrees) % 360;
   mRoll = DEGTORAD(rollInDegrees);
    ComputeCameraLocation();
}

float ArcBallCamera::GetDistance() const
{
    return mRadius;
}

void ArcBallCamera::SetDistance(float dist)
{
    if(mRadius != dist) {
        mRadius = dist;
        ComputeCameraLocation();
    }
}

void ArcBallCamera::ComputeCameraLocation()
{
    vec3 p;
    p.x = mRadius * sin(mTilt) * cos(mRoll);
    p.z = mRadius * sin(mTilt) * sin(mRoll);
    p.y = mRadius * cos(mTilt);
    mCamLocation = p;

    //recompute lookat
    mViewMatrices[0].LookAt(mCamLocation, mTarget, mUpVector);

    if(mfOnCamUpdated)
        mfOnCamUpdated();
}

void ArcBallCamera::Setup()
{
    //setup values
    mCamLocation = vec3(0, 0, 0);
    mTarget = vec3(0, 0, 0);
    mUpVector = vec3(0, 1, 0);

    //default distance is 50 mm
    mRadius = 50;
    mTilt = DEGTORAD(60);
    mRoll = DEGTORAD(90);

    RecomputeProjection();
    ComputeCameraLocation();
}

}
}
