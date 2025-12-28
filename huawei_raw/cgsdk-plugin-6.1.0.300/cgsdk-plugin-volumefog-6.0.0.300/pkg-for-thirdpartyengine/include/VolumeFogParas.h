/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description:
 * Author: wujun
 * Create: 2021-4-20
 */
#ifndef VOLUME_FOG_PARAS_H
#define VOLUME_FOG_PARAS_H

#pragma pack(4)
struct BaseParas {
    float density;
    float absorb;
    float scatter;

    // for noise fog
    bool noiseFogEnable;
    float noiseFogAmount;
    float noiseFogScale[3];
    float noiseBias;
    float windSpeed[3];
    float time;

    // for height fog
    bool heightFogEnable;
    float heightFogExponent;
    float heightFogOffset;

    // for ambient
    float ambientLightIntensity;
    float ambientLightColor[3];

    // for camera
    float camPos[3];
    float camDir[3];
    float nearClip;
    float farClip;
    float withdraw;
    float posLB[3];
    float posRB[3];
    float posLT[3];

    int pointLightNum;
    int spotLightNum;

    // for volume size
    int tileSize;
    int volumeDepth;
};

struct DirLightParas {
    float dir[3];
    float color[3];
    float intensity;
    int shadowFlag;
    float shadowMatrix[16];
    void* shadowMap;
    int shadowMapResolution;
};

struct PointLightParas {
    float pos[3];
    float color[3];
    float range;
    float intensity;
};

struct SpotLightParas {
    float pos[3];
    float color[3];
    float dir[3];
    float angle;
    float range;
    float intensity;
};

#pragma pack()

#endif //VOLUME_RENDER_PARAS_H