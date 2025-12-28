/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Material Instance.
 */
#ifndef MATERIAL_INSTANCE_H
#define MATERIAL_INSTANCE_H

#include "Rendering/Graphics/GraphicsRenderer.h"
#include "Resource/ResourceManager.h"
#include "Rendering/RenderCommon.h"
#include "Rendering/Graphics/Texture.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"
#include "Math/Color.h"

NS_CG_BEGIN

class CGKIT_EXPORT MaterialInstance {
public:
    /*
     * Request a Shareable MaterialInstance Object.
     */
    static MaterialInstance* Request(const String& materialFile, const ResourceManager* resourceManager);

    /*
     * New a MaterialInstance Obejct.
     */
    static MaterialInstance* New(const String& materialFile, const ResourceManager* resourceManager);

    /*
     * Release MaterialInstance
     */
    static void Release(const MaterialInstance* materialInstance);

    /*
     * A constructor.
     */
    MaterialInstance() = default;

    /*
     * A destructor.
     */
    virtual ~MaterialInstance() = default;

    /*
     * Get the name of the currently active technique
     */
    virtual String GetTechniqueName() const = 0;

    /*
     * Get the index of pass by name
     */
    virtual u32 GetPassIndex(const String& name) const = 0;

    /*
     * Set the current pass to be modified by index.
     * The first pass configured in the cgmat is used by default.
     */
    virtual bool SetPass(u32 index) = 0;

    /*
     * Get the index of the currently active pass
     */
    virtual u32 GetPass() const = 0;

    /*
     * Determine whether there is a texture with the specified name, and the parameter name is the
     * texture name.
     */
    virtual bool HasTexture(const String& name) const = 0;

    /*
     * Set the texture, the first parameter is the texture name in the shader, and the second
     * parameter is object.
     */
    virtual void SetTexture(const String& name, Texture* texture) = 0;

    /*
     * Get texture by name.
     */
    virtual const Texture* GetTexture(const String& name) const = 0;

    /*
     * Sets the culling mode in the rasterizer phase of the pipeline. The argument is an enum value
     * of CullMode.
     */
    virtual void SetCullMode(CullMode cullMode) = 0;

    /*
     * Obtains the culling mode in the rasterizer phase of the pipeline. An enum value of CullMode
     * is returned.
     */
    virtual CullMode GetCullMode() const = 0;

    /*
     * Sets the diagram element filling mode in the rasterizer phase of the pipeline. The argument
     * is an enum value of FillMode.
     */
    virtual void SetFillMode(FillMode fillMode) = 0;

    /*
     * Obtains the diagram element filling mode in the rasterizer phase of the pipeline.
     */
    virtual FillMode GetFillMode() const = 0;

    /*
     * Set the triangle winding order in the rasterizer phase of the pipeline. The argument is an
     * enum value of FrontFace.
     */
    virtual void SetFrontFace(FrontFace frontFace) = 0;

    /*
     * Obtains the triangle winding order in the rasterizer phase of the pipeline.
     */
    virtual FrontFace GetFrontFace() const = 0;

    /*
     * set line width.
     */
    virtual void SetLineWidth(f32 lineWidth) = 0;

    /*
     * get line width.
     */
    virtual f32 GetLineWidth() const = 0;

    /*
     * set an array of four values specifying the R, G, B, and A components of
     * the blend constant color used in blending
     */
    virtual void SetBlendConstants(const std::vector<f32>& blendConstants) = 0;

    /*
     * get an array of four values specifying the R, G, B, and A components of
     * the blend constant color used in blending
     */
    virtual const std::vector<f32>& GetBlendConstants() const = 0;

    /*
     * Sets the enable variable of the depth test. The argument is a bool.
     */
    virtual void SetDepthTestEnable(bool depthTestEnable) = 0;

    /*
     * Obtains the enable variable of the depth test. A bool is returned.
     */
    virtual bool GetDepthTestEnable() const = 0;

    /*
     * Sets the write enable variable of the depth test. The argument is a bool.
     */
    virtual void SetDepthWriteEnable(bool depthWriteEnable) = 0;

    /*
     * Obtains the write enable variable of the depth test.
     */
    virtual bool GetDepthWriteEnable() const = 0;

    /*
     * Sets the comparison mode of the depth test. The argument is an enum value of
     * CompareOperation.
     */
    virtual void SetDepthCompareOp(CompareOperation op) = 0;

    /*
     * Obtains the comparison mode of the depth test.
     */
    virtual CompareOperation GetDepthCompareOp() const = 0;

    /*
     * Set whether to open stencil test enable.
     */
    virtual void SetStencilTestEnable(bool bEnable) = 0;

    /*
     * get whether to open stencil test enable.
     */
    virtual bool GetStencilTestEnable() const = 0;

    /*
     * Set stencil test fail.
     */
    virtual void SetStencilFail(StencilFaceFlag stencilFaceFlag, StencilOperation op) = 0;

    /*
     * get stencil test fail.
     */
    virtual StencilOperation GetStencilFail(StencilFaceFlag stencilFaceFlag) const = 0;

    /*
     * set Stencil Depth Fail.
     */
    virtual void SetStencilDepthFail(StencilFaceFlag stencilFaceFlag, StencilOperation op) = 0;

    /*
     * get Stencil Depth Fail.
     */
    virtual StencilOperation GetStencilDepthFail(StencilFaceFlag stencilFaceFlag) const = 0;

    /*
     * set Stencil pass.
     */
    virtual void SetStencilPass(StencilFaceFlag stencilFaceFlag, StencilOperation op) = 0;

    /*
     * Get the Stencil template test.
     */
    virtual StencilOperation GetStencilPass(StencilFaceFlag stencilFaceFlag) const = 0;

    /*
     * Set the Stencil CompareOperation function
     */
    virtual void SetStencilCompareOp(StencilFaceFlag stencilFaceFlag, CompareOperation op) = 0;

    /*
     * Get the Stencil CompareOperation function.
     */
    virtual CompareOperation GetStencilCompareOp(StencilFaceFlag stencilFaceFlag) const = 0;

    /*
     * Set Stencil comparison mask
     */
    virtual void SetStencilCompareMask(StencilFaceFlag stencilFaceFlag, u32 mask) = 0;

    /*
     * Get Stencil Compare Mask.
     */
    virtual u32 GetStencilCompareMask(StencilFaceFlag stencilFaceFlag) const = 0;

    /*
     * Set Stencil reference.
     */
    virtual void SetStencilReference(StencilFaceFlag stencilFaceFlag, u32 ref) = 0;

    /*
     * Obtain the Stencil reference.
     */
    virtual u32 GetStencilReference(StencilFaceFlag stencilFaceFlag) const = 0;

    /*
     * Set the Stencil's Read Mask.
     */
    virtual void SetStencilReadMask(StencilFaceFlag stencilFaceFlag, u32 mask) = 0;

    /*
     * Get the Stencil's Read mask .
     */
    virtual u32 GetStencilReadMask(StencilFaceFlag stencilFaceFlag) const = 0;

    /*
     * Set the Stencil's write mask.
     */
    virtual void SetStencilWriteMask(StencilFaceFlag stencilFaceFlag, u32 mask) = 0;

    /*
     * Get the Stencil's write mask.
     */
    virtual u32 GetStencilWriteMask(StencilFaceFlag stencilFaceFlag) const = 0;

    /*
     * Sets the enable variable of color attachment blending. The argument is the index of a color
     * attachment, and the second argument is the blending enable variable.
     */
    virtual void SetBlendingEnable(u32 index, bool bEnable) = 0;

    /*
     * Obtains the enable variable of color attachment blending. The argument is the index of a
     * color attachment.
     */
    virtual bool GetBlendingEnable(u32 index) const = 0;

    /*
     * Sets the blend factor of the source color channels of a color attachment. The argument is the
     * index of a color attachment, and the second argument is an enum value of BlendFactor.
     */
    virtual void SetSrcColorBlend(u32 index, BlendFactor srcColorBlend) = 0;

    /*
     * Obtains the blend factor of the source color channels of a color attachment. The argument is
     * the index of a color attachment.
     */
    virtual BlendFactor GetSrcColorBlend(u32 index) const = 0;

    /*
     * Sets the blend factor of the destination color channels of a color attachment. The argument
     * is the index of a color attachment, and the second argument is an enum value of BlendFactor.
     */
    virtual void SetDstColorBlend(u32 index, BlendFactor dstColorBlend) = 0;

    /*
     * Obtains the blend factor of the destination color channels of a color attachment. The
     * argument is the index of a color attachment.
     */
    virtual BlendFactor GetDstColorBlend(u32 index) const = 0;

    /*
     * Sets the color blend operation of a color attachment. The argument is the index of a color
     * attachment, and the second argument is an enum value of BlendOperation.
     */
    virtual void SetColorBlendOperation(u32 index, BlendOperation colorBlendOp) = 0;

    /*
     * Obtains the color blend operation of a color attachment. The argument is the index of a color
     * attachment.
     */
    virtual BlendOperation GetColorBlendOperation(u32 index) const = 0;

    /*
     * Sets the alpha channel blend factor of the source color channels of a color attachment.
     * The argument is the index of a color attachment, and the second argument is an enum value of
     * BlendFactor.
     */
    virtual void SetSrcAlphaBlend(u32 index, BlendFactor srcAlphaBlend) = 0;

    /*
     * Obtains the alpha channel blend factor of the source color channels of a color attachment.
     * The argument is the index of a color attachment.
     */
    virtual BlendFactor GetSrcAlphaBlend(u32 index) const = 0;

    /*
     * Sets the alpha channel blend factor of the destination color channels of a color attachment.
     * The argument is the index of a color attachment, and the second argument is an enum value of
     * BlendFactor.
     */
    virtual void SetDstAlphaBlend(u32 index, BlendFactor dstAlphaBlend) = 0;

    /*
     * Obtains the alpha channel blend factor of the destination color channels of a color
     * attachment. The argument is the index of a color attachment.
     */
    virtual BlendFactor GetDstAlphaBlend(u32 index) const = 0;

    /*
     * Obtains the alpha channel blend operation of a color attachment. The argument is the index
     * of a color attachment.
     */
    virtual void SetAlphaBlendOperation(u32 index, BlendOperation alphaBlendOp) = 0;

    /*
     * Obtains the alpha channel blend operation of a color attachment. The argument is the index
     * of a color attachment.
     */
    virtual BlendOperation GetAlphaBlendOperation(u32 index) const = 0;

    /*
     * Whether the current technique is applied to transparent objects
     */
    virtual bool IsTransparent() const = 0;

    /*
     * Set PushConstant
     */
    virtual void SetPushConstant(const String& name, const void* data) = 0;

    /*
     * Get constant value index by uniformName and varName.
     * The index is related to the sequence configured in the cgmat file.
     * The first 16 bits of the returned value indicate the sequence number of Uniform,
     * and the last 16 bits indicate the sequence number of Value in Uniform.
     */
    virtual u32 GetConstantValueIndex(const String& uniformName, const String& varName) const = 0;

    /*
     * Set uniform value by index (Return by GetConstantValueIndex).
     */
    virtual bool SetConstantValue(u32 index, u32 data) = 0;

    virtual bool SetConstantValue(u32 index, f32 data) = 0;

    virtual bool SetConstantValue(u32 index, const Vector2& data) = 0;

    virtual bool SetConstantValue(u32 index, const Vector3& data) = 0;

    virtual bool SetConstantValue(u32 index, const Vector4& data) = 0;

    virtual bool SetConstantValue(u32 index, const Matrix4& data) = 0;

    virtual bool SetConstantValue(u32 index, const Color& data) = 0;

    /*
     * Get uniform value by index (Return by GetConstantValueIndex).
     */
    virtual u32 GetConstantValueU32(u32 index) const = 0;

    virtual f32 GetConstantValueF32(u32 index) const = 0;

    virtual Vector2 GetConstantValueVec2(u32 index) const = 0;

    virtual Vector3 GetConstantValueVec3(u32 index) const = 0;

    virtual Vector4 GetConstantValueVec4(u32 index) const = 0;

    virtual Matrix4 GetConstantValueMat4(u32 index) const = 0;

    virtual Color GetConstantValueColor(u32 index) const = 0;

    /*
     * Update operation.
     */
    virtual void Update() = 0;

    virtual void Pause() = 0;

    virtual bool Resume() = 0;

    void SetResourceManager(ResourceManager* resourceManager)
    {
        m_resourceManager = resourceManager;
    }

private:
    ResourceManager* m_resourceManager = nullptr;

};
NS_CG_END
#endif
