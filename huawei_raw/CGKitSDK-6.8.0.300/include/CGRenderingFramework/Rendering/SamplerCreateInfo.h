/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2022. All rights reserved.
 * Description: SamplerCreateInfo struct
 */
#ifndef SAMPLER_CREATE_INFO_H
#define SAMPLER_CREATE_INFO_H

#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

/*
 * Sampler's Create Info.
 */
struct SamplerCreateInfo {
    /*
     * min filte.
     */
    SamplerFilter filterMin = SAMPLER_FILTER_BILINEAR;

    /*
     * mag filte.
     */
    SamplerFilter filterMag = SAMPLER_FILTER_BILINEAR;

    /*
     * mipmap filte.
     */
    SamplerMipmapMode filterMipmap = SAMPLER_MIPMAP_BILINEAR;

    /*
     * texture wrapping.
     */
    SamplerAddress addressMode = SAMPLER_ADDRESS_WRAP;

    /*
     * comparison condition.
     */
    CompareOperation comparisonFunc = COMPARISON_OPERATION_NEVER;

    /*
     * anisotropy.
     */
    bool anisotropyEnabled = false;

    /*
     * comparison
     */
    bool comparisonEnabled = false;
};

NS_CG_END

#endif