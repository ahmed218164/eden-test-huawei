/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.
 * Description: Queue Create Info
 */

#ifndef QUEUE_CREATE_INFO_H
#define QUEUE_CREATE_INFO_H

#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

struct QueueCreateInfo {
    QueueType type{QueueType::GRAPHICS};
};

NS_CG_END

#endif