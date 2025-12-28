/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2022. All rights reserved.
 * Description:
 */
#ifndef PIPELINE_LAYOUT_H
#define PIPELINE_LAYOUT_H

#include "Core/Types.h"
#include "Rendering/Graphics/ShaderStage.h"
NS_CG_BEGIN

class DescriptorSetLayout;

/**
 * Structure parameters for creating PipelineLayout
 */
struct PipelineLayoutCreateInfo {
    std::map<u32, DescriptorSetLayout*> layouts;
    std::vector<ShaderResource> pushConstants;
};

class CGKIT_EXPORT PipelineLayout {
public:
    /**
     * Default constructor.
     */
    PipelineLayout() = default;

    /**
     * Default destructor.
     */
    virtual ~PipelineLayout() = default;

    /**
     * Delete function is used to prevent the copy and assignment of the class.
     */
    CG_DELETE_COPY_CONSTRUCTOR(PipelineLayout);

    /**
     * Create a PipelineLayout object based on the creation information.
     */
    bool Create(const PipelineLayoutCreateInfo& pipelineLayoutCreateInfo);

    /**
     * Acquire the creation information of the PipelineLayout object.
     */
    const PipelineLayoutCreateInfo& GetPipelineLayoutCreateInfo() const { return m_baseInfo; }

protected:
    virtual bool CreateImpl(const PipelineLayoutCreateInfo& pipelineLayoutCreateInfo) = 0;

private:
    PipelineLayoutCreateInfo m_baseInfo;
};

NS_CG_END

#endif