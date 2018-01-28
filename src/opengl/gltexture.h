//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#ifndef LIBUMF_OPENGL_GLTEXTURE_H
#define LIBUMF_OPENGL_GLTEXTURE_H

#include "linalg/interval.h"
#include "linalg/vec.h"
#include "linalg/color.h"
#include "utils/bindableinterface.h"
#include "gltextureinterface.h"
#include "glpixeldefinitionadapter.h"

using namespace nb;
using namespace nb::linalg;

namespace nb {
namespace opengl {

class GLTexture : public nb::utils::BindableInterface, public GLTextureInterface {
public:
    GLTexture(U32 texture_unit = 0);
    explicit GLTexture(const PixelDefinition& pixel_definition, U32 width, U32 height, U32 texture_unit = 0);
    explicit GLTexture(const string& strFP, U32 texture_unit = 0);
    virtual ~GLTexture();

    //File IO
    bool ReadImageFile(const string &strFP);
    bool WriteImageFile(const string &strFP);

    //Memory IO
    bool ReadImageMemoryBlock(const nb::linalg::ImageDefinition &blockdef, const void *block) override;
    bool WriteImageMemoryBlock(U64 block_size, void* block) const override;

    //Binding
    void Bind() override;
    void Unbind() override;

    //glinterface
    U32 GetTextureHandle() const override;
    ImageDefinition GetImageDefinition() const override;
    void SetImageDefinition(const ImageDefinition& d);

    //dimension
    void Resize(U32 width, U32 height);


    //texture unit
    U32 GetActiveTextureUnit() const { return mTextureUnit;}
    void SetActiveTextureUnit(U32 unit);

    bool ComputeValueRange(int channel, nb::linalg::Interval<float>& interval) const;

    static SupportedImageFormats GetImageFileType(const string& strFP);

    static bool CheckerBoard(shared_ptr<GLTexture>& outTexture,
                             U32 nTilesAtX = 8,
                             U32 nTilesAtY = 8,
                             U32 nPixelsPerTile = 16,
                             const Color& darkcolor = Color::Grey(),
                             const Color& lightcolor = Color::White());

    static bool CheckerBoardFloatImage(shared_ptr<GLTexture> &outTexture,
                                       U32 nTilesAtX = 8,
                                       U32 nTilesAtY = 8,
                                       U32 nPixelsPerTile = 16,
                                       float dark_intensity = 0.5f,
                                       float light_intensity = 1.0f);

    static bool BarGraphFloatImage(shared_ptr<GLTexture> &outTexture,
                                   U32 width,
                                   U32 height,
                                   float min_intensity = 0.0f,
                                   float max_intensity = 1.0f);

    bool IsValid() const;

    /*!
     * \brief GetTextureParameters as a string
     * \param handle handle to the OpenGL Texture
     * \return string containing all the extracted information
     */
    static std::string GetTextureParameters(U32 handle);

    static bool IsValidTextureHandle(U32 handle);
protected:
    //const binding
    void ConstBind() const;
    void ConstUnbind() const;


    void Cleanup();

    bool ReadPngImage(const string &strFP);
    bool WritePngImage(const string &strFP);

    bool ReadRawImage(const string &strFP);
    bool WriteRawImage(const string &strFP);

    void Setup();

protected:
    static const U32 kRawImageFormatSignature = (U32)(0xAAFFAAFF);
    U32     mTextureMode;
    U32     mTextureUnit;
    U32     mGLTextureHandle;
    ImageDefinition mImageDefinition;
};

}
}


#endif // LIBUMF_OPENGL_GLTEXTURE_H
