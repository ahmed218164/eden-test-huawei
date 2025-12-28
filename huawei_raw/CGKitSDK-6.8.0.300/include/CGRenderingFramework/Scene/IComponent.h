/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: IComponent utils.
 */

#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "Core/Types.h"
#include "Rendering/Graphics/GraphicsRenderer.h"

NS_CG_BEGIN

class SceneObject;
class SceneManager;

/*
 * A component base class used for component startup and update every frame.
 */
class CGKIT_EXPORT IComponent {
    friend class SceneObject;
RTTI_DEFINE(CGKit::IComponent);

public:
    IComponent(SceneObject* object);
    virtual ~IComponent();

    /*
     * Starts a component.
     */
    virtual void Start();

    /*
     * Updates a component every frame.
     */
    virtual void Update(f32 deltaTime);

    /*
     * Post updates a component every frame.
     */
    virtual void PostUpdate(f32 deltaTime);

    const SceneManager* GetSceneManager() const;


private:
    void Destroy();

protected:
    SceneObject* m_sceneObject = nullptr;
};

using ComponentList = std::list<IComponent*>;
using ComponentListIt = std::list<IComponent*>::iterator;

NS_CG_END

#endif