/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2022. All rights reserved.
 * Description: RenderingPath utils.
 */

#ifndef RENDER_PATH_H
#define RENDER_PATH_H

#include "Rendering/RenderCommon.h"
#ifdef CGKIT_SUPPORT_UIPHASE
#include "Rendering/Graphics/RenderPass.h"
#include "Rendering/Graphics/UIPhase.h"
#endif

NS_CG_BEGIN

class Camera;
class Texture;
class RenderStage;
class RenderContext;
class PostProcessStage;
class PostProcessStageManager;

class CGKIT_EXPORT RenderingPath {
    friend class Camera;
    friend class RenderStage;
public:
    RenderingPath(Camera* camera, RenderContext* renderContext, RenderingPathType renderingPathType);
    virtual ~RenderingPath();

    virtual void Initialize();
    virtual void Uninitialize();
    virtual void Resume();
    virtual void Pause();
    virtual void Update(f32 deltaTime);
    virtual void Render();
    virtual void Resize(u32 width, u32 height);

    virtual const std::vector<Texture*>& GetGBuffer() const = 0;
    virtual const Texture* GetGBuffer(u32 index) const = 0;
    virtual const Texture* GetDepthStencilTexture() const = 0;
    virtual RenderingPathType GetRenderingPathType() const;
    virtual RenderTargetType GetRenderTargetType() const;
    virtual const Texture* GetOutputTexture(PostProcessStage* stage = nullptr) const;
#ifdef CGKIT_SUPPORT_UIPHASE
    const UIPhase* GetUIPhase() const
    {
        return m_uiPhase;
    }

    void SetUIPhase(UIPhase* uiPhase)
    {
        this->m_uiPhase = uiPhase;
    }
#endif

protected:
    const RenderContext* GetRenderContext() const;
    const PostProcessStageManager* GetPostProcessStageManager() const;
    bool BeginCommand();
    void EndCommand();
    void RenderStages();
    void Submit();
    void Reset();
    void PreRotate();
    void DestroyProcessStageManager();
#ifdef CGKIT_SUPPORT_UIPHASE
    UIPhase* m_uiPhase;
#endif

protected:
    std::vector<RenderStage*> m_renderStages;
    RenderContext* m_renderContext = nullptr;
    Camera* m_camera = nullptr;
    RenderingPathType m_renderingPathType = RENDER_PATH_TYPE_FORWARD;
    PostProcessStageManager* m_postProcessStageManager = nullptr;
    bool m_resize = false;
};

NS_CG_END

#endif
