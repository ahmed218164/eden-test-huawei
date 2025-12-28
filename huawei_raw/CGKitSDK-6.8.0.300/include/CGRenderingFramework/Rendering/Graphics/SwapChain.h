/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2022. All rights reserved.
 * Description: SwapChain
 */

#ifndef SWAPCHAIN_H
#define SWAPCHAIN_H

#include "Core/Types.h"

NS_CG_BEGIN

class Texture;
struct SwapChainTextureInfo;

const u32 DEFAULT_SWAPCHAIN_BUFFER_COUNT = 3;

struct SwapChainCreateInfo {
    u32 width = 0;
    u32 height = 0;
    u32 backBufferCount = DEFAULT_SWAPCHAIN_BUFFER_COUNT;
};

class CGKIT_EXPORT SwapChain {
public:
    SwapChain() = default;
    virtual ~SwapChain();

    bool Create(const SwapChainCreateInfo& swapChainCreateInfo);

    virtual void Resize(u32 width, u32 height);

    const SwapChainCreateInfo& GetSwapChainCreateInfo() const { return m_baseInfo; }

    const Texture* GetColorTexture() const { return m_colorTexture; }

    virtual u32 GetFrameIndex() const = 0;
protected:
    virtual bool CreateImpl(const SwapChainCreateInfo& swapChainInfo) = 0;

    void InitTexture(const SwapChainTextureInfo& info, Texture* texture);

    Texture* m_colorTexture = nullptr;
private:
    SwapChainCreateInfo m_baseInfo;
};
NS_CG_END

#endif