#ifndef FRAME_GRAPH_H
#define FRAME_GRAPH_H

#include "Core/Global.h"
#include "Core/Macro.h"
#include "Utils/MemoryAllocator/MemoryAllocator.h"
#include "Rendering/FrameGraph/FGHandle.h"
#include "Rendering/FrameGraph/ResourceNode.h"
#include "Rendering/FrameGraph/PassExecuter.h"
#include "Rendering/FrameGraph/FGCommon.h"
#include "Rendering/FrameGraph/ResourceEdge.h"
#include "Rendering/FrameGraph/DirectedAcyclicGraph.h"
#include "Rendering/FrameGraph/PassNode.h"
#include "Rendering/FrameGraph/VirtualResource.h"

NS_CG_BEGIN

class CGKIT_EXPORT FrameGraph {
public:
    FrameGraph(GraphicsRenderer* graphicsRenderer);

    ~FrameGraph();

    class FGBuilder {
    public:
        ~FGBuilder();

        FGBuilder(FrameGraph& fg, PassNode& passNode);

        /**
         * create internal temporary resource
         */
        template<typename ResourceType>
        FGHandle<ResourceType> Create(const char* const name, typename ResourceType::Descriptor const& desc);

        /*
         * set write relationship between resource and pass
         */
        template<typename ResourceType>
        FGHandle<ResourceType> Write(const FGHandle<ResourceType>& h, ResourceUsage usage);

        /*
         * set read relationship between resource and pass
         */
        template<typename ResourceType>
        FGHandle<ResourceType> Read(const FGHandle<ResourceType>& h, ResourceUsage usage);

        /**
         * set param of render pass
         */
        void SetRenderPassDescriptor(const FGRenderPass::Descriptor& descriptor);

    private:
        FrameGraph& m_fg;
        PassNode& m_passNode;
    };

    /*
     * import external resource: texture, swapChain, etc.
     */
    template<typename ResourceType>
    FGHandle<ResourceType>
    Import(const char* const name, const ResourceType& resource, typename ResourceType::Descriptor const& desc);

    /*
     * add render pass node to frameGraph
     */
    template<typename PassData, typename Setup, typename Executer>
    PassExecutor<PassData, Executer>& AddPass(
        const char* name, Setup setup, Executer&& execute, PassType passType = PassType::GRAPHICS_PASS);

    /**
     * fill command buffer
     */
    void Begin(const std::vector<CommandBuffer*>& commandBuffer);

    /*
     * compute life cycle of resource, facilitate to create and release resource.
     */
    void Compile();

    /**
     * execute render passes in frameGraph order by the sequence of declaration,
     * and properly create and release resources before and after each render pass.
     */
    void Execute();

    /**
     * empty command buffer
     */
    void End();

private:
    CG_DELETE_COPY_AND_MOVE_CONSTRUCTOR(FrameGraph);
    ResourceNode* GetResourceNode(Handle h)
    {
        return m_resouceNodes.at(h);
    }

    Handle AddVirtualResource(VirtualResourceBase* virtualResource);

    PassNode* AddPassNode(const char* name, IPassExecuter& passExecuter, PassType passType);

    template<typename ResourceType>
    FGHandle<ResourceType> Create(const char* const name, typename ResourceType::Descriptor const& desc);

    template<typename Resource>
    FGHandle<Resource> Write(PassNode& passNode, const FGHandle<Resource>& h, ResourceUsage usage);

    template<typename Resource>
    FGHandle<Resource> Read(PassNode& passNode, const FGHandle<Resource>& h, ResourceUsage usage);

    MemoryAllocator m_allocator;
    Vector<VirtualResourceBase*> m_virtualResources;
    Vector<ResourceNode*> m_resouceNodes;
    Vector<PassNode*> m_passNodes;
    DirectedAcyclicGraph m_daGraph;
    CommandBuffer* m_commandBuffer = nullptr;
    CommandBuffer* m_computeCommandBuffer = nullptr;
    GraphicsRenderer* m_graphicsRenderer;

    friend class FGBuilder;

    friend class FGRenderPass;

    friend class PassNode;
};

template<typename ResourceType>
FGHandle<ResourceType> FrameGraph::Import(const char* const name, const ResourceType& resource,
                                          typename ResourceType::Descriptor const& desc)
{
    VirtualResourceBase* vResource =
        m_allocator.Allocate<VirtualResource<ResourceType>>(name, resource, desc, true);
    ASSERT(vResource != nullptr);

    return FGHandle<ResourceType>{AddVirtualResource(vResource)};
}

template<typename ResourceType>
FGHandle<ResourceType> FrameGraph::Create(const char* const name,
                                          typename ResourceType::Descriptor const& desc)
{
    VirtualResourceBase* vResource =
        m_allocator.Allocate<VirtualResource<ResourceType>>(name, desc, false);
    ((VirtualResource<ResourceType>*) (vResource))->AddGraphicsRenderer(m_graphicsRenderer);
    ASSERT(vResource != nullptr);
    return FGHandle<ResourceType>{AddVirtualResource(vResource)};
}

template<typename PassData, typename Setup, typename Executer>
PassExecutor<PassData, Executer>& FrameGraph::AddPass(
    const char* name, Setup setup, Executer&& execute, PassType passType)
{
    auto* const passExecuter = m_allocator.Allocate<PassExecutor<PassData, Executer>>(std::forward<Executer>(execute));
    ASSERT(passExecuter != nullptr);

    PassNode* passNode = AddPassNode(name, *passExecuter, passType);
    ASSERT(passNode != nullptr);

    FGBuilder builder(*this, *passNode);
    setup(builder, const_cast<PassData&>(passExecuter->GetData()));
    return *passExecuter;
}

template<typename Resource>
FGHandle<Resource> FrameGraph::Write(PassNode& passNode, const FGHandle<Resource>& h, ResourceUsage usage)
{
    ResourceNode* resourceNode = GetResourceNode(h.GetHandle());
    ASSERT(resourceNode != nullptr);

    ResourceEdge* resourceEdge = m_allocator.Allocate<ResourceEdge>(m_daGraph, passNode, *resourceNode, usage);
    ASSERT(resourceEdge != nullptr);

    resourceNode->SetWriteEdge(resourceEdge);
    passNode.AddWriteResource(h.GetHandle());

    return h;
}

template<typename Resource>
FGHandle<Resource> FrameGraph::Read(PassNode& passNode, const FGHandle<Resource>& h, ResourceUsage usage)
{
    ResourceNode* resourceNode = GetResourceNode(h);
    ASSERT(resourceNode != nullptr);

    ResourceEdge* resourceEdge = m_allocator.Allocate<ResourceEdge>(m_daGraph, passNode, *resourceNode, usage);
    ASSERT(resourceEdge != nullptr);

    resourceNode->AddReadEdge(resourceEdge);
    passNode.AddReadResource(h);

    return h;
}

template<typename ResourceType>
FGHandle<ResourceType> FrameGraph::FGBuilder::Create(const char* const name,
                                                     typename ResourceType::Descriptor const& desc)
{
    return m_fg.Create<ResourceType>(name, desc);
}

template<typename ResourceType>
FGHandle<ResourceType> FrameGraph::FGBuilder::Write(const FGHandle<ResourceType>& h, ResourceUsage usage)
{
    return m_fg.Write<ResourceType>(m_passNode, h, usage);
}

template<typename ResourceType>
FGHandle<ResourceType> FrameGraph::FGBuilder::Read(const FGHandle<ResourceType>& h, ResourceUsage usage)
{
    return m_fg.Read<ResourceType>(m_passNode, h, usage);
}

NS_CG_END

#endif
