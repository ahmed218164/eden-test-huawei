#ifndef DIRECTED_ACYCLIC_GRAPH_H
#define DIRECTED_ACYCLIC_GRAPH_H

#include "Core/Global.h"
#include "Core/Types.h"

NS_CG_BEGIN

class FrameGraph;
class NodeFG;
class EdgeFG;

class CGKIT_EXPORT DirectedAcyclicGraph {
    friend class FrameGraph;
    friend class NodeFG;
    friend class EdgeFG;

public:
    virtual ~DirectedAcyclicGraph();

protected:
    void Cull();

    u32 AddNode(NodeFG* node)
    {
        u32 nodeId = static_cast<u32>(m_nodes.size());
        m_nodes.push_back(node);
        return nodeId;
    }

    void AddEdge(EdgeFG* edge)
    {
        m_edges.push_back(edge);
    }

private:
    std::vector<NodeFG*> m_nodes;
    std::vector<EdgeFG*> m_edges;
};

NS_CG_END

#endif