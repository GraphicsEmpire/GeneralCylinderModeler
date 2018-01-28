//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#ifndef LIBUMF_OPENGL_GLPIXELDEFINITIONADAPTER_H
#define LIBUMF_OPENGL_GLPIXELDEFINITIONADAPTER_H

#include <map>
#include <unordered_map>
#include "linalg/pixeldefinition.h"

using namespace std;
using namespace nb::linalg;

namespace nb {
    namespace opengl {

        class GLPixelDefinitionAdapter : public PixelDefinition {
        public:
            GLPixelDefinitionAdapter();
            GLPixelDefinitionAdapter(const PixelDefinition& rhs);

            /*!
             * @return the opengl data element type per color channel
             */
            U32 GetOpenGLPerChannelDataType() const;
            U32 GetOpenGLPixelFormat() const;
            U32 GetOpenGLInternalPixelFormat() const;
            U32 GetOpenGLIsNormalized() const;

            const GLPixelDefinitionAdapter& operator=(const GLPixelDefinitionAdapter& rhs);
            const GLPixelDefinitionAdapter& operator=(const PixelDefinition& rhs);


            static map<PixelFormat, U32> MapPixelInternalFormatFromFrameworkToOpenGL();
            static map<PixelFormat, U32> MapPixelFormatFromFrameworkToOpenGL();
            static map<DataElementTypeID, U32> MapDataTypeFromFrameworkToOpenGL();

            static map<U32, PixelFormat> MapOpenGLInternalFormatToFramework();
            static map<U32, DataElementTypeID> MapOpenGLDataTypeToFramework();

            static map<U32, std::string> MapOpenGLInternalFormatToString();
            static map<U32, std::string> MapOpenGLPixelFormatToString();
            static map<U32, std::string> MapOpenGLDataTypeToString();

            std::string ToString() const override;

            /*!
             * \brief ConvertOpenGLInternalFormatToString converts the internal image format to string
             * \param format
             * \return string representation of the pixel format
             */
            static std::string ConvertOpenGLInternalFormatToString(int pixelformat);

        };
    }
}

#endif // LIBUMF_OPENGL_GLPIXELDEFINITIONADAPTER_H