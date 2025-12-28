
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description:
 * Author: houyaolin
 * Create: 2020-12-20
 */
#pragma once

#include <vector>
#include "VolumeRenderParas.h"

#ifndef __ANDROID__
#define VolumeCloudEXPORT _declspec(dllexport)
#endif // __ANDROID__

typedef enum GraphicAPI {
    GraphicAPI_OpenGLES30 = 0, // Android平台使用OpenGLES 3.0
    GraphicAPI_OpenGL = 1,     // Windows平台使用OpenGL 4.0
} GraphicAPI;

#ifdef __ANDROID__
class  VolumeCloudRenderAPI
#else
class VolumeCloudEXPORT VolumeCloudRenderAPI
#endif // __ANDROID__
{
public:
    VolumeCloudRenderAPI() { }
    virtual ~VolumeCloudRenderAPI() { }
    virtual bool CreateResources() = 0;
    virtual void RenderCloudFrameTexture(void* textureHandle,
        void* depthTexHandle,
        int textureWidth,
        int textureHeight) = 0;
    virtual bool SetRenderCloudParas(VolumeRenderParas &paras) = 0;
    virtual void ReleaseData() = 0;

};

#ifdef __ANDROID__
#define EXPORT __attribute__((visibility("default")))
EXPORT VolumeCloudRenderAPI* CreateVolumeCloudRenderAPI(GraphicAPI apiType);
#else
typedef  VolumeCloudRenderAPI* rt;
rt VolumeCloudEXPORT CreateVolumeCloudRenderAPI(GraphicAPI apiType);
#endif // __ANDROID__