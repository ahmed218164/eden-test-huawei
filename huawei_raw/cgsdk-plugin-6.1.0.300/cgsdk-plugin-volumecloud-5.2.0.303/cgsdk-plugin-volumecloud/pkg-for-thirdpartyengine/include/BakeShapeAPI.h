/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: a head file to offer a connection
 * Author: liwanqi
 * Create: 2020-12-01
 */

#ifndef BAKE_SHAPE_API_H
#define BAKE_SHAPE_API_H

#define VolumeCloudEXPORT _declspec(dllexport)

struct BakeData {
    float* vDatas = nullptr;
    int vDatasLength = 0;
    float* fDatas = nullptr;
    int fDatasLength = 0;
    float* minBox = nullptr;
    float* maxBox = nullptr;
    int* volumeSize = nullptr;
};


class VolumeCloudEXPORT BakeShapeAPI
{
public:
    BakeShapeAPI() { };
    ~BakeShapeAPI() { };
    bool BakeMultiMesh(const BakeData bakeData, char savePath[]);
};

typedef  BakeShapeAPI* bt;
bt VolumeCloudEXPORT CreateBakeShapeAPI();

#endif