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
 * @file HiCulling.h
 * @brief Sofware occlusion culling is occlusion method that uses designated level of datails(LOD)
 *        of a model to occlude ones behind it. The culling method rasterizes the models(the models
 *        is divided into occluder and occludee) one the CPU. The current implementation assumes that
 *        the projection matrix must map far plane to 0 and near plane to 1, this is somewhat different
 *        from opengl, the caller needs to pay specail attention. In addition, the implementation
 *        support multi-thread, and users can decide whether to enable it according to the actual needs
 *        of the application scenario.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The software culling object
 */
struct HiCulling;

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
 * The winding order of backface, and the backface triangle will not rasterized
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
    /* The stride of vertex buffer in component(float) */
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

/*
 * @brief Creates a new object, z buffer will be initialized with the default size
 *
 * @param enableMutiThread Indicates whether to enable multithread, if enabled, rasterization
 *        testing will be executed in parallel on multiple threads
 * @return Will return HiCulling object
 */
struct HiCulling *HcCreate(bool enableMutiThread);

/*
 * @brief Destroy the object and frees the memory resource
 *
 * @param obj Pointer to the object that will be Destroy
 */
void HcDestroy(struct HiCulling *obj);

/*
 * @brief Set the resolution of depth buffer. the previous z buffer will no longer be
 *        available after the function call, and ClearBuffer will be called once internally
 *
 * @param obj Pointer to the HiCulling object
 * @param width The width of the depth buffer in pixels, must be a multiple of 2
 * @param height The height of the depth buffer in pixels, must be a multiple of 2
 * @return Will return ERROR_PARA/ERROR_OOM if failed, returns OK otherwise
 */
HcErrorCode HcSetResolution(struct HiCulling *obj, unsigned int width, unsigned int height);

/*
 * @brief Get the resolution of the depth buffer
 *
 * @param obj Pointer to the HiCulling object
 * @param width Output the width of the depth buffer in pixels
 * @param height Output the height of the depth buffer in pixels
 * @return Will return ERROR_PARA/ERROR_OOM if failed, returns OK otherwise
 */
HcErrorCode HcGetResolution(struct HiCulling *obj, unsigned int &width, unsigned int &height);

/*
 * @brief Clear the depth buffer to zero(far plane), it is recommended to call this api at the
 *        end of each frame.
 *
 * @param obj Pointer to the HiCulling object
 * @return Will return ERROR_PARA/ERROR_OOM if failed, returns OK otherwise
 */
HcErrorCode HcClearBuffer(struct HiCulling *obj);

/*
 * @brief Add occluder meshes for rasterization
 *
 * @param obj Pointer to the HiCulling object
 * @param meshes The occluder meshes
 * @return Will return ERROR_PARA/ERROR_OOM if failed, returns OK otherwise
 */
HcErrorCode HcAddOccluderMeshes(struct HiCulling *obj, const HcOccluderMeshType &meshes);

/*
 * @brief Rasterize the meshes added by AddOccluderMeshes interface, it will update the depth buffer
 *
 * @param obj Pointer to the HiCulling object
 * @return Will return ERROR_PARA/ERROR_OOM if failed, returns OK otherwise
 */
HcErrorCode HcRasterizeOccluder(struct HiCulling *obj);

/*
 * @brief Occlusion query for occldees, occludee is represented by AABB bounding boxes in world space,
 *        and the query return a corresponding bool value to indicate visibility
 *
 * @param obj Pointer to the HiCulling object
 * @param boxes The AABB bounding boxes in world space
 * @param result The pointer array, and each member points to the real address of visibility
 * @return Will return ERROR_PARA/ERROR_OOM if failed, returns OK otherwise
 */
HcErrorCode HcTestOccludeesAABB(struct HiCulling *obj, HcOccludeeBoxType &boxes, bool **result);

/*
 * @brief Get a per-pixel depth buffer, it intended for visualizing depth buffer for debugging
 *
 * @param obj Pointer to the HiCulling object
 * @param depthBuffer Pointer to memory where the data is written
 * @return Will return ERROR_PARA/ERROR_OOM if failed, returns OK otherwise
 */
HcErrorCode HcGetDepthBuffer(struct HiCulling *obj, float *depthBuffer);

#ifdef __cplusplus
};
#endif

#endif
