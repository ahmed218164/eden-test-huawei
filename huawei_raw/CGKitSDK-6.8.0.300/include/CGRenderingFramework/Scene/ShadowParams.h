
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.
 * Description: Shadow Params.
 */

#ifndef SHADOW_PARAMS_H
#define SHADOW_PARAMS_H

#include "Core/Types.h"
#include "Math/Matrix4.h"

NS_CG_BEGIN

namespace ShadowParams {
/*
 * Shadow's cascade's max count, default is 4.
 */
const u32 MAX_SHADOW_CASCADE_COUNT = 4;

/*
 * Shadow texture's width, default is 1024.
 */
const u32 SHADOW_MAP_WIDTH = 1024;

/*
 * shadow texture's height, default is 1024.
 */
const u32 SHADOW_MAP_HEIGHT = 1024;

struct CascadeViewProjMatrixUniform {
    alignas(16) Matrix4 viewProjMatrix[MAX_SHADOW_CASCADE_COUNT] = { Matrix4::IDENTITY };
    alignas(4) Vector4 splitDepth[MAX_SHADOW_CASCADE_COUNT] = { Vector4::ZERO };
    alignas(4) f32 cascadeCount = 1;
};

}

NS_CG_END

#endif