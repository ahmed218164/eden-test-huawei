/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.
 * Description: Shader Stage Info
 */
#ifndef SHADER_STAGE_CREATE_INFO_H
#define SHADER_STAGE_CREATE_INFO_H

#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

struct ShaderStageCreateInfo {
    String name;
    String entryPoint = "main";
    ShaderStageType stageType = SHADER_STAGE_NONE;
    ShaderSourceType sourceType = SPIRV;
    u8* spvShader = nullptr;
    u32 sourceLength = 0;
};

NS_CG_END

#endif
