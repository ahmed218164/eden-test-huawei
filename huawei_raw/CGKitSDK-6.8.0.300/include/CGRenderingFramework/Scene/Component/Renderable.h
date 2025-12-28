/*
* Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
* Description: A renderable class used to define renderable parameters.
*/
#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Scene/IComponent.h"
#include "Math/AABB.h"
#include "Math/Matrix4.h"

NS_CG_BEGIN

class Camera;
class SceneObject;
class Mesh;
class MaterialInstance;

class CGKIT_EXPORT Renderable : public IComponent {
    friend class SceneObject;
RTTI_DEFINE(CGKit::Renderable);

protected:
    Renderable(SceneObject* pSceneObject = nullptr);
    virtual ~Renderable();

public:
    /*
     * Renders a mesh. Sets the model matrix and material parameters of all submeshes of the current mesh,
     * and adds them to the rendering queue. The argument is a transformation matrix of the Matrix4 type.
     */
    virtual void Render(Camera* camera, const Matrix4& transMat);

    /*
     * Set the mesh.
     */
    void SetMesh(const Mesh* pMesh);

    /*
     * Obtains the mesh.
     */
    const Mesh* GetMesh() const;

    /*
     * Set the material instance.
     */
    void SetMaterialInstance(u32 index, const MaterialInstance* MaterialInstance);

    /*
     * Update the aabb, the argument is a transformation matrix of the Matrix4 type.
     */
    void UpdateAABB(const Matrix4& transMat);

    /*
     * Obtains the aabb.
     */
    const AABB& GetAABB() const {
        return m_aabb;
    }

    /*
     * Obtains the vector of materialInstance.
     */
    const std::vector<MaterialInstance*>& GetMaterialInstances() const {
        return m_materialInstances;
    }

private:
    void Destroy();

protected:
    Mesh* m_mesh = nullptr;
    std::vector<MaterialInstance*> m_materialInstances;
    AABB m_aabb;
};

NS_CG_END

#endif