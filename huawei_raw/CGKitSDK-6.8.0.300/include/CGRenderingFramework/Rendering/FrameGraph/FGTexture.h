#ifndef FGTEXTURE_H
#define FGTEXTURE_H

#include "Core/Global.h"
#include "Core/Types.h"
#include "Rendering/RenderCommon.h"
#include "Rendering/Graphics/Texture.h"
#include "Rendering/FrameGraph/FGCommon.h"
#include "Rendering/FrameGraph/ResourceAllocator.h"

NS_CG_BEGIN

class CGKIT_EXPORT FGTexture {
public:
    struct Descriptor {
        ImageType imageType = IMAGE_TYPE_2D;
        PixelFormat format = PIXEL_FORMAT_R8G8B8A8_UNORM;
        SampleCountFlagBits sampleCount = SAMPLE_COUNT_1_BIT;
        u32 width = 128;
        u32 height = 128;
        u32 depth = 1;
        u8 mipLevels = 1;
        u8 layerCount = 1;
    };

    ~FGTexture();

    /**
     * set Graphics Renderer
     */
    void SetGraphicsRenderer(GraphicsRenderer* graphicsRenderer)
    {
        this->m_graphicsRenderer = graphicsRenderer;
    }

    /**
     * get backend texture
     */
    const Texture* GetBackendTexture() const
    {
        return m_textureHandle.resource;
    }

    /**
     * import external texture
     */
    void ImportTexture(Texture* texture);

    /*
     * create texture
     */
    void Create(const Descriptor& descriptor, ResourceUsage usage);

    /**
     * destroy texture
     */
    void Destroy();

private:
    GraphicsRenderer* m_graphicsRenderer;

    struct TextureFactory {
        Texture* Create(const TextureCreateInfo& info, GraphicsRenderer* graphicsRenderer);
        void Destroy(Texture* res);
    };

    struct TextureHasher {
        size_t Compute(const TextureCreateInfo& info);
    };

    using FGTextureAllocator = ResourceAllocator<Texture, TextureCreateInfo, TextureFactory, TextureHasher>;
    using TextureHandle = FGTextureAllocator::ResourceHandle;
    static FGTextureAllocator s_TextureAllocator;
    bool m_imported = false;
    TextureHandle m_textureHandle;
};

NS_CG_END

#endif