//
// Created by sWX700802 on 2021/4/15.
//

#ifndef FLUIDSHAKE_FLUIDSHAKE_H
#define FLUIDSHAKE_FLUIDSHAKE_H

#include <android/log.h>
#include <cmath>
#include <jni.h>
#include <string>

#define JNAAPI extern "C" __declspec(dllexport)

#if DYNAMIC_ES3
#include "gl3stub.h"
#else
// Include the latest possible header file( GL version header )
#if __ANDROID_API__ >= 24
#include <GLES3/gl32.h>
#elif __ANDROID_API__ >= 21
#include <GLES3/gl31.h>
#else
#include <GLES3/gl3.h>
#endif

#endif

#define DEBUG 1

#define LOG_TAG "GLES3JNI"
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define ALOGV(...)
#endif

// ----------------------------------------------------------------------------
// Types, functions, and data used by both ES2 and ES3 renderers.
// Defined in gles3jni.cpp.

#define MAX_INSTANCES_PER_SIDE 16
#define MAX_INSTANCES   (MAX_INSTANCES_PER_SIDE * MAX_INSTANCES_PER_SIDE)
#define TWO_PI          (2.0 * M_PI)
#define MAX_ROT_SPEED   (0.3 * TWO_PI)

struct Box {
    int boxType;
    float boxSize[3];
    std::string filename;
};

struct Float3 {
    float x;
    float y;
    float z;
};

struct Float4 {
    float x;
    float y;
    float z;
    float w;
};

struct FluidShakeContext;

struct Result {
    unsigned int size;
    GLuint posGPU;
    GLfloat *posArrayCPU;
};

struct ResultType {
    bool resultType;
    bool surfaceFlag;
};

extern "C" {
__attribute__ ((visibility ("default"))) FluidShakeContext *FluidShakeInit(Result *outRes, ResultType flag,
               Float3 startCoordinate, int particleNum, Box boxType);

__attribute__ ((visibility ("default"))) int FluidShakeContainerMove(Result *outRes, Float3 delta,
                                                                     FluidShakeContext *context);

__attribute__ ((visibility ("default"))) int FluidShakeContainerScale(Result *outRes, float ratio,
                                                                      FluidShakeContext *context);

__attribute__ ((visibility ("default"))) void FluidShakeDestroy(FluidShakeContext *context);
}
#endif //FLUIDSHAKE_FLUIDSHAKE_H
