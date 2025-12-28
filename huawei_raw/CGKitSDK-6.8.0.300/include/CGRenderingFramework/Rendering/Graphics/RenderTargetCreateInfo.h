/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: RenderTargetCreateInfo.
 */

#ifndef RENDER_TARGET_CREATEINFO_H
#define RENDER_TARGET_CREATEINFO_H

#include "Core/Types.h"
#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

struct RenderTargetCreateInfo {
    PixelFormat colorFormat = PixelFormat::PIXEL_FORMAT_R8G8B8A8_UNORM;
    PixelFormat depthFormat = PixelFormat::PIXEL_FORMAT_D24_UNORM_S8_UINT;
    u32 width = 0;
    u32 height = 0;
    RenderTargetType targetType = RenderTargetType::FROM_SWAPCHAIN;
};

NS_CG_END

#endif