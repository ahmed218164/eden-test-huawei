/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Scene manager for scene objects and components.
 */

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Rendering/RenderCommon.h"
#include "Rendering/SamplerCreateInfo.h"
#include "Scene/SceneObject.h"
#include "Scene/Component/Camera.h"
#include "Math/Matrix4.h"
#include "Utils/DynamicArray.h"
#include "Resource/ResourceManager.h"
#include "Rendering/Graphics/GraphicsRenderer.h"

NS_CG_BEGIN

class RenderingPath;
class Renderable;
class MaterialInstance;
class ResourceObjectManager;
class SceneCullingDataManager;

/*
 * A singleton scene manager class used to initialize the scene system, release resources, add and
 * delete scene objects, manage rendering queues, and obtain and set Camera objects.
 */
class CGKIT_EXPORT SceneManager {
    friend class SceneObject;
public:
    SceneManager(GraphicsRenderer *graphicsRenderer);
    virtual ~SceneManager();

public:
    /*
     * Initialize the rendering path, root node object, and light information.
     */
    virtual void Initialize();

    /*
     * initialize the scene.create the light,camera,skybox and somes things.
     */
    virtual void InitScene(const Vector3& sceneCenter, u32 sceneWidth, u32 sceneHeight,
        u32 sceneDepth);

    /*
     * Exit the scene manager system and releases all resources in the scene manager.
     */
    virtual void Uninitialize();

    /*
     * Rebuild the scene manager system when the app is switched from the background to the
     * foreground.
     */
    virtual bool Resume();

    /*
     * Destroy the scene manager system when the app is switched from the foreground to the
     * background.
     */
    virtual void Pause();

    /*
     * Update all scene objects, light, and camera. The argument is the time difference between the
     * previous frame and the current frame, in seconds.
     */
    virtual void Update(f32 deltaTime);

    /*
     * Crop a render object based on the frustum, recursively collects renderable scene objects,
     * add the objects to the render queue, and perform render operations to complete frame drawing.
     */
    virtual void Render();

    /*
     * Wait until the queue operation is complete and then changes the window size. If a camera
     * exists, the width and height, and aspect ratio of the camera viewport are changed.
     * The arguments are the updated width and height of the window.
     */
    virtual void Resize(u32 width, u32 height);

    /*
     * Create a scenario object. If the parent scene object is empty, the scene root node object is
     * used as the parent node.
     */
    virtual SceneObject* CreateSceneObject(SceneObject* parent = nullptr);

    /*
     * Create a scenario object using a model file. If the parent scene object is empty, the scene root node object is
     * used as the parent node.
     */
    SceneObject* CreateSceneObject(const String& modelFile, SceneObject* parent = nullptr);

    /*
     * Create a scenario object using a model file and a cgmat file. If the parent scene object is empty,
     * the scene root node object is used as the parent node.
     */
    SceneObject* CreateSceneObject(const String& modelFile, const String& cgmatName, SceneObject* parent = nullptr);

    /*
     * Create a scenario object using a model file and a list of cgmat files. If the parent scene object is empty,
     * the scene root node object is used as the parent node.
     */
    SceneObject* CreateSceneObject(const String& modelFile, const std::vector<String>& cgmatNameVec,
        SceneObject* parent = nullptr);

    /*
     * Delete a scene object from the scene object list. If a parent scene object exists, the scene
     * object is also deleted from the sub-scene objects of the parent scene object.
     */
    virtual void DeleteObject(SceneObject* object);

    /*
     * Add a scene object. The argument is a scene object pointer of the SceneObject type.
     */
    virtual void AddSceneObject(SceneObject* object);

    /*
     * Delete a scene object. The argument is a scene object pointer of the SceneObject type.
     */
    virtual void RemoveSceneObject(SceneObject* object);

    /*
     * Find a scene object. The argument is the parent pointer and the nodeIndex of a scene object.
     */
    const SceneObject* FindSceneObject(const SceneObject* parent, u32 nodeIndex) const;

    /*
     * Find a scene object. The argument is the parent pointer and the name of a scene object.
     */
    const SceneObject* FindSceneObject(const SceneObject* parent, const String& name) const;

    /*
     * Obtain scene object List.
     */
    const SceneObjectList& GetSceneObjectList() const;

    /*
     * Obtain the main camera component of a scene.
     */
    const Camera* GetMainCamera() const;

    /*
     * Set the main camera. The main camera is unique. The argument is the pointer to a camera
     * object.
     */
    void SetMainCamera(Camera* camera);

    /*
     * Add camera component of a scene.
     */
    void AddCamera(Camera* camera);

    /*
     * Remove camera component of a scene.
     */
    void RemoveCamera(Camera* camera);

    /*
     * Has camera component or not of a scene.
     */
    bool HasCamera(Camera* camera);

    /*
     * Get all camera component of a scene.
    */
    const std::vector<Camera*>& GetAllCamera() const;

    const SceneCullingDataManager* GetSceneCullingDataManager() const
    {
        return m_sceneCullingDataManager;
    }

    ResourceManager* GetResourceManager() const
    {
        return m_resourceManager;
    }

    const GraphicsRenderer* GetGraphicsRenderer() const
    {
        return m_graphicsRenderer;
    }

    /*
     * single sceneManager object.
     */
    static SceneManager& GetInstance();

protected:
    QuadTreeNode* GetBelongNode(const SceneObject& object) const;
    virtual void UpdateSceneObjectNode(SceneObject* object) const;

    GraphicsRenderer* m_graphicsRenderer = nullptr;
    ResourceManager* m_resourceManager = nullptr;
    ResourceObjectManager* m_resourceObjectManager = nullptr;
    SceneCullingDataManager* m_sceneCullingDataManager = nullptr;
    Camera* m_mainCamera = nullptr;
    std::vector<Camera*> m_cameras;
    SceneObjectList m_sceneObjects;
    SceneObjectList m_deleteSceneObjects;
    SceneObjectList m_lightsObjects;
    Vector3 m_sceneCenter;
    u32 m_sceneWidth = 0;
    u32 m_sceneHeight = 0;
    u32 m_sceneDepth = 0;
    static const u32 FRUSTUM_CULLING_JOB_COUNT = 4; // the job count should be decided after future perf test.

private:
    void AddObjectToRenderQueue(Camera* camera, SceneObject& object);
    void DeleteSceneObjects();
    void UpdateCamera(f32 deltaTime);
    void UpdateSceneObjectRecursive(SceneObject* object, f32 deltaTime);
    virtual void CullObjectByFrustum();
    void SortCamera();
    bool Resume(const SceneObject* object);
    void Pause(const SceneObject* object);
    virtual void SetSceneCenter(const Vector3& sceneCenter);
    virtual void SetSceneWidth(u32 sceneWidth);
    virtual void SetSceneHeight(u32 sceneHeight);
    virtual void SetSceneDepth(u32 sceneDepth);
    virtual void EnsureDefaultLightExists();

};

NS_CG_END

#endif