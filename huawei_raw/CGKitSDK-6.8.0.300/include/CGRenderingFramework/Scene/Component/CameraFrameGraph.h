/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2022. All rights reserved.
 * Description: A CameraFrameGraph class used to set and obtain the CameraFrameGraph position,
 *     projection type, field of view (FOV),and near and far clipping planes.
 */

#ifndef CameraFrameGraph_H
#define CameraFrameGraph_H

#include "Scene/Component/Camera.h"
#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

class CGKIT_EXPORT CameraFrameGraph : public Camera {
public:
    /*
     * A constructor used to initialize the CameraFrameGraph.
     */
    CameraFrameGraph(SceneObject* sceneObject = nullptr);

    /*
     * A destructor used to free memory.
     */
    ~CameraFrameGraph();

    /*
     * Set the rendering path base on framegraph of CameraFrameGraph.
     */
    void SetRenderingPathFG(GraphicsRenderer* graphicsRenderer);

     /*
     * Set multisample info.
     */
    void SetMultiSampleInfo(const MultiSampleInfo& sampleInfo) override;

    /*
     * Camera rendering.
     */
    void Render() override;

private:
    GraphicsRenderer* m_graphicsRenderer = nullptr;
    MultiSampleInfo m_multiSampleInfo;
};

NS_CG_END

#endif
