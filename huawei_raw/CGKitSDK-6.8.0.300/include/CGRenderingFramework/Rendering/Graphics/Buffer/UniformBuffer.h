/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2022. All rights reserved.
 * Description: uniform buffer for rendering
 */

#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

#include "Rendering/Graphics/Buffer/DynamicBuffer.h"

NS_CG_BEGIN

class UniformBuffer : public DynamicBuffer {
public:
    explicit UniformBuffer(const GraphicsRenderer* graphicsRenderer)
        : DynamicBuffer(graphicsRenderer, BUFFER_CONSTANT) {};
    virtual ~UniformBuffer();

protected:
    /* !
     * @brief The size of base buffer is as much as frame number times
     * uBufferSize, thus the base buffer can be sliced to frame number and each
     * for one uniform buffer to use. Just like the swap chain's image, the buffer
     * slice can be reused only if it is safe and has no increase in size,
     * otherwise, a new base buffer should be create for each frame's rendering.
     * @param uBufferSize: Size of allocated uniform buffer
     * @return:  Slice of base buffer
     */
    Buffer* Allocate(u64 uBufferSize) override;

private:
    Buffer* AllocateFromBaseBuffer(u64& usedSize, u64 size);
    u64 GetAlignmentSize(u64 offset);
    bool TryAllocate(u64 offset, u64 size);
    void ReleaseBuffer();

private:
    static const u64 ALIGNMENT_DEFAULT = 1024;
    static const u64 ORIGIN_SIZE = 0;
    u64 m_size { 0 };
    u64 m_usedSize { 0 };
    u64 m_maxFrameNum { 0 };
    Buffer* m_baseBuffer { nullptr };
    std::list<Buffer*> m_unreleasedBuffers;
};
NS_CG_END
#endif
