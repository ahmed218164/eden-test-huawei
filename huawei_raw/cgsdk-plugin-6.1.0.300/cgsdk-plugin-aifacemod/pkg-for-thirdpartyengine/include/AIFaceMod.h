/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 游戏捏脸接口
 */

#ifndef _AI_FACEMOD_H_
#define _AI_FACEMOD_H_

#include <vector>
#include <string>

#ifdef __ANDROID__
#define EXPORT __attribute__((visibility("default")))
#else
#define EXPORT _declspec(dllexport)
#endif // __ANDROID__

struct AIFaceModParas {
    int landmarkMode;
    std::vector<float> landmarkData;
    int segmentImgW;
    int segmentImgH;
    std::vector<unsigned char> segmentImg;
    std::string modAPath;
    std::string modBPath;
    std::string modCPath;
    std::string shapePath;
    std::string characterPath;
    int characterGender;
    int enableRealTex;
};

struct GeneratedParas {
    std::vector<float> continuousParas;
    std::vector<int> discreteParas;
    int realTexHeight;
    int realTexWidth;
    std::vector<unsigned char> realTex;
};

EXPORT int GenerateFaceParas(const AIFaceModParas& modParas, GeneratedParas& genParas);
EXPORT int ModifyFaceParas(const float modifyDegree, GeneratedParas& genParas);

#endif
