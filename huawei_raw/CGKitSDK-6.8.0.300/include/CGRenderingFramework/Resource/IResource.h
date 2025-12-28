/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: IResource utils.
 */

#ifndef RESOURCE_H
#define RESOURCE_H

#include "Core/Types.h"
#include "RefCount.h"

NS_CG_BEGIN

/*
 * Defines the resource types based on the resource content.
 */
enum ResourceType {
    RESOURCE_TYPE_MODEL,          // Model resource
    RESOURCE_TYPE_TEXTURE,        // Texture resource
    RESOURCE_TYPE_MATERIAL_BASE,  // Base Material resource
    RESOURCE_TYPE_MATERIAL,       // Material resource
    RESOURCE_TYPE_GLTF,           // GLTF resource
    RESOURCE_TYPE_GLB,            // GLB resource
    RESOURCE_TYPE_SHADER,         // Shader resource
    RESOURCE_TYPE_MAX             // Maximum enum value. A valid enum value is less than this value
};

/*
 * Defines the resource loading states.
 */
enum LoadState {
    LOAD_STATE_IDLE,        // Idle
    LOAD_STATE_STARTED,     // Loading started
    LOAD_STATE_COMPLETED,   // Loading completed
    LOAD_STATE_FAILED,      // Loading failed

    /*
     * Maximum enum value. A valid enum value is equal to or less than this value.
     */
    LOAD_STATE_MAX = LOAD_STATE_FAILED
};

/*
 * Class IResource : public RefCount
 * A common resource class that inherits from RefCount, used to store binary data such as textures,
 * models, and materials and contain information such as the resource paths, resource sizes,
 * resource types, IDs, and read states.
 */
class CGKIT_EXPORT IResource : public RefCount {
public:
    IResource(const String& filePath, ResourceType resourceType);

    virtual ~IResource();

    /*
     * Obtains the resource path.
     */
    const String& GetFilePath() const;

    /*
     * Sets the resource path. The argument is a resource path string.
     */
    void SetFilePath(const String& filePath);

    /*
     * Obtains the resource ID.
     */
    u32 GetId() const;

    /*
     * Sets the resource ID. The argument is a 32-bit unsigned integer specifying the resource ID.
     */
    void SetId(u32 id);

    /*
     * Obtains the resource loading state. An enum value of LoadState is returned.
     */
    LoadState GetLoadState() const;

    /*
     * Sets the resource loading state. The argument is an enum value of LoadState.
     */
    void SetLoadState(LoadState loadState);

    /*
     * Obtains the resource type. The argument is an enum value of the ResourceType type.
     */
    ResourceType GetResourceType() const;

    /*
     * Rebuilds resources when the app is switched from the background to the foreground.
     */
    virtual bool Resume() { return true; }

    /*
     * Destroys resources when the app is switched from the foreground to the background.
     */
    virtual void Pause() {}

private:
    /*
     * Destroy gpu resource when the app goes to background
     */
    void Destroy() {}

    /*
     * Generate resource ID
     */
    static u32 GenerateId();

private:
    static u32 m_gId;
    String m_filePath;
    ResourceType m_resourceType;
    LoadState m_loadState = LOAD_STATE_IDLE;
    u32 m_id;
};

NS_CG_END

#endif