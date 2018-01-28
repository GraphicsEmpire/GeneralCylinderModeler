#include "sgmodel.h"
#include "opengl/glmeshbuffer.h"

namespace nb {
    namespace render {

        class SGModelImplementation {
        public:
            SGModelImplementation() {

            }

            void Render(const nb::linalg::mat4 &modelview, const nb::linalg::mat4 &projection) {

            }

        protected:
            nb::opengl::GLMeshBuffer mMeshBuffer;
        };

        ////////////////////////////////////////
        SGModel::SGModel() {
            mImpl.reset(new SGModelImplementation());
        }

        SGModel::~SGModel() {
            Cleanup();
        }

        void SGModel::AddFace(U32 *faces, U32 count) {
            for (U32 i = 0; i < count; i++) {
                mIndices.push_back(faces[i]);
            }
        }

        void SGModel::AddFace(const std::vector<U32> &indices) {
            mIndices.insert(mIndices.end(), indices.begin(), indices.end());
        }

        void SGModel::Render(const nb::linalg::mat4 &modelview, const nb::linalg::mat4 &projection) {

        }

        void SGModel::SyncDeviceBuffers() {

        }

        void SGModel::Cleanup() {
            mIndices.resize(0);
            mVertexAttribs.clear();
        }


    }
}
