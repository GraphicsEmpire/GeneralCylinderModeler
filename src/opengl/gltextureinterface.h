//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#ifndef LIBUMF_OPENGL_GLTEXTUREINTERFACE_H
#define LIBUMF_OPENGL_GLTEXTUREINTERFACE_H

#include "linalg/datatypes.h"
#include "linalg/vec.h"
#include "linalg/imagedefinition.h"

namespace nb {
    namespace opengl {

        //Enums
        enum SupportedImageFormats {sifPNG, sifRAW, sifUnsupported};

        /*!
         * defines a standard interface for all textures
         */
        class GLTextureInterface {
        public:
            virtual ~GLTextureInterface() {}

            /*!
             * @return the definition of the image, using pixel and dimension info
             */
            virtual nb::linalg::ImageDefinition GetImageDefinition() const = 0;

            /*!
             * @return opengl handle to the texture memory
             */
            virtual U32 GetTextureHandle() const = 0;

            /*!
             * Reads an image from a memory block
             * @param definition of the image in memory
             * @param pdata
             * @return true when read operation completed successfully
             */
            virtual bool ReadImageMemoryBlock(const nb::linalg::ImageDefinition &blockdef, const void *block) = 0;

            /*!
             * Writes the image/texture content into a memory block pre-allocated for this use-case
             * @param block_size size of the memory allocated to store the image pixels
             * @param block memory arena to store the payload
             * @return true when write operation is completed
             */
            virtual bool WriteImageMemoryBlock(U64 block_size, void* block) const = 0;
        };
    }
}

#endif //LIBUMF_OPENGL_GLTEXTUREINTERFACE_H
