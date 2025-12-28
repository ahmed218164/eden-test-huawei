/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.
 * Description: TextureViewCreateInfo.
 */

#ifndef TEXTURE_VIEW_CREATEINFO_H
#define TEXTURE_VIEW_CREATEINFO_H

#include "Core/Types.h"
#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

class Texture;

struct TextureViewCreateInfo {
    Texture* texture = nullptr;
    ImageType imageType = ImageType::IMAGE_TYPE_2D;
    PixelFormat format = PixelFormat::PIXEL_FORMAT_R8G8B8A8_UNORM;
    u8 baseLevel = 0;
    u8 levelCount = 1;
    u8 baseLayer = 0;
    u8 layerCount = 1;
};

NS_CG_END

#endif