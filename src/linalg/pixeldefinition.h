//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#ifndef LIBUMF_LINALG_PIXELDEFINITION_H
#define LIBUMF_LINALG_PIXELDEFINITION_H

#include "base.h"
#include "datatypes.h"

namespace nb {
    namespace linalg {

        #define GeneratePixelFormat(C1, C2, C3, C4, T) ((C1) << 16 | (C2) << 12 | (C3) << 8 | (C4) << 4 | (T))

        /*!
         * \brief defines a pixel by its number of channels and the data-type used to represent each channel
         */
        class PixelDefinition {
        public:
            enum ColorChannelType : U8 {
                red = 0, green = 1, blue = 2, alpha = 3, depth = 4
            };
            enum ColorDataType : U8 {
                norm8   = 0, norm16  = 1,
                snorm8  = 2, snorm16 = 3,
                uint8   = 4, uint16  = 5, uint32 = 6,
                int8    = 7, int16   = 8, int32  = 9,
                float32 = 10
            };
            /*!
             * Currently used pixel formats in the framework.
             * Each format is a combination of four channels and a data type.
             * Unused channels are set to 0xF.
             */
            enum PixelFormat : U32 {
                // unsigned normalized integer /////////////////////////////////
                PF_R8     = GeneratePixelFormat(red, 0xF, 0xF, 0xF, norm8),
                PF_R16    = GeneratePixelFormat(red, 0xF, 0xF, 0xF, norm16),
                PF_RG8    = GeneratePixelFormat(red, green, 0xF, 0xF, norm8),
                PF_RG16   = GeneratePixelFormat(red, green, 0xF, 0xF, norm16),
                PF_RGB8   = GeneratePixelFormat(red, green, blue, 0xF, norm8),
                PF_RGB16  = GeneratePixelFormat(red, green, blue, 0xF, norm16),
                PF_RGBA8  = GeneratePixelFormat(red, green, blue, alpha, norm8),
                PF_RGBA16 = GeneratePixelFormat(red, green, blue, alpha, norm16),
                // signed normalized integer ///////////////////////////////////
                PF_R8_SNORM     = GeneratePixelFormat(red, 0xF, 0xF, 0xF, snorm8),
                PF_R16_SNORM    = GeneratePixelFormat(red, 0xF, 0xF, 0xF, snorm16),
                PF_RG8_SNORM    = GeneratePixelFormat(red, green, 0xF, 0xF, snorm8),
                PF_RG16_SNORM   = GeneratePixelFormat(red, green, 0xF, 0xF, snorm16),
                PF_RGB8_SNORM   = GeneratePixelFormat(red, green, blue, 0xF, snorm8),
                PF_RGB16_SNORM  = GeneratePixelFormat(red, green, blue, 0xF, snorm16),
                PF_RGBA8_SNORM  = GeneratePixelFormat(red, green, blue, alpha, snorm8),
                PF_RGBA16_SNORM = GeneratePixelFormat(red, green, blue, alpha, snorm16),
                // unsigned integer ////////////////////////////////////////////
                PF_R8UI     = GeneratePixelFormat(red, 0xF, 0xF, 0xF, uint8),
                PF_R16UI    = GeneratePixelFormat(red, 0xF, 0xF, 0xF, uint16),
                PF_R32UI    = GeneratePixelFormat(red, 0xF, 0xF, 0xF, uint32),
                PF_RG8UI    = GeneratePixelFormat(red, green, 0xF, 0xF, uint8),
                PF_RG16UI   = GeneratePixelFormat(red, green, 0xF, 0xF, uint16),
                PF_RG32UI   = GeneratePixelFormat(red, green, 0xF, 0xF, uint32),
                PF_RGB8UI   = GeneratePixelFormat(red, green, blue, 0xF, uint8),
                PF_RGB16UI  = GeneratePixelFormat(red, green, blue, 0xF, uint16),
                PF_RGB32UI  = GeneratePixelFormat(red, green, blue, 0xF, uint32),
                PF_RGBA8UI  = GeneratePixelFormat(red, green, blue, alpha, uint8),
                PF_RGBA16UI = GeneratePixelFormat(red, green, blue, alpha, uint16),
                PF_RGBA32UI = GeneratePixelFormat(red, green, blue, alpha, uint32),
                // signed integer //////////////////////////////////////////////
                PF_R8I     = GeneratePixelFormat(red, 0xF, 0xF, 0xF, int8),
                PF_R16I    = GeneratePixelFormat(red, 0xF, 0xF, 0xF, int16),
                PF_R32I    = GeneratePixelFormat(red, 0xF, 0xF, 0xF, int32),
                PF_RG8I    = GeneratePixelFormat(red, green, 0xF, 0xF, int8),
                PF_RG16I   = GeneratePixelFormat(red, green, 0xF, 0xF, int16),
                PF_RG32I   = GeneratePixelFormat(red, green, 0xF, 0xF, int32),
                PF_RGB8I   = GeneratePixelFormat(red, green, blue, 0xF, int8),
                PF_RGB16I  = GeneratePixelFormat(red, green, blue, 0xF, int16),
                PF_RGB32I  = GeneratePixelFormat(red, green, blue, 0xF, int32),
                PF_RGBA8I  = GeneratePixelFormat(red, green, blue, alpha, int8),
                PF_RGBA16I = GeneratePixelFormat(red, green, blue, alpha, int16),
                PF_RGBA32I = GeneratePixelFormat(red, green, blue, alpha, int32),
                // float ///////////////////////////////////////////////////////
                PF_R32F = GeneratePixelFormat(red, 0xF, 0xF, 0xF, float32),
                PF_RG32F = GeneratePixelFormat(red, green, 0xF, 0xF, float32),
                PF_RGB32F = GeneratePixelFormat(red, green, blue, 0xF, float32),
                PF_RGBA32F = GeneratePixelFormat(red, green, blue, alpha, float32),
                // depth ///////////////////////////////////////////////////////
                PF_DEPTH16 = GeneratePixelFormat(depth, 0xF, 0xF, 0xF, norm16),
                PF_DEPTH32F = GeneratePixelFormat(depth, 0xF, 0xF, 0xF, float32)
            };

            static const U32 MAX_NUM_COLOR_CHANNELS = 4;

            /*!
             * \brief default pixel definition is a 4 channel, normalized unsigned byte pixel
             */
            PixelDefinition();

            PixelDefinition(const PixelFormat& format);

            /*!
             * \brief copies the content of another pixel definition
             */
            PixelDefinition(const PixelDefinition& rhs);

            virtual ~PixelDefinition() {}

            static PixelDefinition Create(const PixelFormat& format);

            /*!
             *
             * @return a string representing the current pixel definition
             */
            virtual std::string ToString() const;
            static std::map<ColorChannelType, std::string> MapColorChannelTypeToString();
            static std::string ConvertPixelFormatToString(const PixelFormat& f);
            static U32 ExtractNumChannelsFromPixelFormat(const PixelFormat& f);
            static DataElementTypeID ExtractPerChannelDataTypeFromPixelFormat(const PixelFormat& f);

            /*!
             * @return number of bytes required to store a pixel in this format
             */
            U32 GetPixelSizeInBytes() const;

            /*!
             *
             * @return number of color channels available per pixel
             */
            U32 GetNumberOfColorChannels() const;

            /*!
             *
             * @return the data element type per color channel
             */
            DataElementTypeID GetPerChannelDataType() const;

            /*!
             *
             * @return the pixel format
             */
            PixelFormat GetPixelFormat() const;

            /*!
             *
             * @return whether channel data type is normalized integer
             */
            bool IsNormalized() const;

            /*!
             *
             * @return whether pixel format is signed integer format
             */
            bool IsSignedIntegerFormat() const;

            /*!
             *
             * @return whether pixel format is unsigned integer format
             */
            bool IsUnsignedIntegerFormat() const;

            /*!
             * @param rhs another PixelDefinition
             * @return true if the two definitions match and false otherwise
             */
            bool Matches(const PixelDefinition& rhs) const;

            /*!
             * Copies the content of another instance of PixelDefinition into this instance.
             * @param rhs another PixelDefinition
             */
            void CopyFrom(const PixelDefinition& rhs);

            /*!
             *
             * @param rhs another PixelDefinition
             * @return true of the two definitions match and false otherwise
             */
            bool operator==(const PixelDefinition& rhs) const;

            const PixelDefinition& operator=(const PixelDefinition& rhs);

        protected:
            U32 mNumberOfChannels;
            DataElementTypeID mPerChannelDataType;
            PixelFormat       mPixelFormat;
        };


    }
}

#endif //LIBUMF_LINALG_PIXELDEFINITION_H
