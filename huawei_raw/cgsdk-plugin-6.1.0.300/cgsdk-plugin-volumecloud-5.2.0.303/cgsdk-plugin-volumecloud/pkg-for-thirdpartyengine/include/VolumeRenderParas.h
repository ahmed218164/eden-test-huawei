/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description:
 * Author: houyaolin
 * Create: 2020-12-20
 */
#ifndef VOLUME_RENDER_PARAS_H
#define VOLUME_RENDER_PARAS_H

#define THREE_DIMS 3
#define TWO_DIMS 2
#define MATRIX_DIMS 16
#define PATH_DIMS 128

#pragma pack(1)
struct VolumeRenderParas {
    // render
    int rayMarchSteps[TWO_DIMS] = { 0 };
    int downSample = 0;
    
    // shape
    float cloudBoxMinCoordinate[THREE_DIMS] = { 0 };
    float cloudSize[THREE_DIMS] = { 0 };
    float shapeTiling[THREE_DIMS] = { 0 };
    
    // detail
    float noiseTiling = 0;
    float noiseIntensity = 0;
    
    // light
    float density = 0;
    float sigmaExtinction = 0;
    float sigmaScattering = 0;
    float mainLightColor[THREE_DIMS] = { 0 };
    float ambientLightColor[THREE_DIMS] = { 0 };
    float mainLightIntensity = 0;
    float ambientLightIntensity = 0;
    float silverSpread = 0;
    float shadowStepSize = 0;
    
    // wind
    float detailWindStrength[THREE_DIMS] = { 0 };
    float shapeWindStrength[THREE_DIMS] = { 0 };
    
    // other
    float timeSinceLevelLoad = 0;
    float worldSpaceLightDirection[THREE_DIMS] = { 0 };
    float worldSpaceCameraPosition[THREE_DIMS] = { 0 };
    float cameraClippingPlanesNear = 0;
    float cameraClippingPlanesFar = 0;

    float camera2World[MATRIX_DIMS] = { 0 };         // matrix
    float world2Camera[MATRIX_DIMS] = { 0 };         // matrix
    float cameraProjection[MATRIX_DIMS] = { 0 };     // matrix
    float cameraInvProjection[MATRIX_DIMS] = { 0 };  // matrix

    char noisePath[PATH_DIMS] = { 0 };
    char shapePath[PATH_DIMS] = { 0 };
};

#pragma pack()

#endif //VOLUME_RENDER_PARAS_H