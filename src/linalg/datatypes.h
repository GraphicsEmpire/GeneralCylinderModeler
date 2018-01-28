//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#ifndef LIBUMF_LINALG_DATATYPES_H
#define LIBUMF_LINALG_DATATYPES_H

#include <map>
#include <string>
#include "base.h"

namespace nb {
namespace linalg {


/*!
 * \brief The DataElementTypeID enum
 */
enum DataElementTypeID  : U32
                         {etInt8, etUnsignedInt8,
                          etInt16, etUnsignedInt16,
                          etInt32, etUnsignedInt32,
                          etInt64, etUnsignedInt64,
                          etFloat, etDouble,
                          etCount, etUnrecognized
                         };

//TypeID to Type
template <DataElementTypeID TID>
struct TypeIDToType {
};

template <>
struct TypeIDToType<etInt8> {
    using RESULT=I8;
};

template <>
struct TypeIDToType<etInt16> {
    using RESULT=I16;
};

template <>
struct TypeIDToType<etInt32> {
    using RESULT=I32;
};

template <>
struct TypeIDToType<etInt64> {
    using RESULT=I64;
};

template <>
struct TypeIDToType<etFloat> {
    using RESULT=float;
};

template <>
struct TypeIDToType<etUnsignedInt8> {
    using RESULT=U8;
};

template <>
struct TypeIDToType<etUnsignedInt16> {
    using RESULT=U16;
};

template <>
struct TypeIDToType<etUnsignedInt32> {
    using RESULT=U32;
};

template <>
struct TypeIDToType<etUnsignedInt64> {
    using RESULT=U64;
};

template <>
struct TypeIDToType<etDouble> {
    using RESULT=double;
};
//////////////////////////////////////////////////////
//Type to TypeID
template <typename T>
struct TypeToTypeID {
};

template <>
struct TypeToTypeID<I8> {
    static const DataElementTypeID value=etInt8;
};

template <>
struct TypeToTypeID<I16> {
    static const DataElementTypeID value=etInt16;
};

template <>
struct TypeToTypeID<I32> {
    static const DataElementTypeID value=etInt32;
};

template <>
struct TypeToTypeID<I64> {
    static const DataElementTypeID value=etInt64;
};

template <>
struct TypeToTypeID<float> {
    static const DataElementTypeID value=etFloat;
};

template <>
struct TypeToTypeID<U8> {
    static const DataElementTypeID value=etUnsignedInt8;
};

template <>
struct TypeToTypeID<U16> {
    static const DataElementTypeID value=etUnsignedInt16;
};

template <>
struct TypeToTypeID<U32> {
    static const DataElementTypeID value=etUnsignedInt32;
};

template <>
struct TypeToTypeID<U64> {
    static const DataElementTypeID value=etUnsignedInt64;
};

template <>
struct TypeToTypeID<double> {
    static const DataElementTypeID value=etDouble;
};

std::map<DataElementTypeID, U32> MapDataElementTypeToSizeInBytes();
std::map<DataElementTypeID, std::string> MapDataElementTypeToNameString();

////////////////////////////////////////////////////

}
}

#endif // LIBUMF_LINALG_DATATYPES_H
