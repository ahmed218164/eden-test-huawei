/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2022. All rights reserved.
 * Description: Base class of post process renderStage.
 */

#ifndef POST_PROCESS_BASE_H
#define POST_PROCESS_BASE_H

#include "Rendering/RenderStage.h"

NS_CG_BEGIN

class CGKIT_EXPORT PostProcessStage : public RenderStage {
public:
    PostProcessStage(RenderingPath* renderingPath);
    virtual ~PostProcessStage();
    virtual void Initialize() override;
    virtual void Uninitialize() override;
    virtual void Update(const Camera* camera, f32 deltaTime) override;
    virtual void Render(const Camera* camera) override;
    virtual void PostRender(Texture* srcTexture);
    virtual void Pause() override;
    virtual void Resume() override;
    virtual const Texture* GetOutputTexture(u32 index) const;
};

NS_CG_END

#endif
