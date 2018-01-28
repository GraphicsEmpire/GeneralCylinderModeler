#ifndef SGRENDERINTERFACE_H
#define SGRENDERINTERFACE_H

#include "linalg/matrix.h"

using namespace nb::linalg;

namespace nb {
namespace render {

class SGRenderInterface {
public:
    virtual void Render(const nb::linalg::mat4 &modelview,
                const nb::linalg::mat4 &projection) = 0;

};

}
}

#endif // SGRENDERINTERFACE_H
