//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cctype>
#include "gltexture.h"
#include "glselect.h"
#include "gltypes.h"
#include "glerror.h"
#include "utils/logger.h"
#include "utils/path.h"
#include "lodepng.h"

using namespace nb;
using namespace nb::utils;
using namespace std;

namespace nb {
    namespace opengl {

        GLTexture::GLTexture(U32 texture_unit): mTextureMode((U32) GL_TEXTURE_2D),
                                                mTextureUnit(texture_unit),
                                                mGLTextureHandle((U32) INVALID_GLBUFFER)
        {
            Setup();

            mImageDefinition.SetPixelFormat(PixelDefinition::PF_RGBA8);
            mImageDefinition.SetDimension(0, 0);
        }

        GLTexture::GLTexture(const PixelDefinition &pixel_definition,
                             U32 width,
                             U32 height,
                             U32 texture_unit):mTextureMode((U32) GL_TEXTURE_2D),
                                               mTextureUnit(texture_unit),
                                               mGLTextureHandle((U32) INVALID_GLBUFFER)
        {
            //setup
            Setup();

            //image definition
            mImageDefinition.SetPixelFormat(PixelDefinition::PF_RGBA8);
            mImageDefinition.SetDimension(width, height);

            ReadImageMemoryBlock(mImageDefinition, NULL);
        }

        GLTexture::GLTexture(const string &strFP, U32 texture_unit):mTextureMode((U32) GL_TEXTURE_2D),
                                                                    mTextureUnit(texture_unit),
                                                                    mGLTextureHandle((U32) INVALID_GLBUFFER) {
            //setup
            Setup();

            //image definition
            mImageDefinition.SetPixelFormat(PixelDefinition::PF_RGBA8);
            mImageDefinition.SetDimension(0, 0);

            if (!ReadImageFile(strFP)) {
                nbLogError("Texture creation failed for file: %s", strFP.c_str());
            }
        }

        GLTexture::~GLTexture() {
            Cleanup();
        }

        void GLTexture::Cleanup() {
            if (glIsTexture(mGLTextureHandle)) {
                glDeleteTextures(1, &mGLTextureHandle);
                mGLTextureHandle = INVALID_GLBUFFER;
            }
        }

        bool GLTexture::IsValid() const {
            return IsValidTextureHandle(mGLTextureHandle);
        }


        bool GLTexture::ReadImageFile(const string &strFP) {
            if (!Path::FileExists(strFP))
                return false;

            //filetype
            SupportedImageFormats ft = GetImageFileType(strFP);

            //Load image data
            switch (ft) {
                case sifPNG:
                    return ReadPngImage(strFP);
                case sifRAW:
                    return ReadRawImage(strFP);
                default:
                    break;
            }

            return true;
        }


        bool GLTexture::ReadPngImage(const string &strFP) {

            vector<U8> payload;
            U32 width, height = 0;
            U32 error = lodepng::decode(payload, width, height, strFP.c_str());
            if (error) {
                nbLogError("Unable to load png image from file: %s", strFP.c_str());
                return false;
            }


            //Now read from memory block
            ImageDefinition imd;
            imd.SetPixelFormat(PixelDefinition::PF_RGBA8);
            imd.SetDimension(width, height);

            //Force the image definition
            if(!mImageDefinition.Matches(imd)) {
                SetImageDefinition(imd);
                nbLogInfo("Forced the image definition to match that of the input file [%s]", imd.ToString().c_str());
            }

            //read from memory block
            return ReadImageMemoryBlock(imd, payload.data());
        }

        bool GLTexture::WritePngImage(const string &strFP) {
            vector<U8> payload;
            payload.resize(mImageDefinition.GetMemorySizeInBytes());
            if(!WriteImageMemoryBlock(payload.size(), payload.data())) {
                return false;
            }

            U32 error = lodepng::encode(strFP, payload, mImageDefinition.GetWidth(), mImageDefinition.GetHeight());
            if (error) {
                nbLogError("Unable to store png to file: %s", strFP.c_str());
                return false;
            }


            return true;
        }

        bool GLTexture::WriteImageFile(const string &strFP) {
            if (Path::FileExists(strFP)) {
                nbLogWarn("I will overwrite at [%s]", strFP.c_str());
            }

            //filetype
            SupportedImageFormats ft = GetImageFileType(strFP);

            //Load image data
            switch (ft) {
                case sifPNG:
                    return WritePngImage(strFP);
                case sifRAW:
                    return WriteRawImage(strFP);
                default:
                    break;
            }

            return false;
        }

        void GLTexture::Setup() {
            //delete the previous texture
            Cleanup();

            //Generate Texture
            glActiveTexture((GLenum)((U32)(GL_TEXTURE0) + mTextureUnit));
            glGenTextures(1, &mGLTextureHandle);
            glBindTexture((GLenum) mTextureMode, mGLTextureHandle);

            //Params
            glTexParameteri((GLenum) mTextureMode, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri((GLenum) mTextureMode, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri((GLenum) mTextureMode, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri((GLenum) mTextureMode, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glBindTexture((GLenum) mTextureMode, 0);
        }

        void GLTexture::Bind() {
            ConstBind();
        }

        void GLTexture::Unbind() {
            ConstUnbind();
        }

        void GLTexture::ConstBind() const {
            if (!IsValid()) {
                nbLogError("Texture is not initialized yet!");
                return;
            }

            //bind
            glEnable((GLenum) mTextureMode);
            glActiveTexture((GLenum)((U32)(GL_TEXTURE0) + mTextureUnit));
            glBindTexture((GLenum) mTextureMode, mGLTextureHandle);

            //set all channels swizzle to RED
            if((mImageDefinition.GetPixelDefinition().GetPixelFormat() == PixelDefinition::PF_DEPTH32F)||
                (mImageDefinition.GetPixelDefinition().GetPixelFormat() == PixelDefinition::PF_R32F)){
                GLint Swizzle[] = {GL_RED, GL_RED, GL_RED, GL_RED};
                glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, Swizzle);
            }
        }

        void GLTexture::ConstUnbind() const {
            //unbind
            glBindTexture((GLenum) mTextureMode, 0);
            glDisable((GLenum) mTextureMode);
        }


        void GLTexture::Resize(U32 width, U32 height) {

            if (mImageDefinition.GetWidth() == width && mImageDefinition.GetHeight() == height)
                return;

            //assign new size
            mImageDefinition.SetDimension(width, height);

            //Force reallocating texture in video memory
            ReadImageMemoryBlock(mImageDefinition, NULL);
        }

        void GLTexture::SetActiveTextureUnit(U32 unit) {
            if(unit != mTextureUnit) {
                mTextureUnit = unit;
            }
        }

        SupportedImageFormats GLTexture::GetImageFileType(const string &strFP) {
            string extension = Path::ToUpper(Path::GetFileExtension(strFP));

            if(extension == string("PNG"))
                return sifPNG;
            else if(extension == string("RAW"))
                return sifRAW;
            else
                return sifUnsupported;
        }

        bool GLTexture::CheckerBoard(shared_ptr<GLTexture> &outTexture,
                                     U32 nTilesAtX,
                                     U32 nTilesAtY,
                                     U32 nPixelsPerTile,
                                     const Color &darkcolor,
                                     const Color &lightcolor) {
            if (!outTexture) {
                nbLogError("Invalid input texture");
                return false;
            }

            if (nTilesAtX == 0 || nTilesAtY == 0 || nPixelsPerTile <= 0) {
                nbLogError("Invalid input dimension");
                return false;
            }

            U32 log2 = Log2i(nPixelsPerTile);
            U32 two_power_n = 1 << log2;

            //create the shared_ptr output
            U32 nPixelsAtX = nTilesAtX * nPixelsPerTile;
            U32 nPixelsAtY = nTilesAtY * nPixelsPerTile;
            vector<U8> pixels;
            //pixels.resize(nPixelsAtX * nPixelsAtY * outTexture->GetPixelDefinition().GetNumberOfColorChannels());
            pixels.resize(nPixelsAtX * nPixelsAtY * 4);

            U32 pixel_index = 0;
            vec4u8 dark = darkcolor.ToVec4u8();
            vec4u8 light = lightcolor.ToVec4u8();

            for (U32 i = 0; i < nPixelsAtY; i++) {
                for (U32 j = 0; j < nPixelsAtX; j++) {
                    bool is_white = (((i & two_power_n) == 0) ^ ((j & two_power_n) == 0));
                    pixel_index = i * nPixelsAtX * 4 + j * 4;

                    if (is_white)
                        light.Store(&pixels[pixel_index]);
                    else
                        dark.Store(&pixels[pixel_index]);
                }
            }

            //setup output
            ImageDefinition imd;
            imd.SetPixelFormat(PixelDefinition::PF_RGBA8);
            imd.SetDimension(nPixelsAtX, nPixelsAtY);

            //set output
            outTexture->SetImageDefinition(imd);
            return outTexture->ReadImageMemoryBlock(imd, pixels.data());
        }

        bool GLTexture::CheckerBoardFloatImage(shared_ptr<GLTexture> &outTexture, U32 nTilesAtX, U32 nTilesAtY, U32 nPixelsPerTile,
                                                      float dark_intensity, float light_intensity) {
            if (!outTexture) {
                nbLogError("Invalid input texture");
                return false;
            }

            if (nTilesAtX == 0 || nTilesAtY == 0 || nPixelsPerTile <= 0) {
                nbLogError("Invalid input dimension");
                return false;
            }

            U32 log2 = Log2i(nPixelsPerTile);
            U32 two_power_n = 1 << log2;

            //create the shared_ptr output
            U32 nPixelsAtX = nTilesAtX * nPixelsPerTile;
            U32 nPixelsAtY = nTilesAtY * nPixelsPerTile;

            vector<float> pixels;
            pixels.resize(nPixelsAtX * nPixelsAtY);
            U32 pixel_index = 0;
            for (U32 i = 0; i < nPixelsAtY; i++) {
                for (U32 j = 0; j < nPixelsAtX; j++) {
                    bool is_white = (((i & two_power_n) == 0) ^ ((j & two_power_n) == 0));
                    pixel_index = i * nPixelsAtX + j;

                    if (is_white)
                        pixels[pixel_index] = light_intensity;
                    else
                        pixels[pixel_index] = dark_intensity;
                }
            }

            //setup output
            ImageDefinition imd;
            imd.SetPixelFormat(PixelDefinition::PF_R32F);
            imd.SetDimension(nPixelsAtX, nPixelsAtY);

            //set output
            outTexture->SetImageDefinition(imd);
            return outTexture->ReadImageMemoryBlock(imd, pixels.data());
        }

        bool
        GLTexture::BarGraphFloatImage(shared_ptr<GLTexture> &outTexture,
                                      U32 width, U32 height,
                                      float min_intensity,
                                      float max_intensity) {
            if (!outTexture) {
                nbLogError("Invalid input texture");
                return false;
            }

            if (width == 0 || height == 0) {
                nbLogError("Invalid input dimension");
                return false;
            }

            //compute pixels
            vector<float> pixels;
            pixels.resize(width * height);
            U32 pixel_index = 0;

            for (U32 col = 0; col < width; col++) {
                float t = (float)col/(float)(width-1);
                float intensity = Lerp(t, min_intensity, max_intensity);

                for (U32 row = 0; row < height; row++) {
                    pixel_index = row * width + col;
                    pixels[pixel_index] = intensity;
                }
            }

            //setup output
            ImageDefinition imd;
            imd.SetPixelFormat(PixelDefinition::PF_R32F);
            imd.SetDimension(width, height);

            //set output
            outTexture->SetImageDefinition(imd);
            return outTexture->ReadImageMemoryBlock(imd, pixels.data());
        }



        string GLTexture::GetTextureParameters(U32 handle) {
            if (glIsTexture(handle) == GL_FALSE)
                return "Not texture object";

            int width, height;
            int format;
            glBindTexture(GL_TEXTURE_2D, handle);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);            // get texture width
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);          // get texture height
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT,
                                     &format); // get texture internal format
            glBindTexture(GL_TEXTURE_2D, 0);

            //Convert internal format to string
            std::string formatName = GLPixelDefinitionAdapter::ConvertOpenGLInternalFormatToString(format);

            ///Create the final string
            std::stringstream ss;
            ss << width << "x" << height << ", " << formatName;
            return ss.str();
        }

        U32 GLTexture::GetTextureHandle() const {
            return mGLTextureHandle;
        }

        bool GLTexture::IsValidTextureHandle(U32 handle) {
            return (handle != (U32) INVALID_GLBUFFER && glIsTexture(handle));
        }

        ImageDefinition GLTexture::GetImageDefinition() const {
            return mImageDefinition;
        }

        void GLTexture::SetImageDefinition(const ImageDefinition &d) {
            if(mImageDefinition.Matches(d)) {
                return;
            }

            //store the new image definition and resize the texture accordingly
            mImageDefinition = d;
            ReadImageMemoryBlock(mImageDefinition, NULL);
        }


        bool GLTexture::ReadImageMemoryBlock(const nb::linalg::ImageDefinition &blockdef, const void *block) {
            if(!mImageDefinition.Matches(blockdef)) {
                nbLogError("The image definition for the supplied memory block does not match mine. Expected = [%s], Supplied = [%s]",
                           mImageDefinition.ToString().c_str(), blockdef.ToString().c_str());
                return false;
            }

            //adapt pixel definition to opengl
            GLPixelDefinitionAdapter glpixel = mImageDefinition.GetPixelDefinition();
            GLenum format = (GLenum)glpixel.GetOpenGLPixelFormat();
            GLenum dtype = (GLenum)glpixel.GetOpenGLPerChannelDataType();


            Bind();
            glTexImage2D((GLenum) mTextureMode,
                         0,
                         (GLenum) glpixel.GetOpenGLInternalPixelFormat(),
                         mImageDefinition.GetWidth(),
                         mImageDefinition.GetHeight(),
                         0,
                         format,
                         dtype,
                         block);
            nbCheckGLError();
            Unbind();
            return true;
        }

        bool GLTexture::WriteImageMemoryBlock(U64 block_size, void *block) const {
            if(block == NULL) {
                nbLogError("Supplied memory block is not allocated!");
                return false;
            }

            if(block_size < mImageDefinition.GetMemorySizeInBytes()) {
                nbLogError("Supplied memory block is too small! Expected: [%llu], Got: [%llu]",
                           mImageDefinition.GetMemorySizeInBytes(),
                           block_size);
                return false;
            }

            //adapt pixel definition to opengl
            GLPixelDefinitionAdapter glpixel = mImageDefinition.GetPixelDefinition();
            GLenum format = (GLenum)glpixel.GetOpenGLPixelFormat();
            GLenum dtype = (GLenum)glpixel.GetOpenGLPerChannelDataType();

            //bind
            ConstBind();
            glGetTexImage((GLenum)mTextureMode,
                          0,
                          format,
                          dtype,
                          block);
            nbCheckGLError();
            ConstUnbind();

            return true;
        }

        bool GLTexture::ReadRawImage(const string &strFP) {

            ifstream myfile (strFP.c_str(), ios::in | ios::binary);
            if (!myfile.is_open())
            {
                nbLogError("Invalid input raw file [%s]", strFP.c_str());
                return false;
            }


            U32 signature = 0;
            myfile.read((char*)&signature, sizeof(signature));
            if(signature != kRawImageFormatSignature) {
                nbLogError("Invalid raw file [%s]", strFP.c_str());
                myfile.close();
                return false;
            }

            U64 header_size = 0;
            ImageDefinition header;
            myfile.read((char*)&header_size, sizeof(header_size));
            if(header_size != sizeof(ImageDefinition)) {
                myfile.close();
                return false;
            }

            //read header
            myfile.read((char*)&header, sizeof(ImageDefinition));

            //Force the image definition
            if(!mImageDefinition.Matches(header)) {
                SetImageDefinition(header);
                nbLogInfo("Forced the image definition to match that of the input file [%s]", header.ToString().c_str());
            }

            //Read the binary payload
            vector<U8> payload;
            payload.resize(header.GetMemorySizeInBytes());

            //read payload
            myfile.read((char*)payload.data(), payload.size());
            myfile.close();

            //read from memory block
            return ReadImageMemoryBlock(header, payload.data());
        }

        bool GLTexture::WriteRawImage(const string &strFP) {
            ofstream myfile (strFP.c_str(), ios::out | ios::binary);
            if (!myfile.is_open()) {
                nbLogError("Unable to open output raw file [%s]", strFP.c_str());
                return false;
            }

            U32 sig = kRawImageFormatSignature;
            myfile.write((const char*)&sig, sizeof(sig));

            U64 header_size = sizeof(ImageDefinition);
            myfile.write((char*)&header_size, sizeof(header_size));

            //write header
            myfile.write((char*)&mImageDefinition, sizeof(ImageDefinition));

            //fetch the binary payload from GPU
            vector<U8> payload;
            payload.resize(mImageDefinition.GetMemorySizeInBytes());
            if(!WriteImageMemoryBlock(payload.size(), payload.data())) {
                return false;
            }

            //write payload
            myfile.write((char*)payload.data(), payload.size());
            myfile.close();

            //return result
            return true;
        }

        bool GLTexture::ComputeValueRange(int channel, nb::linalg::Interval<float> &interval) const {
            const int num_channels = mImageDefinition.GetPixelDefinition().GetNumberOfColorChannels();
            if(channel >= num_channels)
                return false;

            if(mImageDefinition.GetPixelDefinition().GetPerChannelDataType() != DataElementTypeID::etFloat)
                return false;

            vector<float> payload;
            payload.resize(mImageDefinition.GetMemorySizeInBytes() / sizeof(float));
            if(!WriteImageMemoryBlock(mImageDefinition.GetMemorySizeInBytes(), payload.data())) {
                return false;
            }

            U64 num_pixels = mImageDefinition.GetWidth() * mImageDefinition.GetHeight();
            float max_value = std::numeric_limits<float>::min();
            float min_value = std::numeric_limits<float>::max();
            for(U64 i = 0; i < num_pixels; i++) {
                float v = payload[i * num_channels + channel];
                min_value = std::min<float>(min_value, v);
                max_value = std::max<float>(max_value, v);
            }

            interval.Set(min_value, max_value);
            return true;
        }



    }
}
