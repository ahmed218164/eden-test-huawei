/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: A light class used to set and obtain the light color, type, intensity, and position.
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "Math/Vector4.h"
#include "Math/Vector3.h"
#include "Math/Vector2.h"
#include "Rendering/RenderCommon.h"
#include "Scene/IComponent.h"

NS_CG_BEGIN

struct LightInfo;
struct ShadowInfo;
struct CascadeViewProjMatrixUniform;
class Texture;
class UniformBuffer;

class CGKIT_EXPORT Light : public IComponent {
    friend class RenderStage;
    friend class RenderContext;
    friend class RenderContextFrameGraph;
    friend class RenderForward;
RTTI_DEFINE(CGKit::Light);

protected:
    Light& operator=(const Light& light) = delete;
    Light(const Light& light) = delete;

public:
    /*
     * A constructor used to initialize the light.
     */
    Light(SceneObject* sceneObject = nullptr);

    /*
     * A destructor used to free memory.
     */
    virtual ~Light();

    /*
     * Creates light information and initializes the color, position, direction, and type of the light.
     */
    virtual void Start() override;

    /*
     * Updates the light position (for a point light source) or light direction (for a directional light source).
     * The argument is the number of seconds between the previous frame and the current frame.
     */
    virtual void Update(f32 deltaTime) override;

    /*
     * Sets the light type (directional light or point light). The argument is an enum value of LightType.
     */
    void SetLightType(LightType type);

    /*
     * Sets the light color. The argument is of the Vector3 type. Value range: (0.0, 1.0).
     */
    void SetColor(const Vector3& color);

    /*
     * Sets the light intensity. The argument is a floating-point number, which can be any number greater than 0 and
     * defaults to 1.0.
     */
    void SetIntensity(f32 intensity);

    /*
     * Sets the position of the light source. The argument is of the Vector3 type.
     */
    void SetPosition(const Vector3& position);

    /*
     * Sets the light direction. The argument is of the Vector3 type.
     */
    void SetDirection(const Vector3& direction);

    /*
     * Sets the light attenuation. The argument is of the Vector3 type.
     */
    void SetAttenuation(const Vector3& attenuation);

    /*
     * Sets the light cutoff. The argument is of the Vector2 type.
     */
    void SetCutoff(const Vector2& cutoff);

    /*
     * Sets the light ambient. The argument is of the Vector3 type.
     */
    void SetAmbient(const Vector3& ambient);

    /*
     * Sets the light diffuse. The argument is of the Vector3 type.
     */
    void SetDiffuse(const Vector3& diffuse);

    /*
     * Sets the light specular. The argument is of the Vector3 type.
     */
    void SetSpecular(const Vector3& specular);

    /*
     * Sets the light range. The argument is of the float type.
     */
    void SetRange(f32 range);

    /*
     * Obtains the light type (directional light or point light).
     */
    LightType GetLightType() const;

    /*
     * Obtains the light color.
     */
    Vector3 GetColor() const;

    /*
     * Obtains the light intensity.
     */
    f32 GetIntensity() const;

    /*
     * Obtains the position of the light source.
     */
    Vector3 GetPosition() const;

    /*
     * Obtains the light direction.
     */
    Vector3 GetDirection() const;

    /*
     * Obtains the light attenuation.
     */
    Vector3 GetAttenuation() const;

    /*
     * Obtains the light cutoff.
     */
    Vector2 GetCutoff() const;

    /*
     * Obtains the light ambient.
     */
    Vector3 GetAmbient() const;

    /*
     *  Obtains the light diffuse.
     */
    Vector3 GetDiffuse() const;

    /*
     * Obtains the light specular.
     */
    Vector3 GetSpecular() const;

    /*
     * Obtains the light range.
     */
    f32 GetRange() const;

    /*
     * Obtains the shadow enable or not.
     */
    bool IsShadowEnable() const;

    /*
     * Sets the CascadeCount. The argument is of the u32 type.
     */
    bool SetShadowParam(bool shadowEnable, u32 cascadeCount = 2);

    /*
     * Obtains the shadow texture.
     */
    const Texture* GetShadowTexture() const;

    /*
     * Sets the shadow visable or not.
     */
    void SetShadowVisable(bool isShadowVisable);

    /*
     * Obtains the shadow visable or not.
     */
    bool IsShadowVisable() const;

    /*
     * Obtains the shadow CascadeCount.
     */
    u32 GetShadowCascadeCount() const;

    /*
     * Update the cascade uniform buffer.
     */
    void SetShadowInfoCascadeViewProjMatrixUniformBuffer(UniformBuffer& uniformBuffer);

private:
    void Destroy();
    bool CreateShadowMap(u32 shadowMapWidth, u32 shadowMapHeight);
    const UniformBuffer* GetCascadeViewProjMatrixUniformBuffer() const;
    const LightInfo* GetLightInfo() const;

private:
    LightInfo* m_lightInfo = nullptr;
    ShadowInfo* m_shadowInfo = nullptr;
    bool m_shadowVisable = false;
};

NS_CG_END

#endif
