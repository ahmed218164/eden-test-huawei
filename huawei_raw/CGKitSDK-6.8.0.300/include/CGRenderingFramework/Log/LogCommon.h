/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Common types for log.
 */

#ifndef LOG_COMMON_H
#define LOG_COMMON_H

#include "Core/Types.h"

NS_CG_BEGIN

/*
 * Defines the log output path types.
 */
enum LogPathType {
    LOG_PATH_CONSOLE = 0x01,
};

/*
 * Defines the log levels, that is, the log output types.
 */
enum LogType {
    LOG_VERBOSE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
};

NS_CG_END

#endif