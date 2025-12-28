/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2022. All rights reserved.
 * Description: Shader Info
 */
#ifndef SHADER_H
#define SHADER_H

#include "Rendering/RenderCommon.h"
#include "Rendering/Graphics/ShaderStage.h"
#include "Rendering/Graphics/DescriptorSetLayout.h"

NS_CG_BEGIN

struct ShaderCreateInfo {
    String name;
    std::map<ShaderStageType, ShaderStage*> m_shaderStages;
};

class GraphicsRenderer;
class PipelineLayout;

class CGKIT_EXPORT Shader : public RefCount {
public:
    Shader(const GraphicsRenderer* graphicsRenderer);
    ~Shader();

    u32 GetShaderStageCount();
    const std::map<ShaderStageType, ShaderStage*>& GetShaderStages() const;
    const String& GetEntryPoint(ShaderStageType stage) const;
    void Create(const ShaderCreateInfo& shaderCreateInfo);
    std::size_t GetHash() const;
    const std::vector<ShaderResource>& GetUniformBuffer() const;
    const std::vector<ShaderResource>& GetTextures() const;
    const std::vector<ShaderResource>& GetPushConstants() const;
    const std::vector<ShaderResource>& GetInputAttachments() const;
    const std::vector<ShaderResource>& GetInputAndOutputAttribute() const;
    const std::map<u32, std::vector<ShaderResource>>& GetShaderSets() const;
    const std::map<u32, DescriptorSetLayout*>& GetSetLayoutMap() const;
    const PipelineLayout* GetPipelineLayout() const { return m_pipelineLayout; }

private:
    void Destroy();
    void GenHash();
    void ParseShaderResource(const ShaderResource& shaderResource);
    void GenerateShaderResource(const ShaderResource& shaderResource,
        std::vector<ShaderResource>& vecShaderResource);
    void UpdateSets(const ShaderResource& shaderResource);
    void CombineShaderResource();
    void GenDescriptorSetLayout();
    void GenPipelineLayout();
    bool MergeShaderResourceStage(const ShaderResource& shaderResource,
        std::vector<ShaderResource>& vecShaderResource);

private:
    std::size_t m_hash = 0;
    std::map<ShaderStageType, ShaderStage*> m_attachedShaders;
    std::vector<ShaderResource> m_uniformBuffers;
    std::vector<ShaderResource> m_textures;
    std::vector<ShaderResource> m_pushConstants;
    std::vector<ShaderResource> m_inputAttachments;
    std::vector<ShaderResource> m_inputAndOutputAttribute;
    std::map<u32, std::vector<ShaderResource>> m_sets;
    std::map<u32, DescriptorSetLayout*> m_setLayoutMap;
    PipelineLayout* m_pipelineLayout = nullptr;
    const GraphicsRenderer* m_graphicsRenderer = nullptr;
};
NS_CG_END

#endif
