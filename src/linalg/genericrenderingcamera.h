//
// Created by mvpdev on 9/12/17.
//

#ifndef GENERICRENDERINGCAMERA_H
#define GENERICRENDERINGCAMERA_H

#include "camerainterface.h"

namespace nb {
    namespace linalg {

        /*!
         *  \brief multi-channel rendering camera
         */
        template<U32 nchannels>
        class GenericRenderingCamera : public CameraInterface {
        public:
            const static U32 NCHANNELS = nchannels;

            GenericRenderingCamera() {
                Reset();
            }

            virtual ~GenericRenderingCamera() {

            }

            void Reset() {
                for (U32 i = 0; i < nchannels; i++) {
                    mProjMatrices[i].SetIdentity();
                    mViewMatrices[i].SetIdentity();
                }

                if (mfOnCamUpdated)
                    mfOnCamUpdated();
            }

            mat4 GetViewMatrix(U32 channel = 0) const override {
                if (!IsChannelIndex(channel))
                    return mat4();
                return mViewMatrices[channel];
            }

            mat4 GetProjectionMatrix(U32 channel = 0) const override {
                if (!IsChannelIndex(channel))
                    return mat4();
                return mProjMatrices[channel];
            }

            U32 GetChannelsCount() const override { return NCHANNELS; }

        protected:
            bool IsChannelIndex(U32 index) const {
                return (index < nchannels);
            }

            void SetViewMatrix(U32 channel, const mat4 &view) override {
                mViewMatrices[channel] = view;
                if (mfOnCamUpdated)
                    mfOnCamUpdated();
            }

            void SetProjectionMatrix(U32 channel, const mat4 &proj) override {
                mProjMatrices[channel] = proj;
                if (mfOnCamUpdated)
                    mfOnCamUpdated();
            }

        protected:
            mat4 mViewMatrices[nchannels];
            mat4 mProjMatrices[nchannels];
        };

    }
}


#endif //MIRAGE_GENERICRENDERINGCAMERA_H
