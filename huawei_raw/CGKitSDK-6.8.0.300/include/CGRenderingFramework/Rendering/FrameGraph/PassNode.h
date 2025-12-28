#ifndef PASS_NODE_H
#define PASS_NODE_H

#include "Core/Global.h"
#include "Rendering/FrameGraph/NodeFG.h"
#include "Rendering/FrameGraph/PassExecuter.h"
#include "Rendering/FrameGraph/FGCommon.h"
#include "Rendering/FrameGraph/FGRenderPass.h"
#include "Rendering/FrameGraph/FGHandle.h"

NS_CG_BEGIN

class FrameGraph;
class VirtualResourceBase;

class CGKIT_EXPORT PassNode : public NodeFG {
public:
    virtual ~PassNode();
    PassNode(FrameGraph& fg, const char* const name, IPassExecuter& executer, GraphicsRenderer* graphicsRenderer);

    /**
     * set RenderPass and FrameBuffer, begin new render pass.
     */
    virtual void Begin(CommandBuffer* commandBuffer) = 0;

    /*
     * execute callback of the pass, record command of commandBuffer.
     */
    virtual void Execute() = 0;

    /*
     * destroy RenderPass and FrameBuffer, end render pass.
     */
    virtual void End() = 0;

    /**
     * get passType, only support GRAPHICS_PASS.
     */
    virtual PassType GetPassType() const = 0;

    /*
     * get name of PassNade
     */
    const char* GetName();

    /**
     * update read resource and write resource life cycle
     */
    void Resolve();

    /*
     * add read resource
     */
    void AddReadResource(Handle h);

    /*
     * add write resource
     */
    void AddWriteResource(Handle h);

    /*
     * add realize resource
     */
    void AddRealizeResource(VirtualResourceBase* v);

    /**
     * add destroy resource
     */
    void AddDestroyResource(VirtualResourceBase* v);

    /*
     * realize resources
     */
    void RealizeResources();

    /*
     * destroy resources
     */
    void DestroyResources();

    /*
     * get command buffer
     */
    const CommandBuffer* GetCommandBuffer() const;
protected:

    /*
     *  update resource life cycle
     */
    void UpdateResourceLifeCycle(const std::vector<Handle>& resources, bool readFlag = false);

    FrameGraph& m_fg;
    std::vector<Handle> m_readResources;
    std::vector<Handle> m_writeResources;
    CommandBuffer* m_commandBuffer = nullptr;
    IPassExecuter& m_executer;
    FGRenderPass m_pass;

private:
    AccessFlagBits GetAccessFlags(ResourceUsage usage, bool readFlag);
    ImageLayout GetImageLayout(ResourceUsage usage, bool readFlag);

    const char* const m_name;
    std::vector <VirtualResourceBase*> m_realizeResources;
    std::vector <VirtualResourceBase*> m_destroyResources;
};

NS_CG_END

#endif