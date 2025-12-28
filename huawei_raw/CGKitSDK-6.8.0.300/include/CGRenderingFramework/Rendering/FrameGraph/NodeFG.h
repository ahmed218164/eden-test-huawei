#ifndef NODE_H
#define NODE_H

#include "Core/Global.h"
#include "Core/Types.h"
#include "Rendering/Graphics/GraphicsRenderer.h"

NS_CG_BEGIN

class DirectedAcyclicGraph;

class CGKIT_EXPORT NodeFG {
public:
    explicit NodeFG(DirectedAcyclicGraph& daGraph);
    virtual ~NodeFG();

    /*
     * get ref count
     */
    u32 GetRefCount()
    {
        return m_refCount;
    }

    /*
     * is needed to be culled
     */
    bool IsCulled()
    {
        return false;
    }

protected:
    GraphicsRenderer* m_graphicsRenderer = nullptr;

private:
    u32 m_refCount{0};
};

NS_CG_END

#endif