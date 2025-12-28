#ifndef FGRENDERPASS_H
#define FGRENDERPASS_H

#include "Core/Global.h"
#include "Core/Types.h"
#include "Rendering/Viewport.h"
#include "Rendering/Graphics/FrameBuffer.h"
#include "Rendering/FrameGraph/FGHandle.h"
#include "Rendering/FrameGraph/FGCommon.h"
#include "Rendering/FrameGraph/FGTexture.h"

NS_CG_BEGIN

class ResourceNode;
class RenderPass;
class CommandBuffer;
class IPassExecuter;
class FrameGraph;

class CGKIT_EXPORT FGRenderPass {
    friend class RenderPassNode;
    friend class ComputePassNode;
    friend class FrameGraph;
    friend class RenderingPathFrameGraph;

public:
    explicit FGRenderPass(FrameGraph& fg, GraphicsRenderer* graphicsRenderer);

    ~FGRenderPass();

private:
    static const PassType PASS_TYPE = PassType::GRAPHICS_PASS;

    static constexpr u32 COLOR_ATTACHMENT_COUNT = 8;
    static constexpr u32 TOTAL_ATTACHMENT_COUNT = COLOR_ATTACHMENT_COUNT + 1;

    struct RenderTarget {
        FGHandle<FGTexture> colors[COLOR_ATTACHMENT_COUNT];
        FGHandle<FGTexture> depthstencil;
    };

    union Attachments {
        FGHandle<FGTexture> array[TOTAL_ATTACHMENT_COUNT];
        RenderTarget target;
    };

    struct AttachmentFlag {
        bool clearFlag = false;
        bool colorFlag = false;
        bool depthFlag = false;
        bool readByNextPass = false;
        bool presentByNextPass = false;
    };

    struct Descriptor {
        Attachments attachments{};
        Viewport viewPort{};
        u32 msaaSamples{0};
        bool isResize = false;

        ClearValue clearValue{};
        AttachmentFlages attachmentClearFlags{AttachmentFlages::NONE_ATTACHMENT};

        const ResourceNode* GetResourceNode(FrameGraph& fg, u32 index) const;

        void ResolveAttachmentFlag(FrameGraph& fg, u32 index, AttachmentFlag& attachmentFlag) const;
    };

    void SetDescriptor(const Descriptor& descriptor);

    void Create();

    void Destroy();

    void Begin(CommandBuffer* commandBuffer);

    void End(CommandBuffer* commandBuffer);

    const RenderPass* GetBackendRenderPass() const;

    void ResolveRenderPassInfo(RenderPassCreateInfo& rpInfo);

    void ResolveFrameBufferInfo(FrameBufferCreateInfo& fbInfo);

    void CreateBackendRenderPass();

    void CreateBackendFrameBuffer();

    Descriptor m_descriptor;
    FrameGraph& m_fg;
    GraphicsRenderer* m_graphicsRenderer = nullptr;

    struct RenderPassFactory {
        RenderPass* Create(const RenderPassCreateInfo& info, GraphicsRenderer* graphicsRenderer);
        void Destroy(RenderPass* res);
    };

    struct RenderPassHasher {
        size_t Compute(const RenderPassCreateInfo& info);
    };

    using FGRenderPassAllocator = ResourceAllocator<RenderPass, RenderPassCreateInfo, RenderPassFactory,
        RenderPassHasher>;
    using RenderPassHandle = FGRenderPassAllocator::ResourceHandle;
    static FGRenderPassAllocator s_RenderPassAllocator;

    struct FrameBufferFactory {
        FrameBuffer* Create(const FrameBufferCreateInfo& info, GraphicsRenderer* graphicsRenderer);
        void Destroy(FrameBuffer* res);
    };

    struct FrameBufferHasher {
        size_t Compute(const FrameBufferCreateInfo& info);
    };

    using FGFrameBufferAllocator = ResourceAllocator<FrameBuffer, FrameBufferCreateInfo,
        FrameBufferFactory, FrameBufferHasher>;
    using FrameBufferHandle = FGFrameBufferAllocator::ResourceHandle;
    static FGFrameBufferAllocator s_FrameBufferAllocator;

    RenderPassHandle m_renderPassHandle;
    FrameBufferHandle m_frameBufferHandle;
};

NS_CG_END

#endif
