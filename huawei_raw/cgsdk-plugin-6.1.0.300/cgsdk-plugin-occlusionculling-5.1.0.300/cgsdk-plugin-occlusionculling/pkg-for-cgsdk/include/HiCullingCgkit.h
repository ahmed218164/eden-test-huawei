/**
 * Copyright (c) Hisilicon Technologies Co., Ltd. 2020-2020. All rights reserved.
 *
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from Hisilicon Technologies Co.
 */
#ifndef HI_CULLING_H
#define HI_CULLING_H

/*
 * @file HiCullingCgkit.h
 * @brief Sofware occlusion culling is occlusion method that uses designated level of datails(LOD)
 *        of a model to occlude ones behind it. The culling method rasterizes the models(the models
 *        is divided into occluder and occludee) one the CPU. The current implementation assumes that
 *        the projection matrix must map far plane to 0 and near plane to 1, this is somewhat different
 *        from opengl, the caller needs to pay specail attention. In addition, the implementation
 *        support multi-thread, and users can decide whether to enable it according to the actual needs
 *        of the application scenario.
 */

/*
 * The error code of culling sysytem
 */
enum HcErrorCode {
    /* No error */
    HC_OK = 0,
    /* Parameter error */
    HC_ERROR_PARA,
    /* Out of memory */
    HC_ERROR_OOM
};

/*
 * The winding order of backface triangle which will not rasterized
 */
enum HcBackfaceWinding {
    /* Clockwise */
    HC_CW = 0,
    /* Counter-clockwise */
    HC_CCW,
    /* No face culling */
    HC_NONE
};

/*
 * Specifies the type of index buffer
 */
enum HcIndexBufferType {
    /* Unsigned byte */
    HC_UNSIGNED_BYTE = 0,
    /* Unsigned short */
    HC_UNSIGNED_SHORT,
    /* Unsigned int */
    HC_UNSIGNED_INT
};

/*
 * The type used to discribe the occluder mesh. On the engine side, it can choose a certain LOD level
 * as the occluder. There are some limitations:
 * 1) Projection must map the interval between near and far plane [Zn,Zf] to [1,0], for right handed
 *    coordinate systems, we suggest:
 *              | 2xZn/W   0       0       0 |
 *          P = | 0        2xZn/H  0       0 |
 *              | 0        0       0       Zn|
 *              | 0        0      -1       0 |
 *          note: a)W/H is width/height of the view volume at the near view-plane in camera space
 *                b)Zn is the distances of near view-plane in camera space
 * 2) The final transformation matrix (localToClip = World x View x Projection) should be stored in
 *    column-major order
 * 3) The layout of vertex data must be AoS(array of structures), but vertex stride is configurable
 * 4) The topology of mesh must be triangle list
 */
typedef struct {
    /* Pointer to vertex buffer  */
    float *vertices;
    /* The number of vertices */
    unsigned int nVertices;
    /* Pointer to indices buffer  */
    void *indices;
    /* The number of indices */
    unsigned int nIndices;
    /* localToClip = projection * view * world (stored in column-major order) */
    float localToClip[4][4];
} HcMeshType;

/*
 * The collection of occluder meshes to be rasterized.
 */
typedef struct {
    /* The number of meshes */
    unsigned int numMesh;
    /* Pointer to array of mesh */
    HcMeshType *meshes;
    /* Backface winding order */
    HcBackfaceWinding bWinding;
    /* Index bufer type */
    HcIndexBufferType idxType;
    /* The stride of vertex buffer */
    unsigned int vtxStride;
    /* Near clip plane distance in camera space */
    float nearClipDistance;
} HcOccluderMeshType;

/*
 * Used to specify a occludee bounding box in world space,
 * The layout of buffer must be (xmin,ymin,zmin,xmax,ymax,zmax)
 */
typedef struct {
    /* The number of occludees bounding box */
    int numBox;
    /* Pointer to bounding box buffer */
    float *boxMinMax;
    /* worldToClip = projection * view (stored in column-major order) */
    float worldToClip[4][4];
} HcOccludeeBoxType;

#endif