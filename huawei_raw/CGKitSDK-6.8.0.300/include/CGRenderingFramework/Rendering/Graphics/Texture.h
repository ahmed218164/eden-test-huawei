/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2022. All rights reserved.
 * Description: Texture for rendering.
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Rendering/RenderCommon.h"
#include "Rendering/Graphics/Sampler.h"
#include "Rendering/Graphics/TextureViewCreateInfo.h"
#include "Math/Vector3.h"

NS_CG_BEGIN

struct SwapChainTextureInfo;

class SwapChain;

class GraphicsRenderer;

struct TextureCreateInfo {
    /*
     * Texture's filePath.
     */
    String filePath = "";

    /*
     * Texture's type.
     */
    ImageType imageType = ImageType::IMAGE_TYPE_2D;

    /*
     * Texture's pixelFormat.
     */
    PixelFormat format = PixelFormat::PIXEL_FORMAT_R8G8B8A8_UNORM;

    /*
     * Texture's sample count.
     */
    SampleCountFlagBits sampleCount = SampleCountFlagBits::SAMPLE_COUNT_1_BIT;

    /*
     * Texture's usage.
     */
    TextureUsage usage = TextureUsage::TEXTURE_USAGE_SAMPLED;

    /*
     * Image tiling.
     */
    ImageTiling imageTiling = ImageTiling::IMAGE_TILING_OPTIMAL;

    /*
     * Memory property flag bits.
     */
    u32 properties = MemoryPropertyFlagBits::MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

    /*
     * Texture's width.
     */
    u32 width = 0;

    /*
     * Texture's heigth.
     */
    u32 height = 0;

    /*
     * Testure's depth.
     */
    u32 depth = 1;

    /*
     * Texture' miplevels.
     */
    u8 mipLevels = 1;

    /*
     * Texture's layer count when using texture array.
     */
    u8 layerCount = 1;

    /*
     * is frameGraph path or not
     */
    bool isFrameGraph = false;
};

struct TextureExtent {
    u32 width = 0;
    u32 height = 0;
    u32 depth = 1 ;
};

struct TextureSubresLayers {
    /*
     * Texture' miplevels.
     */
    u32 mipLevel = 0;

    /*
     * are the starting layer and number of layers to copy.
     */
    u32 baseArrayLayer = 0;
    u32 layerCount = 1;
};

struct TextureUpdateRegion {
    /*
     * selects the initial x, y, z offsets in texels of the sub-region of the destination image data.
     */
    Vector3 textureOffset;

    /*
     * is the size in texels of the image to copy in width, height and depth.
     */
    TextureExtent textureExtent;
    TextureSubresLayers textureSubres;

    /*
     * is the offset in bytes from the start of the buffer object where the image data is copied from.
     */
    u32 bufferOffset = 0;

    /*
     * specify in texels a subregion of a larger two- or three-dimensional image in buffer memory,
     * and control the addressing calculations.
     */
    u32 bufferRowLength = 0;
    u32 bufferImageHeight = 0;
};

class CGKIT_EXPORT Texture {
    friend class SwapChain;
public:
    Texture() = default;
    explicit Texture(const GraphicsRenderer* graphicsRenderer);
    virtual ~Texture();
    Texture(const Texture& texture) = delete;
    Texture& operator=(const Texture& texture) = delete;

    bool Create(const TextureCreateInfo& textureInfo);
    bool Create(const TextureViewCreateInfo& textureViewInfo);
    inline const TextureCreateInfo& GetTextureCreateInfo() const { return m_baseInfo; }
    inline const TextureViewCreateInfo& GetTextureViewCreateInfo() const { return m_baseViewInfo; }
    void SetSampler(const Sampler* sampler);
    inline const Sampler* GetSampler() const { return m_sampler; }
    virtual bool Update(const u8* data, u32 dataSize) = 0;

    /*
     * To effect a partial update of the texture
     */
    virtual bool Update(const u8* const* buffers, const TextureUpdateRegion* regions, u32 count) = 0;
    virtual void Resize(u32 width, u32 height);
    virtual bool Resume() = 0;
    virtual void Pause() = 0;

private:
    virtual bool CreateImpl(const TextureCreateInfo& info) = 0;
    virtual bool CreateImpl(const TextureViewCreateInfo& info) = 0;
    void Destroy();

protected:
    static void Initialize(const SwapChainTextureInfo& info, Texture* texture);
    virtual void Initialize(const SwapChainTextureInfo& info) = 0;

    bool m_isTextureView = false;
    TextureCreateInfo m_baseInfo;
    TextureViewCreateInfo m_baseViewInfo;
    Sampler* m_sampler = nullptr;
    const GraphicsRenderer* m_graphicsRenderer = nullptr;
};

NS_CG_END

#endif
