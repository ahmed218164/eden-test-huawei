/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2022. All rights reserved.
 * Description: Operations related to CommandBuffer.
 */

#ifndef COMMAND_BUFFER_H
#define COMMAND_BUFFER_H

#include "Core/Global.h"
#include "Rendering/RenderCommon.h"
#include "Rendering/Graphics/Buffer/DynamicBuffer.h"
#include "Rendering/Graphics/BufferMemoryBarrier.h"
#include "Rendering/Graphics/TextureMemoryBarrier.h"
#include "Rendering/Graphics/RenderPass.h"
#include "Rendering/Graphics/FrameBuffer.h"
#include "Rendering/Graphics/Texture.h"
#include "Rendering/Graphics/CommandBufferCreateInfo.h"

NS_CG_BEGIN

class Pipeline;
struct Viewport;

class CGKIT_EXPORT CommandBuffer {
public:

    /*
     * A default constructor is used.
     */
    CommandBuffer();

    /*
     * A destructor used to free memories.
     */
    virtual ~CommandBuffer();

    /*
     * A delete function is used to prevent the copy of the class.
     */
    CommandBuffer(const CommandBuffer& commandBuffer) = delete;

    /*
     * A delete function is used to prevent the assignment of the class.
     */
    CommandBuffer& operator=(const CommandBuffer& commandBuffer) = delete;

    /*
     * is recorded or not
     */
    bool isRecorded() const { return m_Recorded; };

    /*
     * set recorded status
     */
    void SetRecordedStatus(bool status) { m_Recorded = status; };

    /*
     * A Commandbuffer object is created based on the creation information.
     */
    bool Create(const CommandBufferCreateInfo& commandBufferCreateInfo);

    /*
     * Get the creation information of a commandbuffer object.
     */
    const CommandBufferCreateInfo& GetCommandBufferCreateInfo() const;

    /*
     * Begin a renderpass.
     */
    virtual void BeginRenderPass(const ClearValue& clearValue, const Viewport& viewPort,
        const RenderPass* renderPass, const FrameBuffer* frameBuffer, SubpassContents subpassContents) = 0;

    /*
     * End a renderpass.
     */
    virtual void EndRenderPass() = 0;

    /*
     * Begin running a command.
     */
    virtual bool BeginCommand(const RenderPass* renderPass = nullptr, const FrameBuffer* frameBuffer = nullptr) = 0;

    /*
     * Finish running a command.
     */
    virtual void EndCommand() = 0;

    /*
     * Initialize a viewport object and bind to a command buffer.
     */
    virtual void BindViewport(const Viewport& viewport) = 0;

    /*
     * Initialize a scissor object and bind to a command buffer.
     */
    virtual void BindScissorRect(s32 x, s32 y, u32 width, u32 height) = 0;

    /*
     * Get vertex buffers and bind to a command buffer.
     */
    virtual void SetVertexBuffer(const std::vector<DynamicBuffer*>& vertexBuffers) = 0;

    /*
     * Bind index buffers to a command buffer.
     */
    virtual void SetIndexBuffer(const Buffer* indexBuffer, u32 stride) = 0;

    /*
     * Bind the pipeline object to a command buffer.
     */
    virtual void SetPipeline(const Pipeline* pipeline) = 0;

    /*
     * Bind the descriptorsets to a command buffer.
     */
    virtual void BindDescriptorSets(const std::map<u32, DescriptorSet*>& descriptorSets) = 0;

    /*
     * Push constants.
     */
    virtual void PushConstant(Pipeline* pipeline, ShaderStageType type,
        const void* values, u32 offset, u32 size) = 0;

    /*
     * Draw primitives.
     */
    virtual void Draw(u32 vertexCount) = 0;

    /*
     * Draw primitives with indexed vertices.
     */
    virtual void DrawIndexed(u32 indexCount, u32 indexOffset, u32 vertexOffset) = 0;

    /*
     * Excute a secondary command buffer from a primary command buffer.
     */
    virtual void ExecuteCommand(CommandBuffer* secondaryCommandBuffer) = 0;

    /*
     * Reset to the initial state.
     */
    virtual void Reset() = 0;

    /*
     * Set a memory dependendcy.
     */
    virtual void SetPipelineBarrier(const BufferMemoryBarrier* bufferMemoryBarrier) = 0;

    /*
     * Set a memory dependendcy for texture.
     */
    virtual void SetPipelineBarrier(const TextureMemoryBarrier* textureMemoryBarrier, const Texture* texture) = 0;

    /*
     * Transition to the next subpass of a render pass.
     */
    virtual void NextSubpass() = 0;

    /*
     * Set line width dynamically for a command buffer.
     */
    virtual void SetLineWidth(f32 width) = 0;

    /*
     * Copy image info to buffer.
     */
    virtual u8* CopyTextureToBuffer(const void* imageView, u8* buffer, u32 width, u32 height) = 0;

    /*
     * Set whether to open stencil test enable.
     */
    virtual void SetStencilTestEnable(bool bEnable) = 0;

    /*
     * Set Stencil comparison mask
     */
    virtual void SetStencilCompareMask(StencilFaceFlag stencilFaceFlag, u32 mask) = 0;

    /*
     * Set Stencil reference.
     */
    virtual void SetStencilReference(StencilFaceFlag stencilFaceFlag, u32 ref) = 0;

    /*
     * Set the Stencil's write mask.
     */
    virtual void SetStencilWriteMask(StencilFaceFlag stencilFaceFlag, u32 mask) = 0;

    /*
     * Set an array of four values specifying the R, G, B, and A components of
     * the blend constant color used in blending.
     */
    virtual void SetBlendConstants(const std::vector<f32>& blendConstants) = 0;

protected:
    virtual bool CreateImpl(const CommandBufferCreateInfo& info) = 0;
    CommandBufferCreateInfo m_baseInfo;
private:
    bool m_Recorded = false;
};

NS_CG_END

#endif
