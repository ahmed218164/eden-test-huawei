/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Animation resources manager.
 */

#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "Scene/IComponent.h"
#include "Rendering/RenderCommon.h"

NS_CG_BEGIN

class AnimationController;
class AnimationClip;

class CGKIT_EXPORT AnimationComponent : public IComponent {
    friend class SceneObject;
    friend class GLTFObjectCreator;
RTTI_DEFINE(CGKit::AnimationComponent);

public:
    AnimationComponent(SceneObject* object);
    virtual ~AnimationComponent();
    AnimationComponent operator=(const AnimationComponent& animationComponent) = delete;
    AnimationComponent(const AnimationComponent& animationComponent) = delete;

    /*
     * Play the animation with name.
     */
    bool Play(const String& name);

    /*
     * Pause the animation.
     */
    void Pause();

    /*
     * Stop the animation.
     */
    void Stop();

    /*
     * Update the animation.
     */
    virtual void Update(f32 deltaTime) override;

    /*
     * Sets animation play speed.
     */
    void SetSpeed(f32 speed);

    /*
     * Obtains animation play speed.
     */
    f32 GetSpeed() const;

    /*
     * Sets animation play mode (Loop, Once, PingPong).
     */
    void SetPlayMode(const AnimationPlayMode mode);

    /*
     * Obtains animation play mode (Loop, Once, PingPong).
     */
    AnimationPlayMode GetPlayMode() const;

private:
    void Destroy();
    void AddAnimationClip(const AnimationClip* animationClip, const SceneObject* rootObject);

    AnimationController* m_controller = nullptr;
    std::map<String, AnimationClip*> m_animationClips;
};

NS_CG_END

#endif
