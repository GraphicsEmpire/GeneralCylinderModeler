//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#include "pixeldefinition.h"
#include <sstream>

using namespace std;

namespace nb {
    namespace linalg {

        PixelDefinition::PixelDefinition() : PixelDefinition(PF_RGBA8) {
        }

        PixelDefinition::PixelDefinition(const PixelDefinition &rhs) {
            CopyFrom(rhs);
        }

        PixelDefinition::PixelDefinition(const PixelDefinition::PixelFormat &format)
            : mPixelFormat(format) {
            mNumberOfChannels = ExtractNumChannelsFromPixelFormat(format);
            mPerChannelDataType = ExtractPerChannelDataTypeFromPixelFormat(format);
        }

        U32 PixelDefinition::GetPixelSizeInBytes() const {
            return mNumberOfChannels * MapDataElementTypeToSizeInBytes()[mPerChannelDataType];
        }

        U32 PixelDefinition::GetNumberOfColorChannels() const {
            return mNumberOfChannels;
        }

        PixelDefinition::PixelFormat PixelDefinition::GetPixelFormat() const {
            return mPixelFormat;
        }

        bool PixelDefinition::IsNormalized() const {
            ColorDataType t = static_cast<ColorDataType>(mPixelFormat & 0xF);
            return (t == norm8 || t == norm16 || t == snorm8 || t == snorm16);
        }

        bool PixelDefinition::IsSignedIntegerFormat() const {
            switch (mPixelFormat) {
                case PF_R8I:
                case PF_R16I:
                case PF_R32I:
                case PF_RG8I:
                case PF_RG16I:
                case PF_RG32I:
                case PF_RGB8I:
                case PF_RGB16I:
                case PF_RGB32I:
                case PF_RGBA8I:
                case PF_RGBA16I:
                case PF_RGBA32I:
                    return true;
            }
            return false;
        }

        bool PixelDefinition::IsUnsignedIntegerFormat() const {
            switch (mPixelFormat) {
                case PF_R8UI:
                case PF_R16UI:
                case PF_R32UI:
                case PF_RG8UI:
                case PF_RG16UI:
                case PF_RG32UI:
                case PF_RGB8UI:
                case PF_RGB16UI:
                case PF_RGB32UI:
                case PF_RGBA8UI:
                case PF_RGBA16UI:
                case PF_RGBA32UI:
                    return true;
            }
            return false;
        }

        bool PixelDefinition::Matches(const PixelDefinition &rhs) const {
            return (mPixelFormat == rhs.mPixelFormat);
        }

        bool PixelDefinition::operator==(const PixelDefinition &rhs) const {
            return Matches(rhs);
        }

        DataElementTypeID PixelDefinition::GetPerChannelDataType() const {
            return mPerChannelDataType;
        }

        void PixelDefinition::CopyFrom(const PixelDefinition &rhs) {
            mNumberOfChannels = rhs.mNumberOfChannels;
            mPerChannelDataType = rhs.mPerChannelDataType;
            mPixelFormat = rhs.mPixelFormat;
        }

        const PixelDefinition &PixelDefinition::operator=(const PixelDefinition &rhs) {
            CopyFrom(rhs);
            return *this;
        }

        PixelDefinition PixelDefinition::Create(const PixelDefinition::PixelFormat &format) {
            return PixelDefinition(format);
        }

        std::string PixelDefinition::ToString() const {
            std::stringstream ss;
            ss << "ChannelDataType(" << MapDataElementTypeToNameString()[mPerChannelDataType] << ") ";
            ss << "x" << mNumberOfChannels;
            ss << (IsNormalized() ? " (normalized), " : ", ");
            ss << "PixelFormat(" << ConvertPixelFormatToString(mPixelFormat) << "), ";
            ss << "BytesPerPixel(" << GetPixelSizeInBytes() << ")";
            return ss.str();
        }

        map<PixelDefinition::ColorChannelType, string> PixelDefinition::MapColorChannelTypeToString() {
            map<PixelDefinition::ColorChannelType, string> m;
            m[red]   = "R";
            m[green] = "G";
            m[blue]  = "B";
            m[alpha] = "A";
            m[depth] = "D";
            return m;
        }

        std::string PixelDefinition::ConvertPixelFormatToString(const PixelFormat &f) {
            std::stringstream ss;
            for (int i = 0; i < MAX_NUM_COLOR_CHANNELS; i++) {
                int shift = (MAX_NUM_COLOR_CHANNELS - i) * 4;
                ColorChannelType c = static_cast<ColorChannelType>((f >> shift) & 0xF);
                if (c == 0xF) {
                    break;
                }
                ss << MapColorChannelTypeToString()[c];
            }
            return ss.str();
        }

        U32 PixelDefinition::ExtractNumChannelsFromPixelFormat(const PixelDefinition::PixelFormat &f) {
            U32 result = 0;
            for (int i = 0; i < MAX_NUM_COLOR_CHANNELS; i++) {
                int shift = (MAX_NUM_COLOR_CHANNELS - i) * 4;
                ColorChannelType t = static_cast<ColorChannelType>((f >> shift) & 0xF);
                if (t < 0xF) {
                    result++;
                }
            }
            return result;
        }

        DataElementTypeID PixelDefinition::ExtractPerChannelDataTypeFromPixelFormat(
          const PixelDefinition::PixelFormat &f) {
            map<PixelDefinition::ColorDataType, DataElementTypeID> m;
            m[norm8] = etUnsignedInt8;
            m[norm16] = etUnsignedInt16;
            m[snorm8] = etInt8;
            m[snorm16] = etInt16;
            m[uint8] = etUnsignedInt8;
            m[uint16] = etUnsignedInt16;
            m[uint32] = etUnsignedInt32;
            m[int8] = etInt8;
            m[int16] = etInt16;
            m[int32] = etInt32;
            m[float32] = etFloat;

            return m[static_cast<ColorDataType>(f & 0xF)];
        };

    }
}
