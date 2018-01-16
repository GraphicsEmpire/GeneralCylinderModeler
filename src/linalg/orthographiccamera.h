#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "genericrenderingcamera.h"

namespace nb {
namespace linalg {

/*!
 * \brief The OrthographicCamera class represents a simple orthographic camera model where parallel line are
 * preserved as parallel.
 */
class OrthographicCamera : public GenericRenderingCamera<1>
{
public:
    OrthographicCamera();
    virtual ~OrthographicCamera();

    void Reset();

    /*!
     * \brief SetPlanes sets the threshold planes for an orthographic camera view
     * \param left
     * \param right
     * \param bottom
     * \param top
     * \param znear
     * \param zfar
     */
    void SetPlanes(float left, float right, float bottom, float top, float znear = -1.0f, float zfar = 1.0f);
};

}
}

#endif // ORTHOGRAPHICCAMERA_H
