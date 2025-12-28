/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2022. All rights reserved.
 * Description: Renderer of Graphics
 */

#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include "Rendering/RenderCommon.h"
#include "Math/Matrix4.h"
#include "Rendering/RenderPassCreateInfo.h"
#include "Rendering/Graphics/BufferMemoryBarrier.h"
#include "Rendering/Graphics/TextureMemoryBarrier.h"
#include "Rendering/Graphics/Texture.h"
#include "Rendering/Graphics/SwapChain.h"
#include "Rendering/Graphics/FrameBuffer.h"
#include "Rendering/Graphics/Queue.h"
#include "Rendering/Graphics/QueueCreateInfo.h"
#include "Rendering/Graphics/RenderPass.h"
#include "Rendering/Graphics/Pipeline.h"
#include "Rendering/Graphics/PipelineLayout.h"
#include "Rendering/Graphics/ShaderStageCreateInfo.h"
#include "Rendering/Graphics/TextureViewCreateInfo.h"
#include "Rendering/Graphics/Shader.h"
#include "Rendering/Graphics/DescriptorSetLayout.h"
#include "Rendering/Graphics/DescriptorSet.h"
#include "Rendering/Graphics/CommandBufferCreateInfo.h"
#include "Rendering/Graphics/Buffer/Buffer.h"


NS_CG_BEGIN

class FrameResource;
class CommandBuffer;
class Semaphore;
class GraphicsConfig;
class Camera;
class PipelineCache;

class CGKIT_EXPORT GraphicsRenderer {
    friend class RenderingPath;
    friend class Camera;
    friend class RenderTarget;
    friend class DynamicBuffer;
    friend class ScreenShot;

public:
    GraphicsRenderer(const GraphicsConfig* graphicsConfig);
    GraphicsRenderer(const GraphicsRenderer& graphicsRenderer) = delete;
    virtual ~GraphicsRenderer();
    GraphicsRenderer& operator = (const GraphicsRenderer& graphicsRenderer) = delete;
    static GraphicsRenderer* CreateGraphicsRenderer(const GraphicsConfig* graphicsConfig);

public:
    virtual Texture* CreateTexture(const TextureCreateInfo& info) const = 0;
    virtual Texture* CreateTextureView(const TextureViewCreateInfo& info) const = 0;
    virtual SwapChain* CreateSwapChain(const SwapChainCreateInfo& info) const = 0;
    virtual DescriptorSetLayout* CreateDescriptorSetLayout(const DescriptorSetLayoutCreateInfo& info) const = 0;
    virtual DescriptorSet* CreateDescriptorSet(const DescriptorSetCreateInfo& info) const = 0;
    virtual FrameBuffer* CreateFrameBuffer(const FrameBufferCreateInfo& info) = 0;

    /**
     * Create Pipeline based on the PipelineCreateInfo.
     */
    virtual Pipeline* CreatePipeline(const PipelineCreateInfo& info) const = 0;

    /**
     * Create PipelineLayout based on the PipelineLayoutCreateInfo.
     */
    virtual PipelineLayout* CreatePipelineLayout(const PipelineLayoutCreateInfo& info) const = 0;
    virtual CommandBuffer* CreateCommandBuffer(const CommandBufferCreateInfo& info) = 0;
    virtual RenderPass* CreateRenderPass(const RenderPassCreateInfo& renderPassCreateInfo) const = 0;
    virtual ShaderStage* CreateShaderStage(const ShaderStageCreateInfo& shaderStageInfo) const = 0;
    virtual Buffer* CreateBuffer(const BufferCreateInfo& bufferCreateInfo) const = 0;
    virtual Buffer* CreateBufferView(const BufferViewCreateInfo& bufferViewCreateInfo) const = 0;
    Shader* CreateShader(const ShaderCreateInfo& shaderCreateInfo) const;
    virtual Sampler* CreateSampler(const SamplerCreateInfo& info) const = 0;
    virtual Queue* CreateQueue(const QueueCreateInfo& queueCreateInfo) const = 0;
    virtual BufferMemoryBarrier* CreateBufferMemoryBarrier(
        const BufferMemoryBarrierInfo& bufferMemoryBarrierInfo) const = 0;
    virtual TextureMemoryBarrier* CreateTextureMemoryBarrier(
        const TextureMemoryBarrierInfo& textureMemoryBarrierInfo) const = 0;

    /**
     * Obtain the pipeline from the cache based on the hash value of the PipelineCreateInfo.
     * If it does not exist in the cache, then create a new pipeline.
     */
    virtual Pipeline* RequestPipeline(const PipelineCreateInfo& createInfo) const;

    // in the future,remove this function to merge with DestroyTexture(Texture* texture).
    virtual void DestroyImage(void* image) const = 0;
    void DestroyBuffer(Buffer* buffer) const;
    void DestroyTexture(Texture* texture) const;
    void DestroySwapChain(SwapChain* swapChain) const;
    virtual void DestroyDescriptorSetLayout(DescriptorSetLayout* layout) const;
    virtual void DestroyDescriptorSet(DescriptorSet* descriptorSet) const;
    void DestroyPipeline(Pipeline* pipeline) const;
    void DestroyPipelineLayout(PipelineLayout* pipelineLayout) const;
    void DestroyShader(Shader* shader) const;
    void DestroyRenderPass(RenderPass* renderPass) const;
    void DestroyQueue(Queue* queue) const;
    void DestroyShaderStage(ShaderStage* shaderStage) const;
    virtual void DestroySampler(Sampler* sampler) const = 0;
    void DestroyBufferMemoryBarrier(const BufferMemoryBarrier* bufferMemoryBarrier) const;
    void DestroyTextureMemoryBarrier(const TextureMemoryBarrier* textureMemoryBarrier) const;
    void DestroyCommandBuffer(CommandBuffer* commandBuffer);

public:
    virtual bool Initialize(const void* window);
    virtual void Uninitialize();
    // recreate gpu resource when the app come to foreground
    virtual bool Resume(const void* winHandle, u32 width, u32 height);
    // destroy gpu resource when the app goes to background
    virtual void Pause();
    virtual void WaitDeviceIdle() const = 0;
    virtual bool Submit(const std::vector<CommandBuffer*>& vecCommandBuffers) = 0;

    virtual bool Begin() = 0;
    virtual void End() = 0;
    virtual void Resize(u32 nWidth, u32 nHeight);
    // return the default texture
    virtual const Texture* GetDefaultTexture() const = 0;
    virtual f32 GetAspectRatio() const = 0;
    virtual u32 GetScreenWidth() const = 0;
    virtual u32 GetScreenHeight() const = 0;
    virtual bool IsSafe(u64 frameNumber) const = 0;
    virtual u32 GetSwapChainBufferCount() const = 0;

    const Queue* GetDefaultQueue(QueueType queueType = QueueType::GRAPHICS);
    const SwapChain* GetDefaultSwapChain() const
    {
        return m_swapChain;
    }

    bool GetInitialized() const
    {
        return m_initialized;
    }

    u64 GetFrameNumber() const
    {
        return m_FrameNumber;
    }

    const GraphicsConfig* GetGraphicsConfig() const;
    virtual void* GetResourceCache() const = 0;

public:
    static std::mutex lock;

protected:
    virtual Semaphore* CreateSemaphore() = 0;
    virtual bool GetFireRotation() const = 0;
    virtual void ResetFireRotation() const = 0;
    virtual const Matrix4& GetPreRotation() = 0;

    void SetInitialized(bool initialized)
    {
        m_initialized = initialized;
    }

protected:
    u64 m_FrameNumber = 0;
    Matrix4 m_preRotation = Matrix4::IDENTITY;
    bool m_initialized = false;
    const GraphicsConfig* m_graphicsConfig = nullptr;
    SwapChain* m_swapChain = nullptr;
    Queue* m_graphicsQ = nullptr;
    Queue* m_computeQ = nullptr;
    Queue* m_transferQ = nullptr;
    PipelineCache* m_pipelineCache = nullptr;

private:
    bool CreateDefaultSwapChain();
    void CreateQueueIfNotPresent(Queue** queue, const QueueCreateInfo& createInfo) const;
};
NS_CG_END

#endif
