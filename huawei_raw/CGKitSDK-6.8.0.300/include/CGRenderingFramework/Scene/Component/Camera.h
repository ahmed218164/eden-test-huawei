/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: A camera class used to set and obtain the camera position, projection type, field of view (FOV),
 * and near and far clipping planes.
 */

#ifndef CG_CAMERA_H
#define CG_CAMERA_H

#include "Rendering/RenderingPath.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Matrix4.h"
#include "Rendering/RenderCommon.h"
#include "Rendering/Viewport.h"
#include "Scene/IComponent.h"

NS_CG_BEGIN

class CommandBuffer;
class Frustum;
class RenderContext;
class RenderingPath;
class RenderContext;
class RenderQueue;
class SceneCullingData;
class PostProcessStage;
class PostProcessStageManager;

class CGKIT_EXPORT Camera : public IComponent {
    friend class SceneObject;
    friend class SceneManager;
    friend class MeshRenderer;
    friend class ScreenShot;
    friend class PostProcessFinalStage;
    RTTI_DEFINE(CGKit::Camera);

public:
    /*
     * A constructor used to initialize the camera.
     */
    Camera(SceneObject* sceneObject = nullptr);

    /*
     * A destructor used to free memory.
     */
    virtual ~Camera();

    /*
     * Initializes the camera's frustum.
     */
    virtual void Start() override;

    /*
     * Updates the camera viewport, projection matrix, view matrix, and frustum.
     */
    virtual void Update(f32 deltaTime) override;

    /*
     * Culling light info and update the renderingPath of camera.
     */
    virtual void PostUpdate(f32 deltaTime) override;

    /*
     * Resize camera.
     */
    void Resize(u32 width, u32 height);

    /*
     * Camera rendering.
     */
    virtual void Render();

    /*
     * Camera resume.
     */
    void Resume();

    /*
     * Camera pause.
     */
    void Pause();
    /*
     * Sets the projection type (either perspective or orthographic projection) of the camera. The argument is an
     * enum value of ProjectionType.
     */
    void SetProjectionType(ProjectionType projectionType);

    /*
     * Sets the FOV, aspect ratio, distance to the near clipping plane, and distance to the far clipping plane.
     */
    void SetPerspective(f32 fov, f32 aspectRatio, f32 zNear, f32 zFar);

    /*
     * Sets the camera orthogonal projection parameters.
     */
    void SetOrthogonal(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar);

    /*
     * Sets the distance from the camera to the near clipping plane.
     */
    void SetZNear(f32 zNear);

    /*
     * Sets the distance from the camera to the far clipping plane.
     */
    void SetZFar(f32 zFar);

    /*
     * Sets the FOV. The argument is the new FOV (not in radians). Set fov to the vertical FOV.
     */
    void SetFOV(f32 fov);

    /*
     * Sets a viewport. The arguments are the coordinates of the upper left corner of the viewport, and width, height,
     * and depth of the viewport.
     */
    void SetViewport(u32 x, u32 y, u32 width, u32 height, f32 minDepth = 0.0f, f32 maxDepth = 1.0f);

    /*
     * Sets the camera position. The argument is of the Vector3 type.
     */
    void SetEyePos(const Vector3& eyePos);

    /*
     * Sets the target position of the camera. The argument is of the Vector3 type.
     */
    void SetTarget(const Vector3& targetPos);

    /*
     * Sets the rotation angle of the camera. The argument is of the Matrix4 type.
     */
    void SetPreRotation(const Matrix4& preRotation);

    /*
     * Sets the ratio of the screen, the ratio decide the screen size of the final presented image.
     * The argument is of the Matrix4 type.
     */
    void SetScreenRatio(const Vector4& ratio);

    /*
     * Set camera as main camera.
     */
    void SetMainCamera(bool bMain);

    /*
     * Check camera is main camera or not.
     */
    bool IsMainCamera() const;

    /*
     * Get the scene object types that the camera can render.
     */
    u32 GetLayerMask() const;

    /*
     * Set the scene object types that the camera can render.
     */
    void SetLayerMask(u32 layerMask);

    /*
     * Obtains the frustum of the camera.
     */
    const Frustum* GetFrustum() const;

    /*
     * Obtains the projection matrix of the camera.
     */
    const Matrix4& GetProjectionMatrix() const;

    /*
     * Obtains the view matrix of the camera.
     */
    const Matrix4& GetViewMatrix() const;

    /*
     * Obtains the projection type (either perspective or orthographic projection) of the camera.
     */
    ProjectionType GetProjectionType() const
    {
        return m_projectionType;
    }

    /*
     * Obtains the aspect ratio.
     */
    f32 GetAspectRatio() const;

    /*
     * Obtains the FOV (not in radians). Set fov to the vertical FOV.
     */
    f32 GetFOV() const
    {
        return m_fov;
    }

    /*
     * Obtains the distance from the camera to the near clipping plane.
     */
    f32 GetZNear() const
    {
        return m_zNear;
    }

    /*
     * Obtains the distance from the camera to the far clipping plane.
     */
    f32 GetZFar() const
    {
        return m_zFar;
    }

    /*
     * Obtains the camera frustum left plane.
     */
    f32 GetLeft() const
    {
        return m_left;
    }

    /*
     * Obtains the camera frustum right plane.
     */
    f32 GetRight() const
    {
        return m_right;
    }

    /*
     * Obtains the camera frustum bottom plane.
     */
    f32 GetBottom() const
    {
        return m_bottom;
    }

    /*
     * Obtains the camera frustum top plane.
     */
    f32 GetTop() const
    {
        return m_top;
    }

    /*
     * Obtains the camera view port.
     */
    const Viewport& GetViewPort() const
    {
        return m_viewPort;
    }

    /*
     * Obtains the camera position.
     */
    const Vector3& GetEyePos() const;

    /*
     * Obtains the target position of the camera.
     */
    const Vector3& GetTarget() const;

    /*
     * Obtains the forward vector of the camera.
     */
    const Vector3& GetLookDir() const;

    /*
     * Obtains the up vector of the camera.
     */
    const Vector3& GetUpDir() const;

    /*
     * Obtains the right vector of the camera.
     */
    const Vector3& GetRightDir() const;

    /*
     * Set the rendering path of camera.
     */
    void SetRenderingPath(RenderingPathType type, RenderTargetType targetType = RenderTargetType::FROM_SWAPCHAIN);

    /*
     * Obtains the render target type of camera.
     */
    RenderTargetType GetRenderTargetType() const;

    /*
     * Set multisample info.
     */
    virtual void SetMultiSampleInfo(const MultiSampleInfo& sampleInfo);

    /*
     * Obtains multisample info.
     */
    const MultiSampleInfo& GetMultiSampleInfo() const;

    /*
     * Set clear color for camera.
     */
    void SetClearColor(const Color& color);

    /*
     * Add post process.
     */
    template <typename T> T* AddPostProcess()
    {
        T* postProcessStage = dynamic_cast<T*>(GetPostProcessStage(T::RTTITypeId()));
        if (postProcessStage != nullptr) {
            return postProcessStage;
        }
        postProcessStage = CG_NEW(T, dynamic_cast<RenderingPath*>(m_renderingPath));
        if (postProcessStage != nullptr) {
            AddPostProcessStage(postProcessStage);
            return postProcessStage;
        }
        return nullptr;
    }

    /*
     * Remove post process.
     */
    template <typename T> void RemovePostProcess()
    {
        T* postProcessStage = dynamic_cast<T*>(GetPostProcessStage(T::RTTITypeId()));
        if (postProcessStage == nullptr) {
            return;
        }
        RemovePostProcessStage(postProcessStage);
    }

    /*
     * Obtains the rendering path of camera.
     */
    const RenderingPath* GetRenderingPath() const;
protected:
    Camera(const Camera& camera) = delete;
    Camera& operator = (const Camera& camera) = delete;

    RenderingPath* m_renderingPath;
    RenderContext* m_renderContext;
private:
    void Destroy();
    void EnsureFrustumUpdate() const;
    void EnsureProjectionMatrixUpdate() const;
    void EnsureViewMatrixUpdate() const;
    void EnsureViewportUpdate() const;

    void InvalidateFrustum() const;
    void InvalidateProjectionMatrix() const;
    void InvalidateViewMatrix() const;
    void InvalidateViewport() const;

    void UpdateFrustum() const;
    void UpdateProjectionMatrix() const;
    void UpdateViewMatrix() const;
    void UpdateViewport() const;
    void UpdataCameraObject() const;
    void UpdateGlobalUniform();

    u32 GetCullObjectCount() const;
    void AddLightObject(SceneObject* object);
    const CommandBuffer* GetPrimaryCommandBuffer() const;

    void CreateRenderingPath(RenderingPathType type);
    void InitRenderContext(RenderingPathType type, RenderTargetType targetType);
    const RenderQueue* GetRenderQueue() const;

    void AddPostProcessStage(PostProcessStage* stage);
    void RemovePostProcessStage(PostProcessStage* stage);
    PostProcessStage* GetPostProcessStage(const RTTIType& typeId) const;

private:
    ProjectionType m_projectionType;

    /*
     * for perspective projection.
     */
    f32 m_fov;
    mutable f32 m_aspectRatio;

    /*
     * for orthogonal projection.
     */
    f32 m_left;
    f32 m_right;
    f32 m_bottom;
    f32 m_top;

    f32 m_zNear;
    f32 m_zFar;
    Frustum* m_frustum;
    Viewport m_originViewPort;
    mutable Viewport m_viewPort;

    mutable Matrix4 m_projectionMatrix;
    mutable Matrix4 m_viewMatrix;
    mutable Matrix4 m_preRotation;

    mutable Vector3 m_eyePos;
    mutable Vector3 m_target;
    mutable Vector3 m_lookDir;
    mutable Vector3 m_upDir;
    mutable Vector3 m_rightDir;
    mutable Vector3 m_rotation;
    mutable f32 m_curZoom;

    mutable bool m_frustumUpdated;
    mutable bool m_projectionMatrixUpdated;
    mutable bool m_viewMatrixUpdated;
    mutable bool m_viewportUpdated;

    SceneCullingData* m_cullData;
    PostProcessStageManager* m_postProcessStageManager;

    Vector4 m_ratio;
    bool m_bMainCamera;
    u32 m_layerMask;

    bool m_pathInitialized = false;
};

struct CameraSortFunc {
    bool operator() (const Camera* first, const Camera* second)
    {
        if ((first == nullptr) || (second == nullptr)) {
            return true;
        }
        if (first->GetRenderTargetType() < second->GetRenderTargetType()) {
            return false;
        } else if (first->GetRenderTargetType() > second->GetRenderTargetType()) {
            return true;
        }
        if (first->IsMainCamera() < second->IsMainCamera()) {
            return false;
        } else if (first->IsMainCamera() > second->IsMainCamera()) {
            return true;
        }
        return false;
    }
};

NS_CG_END

#endif
