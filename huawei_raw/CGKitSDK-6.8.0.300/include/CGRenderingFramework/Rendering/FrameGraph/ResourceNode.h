#ifndef RESOURCE_NODE_H
#define RESOURCE_NODE_H

#include "Core/Global.h"
#include "Rendering/FrameGraph/NodeFG.h"

NS_CG_BEGIN

class PassNode;
class ResourceEdge;
class VirtualResourceBase;

class CGKIT_EXPORT ResourceNode : public NodeFG {
    friend class FrameGraph;
    friend class PassNode;
    friend class FGRenderPass;

public:
    ResourceNode(DirectedAcyclicGraph& daGraph, VirtualResourceBase* v);

private:
    void Resolve();

    void SetWriteEdge(ResourceEdge* edge)
    {
        ASSERT(edge);
        m_writeEdge = edge;
    }

    void AddReadEdge(ResourceEdge* edge)
    {
        m_readEdges.push_back(edge);
    }

    const VirtualResourceBase* GetVirtualResource() const
    {
        return m_virtualResource;
    }

    bool HasReaders() const
    {
        return !m_readEdges.empty();
    }

    const std::vector< ResourceEdge* >& GetReaderEdges() const
    {
        return m_readEdges;
    }

    const ResourceEdge* GetWriteEdge() const
    {
        return m_writeEdge;
    }

    void UsedByPass(PassNode* passNode);

    VirtualResourceBase* m_virtualResource = nullptr;
    ResourceEdge* m_writeEdge = nullptr;
    std::vector<ResourceEdge*> m_readEdges;
};

NS_CG_END

#endif