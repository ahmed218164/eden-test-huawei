/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2022. All rights reserved.
 * Description: sampler
 */
#ifndef SAMPLER_H
#define SAMPLER_H

#include "Rendering/SamplerCreateInfo.h"

NS_CG_BEGIN

class CGKIT_EXPORT Sampler {
public:
    Sampler() = default;
    virtual ~Sampler() = default;

    bool Create(const SamplerCreateInfo& info);

    inline const SamplerCreateInfo& GetSamplerCreateInfo() const { return m_baseInfo; }

protected:
    virtual bool CreateImpl(const SamplerCreateInfo& info) = 0;

    SamplerCreateInfo m_baseInfo;
};
NS_CG_END

#endif