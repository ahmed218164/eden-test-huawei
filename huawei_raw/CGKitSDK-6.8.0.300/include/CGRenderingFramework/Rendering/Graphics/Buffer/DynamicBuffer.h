/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2022. All rights reserved.
 * Description: Dynamic buffer for rendering
 */

#ifndef DYNAMIC_BUFFER_H
#define DYNAMIC_BUFFER_H

#include "Core/Types.h"
#include "Rendering/Graphics/Buffer/Buffer.h"
#include "Rendering/Graphics/GraphicsRenderer.h"
#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

class DynamicBuffer {
public:
    struct BufferAllocation {
        Buffer* buffer;
        u64 frameNumber;
    };

    DynamicBuffer(const GraphicsRenderer* graphicsRenderer, BufferCreateUsage bufferCreateUsage);

    virtual ~DynamicBuffer();

    bool Update(const void* data, u64 offset, u64 size);

    inline const Buffer* Get() const
    {
        return m_currentBuffer;
    }

    void Destroy();

protected:
    virtual Buffer* Allocate(u64 size);
    bool ValidateAllocationInfo(u64 size);
    BufferCreateUsage m_bufferCreateUsage;
    std::list<BufferAllocation> m_bufferList;
    Buffer* m_currentBuffer;
    const GraphicsRenderer* m_graphicsRenderer { nullptr };
};
NS_CG_END
#endif
