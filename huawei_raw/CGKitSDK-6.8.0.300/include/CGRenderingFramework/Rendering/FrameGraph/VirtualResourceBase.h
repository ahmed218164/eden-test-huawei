#ifndef VIRTUAL_RESOURCE_BASE_H
#define VIRTUAL_RESOURCE_BASE_H

#include "Core/Global.h"
#include "Rendering/FrameGraph/FGCommon.h"

NS_CG_BEGIN

class PassNode;

class CGKIT_EXPORT VirtualResourceBase {
    friend class ResourceNode;
    friend class PassNode;

public:
    VirtualResourceBase(const char* const name, bool isImported);
    virtual ~VirtualResourceBase();

protected:
    /**
     * realize resource
     */
    virtual void Realize() = 0;

    /*
     * destroy resource
     */
    virtual void Destroy() = 0;

    /*
     * get name of resource
     */
    const char* GetName();

    /**
     * is external resource or not
     */
    bool IsImported() const;

    /*
     * use pass of the resource
     */
    void UsedByPass(PassNode* passNode);

    /*
     * add usage mode of resource
     */
    void AddUsage(ResourceUsage usage);

    /*
     * set create point and release point of the resource
     */
    void SetLifeCycleEndPoint();

    /**
     * get usage
     */
    ResourceUsage GetUsage()
    {
        return m_usage;
    }

private:
    const char* const m_name;
    bool m_isImported;
    PassNode* m_firstPass{ nullptr };
    PassNode* m_lastPass{ nullptr };
    ResourceUsage m_usage{ ResourceUsage::NONE_USAGE };
};

NS_CG_END

#endif
