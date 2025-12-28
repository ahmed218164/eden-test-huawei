/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2022. All rights reserved.
 * Description: pipeline create info.
 */
#ifndef PIPELINE_CREATE_INFO_H
#define PIPELINE_CREATE_INFO_H

#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

class Shader;
class RenderPass;
class VertexDeclaration;
/*
 * default mask
 */
static const u32 DEFAULT_MASK = 0xFF;

/*
 * default color mask.
 */
static const u32 COLOR_MASK_MAX = 0x0000000F;

/**
 * Structure parameters specifying the pipeline rasterization state.
 */
struct RasterizationState {
    bool depthClampEnable = false;
    bool rasterizerDiscardEnable = false;
    FillMode polygonMode = FILL_MODE_FILL;
    CullMode cullmode = CULL_MODE_BACK;
    FrontFace frontFace = FRONT_FACE_COUNTER_CLOCKWISE;
    bool depthBiasEnable = false;
    f32 depthBiasConstantFactor = 0.0f;
    f32 depthBiasClamp = 0.0f;
    f32 depthBiasSlopeFactor = 0.0f;
    f32 lineWidth = 1.0f;
    std::size_t hash = 0;
};

/*
 * Defines the Depth/Stencil operation.
 */
struct DepthStencilOp {
    StencilOperation stencilFail = STENCIL_OPERATION_KEEP;
    StencilOperation stencilDepthFail = STENCIL_OPERATION_KEEP;
    StencilOperation stencilPass = STENCIL_OPERATION_KEEP;
    CompareOperation stencilFunc = COMPARISON_OPERATION_ALWAYS;
    u32 stencilCompareMask = DEFAULT_MASK;
    u32 stencilReference = DEFAULT_MASK;
    u32 stencilReadMask = DEFAULT_MASK;
    u32 stencilWriteMask = DEFAULT_MASK;
};

/**
 * Structure parameters specifying the pipeline depth/stencil state.
 */
struct DepthStencilState {
    bool depthTestEnable = true;
    bool depthWriteEnable = true;
    CompareOperation depthFunc = COMPARISON_OPERATION_LESS_OR_EQUAL;
    bool depthBoundsTestEnable = false;
    bool stencilTestEnable = false;
    DepthStencilOp front;
    DepthStencilOp back;
    std::size_t hash = 0;
};

/*
 * Defines the Color blending operation.
 */
struct BlendAttachmentState {
    bool blendingEnable = false;
    BlendFactor srcColorBlend = BLEND_SRC_ALPHA;
    BlendFactor dstColorBlend = BLEND_ONE_MINUS_SRC_ALPHA;
    BlendOperation colorBlendOp = BLEND_OPERATION_ADD;
    BlendFactor srcAlphaBlend = BLEND_ONE;
    BlendFactor dstAlphaBlend = BLEND_ZERO;
    BlendOperation alphaBlendOp = BLEND_OPERATION_ADD;
    u32 colorMask = COLOR_MASK_MAX;
    f32 blendFactor = 0.0f;
};

/**
 * Structure parameters specifying the pipeline color blending state.
 */
struct ColorBlendState {
    ColorBlendState()
    {
        attachments.resize(1);
        blendConstants = { 0.0f, 0.0f, 0.0f, 0.0f };
    };
    bool logicOpEnable = false;
    LogicOp logicOp = LOGIC_OP_CLEAR;
    std::vector<BlendAttachmentState> attachments;
    std::size_t hash = 0;
    std::vector<f32> blendConstants;
};

/**
 * Structure parameters for creating `Pipeline`.
 */
struct PipelineCreateInfo {
    PipelineBindPoint bindPoint = PIPELINE_BIND_POINT_GRAPHICS;
    PrimitiveMode primitiveMode = PRIMITIVE_MODE_TRIANGLE_LIST;
    RasterizationState rasterizationState;
    MultiSampleInfo multiSampleInfo;
    DepthStencilState depthStencilState;
    ColorBlendState colorBlendState;
    u32 dynamicStateMask = 0; // Mask value of Dynamic States bitwise AND. @see `DynamicFlag`.
    const Shader* shader = nullptr;
    const RenderPass* renderPass = nullptr;
    const VertexDeclaration* vertexDeclaration = nullptr;
    u32 subpassIndex = 0;
};

NS_CG_END

#endif