#ifndef ARCBALLCAMERA_H
#define ARCBALLCAMERA_H

#include "perspectivecamera.h"

namespace nb {
namespace linalg {

/*!
 * \brief The ArcBallCamera class is a simple spherical camera based on the PerspectiveCamera Model.
 * The camera position is based on the tilt (vertical angle), roll (horizontal angle) and the distance of the
 * camera from the target. All angles are measured in degrees. The location is computed by converting from spherical to
 * Cartesian coordinate space.
 */
class ArcBallCamera : public PerspectiveCamera
{
public:
    ArcBallCamera();
    virtual ~ArcBallCamera();

    float GetTiltAngleInDegrees() const;
    void SetTiltAngleInDegrees(float tiltInDegrees);

    float GetRollAngleInDegrees() const;
    void SetRollAngleInDegrees(float rollInDegrees);

    float GetDistance() const;
    void SetDistance(float dist);

protected:
    void ComputeCameraLocation();
    void Setup();

protected:
    float mRoll;
    float mTilt;
    float mRadius;
};

}
}

#endif // ARCBALLCAMERA_H
