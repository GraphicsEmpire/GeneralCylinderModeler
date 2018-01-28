//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#include "glpixeldefinitionadapter.h"

#include <sstream>
#include "glselect.h"
#include "utils/logger.h"

using namespace nb::utils;

namespace nb {
    namespace opengl {

        GLPixelDefinitionAdapter::GLPixelDefinitionAdapter() : PixelDefinition() {
        }

        GLPixelDefinitionAdapter::GLPixelDefinitionAdapter(const PixelDefinition &rhs) : PixelDefinition(rhs) {
        }

        map<U32, DataElementTypeID> GLPixelDefinitionAdapter::MapOpenGLDataTypeToFramework() {
            map<U32, DataElementTypeID> m;
            m[(U32)GL_UNSIGNED_BYTE]  = etUnsignedInt8;
            m[(U32)GL_UNSIGNED_SHORT] = etUnsignedInt16;
            m[(U32)GL_UNSIGNED_INT]   = etUnsignedInt32;
            m[(U32)GL_BYTE]           = etInt8;
            m[(U32)GL_SHORT]          = etInt16;
            m[(U32)GL_INT]            = etInt32;
            m[(U32)GL_FLOAT]          = etFloat;
            m[(U32)GL_DOUBLE]         = etDouble;

            return m;
        }

        map<DataElementTypeID, U32>
        GLPixelDefinitionAdapter::MapDataTypeFromFrameworkToOpenGL() {
            map<DataElementTypeID, U32> m;
            m[etUnsignedInt8]  = (U32)GL_UNSIGNED_BYTE;
            m[etUnsignedInt16] = (U32)GL_UNSIGNED_SHORT;
            m[etUnsignedInt32] = (U32)GL_UNSIGNED_INT;
            m[etInt8]          = (U32)GL_BYTE;
            m[etInt16]         = (U32)GL_SHORT;
            m[etInt32]         = (U32)GL_INT;
            m[etFloat]         = (U32)GL_FLOAT;
            m[etDouble]        = (U32)GL_DOUBLE;

            return m;
        }

        std::map<PixelDefinition::PixelFormat, U32>
        GLPixelDefinitionAdapter::MapPixelFormatFromFrameworkToOpenGL() {
            std::map<PixelDefinition::PixelFormat, U32> m;
            m[PF_R8]     = (U32)GL_RED;
            m[PF_R16]    = (U32)GL_RED;
            m[PF_RG8]    = (U32)GL_RG;
            m[PF_RG16]   = (U32)GL_RG;
            m[PF_RGB8]   = (U32)GL_RGB;
            m[PF_RGB16]  = (U32)GL_RGB;
            m[PF_RGBA8]  = (U32)GL_RGBA;
            m[PF_RGBA16] = (U32)GL_RGBA;
            // signed normalized integer ///////////////////////////////////
            m[PF_R8_SNORM]     = (U32)GL_RED;
            m[PF_R16_SNORM]    = (U32)GL_RED;
            m[PF_RG8_SNORM]    = (U32)GL_RG;
            m[PF_RG16_SNORM]   = (U32)GL_RG;
            m[PF_RGB8_SNORM]   = (U32)GL_RGB;
            m[PF_RGB16_SNORM]  = (U32)GL_RGB;
            m[PF_RGBA8_SNORM]  = (U32)GL_RGBA;
            m[PF_RGBA16_SNORM] = (U32)GL_RGBA;
            // unsigned integer ////////////////////////////////////////////
            m[PF_R8UI]     = (U32)GL_RED_INTEGER;
            m[PF_R16UI]    = (U32)GL_RED_INTEGER;
            m[PF_R32UI]    = (U32)GL_RED_INTEGER;
            m[PF_RG8UI]    = (U32)GL_RG_INTEGER;
            m[PF_RG16UI]   = (U32)GL_RG_INTEGER;
            m[PF_RG32UI]   = (U32)GL_RG_INTEGER;
            m[PF_RGB8UI]   = (U32)GL_RGB_INTEGER;
            m[PF_RGB16UI]  = (U32)GL_RGB_INTEGER;
            m[PF_RGB32UI]  = (U32)GL_RGB_INTEGER;
            m[PF_RGBA8UI]  = (U32)GL_RGBA_INTEGER;
            m[PF_RGBA16UI] = (U32)GL_RGBA_INTEGER;
            m[PF_RGBA32UI] = (U32)GL_RGBA_INTEGER;
            // signed integer //////////////////////////////////////////////
            m[PF_R8I]     = (U32)GL_RED_INTEGER;
            m[PF_R16I]    = (U32)GL_RED_INTEGER;
            m[PF_R32I]    = (U32)GL_RED_INTEGER;
            m[PF_RG8I]    = (U32)GL_RG_INTEGER;
            m[PF_RG16I]   = (U32)GL_RG_INTEGER;
            m[PF_RG32I]   = (U32)GL_RG_INTEGER;
            m[PF_RGB8I]   = (U32)GL_RGB_INTEGER;
            m[PF_RGB16I]  = (U32)GL_RGB_INTEGER;
            m[PF_RGB32I]  = (U32)GL_RGB_INTEGER;
            m[PF_RGBA8I]  = (U32)GL_RGBA_INTEGER;
            m[PF_RGBA16I] = (U32)GL_RGBA_INTEGER;
            m[PF_RGBA32I] = (U32)GL_RGBA_INTEGER;
            // float ///////////////////////////////////////////////////////
            m[PF_R32F]    = (U32)GL_RED;
            m[PF_RG32F]   = (U32)GL_RG;
            m[PF_RGB32F]  = (U32)GL_RGB;
            m[PF_RGBA32F] = (U32)GL_RGBA;
            // depth ///////////////////////////////////////////////////////
            m[PF_DEPTH16]  = (U32)GL_DEPTH_COMPONENT;
            m[PF_DEPTH32F] = (U32)GL_DEPTH_COMPONENT;

            return m;
        }

        map<PixelDefinition::PixelFormat, U32>
        GLPixelDefinitionAdapter::MapPixelInternalFormatFromFrameworkToOpenGL() {
            map<PixelDefinition::PixelFormat, U32> m;
            m[PF_R8]     = (U32)GL_R8;
            m[PF_R16]    = (U32)GL_R16;
            m[PF_RG8]    = (U32)GL_RG8;
            m[PF_RG16]   = (U32)GL_RG16;
            m[PF_RGB8]   = (U32)GL_RGB8;
            m[PF_RGB16]  = (U32)GL_RGB16;
            m[PF_RGBA8]  = (U32)GL_RGBA8;
            m[PF_RGBA16] = (U32)GL_RGBA16;
            // signed normalized integer ///////////////////////////////////
            m[PF_R8_SNORM]     = (U32)GL_R8_SNORM;
            m[PF_R16_SNORM]    = (U32)GL_R16_SNORM;
            m[PF_RG8_SNORM]    = (U32)GL_RG8_SNORM;
            m[PF_RG16_SNORM]   = (U32)GL_RG16_SNORM;
            m[PF_RGB8_SNORM]   = (U32)GL_RGB8_SNORM;
            m[PF_RGB16_SNORM]  = (U32)GL_RGB16_SNORM;
            m[PF_RGBA8_SNORM]  = (U32)GL_RGBA8_SNORM;
            m[PF_RGBA16_SNORM] = (U32)GL_RGBA16_SNORM;
            // unsigned integer ////////////////////////////////////////////
            m[PF_R8UI]     = (U32)GL_R8UI;
            m[PF_R16UI]    = (U32)GL_R16UI;
            m[PF_R32UI]    = (U32)GL_R32UI;
            m[PF_RG8UI]    = (U32)GL_RG8UI;
            m[PF_RG16UI]   = (U32)GL_RG16UI;
            m[PF_RG32UI]   = (U32)GL_RG32UI;
            m[PF_RGB8UI]   = (U32)GL_RGB8UI;
            m[PF_RGB16UI]  = (U32)GL_RGB16UI;
            m[PF_RGB32UI]  = (U32)GL_RGB32UI;
            m[PF_RGBA8UI]  = (U32)GL_RGBA8UI;
            m[PF_RGBA16UI] = (U32)GL_RGBA16UI;
            m[PF_RGBA32UI] = (U32)GL_RGBA32UI;
            // signed integer //////////////////////////////////////////////
            m[PF_R8I]     = (U32)GL_R8I;
            m[PF_R16I]    = (U32)GL_R16I;
            m[PF_R32I]    = (U32)GL_R32I;
            m[PF_RG8I]    = (U32)GL_RG8I;
            m[PF_RG16I]   = (U32)GL_RG16I;
            m[PF_RG32I]   = (U32)GL_RG32I;
            m[PF_RGB8I]   = (U32)GL_RGB8I;
            m[PF_RGB16I]  = (U32)GL_RGB16I;
            m[PF_RGB32I]  = (U32)GL_RGB32I;
            m[PF_RGBA8I]  = (U32)GL_RGBA8I;
            m[PF_RGBA16I] = (U32)GL_RGBA16I;
            m[PF_RGBA32I] = (U32)GL_RGBA32I;
            // float ///////////////////////////////////////////////////////
            m[PF_R32F]    = (U32)GL_R32F;
            m[PF_RG32F]   = (U32)GL_RG32F;
            m[PF_RGB32F]  = (U32)GL_RGB32F;
            m[PF_RGBA32F] = (U32)GL_RGBA32F;
            // depth ///////////////////////////////////////////////////////
            m[PF_DEPTH16]  = (U32)GL_DEPTH_COMPONENT16;
            m[PF_DEPTH32F] = (U32)GL_DEPTH_COMPONENT32F;

            return m;
        }

        map<U32, PixelDefinition::PixelFormat>
        GLPixelDefinitionAdapter::MapOpenGLInternalFormatToFramework() {
            map<U32, PixelDefinition::PixelFormat> m;
            m[(U32)GL_R8]     = PF_R8;
            m[(U32)GL_R16]    = PF_R16;
            m[(U32)GL_RG8]    = PF_RG8;
            m[(U32)GL_RG16]   = PF_RG16;
            m[(U32)GL_RGB8]   = PF_RGB8;
            m[(U32)GL_RGB16]  = PF_RGB16;
            m[(U32)GL_RGBA8]  = PF_RGBA8;
            m[(U32)GL_RGBA16] = PF_RGBA16;
            // signed normalized integer ///////////////////////////////////
            m[(U32)GL_R8_SNORM]     = PF_R8_SNORM;
            m[(U32)GL_R16_SNORM]    = PF_R16_SNORM;
            m[(U32)GL_RG8_SNORM]    = PF_RG8_SNORM;
            m[(U32)GL_RG16_SNORM]   = PF_RG16_SNORM;
            m[(U32)GL_RGB8_SNORM]   = PF_RGB8_SNORM;
            m[(U32)GL_RGB16_SNORM]  = PF_RGB16_SNORM;
            m[(U32)GL_RGBA8_SNORM]  = PF_RGBA8_SNORM;
            m[(U32)GL_RGBA16_SNORM] = PF_RGBA16_SNORM;
            // unsigned integer ////////////////////////////////////////////
            m[(U32)GL_R8UI]     = PF_R8UI;
            m[(U32)GL_R16UI]    = PF_R16UI;
            m[(U32)GL_R32UI]    = PF_R32UI;
            m[(U32)GL_RG8UI]    = PF_RG8UI;
            m[(U32)GL_RG16UI]   = PF_RG16UI;
            m[(U32)GL_RG32UI]   = PF_RG32UI;
            m[(U32)GL_RGB8UI]   = PF_RGB8UI;
            m[(U32)GL_RGB16UI]  = PF_RGB16UI;
            m[(U32)GL_RGB32UI]  = PF_RGB32UI;
            m[(U32)GL_RGBA8UI]  = PF_RGBA8UI;
            m[(U32)GL_RGBA16UI] = PF_RGBA16UI;
            m[(U32)GL_RGBA32UI] = PF_RGBA32UI;
            // signed integer //////////////////////////////////////////////
            m[(U32)GL_R8I]     = PF_R8I;
            m[(U32)GL_R16I]    = PF_R16I;
            m[(U32)GL_R32I]    = PF_R32I;
            m[(U32)GL_RG8I]    = PF_RG8I;
            m[(U32)GL_RG16I]   = PF_RG16I;
            m[(U32)GL_RG32I]   = PF_RG32I;
            m[(U32)GL_RGB8I]   = PF_RGB8I;
            m[(U32)GL_RGB16I]  = PF_RGB16I;
            m[(U32)GL_RGB32I]  = PF_RGB32I;
            m[(U32)GL_RGBA8I]  = PF_RGBA8I;
            m[(U32)GL_RGBA16I] = PF_RGBA16I;
            m[(U32)GL_RGBA32I] = PF_RGBA32I;
            // float ///////////////////////////////////////////////////////
            m[(U32)GL_R32F]    = PF_R32F;
            m[(U32)GL_RG32F]   = PF_RG32F;
            m[(U32)GL_RGB32F]  = PF_RGB32F;
            m[(U32)GL_RGBA32F] = PF_RGBA32F;
            // depth ///////////////////////////////////////////////////////
            m[(U32)GL_DEPTH_COMPONENT16] = PF_DEPTH16;
            m[(U32)GL_DEPTH_COMPONENT32F] = PF_DEPTH32F;

            return m;
        }

        map<U32, string> GLPixelDefinitionAdapter::MapOpenGLPixelFormatToString() {
            map<U32, std::string> m;
            m[(U32)GL_RED]             = "GL_RED";
            m[(U32)GL_RG]              = "GL_RG";
            m[(U32)GL_RGB]             = "GL_RGB";
            m[(U32)GL_RGBA]            = "GL_RGBA";
            m[(U32)GL_RED_INTEGER]     = "GL_RED_INTEGER";
            m[(U32)GL_RG_INTEGER]      = "GL_RG_INTEGER";
            m[(U32)GL_RGB_INTEGER]     = "GL_RGB_INTEGER";
            m[(U32)GL_RGBA_INTEGER]    = "GL_RGBA_INTEGER";
            m[(U32)GL_DEPTH_COMPONENT] = "GL_DEPTH_COMPONENT";

            return m;
        }

        map<U32, string> GLPixelDefinitionAdapter::MapOpenGLDataTypeToString() {
            map<U32, std::string> m;
            m[(U32)GL_UNSIGNED_BYTE]  = "GL_UNSIGNED_BYTE";
            m[(U32)GL_UNSIGNED_SHORT] = "GL_UNSIGNED_SHORT";
            m[(U32)GL_UNSIGNED_INT]   = "GL_UNSIGNED_INT";
            m[(U32)GL_BYTE]           = "GL_BYTE";
            m[(U32)GL_SHORT]          = "GL_SHORT";
            m[(U32)GL_INT]            = "GL_INT";
            m[(U32)GL_FLOAT]          = "GL_FLOAT";
            m[(U32)GL_DOUBLE]         = "GL_DOUBLE";

            return m;
        }

        map<U32, string> GLPixelDefinitionAdapter::MapOpenGLInternalFormatToString() {
            map<U32, std::string> m;
            m[(U32)GL_R8]     = "GL_R8";
            m[(U32)GL_R16]    = "GL_R16";
            m[(U32)GL_RG8]    = "GL_RG8";
            m[(U32)GL_RG16]   = "GL_RG16";
            m[(U32)GL_RGB8]   = "GL_RGB8";
            m[(U32)GL_RGB16]  = "GL_RGB16";
            m[(U32)GL_RGBA8]  = "GL_RGBA8";
            m[(U32)GL_RGBA16] = "GL_RGBA16";
            // signed normalized integer ///////////////////////////////////
            m[(U32)GL_R8_SNORM]     = "GL_R8_SNORM";
            m[(U32)GL_R16_SNORM]    = "GL_R16_SNORM";
            m[(U32)GL_RG8_SNORM]    = "GL_RG8_SNORM";
            m[(U32)GL_RG16_SNORM]   = "GL_RG16_SNORM";
            m[(U32)GL_RGB8_SNORM]   = "GL_RGB8_SNORM";
            m[(U32)GL_RGB16_SNORM]  = "GL_RGB16_SNORM";
            m[(U32)GL_RGBA8_SNORM]  = "GL_RGBA8_SNORM";
            m[(U32)GL_RGBA16_SNORM] = "GL_RGBA16_SNORM";
            // unsigned integer ////////////////////////////////////////////
            m[(U32)GL_R8UI]     = "GL_R8UI";
            m[(U32)GL_R16UI]    = "GL_R16UI";
            m[(U32)GL_R32UI]    = "GL_R32UI";
            m[(U32)GL_RG8UI]    = "GL_RG8UI";
            m[(U32)GL_RG16UI]   = "GL_RG16UI";
            m[(U32)GL_RG32UI]   = "GL_RG32UI";
            m[(U32)GL_RGB8UI]   = "GL_RGB8UI";
            m[(U32)GL_RGB16UI]  = "GL_RGB16UI";
            m[(U32)GL_RGB32UI]  = "GL_RGB32UI";
            m[(U32)GL_RGBA8UI]  = "GL_RGBA8UI";
            m[(U32)GL_RGBA16UI] = "GL_RGBA16UI";
            m[(U32)GL_RGBA32UI] = "GL_RGBA32UI";
            // signed integer //////////////////////////////////////////////
            m[(U32)GL_R8I]     = "GL_R8I";
            m[(U32)GL_R16I]    = "GL_R16I";
            m[(U32)GL_R32I]    = "GL_R32I";
            m[(U32)GL_RG8I]    = "GL_RG8I";
            m[(U32)GL_RG16I]   = "GL_RG16I";
            m[(U32)GL_RG32I]   = "GL_RG32I";
            m[(U32)GL_RGB8I]   = "GL_RGB8I";
            m[(U32)GL_RGB16I]  = "GL_RGB16I";
            m[(U32)GL_RGB32I]  = "GL_RGB32I";
            m[(U32)GL_RGBA8I]  = "GL_RGBA8I";
            m[(U32)GL_RGBA16I] = "GL_RGBA16I";
            m[(U32)GL_RGBA32I] = "GL_RGBA32I";
            // float ///////////////////////////////////////////////////////
            m[(U32)GL_R32F]    = "GL_R32F";
            m[(U32)GL_RG32F]   = "GL_RG32F";
            m[(U32)GL_RGB32F]  = "GL_RGB32F";
            m[(U32)GL_RGBA32F] = "GL_RGBA32F";
            // depth ///////////////////////////////////////////////////////
            m[(U32)GL_DEPTH_COMPONENT16]  = "GL_DEPTH_COMPONENT16";
            m[(U32)GL_DEPTH_COMPONENT32F] = "GL_DEPTH_COMPONENT32F";

            return m;
        }

        U32 GLPixelDefinitionAdapter::GetOpenGLPerChannelDataType() const {
            return MapDataTypeFromFrameworkToOpenGL()[mPerChannelDataType];
        }

        U32 GLPixelDefinitionAdapter::GetOpenGLPixelFormat() const {
            return MapPixelFormatFromFrameworkToOpenGL()[mPixelFormat];
        }

        U32 GLPixelDefinitionAdapter::GetOpenGLInternalPixelFormat() const {
            return MapPixelInternalFormatFromFrameworkToOpenGL()[mPixelFormat];
        }

        U32 GLPixelDefinitionAdapter::GetOpenGLIsNormalized() const {
            return (IsNormalized() ? (U32)GL_TRUE : (U32)GL_FALSE);
        }

        std::string GLPixelDefinitionAdapter::ToString() const {
            std::stringstream ss;

            ss << "ChannelDataType(" << MapDataElementTypeToNameString()[mPerChannelDataType];
            U32 glDataType = GetOpenGLPerChannelDataType();
            ss << ": " << MapOpenGLDataTypeToString()[glDataType] << ") ";

            ss << "x" << mNumberOfChannels;
            ss << (IsNormalized() ? " (normalized), " : ", ");

            ss << "PixelFormat(" << ConvertPixelFormatToString(mPixelFormat);
            U32 glPixelFormat = GetOpenGLPixelFormat();
            ss << ": " << MapOpenGLPixelFormatToString()[glPixelFormat] << "), ";

            ss << "BytesPerPixel(" << GetPixelSizeInBytes();
            U32 glInternalFormat = GetOpenGLInternalPixelFormat();
            ss << ": " << MapOpenGLInternalFormatToString()[glInternalFormat] << ")";
            return ss.str();
        }

        std::string GLPixelDefinitionAdapter::ConvertOpenGLInternalFormatToString(int pixelformat) {
            std::stringstream ss;
            auto m = MapOpenGLInternalFormatToString();
            if (m.find(pixelformat) != m.end()) {
                ss << m[pixelformat];
            }
            else {
              ss << "Unsupported Format(0x" << std::hex << pixelformat << ")" << std::ends;
            }
            return ss.str();
        }

        const GLPixelDefinitionAdapter &GLPixelDefinitionAdapter::operator=(const GLPixelDefinitionAdapter &rhs) {
            this->CopyFrom(rhs);
            return *this;
        }

        const GLPixelDefinitionAdapter &GLPixelDefinitionAdapter::operator=(const PixelDefinition &rhs) {
            this->CopyFrom(rhs);
            return *this;
        }

    }
}
