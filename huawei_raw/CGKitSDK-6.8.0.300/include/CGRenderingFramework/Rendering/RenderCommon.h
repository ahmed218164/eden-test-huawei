/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2022. All rights reserved.
 * Description: Rendering common types.
 */

#ifndef RENDER_COMMON_H
#define RENDER_COMMON_H

#include "Core/Types.h"
#include "Math/Color.h"

NS_CG_BEGIN

enum RenderingPathType {
    RENDER_PATH_TYPE_FORWARD,
    RENDER_PATH_TYPE_DEFERRED,
    RENDER_PATH_TYPE_MAX
};

/*
 * Defines the lighting projection types.
 */
enum ProjectionType {
    /*
     * Orthographic projection.
     */
    PROJECTION_TYPE_ORTHOGONAL,

    /*
     * Perspective projection
     */
    PROJECTION_TYPE_PERSPECTIVE,
};

/*
 * Defines the primitives.
 */
enum PrimitiveMode {
    /*
     * Renders the specified vertices as a sequence of isolated triangles. Each group of three
     * vertices defines a separate triangle.
     */
    PRIMITIVE_MODE_TRIANGLE_LIST,

    /*
     * Reserved
     */
    PRIMITIVE_MODE_LINE_LIST,

    /*
     * Reserved
     */
    PRIMITIVE_MODE_POINT_LIST,

    /*
     * Reserved
     */
    PRIMITIVE_MODE_TRIANGLE_FAN,

    /*
     * Reserved
     */
    PRIMITIVE_MODE_TRIANGLE_STRIP,
};

/*
 * Defines the fill modes.
 */
enum FillMode {
    /*
     * Fill solids.
     */
    FILL_MODE_FILL,

    /*
     * Fill lines.
     */
    FILL_MODE_LINE,

    /*
     * Fill points.
     */
    FILL_MODE_POINT,
};

/*
 * Defines the culling modes.
 */
enum CullMode {
    /*
     * Cull disabled.
     */
    CULL_MODE_NONE,

    /*
     * Culls front-facing geometry.
     */
    CULL_MODE_FRONT,

    /*
     * Culls back-facing geometry.
     */
    CULL_MODE_BACK,

    /*
     * Culls front and back facing geometry.
     */
    CULL_MODE_FRONT_AND_BACK,
};

/*
 * Defines the triangle winding orders.
 */
enum FrontFace {
    /*
     * Anticlockwise winding.
     */
    FRONT_FACE_COUNTER_CLOCKWISE,

    /*
     * Clockwise winding.
     */
    FRONT_FACE_CLOCKWISE,
};

/*
 * Defines the deep test operation types.
 */
enum CompareOperation {
    /*
     * Always fail the test.
     */
    COMPARISON_OPERATION_NEVER,

    /*
     * Accept the new pixel if its value is less than the value of the current pix.
     */
    COMPARISON_OPERATION_LESS,

    /*
     * Accept the new pixel if its value equals the value of the current pixel.
     */
    COMPARISON_OPERATION_EQUAL,

    /*
     * Accept the new pixel if its value is less than or equal to the value of the current pixel.
     */
    COMPARISON_OPERATION_LESS_OR_EQUAL,

    /*
     * Accept the new pixel if its value is greater than the value of the current pixel.
     */
    COMPARISON_OPERATION_GREATER,

    /*
     * Accept the new pixel if its value does not equal the value of the current pixel.
     */
    COMPARISON_OPERATION_NOT_EQUAL,

    /*
     * Accept the new pixel if its value is greater than or equal to the value of the current pixel.
     */
    COMPARISON_OPERATION_GREATER_OR_EQUAL,

    /*
     * Always pass the test.
     */
    COMPARISON_OPERATION_ALWAYS,
};

/*
 * Defines the RGBA blend modes.
 */
enum BlendFactor {
    /*
     * (0, 0, 0, 0).
     */
    BLEND_ZERO,

    /*
     * (1, 1, 1, 1).
     */
    BLEND_ONE,

    /*
     * (Rs, Gs, Bs, As).
     */
    BLEND_SRC_COLOR,

    /*
     * (1, 1, 1, 1) - (Rs0, Gs0, Bs0, As0).
     */
    BLEND_ONE_MINUS_SRC_COLOR,

    /*
     * (Rd, Gd, Bd, Ad)
     */
    BLEND_DST_COLOR,

    /*
     * (1 -  Rd, 1 - Gd, 1 - Bd, 1 - Ad)
     */
    BLEND_ONE_MINUS_DST_COLOR,

    /*
     * (As0, As0, As0).
     */
    BLEND_SRC_ALPHA,

    /*
     * (1, 1, 1, 1) - (As0, As0, As0, As0).
     */
    BLEND_ONE_MINUS_SRC_ALPHA,

    /*
     * (Ad, Ad, Ad, Ad).
     */
    BLEND_DST_ALPHA,

    /*
     * (1 - Ad, 1 - Ad, 1 - Ad, 1 - Ad).
     */
    BLEND_ONE_MINUS_DST_ALPHA,

    /*
     * (Rc, Gc, Bc, Ac).
     */
    BLEND_CONSTANT_COLOR,

    /*
     * (1, 1, 1, 1) - (Rc, Gc, Bc, Ac).
     */
    BLEND_ONE_MINUS_CONSTANT_COLOR,

    /*
     * (Ac, Ac, Ac, Ac).
     */
    BLEND_CONSTANT_ALPHA,

    /*
     * (1 - Ac, 1 - Ac, 1 - Ac, 1 - Ac).
     */
    BLEND_ONE_MINUS_CONSTANT_ALPHA,
};

/*
 * Defines the RGBA blend operations.
 */
enum BlendOperation {
    /*
     * Result = Source + Destination.
     */
    BLEND_OPERATION_ADD,

    /*
     * Result = Source - Destination.
     */
    BLEND_OPERATION_SUBTRACT,

    /*
     * Result = Destination - Source.
     */
    BLEND_OPERATION_REV_SUBTRACT,

    /*
     * Result = MIN(Source, Destination).
     */
    BLEND_OPERATION_MIN,

    /*
     * Result = MAX(Source, Destination).
     */
    BLEND_OPERATION_MAX,
};

/*
 * Defines the texture addressing modes.
 */
enum SamplerAddress {
    /*
     * Tile the texture at every integer junction.
     */
    SAMPLER_ADDRESS_WRAP,

    /*
     * Flip the texture at every integer junction.
     */
    SAMPLER_ADDRESS_MIRROR,

    /*
     * Texture coordinates outside the range [0.0, 1.0] are set to the texture color at 0.0 or 1.0,
     * respectively.
     */
    SAMPLER_ADDRESS_CLAMP,

    /*
     * Texture coordinates outside the range [0.0, 1.0] are set to the border color.
     */
    SAMPLER_ADDRESS_BORDER,

    /*
     * Takes the absolute value of the texture coordinate (thus, mirroring around 0), and then
     * clamps to the maximum value 1.0.
     */
    SAMPLER_ADDRESS_MIRROR_ONCE,
};

/*
 * Defines the sampler filtering methods.
 */
enum SamplerFilter {
    /*
     * Nearest-point sampling.
     */
    SAMPLER_FILTER_NEAREST,

    /*
     * Bilinear texture filtering.
     */
    SAMPLER_FILTER_BILINEAR,

    /*
     * Trilinear texture filtering.
     */
    SAMPLER_FILTER_TRILINEAR,
};

/*
 * Defines the sampler filtering methods with mipmaps.
 */
enum SamplerMipmapMode {
    /*
     * Nearest-point sampling with mipmaps.
     */
    SAMPLER_MIPMAP_NEAREST,

    /*
     * Bilinear sampling with mipmaps.
     */
    SAMPLER_MIPMAP_BILINEAR,
};

/*
 * Defines the shader stages.
 */
enum ShaderStageType {
    /*
     * Minimum enum value.
     */
    SHADER_STAGE_NONE = 0,
    /*
     * Vertex shader.
     */
    SHADER_STAGE_TYPE_VERTEX = 1 << 0,

    /*
     * Tessellation control shader.
     */
    SHADER_STAGE_TYPE_TESSELLATION_CONTROL = 1 << 1,

    /*
     * Tessellation evaluation shader
     */
    SHADER_STAGE_TYPE_TESSELLATION_EVALUATION = 1 << 2,

    /*
     * Geometry shader.
     */
    SHADER_STAGE_TYPE_GEOMETRY = 1 << 3,

    /*
     * Fragment shader.
     */
    SHADER_STAGE_TYPE_FRAGMENT = 1 << 4,

    /*
     * Compute shader.
     */
    SHADER_STAGE_TYPE_COMPUTE = 1 << 5,

    /*
     * Maximum enum value.
     */
    SHADER_STAGE_ALL = 0x7FFFFFFF,
};

/*
 * Defines the Light Type.
 */
enum LightType {
    LIGHT_TYPE_DIRECTIONAL,
    LIGHT_TYPE_POINT,
    LIGHT_TYPE_SPOT,

    LIGHT_TYPE_MAX,
};

/*
 * Defines the Rendering Sort Type.
 */
enum RenderingSortType {
    RENDERING_SORT_TYPE_DISTANCE,
    RENDERING_SORT_TYPE_ID,
    RENDERING_SORT_TYPE_MAX,
};

/*
 * Defines the SceneManager Type.
 */
enum SceneManagerType {
    SCENE_MANAGER_TYPE_QUADTREE,
    SCENE_MANAGER_TYPE_COMMON,
    SCENE_MANAGER_TYPE_MAX,
};

/*
 * Defines the sampler Stencil Operation.
 */
enum StencilOperation {
    STENCIL_OPERATION_KEEP,
    STENCIL_OPERATION_ZERO,
    STENCIL_OPERATION_REPLACE,
    STENCIL_OPERATION_INCREMENT_AND_CLAMP,
    STENCIL_OPERATION_DECREMENT_AND_CLAMP,
    STENCIL_OPERATION_INVERT,
    STENCIL_OPERATION_INCREMENT_AND_WRAP,
    STENCIL_OPERATION_DECREMENT_AND_WRAP,
};

enum ImageType {
    IMAGE_TYPE_1D,
    IMAGE_TYPE_2D,
    IMAGE_TYPE_3D,
    IMAGE_TYPE_CUBEMAP,
    IMAGE_TYPE_MAX,
};

enum TextureUsage : u16 {
    /*
     * Binding none.
     */
    TEXTURE_USAGE_NONE = 0,

    /*
     * Binding sampled.
     */
    TEXTURE_USAGE_SAMPLED = 1,

    /*
     * Binding render target.
     */
    TEXTURE_USAGE_RENDERTARGET = 2,

    /*
     * Binding depth stencil.
     */
    TEXTURE_USAGE_DEPTHSTENCIL = 3,

    /*
     * Binding depth.
     */
    TEXTURE_USAGE_DEPTH = 4,

    /*
     * Transfer Destination.
     */
    TEXTURE_USAGE_TRANSFER_DST = 5,

    /*
     * Binding color attachment
     */
    TEXTURE_USAGE_COLOR_ATTACHMENT = 6,

    /*
     * Binding storage
     */
    TEXTURE_USAGE_STORAGE = 7,
};

enum PixelFormat {
    // R
    PIXEL_FORMAT_R8_UNORM,
    PIXEL_FORMAT_R16_UINT,
    PIXEL_FORMAT_R16_FLOAT,
    PIXEL_FORMAT_R32_UINT,
    PIXEL_FORMAT_R32_FLOAT,
    PIXEL_FORMAT_D32_FLOAT,
    // RG
    PIXEL_FORMAT_R8G8_UNORM,
    PIXEL_FORMAT_R8G8_UINT,
    PIXEL_FORMAT_R16G16_UINT,
    PIXEL_FORMAT_R16G16_SINT,
    PIXEL_FORMAT_R16G16_FLOAT,
    PIXEL_FORMAT_R32G32_FLOAT,
    // RGB
    PIXEL_FORMAT_R8G8B8_UNORM,
    PIXEL_FORMAT_R8G8B8_UINT,
    PIXEL_FORMAT_R16G16B16_UINT,
    PIXEL_FORMAT_R16G16B16_SINT,
    PIXEL_FORMAT_R16G16B16_FLOAT,
    PIXEL_FORMAT_R32G32B32_FLOAT,
    // RGBA
    PIXEL_FORMAT_R8G8B8A8_UNORM,
    PIXEL_FORMAT_R8G8B8A8_UINT,
    PIXEL_FORMAT_R16G16B16A16_UINT,
    PIXEL_FORMAT_R16G16B16A16_SINT,
    PIXEL_FORMAT_R16G16B16A16_FLOAT,
    PIXEL_FORMAT_R32G32B32A32_FLOAT,

    // BGRA
    PIXEL_FORMAT_B8G8R8A8_UNORM,

    // DepthFormat
    PIXEL_FORMAT_D16_UNORM,
    PIXEL_FORMAT_X8_D24_UNORM_PACK32,
    PIXEL_FORMAT_D32_SFLOAT,
    PIXEL_FORMAT_S8_UINT,
    PIXEL_FORMAT_D16_UNORM_S8_UINT,
    PIXEL_FORMAT_D24_UNORM_S8_UINT,
    PIXEL_FORMAT_D32_SFLOAT_S8_UINT,
    PIXEL_FORMAT_BC1_RGB_UNORM_BLOCK,
    PIXEL_FORMAT_BC1_RGB_SRGB_BLOCK,
    PIXEL_FORMAT_BC1_RGBA_UNORM_BLOCK,

    // ASTC
    PIXEL_FORMAT_ASTC_8x8_UNORM_BLOCK,

    PIXEL_FORMAT_MAX
};

enum CommandBufferLevelType {
    COMMAND_BUFFER_LEVEL_PRIMARY = 0,
    COMMAND_BUFFER_LEVEL_SECONDARY = 1,
};

enum SubpassContents {
    SUBPASS_CONTENTS_INLINE = 0,
    SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS = 1,
};

enum LoadOp {
    ATTACHMENT_LOAD_OP_LOAD = 0,
    ATTACHMENT_LOAD_OP_CLEAR = 1,
    ATTACHMENT_LOAD_OP_DONT_CARE = 2,
};

enum StoreOp {
    ATTACHMENT_STORE_OP_STORE = 0,
    ATTACHMENT_STORE_OP_DONT_CARE = 1,
};

enum ImageLayout {
    IMAGE_LAYOUT_UNDEFINED = 0,
    IMAGE_LAYOUT_GENERAL = 1,
    IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL = 2,
    IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL = 3,
    IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL = 4,
    IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL = 5,
    IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL = 6,
    IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL = 7,
    IMAGE_LAYOUT_PREINITIALIZED = 8,
    IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL = 1000117000,
    IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL = 1000117001,
    IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL = 1000241000,
    IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL = 1000241001,
    IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL = 1000241002,
    IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL = 1000241003,
    IMAGE_LAYOUT_PRESENT_SRC_KHR = 1000001002,
    IMAGE_LAYOUT_SHARED_PRESENT_KHR = 1000111000,
    IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV = 1000164003,
    IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT = 1000218000,
    IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR =
        IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
    IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR =
        IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
    IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL_KHR = IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
    IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL_KHR = IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
    IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL_KHR = IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL,
    IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL_KHR = IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL,
    IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR = IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV,
};

enum PipelineBindPoint {
    PIPELINE_BIND_POINT_GRAPHICS = 0,
    PIPELINE_BIND_POINT_COMPUTE = 1,
    PIPELINE_BIND_POINT_RAY_TRACING_KHR = 1000165000,
    PIPELINE_BIND_POINT_RAY_TRACING_NV = PIPELINE_BIND_POINT_RAY_TRACING_KHR,
};

typedef u32 PipelineStageFlags;
enum PipelineStageFlagBits {
    PIPELINE_STAGE_TOP_OF_PIPE_BIT = 0x00000001,
    PIPELINE_STAGE_DRAW_INDIRECT_BIT = 0x00000002,
    PIPELINE_STAGE_VERTEX_INPUT_BIT = 0x00000004,
    PIPELINE_STAGE_VERTEX_SHADER_BIT = 0x00000008,
    PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT = 0x00000010,
    PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT = 0x00000020,
    PIPELINE_STAGE_GEOMETRY_SHADER_BIT = 0x00000040,
    PIPELINE_STAGE_FRAGMENT_SHADER_BIT = 0x00000080,
    PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT = 0x00000100,
    PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT = 0x00000200,
    PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT = 0x00000400,
    PIPELINE_STAGE_COMPUTE_SHADER_BIT = 0x00000800,
    PIPELINE_STAGE_TRANSFER_BIT = 0x00001000,
    PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT = 0x00002000,
    PIPELINE_STAGE_HOST_BIT = 0x00004000,
    PIPELINE_STAGE_ALL_GRAPHICS_BIT = 0x00008000,
    PIPELINE_STAGE_ALL_COMMANDS_BIT = 0x00010000,
    PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT = 0x01000000,
    PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT = 0x00040000,
    PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR = 0x00200000,
    PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR = 0x02000000,
    PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV = 0x00400000,
    PIPELINE_STAGE_TASK_SHADER_BIT_NV = 0x00080000,
    PIPELINE_STAGE_MESH_SHADER_BIT_NV = 0x00100000,
    PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT = 0x00800000,
    PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_NV = 0x00020000,
    PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_NV = PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR,
    PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV = PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR,
};

typedef u32 AccessFlags;
enum AccessFlagBits {
    ACCESS_NONE = 0x00000000,
    ACCESS_INDIRECT_COMMAND_READ_BIT = 0x00000001,
    ACCESS_INDEX_READ_BIT = 0x00000002,
    ACCESS_VERTEX_ATTRIBUTE_READ_BIT = 0x00000004,
    ACCESS_UNIFORM_READ_BIT = 0x00000008,
    ACCESS_INPUT_ATTACHMENT_READ_BIT = 0x00000010,
    ACCESS_SHADER_READ_BIT = 0x00000020,
    ACCESS_SHADER_WRITE_BIT = 0x00000040,
    ACCESS_COLOR_ATTACHMENT_READ_BIT = 0x00000080,
    ACCESS_COLOR_ATTACHMENT_WRITE_BIT = 0x00000100,
    ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT = 0x00000200,
    ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT = 0x00000400,
    ACCESS_TRANSFER_READ_BIT = 0x00000800,
    ACCESS_TRANSFER_WRITE_BIT = 0x00001000,
    ACCESS_HOST_READ_BIT = 0x00002000,
    ACCESS_HOST_WRITE_BIT = 0x00004000,
    ACCESS_MEMORY_READ_BIT = 0x00008000,
    ACCESS_MEMORY_WRITE_BIT = 0x00010000,
    ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT_EXT = 0x02000000,
    ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT = 0x04000000,
    ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT = 0x08000000,
    ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT = 0x00100000,
    ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT = 0x00080000,
    ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR = 0x00200000,
    ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR = 0x00400000,
    ACCESS_SHADING_RATE_IMAGE_READ_BIT_NV = 0x00800000,
    ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT_EXT = 0x01000000,
    ACCESS_COMMAND_PREPROCESS_READ_BIT_NV = 0x00020000,
    ACCESS_COMMAND_PREPROCESS_WRITE_BIT_NV = 0x00040000,
    ACCESS_ACCELERATION_STRUCTURE_READ_BIT_NV = ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR,
    ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_NV = ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR,
};

enum SampleCountFlagBits {
    SAMPLE_COUNT_1_BIT = 0x00000001,
    SAMPLE_COUNT_2_BIT = 0x00000002,
    SAMPLE_COUNT_4_BIT = 0x00000004,
    SAMPLE_COUNT_8_BIT = 0x00000008,
    SAMPLE_COUNT_16_BIT = 0x00000010,
    SAMPLE_COUNT_32_BIT = 0x00000020,
    SAMPLE_COUNT_64_BIT = 0x00000040,
};

enum SubpassType {
    SUBPASS_EXTERNAL = 1
};

enum RenderTargetType {
    FROM_SWAPCHAIN = 0,
    FROM_TEXTURE = 1
};

enum LayerType {
    LAYER_TYPE_DEFAULT = 1 << 0, // DEFAULT means cannot be culling
    LAYER_TYPE_GEOMETRY = 1 << 1,
    LAYER_TYPE_SKYBOX = 1 << 2,
    LAYER_TYPE_ALL = 0x7FFFFFFF,
};

/*
 * Defines the Animation Play Mode.
 */
enum AnimationPlayMode {
    ANIMATION_PLAY_MODE_LOOP,
    ANIMATION_PLAY_MODE_ONCE,
    ANIMATION_PLAY_MODE_PING_PONG,
    ANIMATION_PLAY_MODE_MAX,
};

/*
 * Defines the framebuffer logical operations
 */
enum LogicOp {
    LOGIC_OP_CLEAR,
    LOGIC_OP_AND,
    LOGIC_OP_AND_REVERSE,
    LOGIC_OP_COPY
};

/*
 * Fence flag.
 */
enum FenceFlag {
    /*
     * zero.
     */
    FENCE_FLAG_INVALID,

    /*
     * FenceCreateFlageBit is one.
     */
    FENCE_FLAG_SIGNALED,

    /*
     * Max flag.
     */
    FENCE_FLAG_MAX = 0x7FFFFFFF
};

enum ImageTiling {
    IMAGE_TILING_OPTIMAL = 0,
    IMAGE_TILING_LINEAR = 1,
    IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT = 1000158000,
    IMAGE_TILING_BEGIN_RANGE = IMAGE_TILING_OPTIMAL,
    IMAGE_TILING_END_RANGE = IMAGE_TILING_LINEAR,
    IMAGE_TILING_RANGE_SIZE = (IMAGE_TILING_LINEAR - IMAGE_TILING_OPTIMAL + 1),
    IMAGE_TILING_MAX_ENUM = 0x7FFFFFFF
};

enum ImageUsageFlagBits {
    IMAGE_USAGE_TRANSFER_SRC_BIT = 0x00000001,
    IMAGE_USAGE_TRANSFER_DST_BIT = 0x00000002,
    IMAGE_USAGE_SAMPLED_BIT = 0x00000004,
    IMAGE_USAGE_STORAGE_BIT = 0x00000008,
    IMAGE_USAGE_COLOR_ATTACHMENT_BIT = 0x00000010,
    IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000020,
    IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT = 0x00000040,
    IMAGE_USAGE_INPUT_ATTACHMENT_BIT = 0x00000080,
    IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV = 0x00000100,
    IMAGE_USAGE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
};

enum ImageCreateFlagBits {
    IMAGE_CREATE_SPARSE_BINDING_BIT = 0x00000001,
    IMAGE_CREATE_SPARSE_RESIDENCY_BIT = 0x00000002,
    IMAGE_CREATE_SPARSE_ALIASED_BIT = 0x00000004,
    IMAGE_CREATE_MUTABLE_FORMAT_BIT = 0x00000008,
    IMAGE_CREATE_CUBE_COMPATIBLE_BIT = 0x00000010,
    IMAGE_CREATE_ALIAS_BIT = 0x00000400,
    IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT = 0x00000040,
    IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT = 0x00000020,
    IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT = 0x00000080,
    IMAGE_CREATE_EXTENDED_USAGE_BIT = 0x00000100,
    IMAGE_CREATE_PROTECTED_BIT = 0x00000800,
    IMAGE_CREATE_DISJOINT_BIT = 0x00000200,
    IMAGE_CREATE_CORNER_SAMPLED_BIT_NV = 0x00002000,
    IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT = 0x00001000,
    IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR = IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT,
    IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT_KHR = IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT,
    IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT_KHR = IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT,
    IMAGE_CREATE_EXTENDED_USAGE_BIT_KHR = IMAGE_CREATE_EXTENDED_USAGE_BIT,
    IMAGE_CREATE_DISJOINT_BIT_KHR = IMAGE_CREATE_DISJOINT_BIT,
    IMAGE_CREATE_ALIAS_BIT_KHR = IMAGE_CREATE_ALIAS_BIT,
    IMAGE_CREATE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
};

enum MemoryPropertyFlagBits {
    MEMORY_PROPERTY_DEVICE_LOCAL_BIT = 0x00000001,
    MEMORY_PROPERTY_HOST_VISIBLE_BIT = 0x00000002,
    MEMORY_PROPERTY_HOST_COHERENT_BIT = 0x00000004,
    MEMORY_PROPERTY_HOST_CACHED_BIT = 0x00000008,
    MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT = 0x00000010,
    MEMORY_PROPERTY_PROTECTED_BIT = 0x00000020,
    MEMORY_PROPERTY_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
};

/*
 * MSAA Setting info
 */
struct MultiSampleInfo {
    bool enableMSAA = false;
    SampleCountFlagBits sampleCount = SAMPLE_COUNT_1_BIT;
    bool enableSampleShading = false;
    f32 minSampleShading = 0.0f;

    MultiSampleInfo() = default;

    MultiSampleInfo(bool enableMSAA, SampleCountFlagBits sampleCount)
        : enableMSAA(enableMSAA),
          sampleCount(sampleCount)
    {}

    MultiSampleInfo(bool enableMSAA, SampleCountFlagBits sampleCount, bool enableSampleShading, f32 minSampleShading)
        : enableMSAA(enableMSAA),
          sampleCount(sampleCount),
          enableSampleShading(enableSampleShading),
          minSampleShading(minSampleShading)
    {}
};

/*
 * Defines the sets of stencil state.
 */
enum StencilFaceFlag {
    /*
     * only the front set of stencil state is updated.
     */
    STENCIL_FACE_FRONT = 0x00000001,

    /*
     * only the back set of stencil state is updated.
     */
    STENCIL_FACE_BACK = 0x00000002,

    /*
     * both sets of stencil state are updated.
     */
    STENCIL_FRONT_AND_BACK = 0x00000003
};

struct ClearValue {
    std::vector<Color> clearColors;
    f32 clearDepth = 1.0f;
    u32 clearStencil = 0;
};

enum BufferCreateUsage {
    BUFFER_VERTEX = 0x00000001,
    BUFFER_INDEX = 0x00000002,
    BUFFER_CONSTANT = 0x00000004,
    BUFFER_TRANSFER = 0x00000008
};

enum MemCreateUsage {
    MEMORY_UNKNOWN_USAGE = 0x00000000,
    MEMORY_GPU_ONLY = 0x00000001,
    MEMORY_CPU_ONLY = 0x00000002,
    MEMORY_CPU_TO_GPU = 0x00000004,
    MEMORY_GPU_TO_CPU = 0x00000008
};

enum ShaderSourceType {
    SPIRV,
    GLSL,
    HLSL,
};

enum QueueType {
    GRAPHICS,
    COMPUTE,
    TRANSFER
};

/*
 * Defines the dynamic states of the pipeline that can be changed during rendering.
 */
enum DynamicFlag {
    DYNAMIC_STATE_VIEWPORT = 1 << 0,
    DYNAMIC_STATE_SCISSOR = 1 << 1,
    DYNAMIC_STATE_LINE_WIDTH = 1 << 2,
    DYNAMIC_STATE_BLEND_CONSTANTS = 1 << 3,
    DYNAMIC_STATE_STENCIL_COMPARE_MASK = 1 << 4,
    DYNAMIC_STATE_STENCIL_REFERENCE = 1 << 5,
    DYNAMIC_STATE_STENCIL_WRITE_MASK = 1 << 6,
    DYNAMIC_STATE_STENCIL_TEST_ENABLE_EXT = 1 << 7,
    DYNAMIC_STATE_FLAG_MAX = 1 << 8,
};

NS_CG_END

#endif
