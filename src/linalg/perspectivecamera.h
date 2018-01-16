#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "genericrenderingcamera.h"

namespace nb {
namespace linalg {

#define DEFAULT_NEAR_PLANE 0.1f
#define DEFAULT_FAR_PLANE 1000.0f
#define DEFAULT_CAM_DISTANCE 50.0f
#define DEFAULT_FOVY_DEG 45.0f

/*!
 * \brief A perspective camera model that generates a frustum-shaped field of view
 */
class PerspectiveCamera : public GenericRenderingCamera<1>
{
public:
    PerspectiveCamera();
    virtual ~PerspectiveCamera();

    void Reset();

    /*!
     * \brief getDepthRange
     * \return an interval for the depth range
     */
    Interval<nbReal> GetDepthRange() const;
    void SetDepthRange(const Interval<nbReal> &depth_range);

    /*!
     * \brief GetFieldOfViewAngleDegrees
     * \return the field of view angle in degree
     */
    nbReal GetFieldOfViewAngleDegrees() const;

    /*!
     * \brief SetFieldOfViewAngleDegrees sets the fieldOfView angle in degrees
     * \param deg
     */
    void SetFieldOfViewAngleDegrees(nbReal deg);

    /*!
     * \brief GetAspectRatio
     * \return
     */
    nbReal GetAspectRatio() const;

    /*!
     * \brief setAspectRatio
     * \param aspect_ratio
     */
    void SetAspectRatio(nbReal aspect_ratio);

    /*!
     * \brief getCamLocation
     * \return
     */
    vec3 GetCamLocation() const;

    /*!
     * \brief GetTarget
     * \return
     */
    vec3 GetTarget() const;

    /*!
     * \brief SetTarget
     * \param target
     */
    void SetTarget(const vec3 &target);

private:
    void RecomputeView();
    void SetCameraLocation(const vec3 &location);

protected:
    void RecomputeProjection();

protected:
    Interval<nbReal> mDepthRange;
    nbReal mFovDeg;
    nbReal mAspectRatio;

    vec3 mCamLocation;
    vec3 mTarget;
    vec3 mUpVector;
};

}
}

#endif // PERSPECTIVECAMERA_H
