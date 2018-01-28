//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#include "datatypes.h"
using namespace std;

namespace nb {
    namespace linalg {

        std::map<DataElementTypeID, U32> MapDataElementTypeToSizeInBytes() {
            std::map<DataElementTypeID, U32> m;
            m[etFloat]  = sizeof(float);
            m[etInt8]   = sizeof(I8);
            m[etInt16]  = sizeof(I16);
            m[etInt32]  = sizeof(I32);
            m[etInt64]  = sizeof(I64);
            m[etDouble]        = sizeof(double);
            m[etUnsignedInt8]  = sizeof(U8);
            m[etUnsignedInt16] = sizeof(U16);
            m[etUnsignedInt32] = sizeof(U32);
            m[etUnsignedInt64] = sizeof(U64);
            return m;
        };

        std::map<DataElementTypeID, std::string> MapDataElementTypeToNameString() {
            std::map<DataElementTypeID, std::string> m;
            m[etFloat]  = string("float");
            m[etInt8]   = string("int8");
            m[etInt16]  = string("int16");
            m[etInt32]  = string("int32");
            m[etInt64]  = string("int64");
            m[etDouble]        = string("double");
            m[etUnsignedInt8]  = string("uint8");
            m[etUnsignedInt16] = string("uint16");
            m[etUnsignedInt32] = string("uint32");
            m[etUnsignedInt64] = string("uint64");

            return m;
        };
    }
}