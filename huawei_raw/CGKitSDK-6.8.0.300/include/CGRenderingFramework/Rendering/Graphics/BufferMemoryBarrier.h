/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.
 * Description: Operations related to BufferMemoryBarrier.
 */

#ifndef BUFFER_MEMORY_BARRIER_H
#define BUFFER_MEMORY_BARRIER_H

#include "Core/Types.h"
#include "Rendering/RenderCommon.h"
#include "Rendering/Graphics/Queue.h"

NS_CG_BEGIN

struct BufferMemoryBarrierAccessAndQueueInfo {
    AccessFlagBits srcAccessType = ACCESS_NONE;
    AccessFlagBits dstAccessType = ACCESS_NONE;
    Queue* srcQueue = nullptr;
    Queue* dstQueue = nullptr;
};

struct BufferMemoryBarrierInfo {
    PipelineStageFlags srcStageMask = PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    PipelineStageFlags dstStageMask = PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    std::vector<BufferMemoryBarrierAccessAndQueueInfo> accessAndQueueInfo;
};

class CGKIT_EXPORT BufferMemoryBarrier {
public:
    BufferMemoryBarrier() = default;
    virtual ~BufferMemoryBarrier() = default;
    void Create(const BufferMemoryBarrierInfo& bufferMemoryBarrierInfo);
    const BufferMemoryBarrierInfo& GetBufferMemoryBarrierInfo() const;

protected:
    virtual void CreateImpl(const BufferMemoryBarrierInfo& bufferMemoryBarrierInfo) = 0;

private:
    BufferMemoryBarrierInfo m_baseInfo;
};

NS_CG_END

#endif
