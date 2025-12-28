/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.
 * Description: Descriptor set include request and clear operations, etc.
 * Author:
 * Create: 2022-05-14
 */

#ifndef DESCRIPTOR_SET_H
#define DESCRIPTOR_SET_H

#include "Rendering/Graphics/Texture.h"
#include "Rendering/Graphics/DescriptorSetLayout.h"
#include "Rendering/Graphics/Buffer/Buffer.h"
#include "Rendering/RenderCommon.h"
#include "Utils/DynamicArray.h"

NS_CG_BEGIN

struct BindingResourceInfo;

/*
 * Structure used to create a DescriptorSet.
 */
struct DescriptorSetCreateInfo {
    DescriptorSetLayout *layout = nullptr;
};

class CGKIT_EXPORT DescriptorSet {
public:
    /*
     * A default constructor is used.
     */
    explicit DescriptorSet() = default;

    /*
     * A delete function is used to prevent the copy of the class.
     */
    DescriptorSet(const DescriptorSet& descriptorSet) = delete;

    /*
     * A delete function is used to prevent the assignment  of the class.
     */
    DescriptorSet& operator = (const DescriptorSet& descriptorSet) = delete;

    /*
     * A destructor used to free memory of m_bindings.
     */
    virtual ~DescriptorSet();

    /*
     * Bind the buffers whose array size is count to the descriptor whose binding number is binding.
     */
    void BindBuffers(u32 binding, const Buffer* const* buffers, u32 count = 1);

    /*
     * Bind the textures whose array size is count to the descriptor whose binding number is binding.
     */
    void BindTextures(u32 binding, const Texture* const* textures, u32 count = 1);

    /*
     * A DescriptorSet object is created based on the creation information.
     */
    bool Create(const DescriptorSetCreateInfo& info);

    /*
     * The creation information of the DescriptorSet object is acquired.
     */
    const DescriptorSetCreateInfo& GetDescriptorSetCreateInfo() const;

    /*
     * Updates the dynamic offsets of all bound buffers.
     */
    void SetActiveDynamicOffsets();

    /*
     * Get the dynamic offsets of all bound buffers.
     */
    const DynamicArray<u32>& GetActiveDynamicOffsets();

protected:
    DescriptorSetCreateInfo m_baseInfo;
    bool m_isDirty = false;
    virtual bool CreateImpl(const DescriptorSetCreateInfo& info) = 0;
    std::map<u32, BindingResourceInfo*> m_bindings;

private:
    DynamicArray<u32> m_activeDynamicOffsets;

private:
    BindingResourceInfo* GetDescriptorSetBinding(u32 binding);
};

NS_CG_END

#endif