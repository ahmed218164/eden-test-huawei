/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Resource manager utils.
 */

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Core/Singleton.h"
#include "Resource/IResource.h"
#include "Resource/ResourceLoadInfo.h"

NS_CG_BEGIN

class ShaderLibrary;
class SceneManager;
class ResourceLoadExecutor;
class LoadManager;
class GraphicsRenderer;
/*
 * Class ResourceManager : public Singleton<ResourceManager>
 * A singleton resource manager class used to load and delete resources in known formats
 * including textures, models, and materials.
 */
class CGKIT_EXPORT ResourceManager {
    friend class ResourceLoadTask;

public:
    ResourceManager(GraphicsRenderer* graphicsRenderer);
    virtual ~ResourceManager();

    /*
     * Initialize.
     */
    void Initialize();

    /*
     * Uninitialize.
     */
    void Uninitialize();

    /*
     * Obtains resources in a path. The argument is a resource file path.
     * The parsing mode of loaded resources is determined by the file name extension.
     * The following file name extensions are supported: .obj (model), .png (texture), and .cube (texture).
     */
    IResource* Get(const String& filePath);

    /*
     * Obtains a resource from a resource loadinfo in Async mode.
     */
    void Load(std::shared_ptr<ResourceLoadInfo> loadInfo);

    /*
     * Deletes resources in a path. The argument is a path string.
     */
    void Delete(const String& filePath);

    /*
     * Deletes a specified resource. The argument is a resource pointer of the IResource type.
     */
    void Delete(IResource* resource);

    /*
     * Deletes all resources.
     */
    void DeleteAll();

    /*
     * Rebuilds the resource manager system when the app is switched from the background to the foreground.
     */
    bool Resume();

    /*
     * Destroys the resource manager system when the app is switched from the foreground to the background.
     */
    void Pause();

    /*
     * Clears resources no longer needed when the time difference is greater than or equal to 5s.
     */
    void Update(f32 deltaTime);

    /*
     * * Add resources pointer to the resource map.
     */
    void Add(IResource* resource);

    const LoadManager* GetLoadManager()
    {
        return m_loadManager;
    }

    const GraphicsRenderer* GetGraphicsRenderer();

    const ShaderLibrary* GetShaderLibrary()
    {
        return m_shaderLibrary;
    }

private:
    IResource* Add(const String& filePath);
    IResource* FindByName(const String& resourceName, ResourceType type);
    void Add(const String& filePath, IResource* resource);

    void DeleteAll(ResourceType type);
    void Destroy();
    void Destroy(ResourceType type);
    void AsyncResourceCheck();
    bool IsAsyncLoading(const String& filePath) const;

    ResourceType GetResourceType(const String& resourceName) const;
    IResource* LoadResource(const String& filePath);

private:
    LoadManager* m_loadManager = nullptr;
    ShaderLibrary* m_shaderLibrary = nullptr;
    GraphicsRenderer* m_graphicsRenderer = nullptr;
    std::recursive_mutex m_resourceMapLock;
    std::array<std::unordered_map<size_t, IResource*>, ResourceType::RESOURCE_TYPE_MAX> m_resourceMap {};
    f32 m_time = 0.0f;
    ResourceLoadExecutor* m_resourceLoadExecutor = nullptr;
};

NS_CG_END

#endif
