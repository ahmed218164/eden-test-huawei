/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Vertex attribute.
 */

#ifndef VERTEX_ATTRIBUTE_H
#define VERTEX_ATTRIBUTE_H

#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

struct CGKIT_EXPORT VertexAttribute {
    VertexAttribute()
    {}

    VertexAttribute(const String& name, u32 location, u32 binding, PixelFormat format, u32 offset = 0)
        : name(name), location(location), binding(binding), format(format), offset(offset)
    {}

    /*
     * Equality judgment with other,equal return true, else return false.
     */
    inline bool operator==(const VertexAttribute& other) const
    {
        bool isNameEqual = (this->name == other.name);
        bool isLocationEqual = this->location == other.location;
        bool isBindingEqual = this->binding == other.binding;
        bool isFormatEqual = this->format == other.format;
        bool isOffsetEqual = this->offset == other.offset;
        return  isNameEqual && isLocationEqual && isBindingEqual && isFormatEqual && isOffsetEqual;
    }

    /*
     * Inequality judgment with other. Not equal,return true. else return false.
     */
    inline bool operator!=(const VertexAttribute& other) const
    {
        return  !(*this == other);
    }

    /*
     * VertexAttribute's name.
     */
    String name;

    /*
     * Corresponds to the location in the shader.
     */
    u32 location = 0;

    /*
     * Corresponds to the binding in the shader.
     */
    u32 binding = 0;

    /*
     * Pixel format.
     */
    PixelFormat format = PixelFormat::PIXEL_FORMAT_MAX;

    /*
     * The offset of the vertex attribute in the vertex data, default is 0.
     */
    u32 offset = 0;
};

NS_CG_END

#endif