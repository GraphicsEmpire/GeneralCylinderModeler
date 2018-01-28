#ifndef SGMODEL_H
#define SGMODEL_H

#include <vector>
#include "sgrenderinterface.h"

using namespace std;

namespace nb {
namespace render {

class SGModel : public SGRenderInterface {
public:
    SGModel();
    virtual ~SGModel();

    void AddFace(U32* faces, U32 count);
    void AddFace(const std::vector<U32>& indices);

    void SyncDeviceBuffers();

protected:
    std::vector<U32> mIndices;
};

}
}

#endif // SGMODEL_H
