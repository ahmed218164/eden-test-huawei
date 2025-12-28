/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.
 * Description: Descriptor set layout include request and clear operations, etc.
 * Author:
 * Create: 2022-03-11
 */

#ifndef DESCRIPTOR_SET_LAYOUT_H
#define DESCRIPTOR_SET_LAYOUT_H

#include "Rendering/Graphics/ShaderStage.h"
#include "Rendering/Graphics/Sampler.h"
#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

/*
 * Structure of binding information of each group of descriptors in DescriptorSetLayout.
 */
struct DescriptorSetLayoutBinding {
    String name = "";
    u32 binding = 0;
    u32 count = 0;
    ShaderResourceType type = SHADER_RESOURCE_TYPE_INPUT;
    u32 stage = 0;
    Sampler* samplerList = nullptr;

    ~DescriptorSetLayoutBinding()
    {
        CG_SAFE_DELETE(samplerList);
    }
};

/*
 * Structure used to create a DescriptorSetLayout.
 */
struct DescriptorSetLayoutCreateInfo {
    std::vector<DescriptorSetLayoutBinding> layoutBindings;
};

class CGKIT_EXPORT DescriptorSetLayout {
public:
    /*
     * A default constructor is used.
     */
    explicit DescriptorSetLayout() = default;

    /*
     * A delete function is used to prevent the copy of the class.
     */
    DescriptorSetLayout(const DescriptorSetLayout& descriptorSetLayout) = delete;

    /*
     * A delete function is used to prevent the assignment  of the class.
     */
    DescriptorSetLayout& operator = (const DescriptorSetLayout& descriptorSetLayout) = delete;

    /*
     * A default destructor is used.
     */
    virtual ~DescriptorSetLayout() = default;

    /*
     * A DescriptorSetLayout object is created based on the creation information.
     */
    bool Create(const DescriptorSetLayoutCreateInfo& info);

protected:
    virtual bool CreateImpl(const DescriptorSetLayoutCreateInfo& info) = 0;

private:
    DescriptorSetLayoutCreateInfo m_baseInfo;
};

NS_CG_END

#endif