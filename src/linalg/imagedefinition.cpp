//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#include <sstream>
#include "imagedefinition.h"

using namespace nb::linalg;

ImageDefinition::ImageDefinition() {
    mPixelDefinition = PixelDefinition(PixelDefinition::PF_RGBA8);
    mDimension = Vec3<U32>(0,0,0);
}

ImageDefinition::ImageDefinition(const ImageDefinition &rhs) {
    CopyFrom(rhs);
}

ImageDefinition::ImageDefinition(const PixelDefinition &pixeldef, const Vec3<U32> &dimension) {
    mPixelDefinition = pixeldef;
    mDimension = dimension;
}

ImageDefinition::ImageDefinition(PixelDefinition::PixelFormat pixel_format, const Vec3<U32> &dimension) {
    mPixelDefinition = PixelDefinition(pixel_format);
    mDimension = dimension;
}

ImageDefinition::~ImageDefinition() {

}

PixelDefinition ImageDefinition::GetPixelDefinition() const {
    return mPixelDefinition;
}

void ImageDefinition::SetPixelDefinition(const PixelDefinition &pixeldef) {
    mPixelDefinition = pixeldef;
}

void ImageDefinition::SetPixelFormat(PixelDefinition::PixelFormat pixel_format) {
    mPixelDefinition = PixelDefinition(pixel_format);
}

Vec3<U32> ImageDefinition::GetDimension() const {
    return mDimension;
}

void ImageDefinition::SetDimension(U32 width, U32 height, U32 nslices) {
    mDimension = Vec3<U32>(width, height, nslices);
}

void ImageDefinition::SetDimension(const Vec3<U32>& dimension) {
    mDimension = dimension;
}

U64 ImageDefinition::GetMemorySizeInBytes() const {
    return mPixelDefinition.GetPixelSizeInBytes() * mDimension[0] * mDimension[1] * mDimension[2];
}

bool ImageDefinition::Matches(const ImageDefinition &rhs) const {
    return (mPixelDefinition.Matches(rhs.mPixelDefinition) && (mDimension == rhs.mDimension));
}

void ImageDefinition::CopyFrom(const ImageDefinition &rhs) {
    mPixelDefinition = rhs.mPixelDefinition;
    mDimension = rhs.mDimension;
}

const ImageDefinition &ImageDefinition::operator=(const ImageDefinition &rhs) {
    CopyFrom(rhs);
    return *this;
}

bool ImageDefinition::operator==(const ImageDefinition &rhs) const {
    return this->Matches(rhs);
}

std::string ImageDefinition::ToString() const {
    std::stringstream ss;
    ss << "Dimension(" << mDimension[0] << "x" << mDimension[1] << "), nSlices(" << mDimension[2]
       << "), " << mPixelDefinition.ToString();

    return ss.str();
}

U32 ImageDefinition::GetWidth() const {
    return mDimension[0];
}

U32 ImageDefinition::GetHeight() const {
    return mDimension[1];
}

U32 ImageDefinition::GetNumSlices() const {
    return mDimension[2];
}
