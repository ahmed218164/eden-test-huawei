/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: A mesh rendering class used to render meshes and set the model matrix and material parameters of
 * all submeshes of the current mesh.
 */

#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "Scene/Component/Renderable.h"

NS_CG_BEGIN

class RenderData;
class UniformBuffer;
struct ModelTransformMatrix;

class CGKIT_EXPORT MeshRenderer : public Renderable {
    friend class SceneObject;
    friend class SceneCullingData;
    CG_DELETE_COPY_CONSTRUCTOR(MeshRenderer)

    RTTI_DEFINE(CGKit::MeshRenderer);
public:
    /*
     * A constructor used to initialize the mesh render.
     */
    MeshRenderer(SceneObject* pSceneObject = nullptr);

    /*
     * A destructor used to free memory.
     */
    virtual ~MeshRenderer();

    /*
     * Render objects of camera.
     */
    virtual void Render(Camera* camera, const Matrix4& transMat) override;

    /*
     * Update the materialinstance.
     */
    virtual void Update(f32 deltaTime) override;

    /*
     * Destroys mesh rendering resources when the app is switched from the foreground to the background.
     */
    void Pause();

    /*
     * Rebuilds mesh rendering resources when the app is switched from the background to the foreground.
     */
    bool Resume();

protected:
    /*
     * Set uniform buffer to Renderdata or MaterialInstance.
     */
    virtual void SetUniformBuffer(RenderData* renderdata, MaterialInstance* materialInstance);

    using RenderDataVector = std::vector<RenderData*>;
    std::map<Camera*, RenderDataVector> m_renderdata;

private:
    RenderDataVector& GetRenderData(Camera* camera);
    void UpdateRenderData(Camera* camera, RenderDataVector& renderdata);
    void UpdateModelTransformBuffer(const Matrix4& matrix);
    void AddLightIndices(Camera* camera, const std::vector<u32>& lightIndices);
    void InitModelTransformMatrix();

    void Destroy();
    f32 CalcDistanceFromCamera(Camera* camera);

    ModelTransformMatrix* m_modelTransformMatrix = nullptr;
};

NS_CG_END

#endif
