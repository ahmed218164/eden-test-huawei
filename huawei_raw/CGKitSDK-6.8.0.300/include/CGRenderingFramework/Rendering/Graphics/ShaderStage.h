/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2022. All rights reserved.
 * Description: Shader Stage Info
 */
#ifndef SHADER_STAGE_H
#define SHADER_STAGE_H

#include "Resource/IResource.h"
#include "Rendering/Graphics/ShaderStageCreateInfo.h"
#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

enum ShaderResourceType {
    SHADER_RESOURCE_TYPE_INPUT,
    SHADER_RESOURCE_TYPE_OUTPUT,

    // for descriptorsetlayout creating
    // VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC or VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER
    SHADER_RESOURCE_TYPE_BUFFER_UNIFORM,
    // VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC or VK_DESCRIPTOR_TYPE_STORAGE_BUFFER
    SHADER_RESOURCE_TYPE_BUFFER_STORAGE,
    SHADER_RESOURCE_TYPE_INPUT_ATTACHMENT, // VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT
    SHADER_RESOURCE_TYPE_IMAGE,           // VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE
    SHADER_RESOURCE_TYPE_IMAGE_SAMPLERR,  // VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
    SHADER_RESOURCE_TYPE_IMAGE_STORAGE,   // VK_DESCRIPTOR_TYPE_STORAGE_IMAGE
    SHADER_RESOURCE_TYPE_SAMPLER,         // VK_DESCRIPTOR_TYPE_SAMPLER

    SHADER_RESOURCE_TYPE_PUSH_CONSTANT,   // for pipeline layout creating
    SHADER_RESOURCE_TYPE_SPECIALIZATION,  // for shader stage creating
    SHADER_RESOURCE_TYPE_All
};

struct CGKIT_EXPORT ShaderResource {
    String name = "";
    u32 stage = 0;
    ShaderResourceType type;
    u32 set = 0;
    u32 binding = 0; // binding

    u32 arraySize = 0;

    u32 offset = 0; // for push constants
    u32 size = 0;   // for push constants

    u32 constantID = 0; // for specialization

    u32 location = 0;
    u32 inputAttachmentIndex = 0;
    u32 vecSize = 0;
    u32 columns = 0;
};

class CGKIT_EXPORT ShaderStage {
public:
    ShaderStage();
    virtual ~ShaderStage();
    const String& GetEntryPoint() const;
    const u8* GetSpv() const;
    ShaderStageType GetShaderStageType() const;
    void AddShaderResource(const ShaderResource& value);
    const std::vector<ShaderResource>& GetResources() const;
    u32 GetSpvShaderSize() const;
    const String& GetShaderName() const;
    void SetStageType(ShaderStageType stageType);
    void ClearResource();
    virtual bool Create(const ShaderStageCreateInfo& shaderStageInfo) = 0;

protected:
    virtual bool CreateImpl(const ShaderStageCreateInfo& shaderStageInfo) = 0;
    virtual void DestroyImpl() = 0;

private:
    void Destroy();

protected:
    std::vector<ShaderResource> m_resources;
    ShaderStageCreateInfo m_baseInfo;
};

NS_CG_END

#endif
