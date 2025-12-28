/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2022. All rights reserved.
 * Description: Render stage used in rendering path
 */

#ifndef RENDER_STAGE_H
#define RENDER_STAGE_H

#include "Scene/SceneManager.h"
#include "Core/Types.h"
#include "Rendering/RenderCommon.h"
#include "Rendering/RenderPassCreateInfo.h"

NS_CG_BEGIN

class CommandBuffer;
class Texture;
class JobResource;
class RenderContext;
class RenderingPath;
class Camera;
class FrameBuffer;
class RenderPass;
class RenderTarget;
class RenderData;
class Light;
class MaterialInstance;
class MaterialInstanceImpl;
class Shader;
class SubMesh;
struct PipelineState;
struct ShaderResourceGroup;

enum StageType {
    STAGE_BASE,
    STAGE_ADDITIONAL,
    STAGE_TYPE_MAX
};

class CGKIT_EXPORT RenderStage {
    RTTI_DEFINE(CGKit::RenderStage);
public:
    RenderStage(RenderingPath* renderingPath);
    virtual ~RenderStage();

    virtual void Initialize();
    virtual void Uninitialize();
    virtual void Update(const Camera* camera, f32 deltaTime);
    virtual void Render(const Camera* camera);
    virtual void Pause();
    virtual void Resume();
    virtual void Resize(u32 width, u32 height);
    virtual void BeginRenderPass();
    virtual void BeginRenderPass(const FrameBuffer* frameBuffer);
    virtual void EndRenderPass();
    virtual const std::vector<Texture*>& GetGBuffer() const;
    virtual const Texture* GetGBuffer(u32 index) const;
    virtual const Texture* GetDepthStencilTexture() const;
    JobResource* GetJobResource(u32 jobId) const;
    CommandBuffer* GetCommandBuffer(u32 jobId) const;
    void Draw(MaterialInstance* materialInstance, const SubMesh* subMesh);
    void SetRenderPassInfo(const RenderPassCreateInfo& renderPassInfo);
    bool CreateRenderPass();

protected:
    virtual const RenderPass* GetRenderPass() const;
    const FrameBuffer* GetFrameBuffer() const;
    const Shader* GetShader(const PipelineState& pipelineState, const Light* light, RenderingPathType type) const;
    virtual void DestroyTextures();
    void SetPushConstantLightInfo(MaterialInstanceImpl* MaterialInstance, const Light* light) const;
    void UpdateShaderResourceCasCadeUniformBuffer(const PipelineState& pipelineState, const ShaderResourceGroup& srg,
        const Light* light);
    GraphicsRenderer* GetGraphicsRenderer() const;
    const GraphicsConfig* GetGraphicsConfig() const;
    const SceneManager* GetSceneManager() const;
    const SceneCullingDataManager* GetSceneCullingDataManager() const;

    virtual void UpdateShaderResource(const PipelineState& pipelineState,
        const ShaderResourceGroup& srg, const RenderData* renderData);

protected:
    RenderingPath* m_renderingPath = nullptr;
    RenderContext* m_renderContext = nullptr;
    RenderPass* m_renderPass = nullptr;
    RenderTarget* m_renderTarget = nullptr;
    std::vector<Texture*> m_colorTextures;
    Texture* m_depthStencil = nullptr;
    RenderPassCreateInfo m_renderPassInfo;
    ClearValue m_clearValue;

private:
    virtual void SetViewPort(CommandBuffer* commandBuffer);
};

NS_CG_END

#endif
