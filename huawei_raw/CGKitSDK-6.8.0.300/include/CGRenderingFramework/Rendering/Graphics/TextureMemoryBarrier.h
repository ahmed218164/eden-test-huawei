/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.
 * Description: Operations related to TextureMemoryBarrier.
 */

#ifndef TEXTURE_MEMORY_BARRIER_H
#define TEXTURE_MEMORY_BARRIER_H

#include "Core/Types.h"
#include "Rendering/RenderCommon.h"
#include "Rendering/Graphics/Queue.h"

NS_CG_BEGIN

struct TextureMemoryBarrierAccessAndQueueInfo {
    AccessFlagBits srcAccessType = ACCESS_NONE;
    AccessFlagBits dstAccessType = ACCESS_NONE;
    ImageLayout oldLayout = IMAGE_LAYOUT_UNDEFINED;
    ImageLayout newLayout = IMAGE_LAYOUT_UNDEFINED;
    Queue* srcQueue = nullptr;
    Queue* dstQueue = nullptr;
};

struct TextureMemoryBarrierInfo {
    PipelineStageFlags srcStageMask;
    PipelineStageFlags dstStageMask;
    std::vector<TextureMemoryBarrierAccessAndQueueInfo> accessAndQueueInfo;
};

class CGKIT_EXPORT TextureMemoryBarrier {
public:
    TextureMemoryBarrier() = default;
    virtual ~TextureMemoryBarrier() = default;
    void Create(const TextureMemoryBarrierInfo& textureMemoryBarrierInfo);
    const TextureMemoryBarrierInfo& GetTextureMemoryBarrierInfo() const;

protected:
    virtual void CreateImpl(const TextureMemoryBarrierInfo& textureMemoryBarrierInfo) = 0;

private:
    TextureMemoryBarrierInfo m_baseInfo;
};

NS_CG_END

#endif