/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: RenderPass.
 */
#ifndef RENDER_PASS_H
#define RENDER_PASS_H

#include "Rendering/RenderPassCreateInfo.h"

NS_CG_BEGIN

class CGKIT_EXPORT RenderPass {
public:
    RenderPass() = default;
    RenderPass(const RenderPass& RenderPass) = delete;
    RenderPass& operator=(const RenderPass& RenderPass) = delete;

    virtual ~RenderPass() = default;
    bool Create(const RenderPassCreateInfo& renderPassCreateInfo);
    const RenderPassCreateInfo& GetRenderPassCreateInfo() const;

protected:
    virtual bool CreateImpl(const RenderPassCreateInfo& info) = 0;
    RenderPassCreateInfo m_createInfo;
};

NS_CG_END

#endif