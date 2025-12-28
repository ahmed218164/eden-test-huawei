#ifndef VIRTUAL_RESOURCE_H
#define VIRTUAL_RESOURCE_H

#include "Core/Global.h"
#include "Rendering/FrameGraph/VirtualResourceBase.h"
#include "Rendering/FrameGraph/FGTexture.h"

NS_CG_BEGIN

template<typename ResourceType>
class CGKIT_EXPORT VirtualResource : public VirtualResourceBase {
    friend class FGRenderPass;
    friend class FrameGraph;

public:
    using DescriptorType = typename ResourceType::Descriptor;

    VirtualResource(const char* const name, const ResourceType& resource, DescriptorType const& desc, bool isImported)
        : VirtualResourceBase(name, isImported), m_resource(resource), m_descriptor(desc)
    {}

    VirtualResource(const char* const name, DescriptorType const& desc, bool isImported)
        : VirtualResourceBase(name, isImported), m_resource(), m_descriptor(desc)
    {}

    ~VirtualResource() {}

private:
    void AddGraphicsRenderer(GraphicsRenderer* graphicsRenderer)
    {
        FGTexture* ptr = &m_resource;
        ptr->SetGraphicsRenderer(graphicsRenderer);
    }

    virtual void Realize() override
    {
        if (IsImported()) {
            return;
        }
        m_resource.Create(m_descriptor, GetUsage());
    }

    virtual void Destroy() override
    {
        if (IsImported()) {
            return;
        }

        m_resource.Destroy();
    }

    const DescriptorType& GetDescriptor() const
    {
        return m_descriptor;
    }

    const ResourceType& GetResource() const
    {
        return m_resource;
    }

    DescriptorType m_descriptor;
    ResourceType m_resource;
};

NS_CG_END

#endif
