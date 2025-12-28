#ifndef RESOURCE_ALLOCATOR_H
#define RESOURCE_ALLOCATOR_H

#include "Core/Global.h"
#include "Core/Types.h"
#include "Rendering/Graphics/GraphicsRenderer.h"

NS_CG_BEGIN

template<typename ResourceType, typename ResourceInfo,
    typename ResourceFactory, typename ResourceHasher>
class CGKIT_EXPORT ResourceAllocator {
public:
    using HashType = size_t;
    static constexpr HashType INVALID_HASH_VALUE = std::numeric_limits<HashType>::max();

    struct ResourceHandle {
        ResourceType* resource = nullptr;
        HashType hashValue = INVALID_HASH_VALUE;
    };

    ~ResourceAllocator()
    {}

    /**
     * allocate resources
     */
    ResourceHandle Allocate(const ResourceInfo& info, GraphicsRenderer* graphicsRenderer)
    {
        HashType hashValue = m_hasher.Compute(info);
        auto it = m_freePool.find(hashValue);
        if (it != m_freePool.end()) {
            ResourceQueue& resQueue = it->second;
            if (!resQueue.empty()) {
                ResourceType* res = resQueue.back().m_resource;
                ASSERT(res);
                resQueue.pop_back();

                m_inUsePool[hashValue].emplace_back(ResourceElement{res, 0});
                return {res, hashValue};
            }
        }

        ResourceType* newRes = m_factory.Create(info, graphicsRenderer);
        ASSERT(newRes);

        m_inUsePool[hashValue].emplace_back(ResourceElement{newRes, 0});
        return {newRes, hashValue};
    }

    /*
     * free resources
     */
    void Free(ResourceHandle& resHandle)
    {
        ASSERT(resHandle.hashValue != INVALID_HASH_VALUE);

        auto it = m_inUsePool.find(resHandle.hashValue);
        ASSERT(it != m_inUsePool.end());

        ResourceQueue& useQueue = it->second;
        auto itRes = std::find_if(useQueue.begin(), useQueue.end(), [&resHandle](const ResourceElement& p) {
            return resHandle.resource == p.m_resource;
        });
        ASSERT(itRes != useQueue.end());
        useQueue.erase(itRes);

        m_freePool[resHandle.hashValue].emplace_back(ResourceElement{resHandle.resource, m_currentFrameCount});
    }

    /*
     * update resources
     */
    void Update()
    {
        m_currentFrameCount++;
        ReleaseUnusedResources();
    }

private:
    struct ResourceElement {
        ResourceType* m_resource{nullptr};
        size_t m_frameCount{0};
    };
    using ResourceQueue = std::list<ResourceElement>;

    using ResourcePool = std::unordered_map<HashType, ResourceQueue>;

    static constexpr size_t UNUSED_FRAME_COUNT = 10u;

    void ReleaseUnusedResources()
    {
        for (auto& x : m_freePool) {
            ResourceQueue& queue = x.second;
            for (auto it = queue.begin(); it != queue.end();) {
                m_factory.Destroy(it->m_resource);
                it = queue.erase(it);
            }
        }
    }

    ResourceFactory m_factory;
    ResourceHasher m_hasher;
    size_t m_currentFrameCount{0};

    ResourcePool m_freePool;
    ResourcePool m_inUsePool;
};

NS_CG_END

#endif