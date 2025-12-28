/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description:
 * Author: wujun
 * Create: 2021-4-20
 */
#pragma once

#include <vector>
#include "VolumeFogParas.h"

#ifndef __ANDROID__
#define VolumeFogEXPORT _declspec(dllexport)
#endif // __ANDROID__

typedef enum GraphicAPI {
    GraphicAPI_OpenGLES31 = 0, // Android平台使用OpenGLES 3.1
    GraphicAPI_OpenGL = 1,     // Windows平台使用OpenGL 4.0
} GraphicAPI;

#ifdef __ANDROID__
class  VolumeFogRenderAPI
#else
class VolumeFogEXPORT VolumeFogRenderAPI
#endif // __ANDROID__
{
public:
    VolumeFogRenderAPI() { }
    virtual ~VolumeFogRenderAPI() { }
    virtual bool CreateResources() = 0;
    virtual void RenderFogFrameTexture(void* FogTexHandle,
        int textureWidth,
        int textureHeight,
        int textureDepth) = 0;
    virtual bool SetRenderFogParas(BaseParas &baseParas,
        DirLightParas &dirLight,
        PointLightParas pointLights[],
        SpotLightParas spotLights[]) = 0;
    virtual void ReleaseData() = 0;

};

#ifdef __ANDROID__
#define EXPORT __attribute__((visibility("default")))
EXPORT VolumeFogRenderAPI*   CreateVolumeFogRenderAPI(GraphicAPI apiType);
#else
typedef  VolumeFogRenderAPI* rt;
rt VolumeFogEXPORT CreateVolumeFogRenderAPI(GraphicAPI apiType);
#endif // __ANDROID__