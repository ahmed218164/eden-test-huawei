/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Model.
 */

#ifndef MODEL_H
#define MODEL_H

#include "Resource/IResource.h"
#include "Rendering/VertexAttribute.h"
#include "Scene/SceneManager.h"
#include "Rendering/Graphics/GraphicsRenderer.h"

NS_CG_BEGIN

class Mesh;

/*
 * A model resource class that inherits from IResource, used to generate a complete Mesh instance
 * during the resource reading process.
 */
class CGKIT_EXPORT Model : public IResource {
public:
    /*
     * A constructor.
     */
    Model(const GraphicsRenderer* graphicsRenderer, const String& filePath);
    Model& operator=(const Model& rhs) = delete;
    Model(const Model& rhs) = delete;

    /*
     * A destructor
     */
    virtual ~Model();

    /*
     * Rebuilds model resources when the app is switched from the background to the foreground.
     */
    virtual bool Resume() override;

    /*
     * Destroys model resources when the app is switched from the foreground to the background.
     */
    virtual void Pause() override;

    /*
     * Creates a mesh model. If a mesh model already exists, the pointer to the existing mesh is
     * returned. Otherwise, a new mesh model is created and the pointer to the new mesh model is
     * returned.
     */
    Mesh* Create();

    /*
     * Obtains a mesh model.
     */
    const Mesh* GetMesh() const;

private:
    void Destroy();

private:
    Mesh* m_mesh = nullptr;
    const GraphicsRenderer* m_graphicsRenderer = nullptr;
};

namespace ModelHelper {
    CGKIT_EXPORT Model* CreateModel(SceneManager* sceneManager, const String& name,
        const std::vector<VertexAttribute>& vertexAttributes);
    CGKIT_EXPORT void DeleteModel(SceneManager* sceneManager, Model* model);
}

NS_CG_END

#endif