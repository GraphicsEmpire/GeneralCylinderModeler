#ifndef CAMERA_H
#define CAMERA_H

#include <functional>
#include "matrix.h"
#include "interval.h"

namespace nb {
namespace linalg {

/*!
 * \brief The CameraInterface class represents a generic rendering camera
 */
class CameraInterface {
public:
    /*!
     * \brief OnCameraUpdatedCallBack is callback function which is triggered whenever the location or orientation of the camera is changed.
     */
    typedef std::function<void(void)> OnCameraUpdatedCallBack;

    CameraInterface() {}
    virtual ~CameraInterface() {}

    virtual mat4 GetViewMatrix(U32 channel = 0) const = 0;
    virtual mat4 GetProjectionMatrix(U32 channel = 0) const = 0;
    virtual U32 GetChannelsCount() const = 0;

    virtual void SetOnCameraUpdatedCallBack(const OnCameraUpdatedCallBack &cb) {
        mfOnCamUpdated = cb;
    }

protected:
    virtual void SetViewMatrix(U32 channel, const mat4 &view) = 0;
    virtual void SetProjectionMatrix(U32 channel, const mat4 &proj) = 0;

protected:
    OnCameraUpdatedCallBack mfOnCamUpdated;

};



}
}
#endif // CAMERA_H
