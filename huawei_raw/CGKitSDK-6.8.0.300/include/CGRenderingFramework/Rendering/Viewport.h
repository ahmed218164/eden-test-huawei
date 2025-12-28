/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description:
 */
#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Core/Types.h"
#include "Math/Math.h"

NS_CG_BEGIN

struct CGKIT_EXPORT Viewport {
    Viewport(u32 x = 0, u32 y = 0, u32 width = 0, u32 height = 0, f32 minDepth = 0.0f, f32 maxDepth = 1.0f)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->minDepth = minDepth;
        this->maxDepth = maxDepth;
    }

    Viewport(const Viewport& viewport)
    {
        x = viewport.x;
        y = viewport.y;
        width = viewport.width;
        height = viewport.height;
        minDepth = viewport.minDepth;
        maxDepth = viewport.maxDepth;
    }

    Viewport& operator=(const Viewport& viewport)
    {
        if (*this != viewport) {
            x = viewport.x;
            y = viewport.y;
            width = viewport.width;
            height = viewport.height;
            minDepth = viewport.minDepth;
            maxDepth = viewport.maxDepth;
        }
        return *this;
    }

    ~Viewport() = default;

    bool operator==(const Viewport& rhs) const
    {
        return Math::Equals(x, rhs.x) &&
               Math::Equals(y, rhs.y) &&
               Math::Equals(width, rhs.width) &&
               Math::Equals(height, rhs.height) &&
               Math::Equals(minDepth, rhs.minDepth) &&
               Math::Equals(maxDepth, rhs.maxDepth);
    }

    bool operator!=(const Viewport& rhs) const
    {
        return !(*this == rhs);
    }

    bool IsDefined() const
    {
        return x >= 0 &&
               y >= 0 &&
               width > 0 &&
               height > 0 &&
               minDepth > 0.0f &&
               maxDepth > 0.0f;
    }

    f32 AspectRatio() const
    {
        return IsDefined() ? width / height : 1.0f;
    }

    u32 x = 0;
    u32 y = 0;
    u32 width = 0;
    u32 height = 0;
    f32 minDepth = 0.0f;
    f32 maxDepth = 1.0f;
};

NS_CG_END

#endif