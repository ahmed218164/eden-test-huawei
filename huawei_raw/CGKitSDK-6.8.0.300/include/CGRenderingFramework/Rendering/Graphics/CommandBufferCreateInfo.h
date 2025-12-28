/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.
 * Description: CommandBuffer Create Info
 */
#ifndef COMMAND_BUFFER_CREATE_INFO_H
#define COMMAND_BUFFER_CREATE_INFO_H

#include "Rendering/RenderCommon.h"
#include "Rendering/Graphics/Queue.h"

NS_CG_BEGIN

struct CommandBufferCreateInfo {
    const Queue* queue { nullptr };
    CommandBufferLevelType type = CommandBufferLevelType::COMMAND_BUFFER_LEVEL_PRIMARY;
};

NS_CG_END

#endif