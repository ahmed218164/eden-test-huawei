/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2022. All rights reserved.
 * Description: Buffer for rendering
 */
#ifndef BUFFER_H
#define BUFFER_H

#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

struct BufferCreateInfo {
    BufferCreateUsage bufferUsage { BUFFER_VERTEX };
    MemCreateUsage memoryUsage { MEMORY_UNKNOWN_USAGE };
    u64 size { 0 };
};

class Buffer;
struct BufferViewCreateInfo {
    const Buffer* baseBuffer { nullptr };
    u64 offset { 0 };
    u64 size { 0 };
};

class CGKIT_EXPORT Buffer {
public:
    Buffer() = default;

    Buffer(const Buffer& buffer) = delete;

    Buffer& operator = (const Buffer& buffer) = delete;

    virtual ~Buffer() = default;

    void Create(const BufferCreateInfo& bufferInfo);

    void Create(const BufferViewCreateInfo& bufferViewCreateInfo);

    void Update(const void* data, u64 offset, u64 size);

    virtual u64 GetOffset() const;

    virtual u64 GetSize() const;

    virtual u64 GetAlignment() const = 0;

    static MemCreateUsage GetRecommendedUsage(BufferCreateUsage bufferCreateUsage);

    /**
     * is buffer view or not
     */
    bool IsBufferView() const;

protected:
    virtual void CreateImpl(const BufferCreateInfo& bufferInfo) = 0;
    virtual void UpdateImpl(const void* data, u64 offset, u64 size) = 0;
    virtual void CreateImpl(const BufferViewCreateInfo& bufferViewInfo) = 0;
    bool m_isBufferView { false };
protected:
    BufferCreateInfo m_bufferCreateInfo {};
    u32 m_hash { 0 };
    u64 m_offset { 0 };

};
NS_CG_END
#endif