//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#ifndef LIBUMF_LINALG_IMAGEDEFINITION_H
#define LIBUMF_LINALG_IMAGEDEFINITION_H

#include "pixeldefinition.h"
#include "vec.h"

namespace nb {
    namespace linalg {

        /*!
         * \brief represents a 2D or 3D image
         * Image is defined by the pixel, the width and height dimension and number of slices in 3D images
         */
        class ImageDefinition {
        public:
            ImageDefinition();

            /*!
             * Copy constructor to set the internal image definition from another definition
             * @param rhs other image definition
             */
            ImageDefinition(const ImageDefinition& rhs);

            /*!
             * Setup a new image definition using the pixel and the dimension info
             * @param pixeldef
             * @param dimension
             */
            explicit ImageDefinition(const PixelDefinition& pixeldef, const Vec3<U32>& dimension);
            /*!
             * Setup a new image definition using the pixel and the dimension info
             * @param pixel_format
             * @param dimension
             */
            explicit ImageDefinition(PixelDefinition::PixelFormat pixel_format, const Vec3<U32>& dimension);
            virtual ~ImageDefinition();

            std::string ToString() const;

            /*!
             *
             * @return the pixel definition part of the image
             */
            PixelDefinition GetPixelDefinition() const;

            /*!
             * sets the pixel definition part of the image
             * @param pixeldef
             */
            void SetPixelDefinition(const PixelDefinition& pixeldef);

            /*!
             * sets the pixel definition part of the image with given pixel format
             * @param pixel_format
             */
            void SetPixelFormat(PixelDefinition::PixelFormat pixel_format);

            /*!
             *
             * @return image dimension in width x height x number of slices
             */
            Vec3<U32> GetDimension() const;

            U32 GetWidth() const;
            U32 GetHeight() const;
            U32 GetNumSlices() const;


            /*!
             *
             * @param width
             * @param height
             * @param nslices number of slices in a 3D images, set to 1 for 2D images
             */
            void SetDimension(U32 width, U32 height, U32 nslices = 1);


            /*!
             *
             * @param dimension
             */
            void SetDimension(const Vec3<U32>& dimension);


            /*!
             * Compute the amount of memory used up by knowing the pixel definition and the image dimension
             * @return number of bytes to represent this image in memory
             */
            U64 GetMemorySizeInBytes() const;

            /*!
             *
             * @param rhs another image definition
             * @return true when the two image definitions match
             */
            bool Matches(const ImageDefinition& rhs) const;

            /*!
             * Copies an image definition from another one
             * @param rhs
             */
            void CopyFrom(const ImageDefinition& rhs);

            const ImageDefinition& operator=(const ImageDefinition& rhs);
            bool operator==(const ImageDefinition& rhs) const;

        protected:
            PixelDefinition mPixelDefinition;
            Vec3<U32>       mDimension;
        };
    }
}

#endif //LIBUMF_LINALG_IMAGEDEFINITION_H
