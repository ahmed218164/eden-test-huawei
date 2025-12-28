/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: FrameBuffer, include create and destroy operations, etc.
 */

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "Core/Types.h"
#include "Rendering/Graphics/RenderPass.h"
#include "Rendering/Graphics/Texture.h"

NS_CG_BEGIN

class CGVkFrameBuffer;

struct FrameBufferCreateInfo {
    std::vector<Texture*> colorTextures;
    Texture* depthStencilTexture = nullptr;
    RenderPass* renderPass = nullptr;
};

class FrameBuffer {
public:
    /*
     * @brief the constructor
     */
    FrameBuffer();

    /*
     * @brief the destructor
     */
    virtual ~FrameBuffer();

    bool Create(const FrameBufferCreateInfo& frameBufferInfo);

    const FrameBufferCreateInfo& GetFrameBufferInfo() const;

    virtual const CGVkFrameBuffer* GetFrameBuffer() const = 0;

protected:
    FrameBufferCreateInfo m_baseInfo;
    virtual bool CreateImpl(const FrameBufferCreateInfo& frameBufferInfo) = 0;
};

NS_CG_END

#endif
