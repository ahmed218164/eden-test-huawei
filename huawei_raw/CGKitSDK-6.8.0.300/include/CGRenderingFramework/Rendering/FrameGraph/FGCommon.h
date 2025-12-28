#ifndef FGCOMMON_H
#define FGCOMMON_H

#include "Core/Global.h"
#include "Core/Types.h"
#include "Rendering/Graphics/CommandBuffer.h"
#include "Rendering/Graphics/RenderPass.h"

NS_CG_BEGIN

enum class ResourceUsage : u8 {
    NONE_USAGE = 0x0,
    COLOR_ATTACHMENT = 0x1,
    DEPTH_STENCIL_ATTACHMENT = 0x2,
    PRESENT = 0x20
};

enum class AttachmentFlages : u32 {
    NONE_ATTACHMENT = 0x0u,
    COLOR0 = 0x00000001u,
    COLOR1 = 0x00000002u,
    COLOR2 = 0x00000004u,
    COLOR3 = 0x00000008u,
    COLOR4 = 0x00000010u,
    COLOR5 = 0x00000020u,
    COLOR6 = 0x00000040u,
    COLOR7 = 0x00000080u,

    COLOR_ALL = COLOR0 | COLOR1 | COLOR2 | COLOR3 | COLOR4 | COLOR5 | COLOR6 | COLOR7,
    DEPTH_STENCIL = 0x00000100u,
    ALL = COLOR_ALL | DEPTH_STENCIL
};

enum class PassType : u8 {
    GRAPHICS_PASS = 0,
    COMPUTE_PASS,
};

struct PassExecuteParam {
    CommandBuffer* commandBuffer = nullptr;
    RenderPass* renderPass = nullptr;
};

NS_CG_END

#endif
