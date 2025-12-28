/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Screen Quad.
 */
#ifndef SCREEN_QUAD_H
#define SCREEN_QUAD_H

#include "Rendering/Graphics/GraphicsRenderer.h"
#include "Core/Types.h"
#include "Math/Vector2.h"
#include "Rendering/Viewport.h"
#include "Scene/SceneManager.h"

NS_CG_BEGIN

class Texture;
class RenderPass;
class JobResource;
class DynamicBuffer;
class VertexDeclaration;
class MaterialInstance;

class CGKIT_EXPORT ScreenQuad {
public:
    ScreenQuad(const SceneManager* sceneManager);
    ~ScreenQuad();

    void Initialize();
    void Uninitialize();

    void UpdateViewport(const Viewport& viewport);
    bool UpdateVertexBuffer(const Viewport& viewport);
    void SetTexture(const String& name, Texture* texture);
    MaterialInstance* UpdateMaterial(const String& cgmatFile);
    void Render(JobResource* jobResource, RenderPass* renderPass);

private:
    void Destroy();
    void ViewPortToNdc(f32& x, f32& y, f32& w, f32& h);

private:
    MaterialInstance* m_materialInstance = nullptr;
    VertexDeclaration* m_declaration = nullptr;
    DynamicBuffer* m_vertexBuffer = nullptr;
    DynamicBuffer* m_texBuffer = nullptr;
    DynamicBuffer* m_indexBuffer = nullptr;
    std::vector<DynamicBuffer*> m_vertexBuffers;
    std::vector<Vector2> m_posList;
    std::vector<Vector2> m_texList;
    std::vector<u32> m_indexList = {0, 2, 1, 1, 2, 3};
    String m_cgmatFile = "";
    const SceneManager* m_sceneManager = nullptr;
};

NS_CG_END

#endif
