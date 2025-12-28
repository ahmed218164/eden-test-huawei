/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: ResourceLoadInfo.
 */

#ifndef RESOURCE_LOAD_INFO_H
#define RESOURCE_LOAD_INFO_H

#include "Resource/IResource.h"

NS_CG_BEGIN
/*
 * Description of Resource to Load.
*/
struct ResourceLoadInfo {
    /*
     * The filepath of the resource to load.
     */
    String filePath;
    /*
     * The callback function user defined when resource was loaded succed.
     */
    std::function<void(IResource*)> OnSuccess = [](IResource*){};
    /*
     * The callback function user defined when resource was loaded failed.
     */
    std::function<void(const String&)> OnFailed = [](const String&){};
};

NS_CG_END

#endif
