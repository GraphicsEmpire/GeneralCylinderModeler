#include "sgmodel.h"

namespace nb {
namespace render {

SGModel::SGModel()
{

}

SGModel::~SGModel()
{

}

void SGModel::AddFace(U32 *faces, U32 count)
{
    for(U32 i=0; i < count; i++) {
        mIndices.push_back(faces[i]);
    }
}

void SGModel::AddFace(const std::vector<U32> &indices)
{
    mIndices.insert(mIndices.end(), indices.begin(), indices.end());
}


}
}
