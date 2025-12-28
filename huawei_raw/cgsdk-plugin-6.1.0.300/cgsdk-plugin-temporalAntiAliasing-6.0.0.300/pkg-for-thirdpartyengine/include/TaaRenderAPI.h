/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description:
 * Author: chuhailong
 * Create: 2021-03-15
 */
#pragma once

#include <vector>
#include <cstddef>

#ifndef __ANDROID__
#define TAAPluginAPI _declspec(dllexport)
#endif

typedef enum GraphicAPI {
    GraphicAPI_OpenGLES30 = 0,
    GraphicAPI_OpenGL = 1,
} GraphicAPI;

#ifdef __ANDROID__
class TaaRenderAPI
#else
class TAAPluginAPI TaaRenderAPI
#endif
{
public:
    TaaRenderAPI() { }
    virtual ~TaaRenderAPI() { }
    virtual bool InitTaaProcess(unsigned int width, unsigned int height) = 0;
    virtual bool UpdateTaaParam(float blendParam[], unsigned int paramLength, unsigned int renderWidth,
        unsigned int renderHeight) = 0;
    virtual bool RunTaaProcess(void* taaRenderRes, void* motionVector, void* source) = 0;
    virtual bool GetTaaProcessError() = 0;
    virtual void FreeTaaResources() = 0;
    virtual bool GetJitterMatrix(float(&mat)[16], float cameraParam[], unsigned int cameraParamLength,
        bool cameraMode) = 0;
};

#ifdef __ANDROID__
#define EXPORT __attribute__((visibility("default")))
EXPORT TaaRenderAPI* CreateTaaRenderAPI(GraphicAPI apiType);
#else
typedef  TaaRenderAPI* rt;
rt TAAPluginAPI CreateTaaRenderAPI(GraphicAPI apiType);
#endif // __ANDROID__