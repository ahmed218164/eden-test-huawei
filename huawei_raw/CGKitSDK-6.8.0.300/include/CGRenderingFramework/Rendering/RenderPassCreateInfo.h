/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: renderpass info.
 */

#ifndef RENDER_PASS_CREATE_INFO_H
#define RENDER_PASS_CREATE_INFO_H

#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

#define INVALID_INDEX 0XFF

struct CGKIT_EXPORT Attachment {
    PixelFormat format = PIXEL_FORMAT_R8G8B8A8_UNORM;
    SampleCountFlagBits sampleCount = SAMPLE_COUNT_1_BIT;
    LoadOp loadOp = ATTACHMENT_LOAD_OP_CLEAR;
    StoreOp storeOp = ATTACHMENT_STORE_OP_STORE;
    LoadOp stencilLoadOp = ATTACHMENT_LOAD_OP_DONT_CARE;
    StoreOp stencilStoreOp = ATTACHMENT_STORE_OP_DONT_CARE;
    ImageLayout beginLayout = IMAGE_LAYOUT_UNDEFINED;
    ImageLayout endLayout = IMAGE_LAYOUT_PRESENT_SRC_KHR;
};

struct CGKIT_EXPORT SubpassInfo {
    PipelineBindPoint bindPoint = PIPELINE_BIND_POINT_GRAPHICS;
    u8 depthStencil = INVALID_INDEX;
    std::vector<u8> inputs;
    std::vector<u8> colors;
    std::vector<u8> resolves;
    std::vector<u8> preserves;
};

struct CGKIT_EXPORT SubpassDependency {
    u8 srcSubpass = SUBPASS_EXTERNAL;
    u8 dstSubpass = 0;
    PipelineStageFlags srcStageMask = PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    PipelineStageFlags dstStageMask = PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    AccessFlags srcAccessMask = 0;
    AccessFlags dstAccessMask = ACCESS_COLOR_ATTACHMENT_READ_BIT | ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
};

typedef std::vector<Attachment> AttachmentList;
typedef std::vector<SubpassInfo> SubpassInfoList;
typedef std::vector<SubpassDependency> SubpassDependencyList;

struct CGKIT_EXPORT RenderPassCreateInfo {
    AttachmentList attachments;
    SubpassInfoList subpasses;
    SubpassDependencyList dependencies;
};

NS_CG_END

#endif