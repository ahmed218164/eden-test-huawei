/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: RenderTarget, include create and Resize operations, etc.
 */

#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include "Core/Types.h"
#include "Rendering/Graphics/RenderTargetCreateInfo.h"
#include "Rendering/Graphics/GraphicsRenderer.h"

NS_CG_BEGIN

class CGKIT_EXPORT RenderTarget {
    friend class RenderStage;
    friend class RenderStageForward;
    friend class RenderStageShadow;
public:
    /*
     * @brief the constructor
     */
    RenderTarget(const RenderTargetCreateInfo& renderTargetCreateInfo);

    /*
     * @brief the destructor
     */
    ~RenderTarget();
    RenderTarget(const RenderTarget& renderTarget) = delete;
    RenderTarget& operator=(const RenderTarget& renderTarget) = delete;

    bool Create(const std::vector<Texture*>& colorTextures, const Texture* depthStencil, const RenderPass* renderPass,
        const GraphicsRenderer* graphicsRenderer);
    void Resize(u32 width, u32 height);

private:
    const FrameBuffer* GetFrameBuffer() const;

private:
    FrameBuffer* m_frameBuffer = nullptr;
    u32 m_width = 0;
    u32 m_height = 0;
    RenderTargetType m_targetType = RenderTargetType::FROM_SWAPCHAIN;
};

NS_CG_END

#endif