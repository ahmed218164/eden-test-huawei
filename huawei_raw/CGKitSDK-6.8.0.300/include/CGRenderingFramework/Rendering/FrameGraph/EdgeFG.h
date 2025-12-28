#ifndef EDGE_H
#define EDGE_H

#include "Core/Global.h"
#include "Core/Types.h"

NS_CG_BEGIN

class DirectedAcyclicGraph;
class NodeFG;

class CGKIT_EXPORT EdgeFG {
public:
    NodeFG& m_from;
    NodeFG& m_to;

    virtual ~EdgeFG();
    EdgeFG(DirectedAcyclicGraph& dag, NodeFG& from, NodeFG& to);
};

NS_CG_END

#endif