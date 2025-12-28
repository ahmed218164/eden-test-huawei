#ifndef RESOURCE_EDGE_H
#define RESOURCE_EDGE_H

#include "Rendering/FrameGraph/EdgeFG.h"
#include "Rendering/FrameGraph/NodeFG.h"
#include "Rendering/FrameGraph/FGCommon.h"

NS_CG_BEGIN

class EdgeFG;
class NodeFG;

class CGKIT_EXPORT ResourceEdge : EdgeFG {
    friend class ResourceNode;

public:
    ResourceUsage m_usage;

    virtual ~ResourceEdge();
    ResourceEdge(DirectedAcyclicGraph& daGraph, NodeFG& from, NodeFG& to, ResourceUsage usage);

private:
    /**
     * is culled or not
     */
    bool IsValid() const
    {
        return (!m_from.IsCulled()) && (!m_to.IsCulled());
    }
};

NS_CG_END

#endif