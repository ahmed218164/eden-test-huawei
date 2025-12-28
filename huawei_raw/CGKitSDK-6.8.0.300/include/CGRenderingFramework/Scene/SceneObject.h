/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Scene object utils.
 */

#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "Math/Vector3.h"
#include "Scene/IComponent.h"
#include "Rendering/RenderCommon.h"
#include "Log/Log.h"

NS_CG_BEGIN

class Transform;
class QuadTreeNode;
class MeshRenderer;

using SceneObjectList = std::list<SceneObject*>;
using SceneObjectListIt = std::list<SceneObject*>::iterator;
using SceneObjectListCIt = std::list<SceneObject*>::const_iterator;

/*
 * A scene object class that enables component management, model rotation, model scaling,
 * scene visibility configuration, parent scene configuration, and child scene configuration.
 */
class CGKIT_EXPORT SceneObject {
    friend class SceneManager;
    friend class QuadTreeNode;
    friend class Transform;

public:
    /*
     * A constructor. If the parent scene is empty, the AddSceneObject function is called to add
     * itself as the scene object and as the parent scene. Otherwise, SetParent is called to set the
     * parent scene. The argument is the pointer to the parent scene object.
     */
    SceneObject(const SceneManager* sceneManager, SceneObject* parent);

    /*
     * A destructor.
     */
    virtual ~SceneObject();

    /*
     * Obtains the name of a scene object.
     */
    void SetName(const String& name);

    /*
     * Obtains the name of a scene object.
     */
    const String& GetName() const;

    /*
     * Sets SceneObject sort id.
     */
    void SetSortId(u32 id);

    /*
     * Gets SceneObject sort id.
     */
    u32 GetSortId() const;

    /*
     * Sets the pre-update logic every frame, used in scenes with available physical update logic.
     * The argument is the time difference between the previous frame and the current frame, in seconds.
     */
    virtual void PreUpdate(f32 deltaTime);

    /*
     * Sets the update logic every frame, used to update the world matrix. The argument is the time
     * difference between the previous frame and the current frame, in seconds.
     */
    virtual void Update(f32 deltaTime);

    /*
     * Sets the post-update logic every frame, used in scenes with available follow-up update logic.
     * For example, the camera follows an object and updates with a delay. The argument is the time
     * difference between the previous frame and the current frame, in seconds.
     */
    virtual void PostUpdate(f32 deltaTime);

    /*
     * Deletes a component. The argument is a pointer of the IComponent type that points to a
     * component.
     */
    bool RemoveComponent(IComponent* component);

    /*
     * A template used to add components of the T type to the component list and start the
     * components
     */
    template <typename T> T* AddComponent()
    {
        T* component = CG_NEW(T, this);
        if (component == nullptr){
            LOG_ALLOC_NULL("New typename T failed.");
            return nullptr;
        }
        component->Start();
        m_components.push_back(component);
        return component;
    }

    /*
     * A template used to obtain the first component of the T type
     */
    template <typename T> T* GetComponent() const
    {
        for (IComponent* component : m_components) {
            if (component->RTTIIsTypeOf(T::RTTITypeId())) {
                return static_cast<T*>(component);
            }
        }
        return nullptr;
    }

    /*
     * A template used to obtain all components of the T type
     */
    template <typename T> std::vector<T*> GetComponents()
    {
        std::vector<T*> ret;
        for (IComponent* component : m_components) {
            T* t = dynamic_cast<T*>(component);
            if (t != nullptr) {
                ret.push_back(t);
            }
        }
        return ret;
    }

    /*
     * A template used to obtain all components of the T type, including children
     */
    template <typename T> std::vector<T*> GetComponentsInChildren()
    {
        std::vector<T*> ret;
        GetComponentsInChildrenRecursive(ret, this);
        return ret;
    }

    /*
     * Obtains the constant pointer to the parent scene object of a scene.
     */
    const SceneObject* GetParent() const;

    /*
     * Replaces the original parent scene object with a new one. The argument is a parent scene
     * pointer of the SceneObject type.
     */
    void SetParent(SceneObject* newParent);

    /*
     * Checks whether a parent scene exists. Returns true if it exists; false otherwise.
     */
    bool HasParent() const;

    /*
     * Returns true if the current scene is the parent scene of a specified scene. The argument is
     * a scene object pointer of the SceneObject type.
     */
    bool IsParentOf(const SceneObject* object) const;

    /*
     * Obtains the child scene objects. A list of child scene objects of the SceneObject type is
     * returned.
     */
    const std::list<SceneObject*>& GetChildren() const;

    /*
     * Obtains the number of child scene objects.
     */
    u32 GetChildrenCount() const;

    /*
     * Adds a child scene object. The argument is a child scene object pointer of the SceneObject
     * type.
     */
    void AddChild(SceneObject* child);

    /*
     * Deletes a child scene object. The argument is a pointer of the SceneObject type that points
     * to a child scene object.
     */
    bool RemoveChild(SceneObject* child);

    /*
     * Checks whether the current scene object is a child scene of a specified scene object.
     */
    bool IsChildOf(const SceneObject* object) const;

    /*
     * Obtains the ID of a scene object.
     */
    u32 GetID() const {
        return m_id;
    }

    /*
     * Set the node index of a scene object.
     */
    void SetNodeIndex(u32 nodeIndex) {
        m_nodeIndex = nodeIndex;
    }

    /*
     * Obtains the node index of a scene object.
     */
    u32 GetNodeIndex() const {
        return m_nodeIndex;
    }

    /*
     * Sets the visibility of a scene object. The argument is a bool.
     */
    void SetVisible(bool visible);

    /*
     * Obtains the visibility of a scene object.
     */
    bool IsVisible() const {
        return m_visible;
    }

    /*
     * Sets the position of a scene object in the Local coordinate system. The argument is a
     * position reference of the Vector3 type.
     */
    void SetLocalPosition(const Vector3& position);

    /*
     * Sets the position of a scene object in the world coordinate system. The argument is a
     * position reference of the Vector3 type.
     */
    void SetPosition(const Vector3& position);

    /*
     * Obtains the position of a scene object in the world coordinate system.
     */
    const Vector3& GetPosition() const;

    /*
     * Sets the scaling vector (relative to the parent scene object) of a scene object in the local
     * coordinate system. The argument is a scaling vector of the Vector3 type.
     */
    void SetScale(const Vector3& scale);

    /*
     * Obtains the scaling vector of a scene object in the local coordinate system (relative to the
     * parent scene object).
     */
    const Vector3& GetScale() const;

    /*
     * Sets the rotation vector (relative to the parent scene object) of a scene object in the local
     * coordinate system. The argument is a rotation vector of the Vector3 type, whose components
     * are in radians.
     */
    void SetRotation(const Vector3& rotation);

    /*
     * Obtains the rotation vector of a scene object in the local coordinate system (relative to the
     * parent scene object). Components of the returns are in radians.
     */
    const Vector3& GetRotation() const;

    /*
     * Obtains the coordinate transformation interface bound to a scene object.
     */
    const Transform* GetTransform() const;

    /*
     * Obtains the coordinate transformation interface bound to a parent scene object. If a parent
     * scene object exists, the pointer to the coordinate transformation interface bound to the
     * parent scene object is returned. Otherwise, a null pointer is returned.
     */
    const Transform* GetParentTransform() const;

    /*
     * Obtains the mesh render components of a scene object.
     */
    const MeshRenderer* GetMeshRenderer();

    /*
     * Obtains the layer type of a scene object.
     */
    u32 GetLayerType() const {
        return m_layerType;
    }

    /*
     * Set the layer type of a scene object.
     */
    void SetLayerType(LayerType layerType);

    const SceneManager* GetSceneManager() const
    {
        return m_sceneManager;
    }

private:
    void UpdateChild(SceneObject* child);
    void SetBelongNode(QuadTreeNode* belongNode);
    QuadTreeNode* GetBelongNode() const;
    void UpdateSceneObjectNode();
    template <typename T> void GetComponentsInChildrenRecursive(std::vector<T*>& ret, SceneObject* object)
    {
        for (IComponent* component : object->m_components) {
            T* t = dynamic_cast<T*>(component);
            if (t != nullptr) {
                ret.push_back(t);
            }
        }
        auto& children = object->GetChildren();
        for (auto& child : children) {
            GetComponentsInChildrenRecursive(ret, child);
        }
    }

    static u32 GenerateId()
    {
        static u32 g_id = 0;
        return ++g_id;
    }

private:
    MeshRenderer* m_meshRenderer;
    Transform* m_transform;
    SceneObject* m_parent;
    u32 m_id;
    u32 m_nodeIndex;
    u32 m_sortId;
    SceneObjectList m_children;
    ComponentList m_components;
    bool m_visible;
    QuadTreeNode* m_belongNode;
    u32 m_layerType;
    String m_name;
    const SceneManager* m_sceneManager = nullptr;
};

NS_CG_END

#endif
