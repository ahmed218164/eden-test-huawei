/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Tween manager.
 */

#ifndef TWEEN_MANAGER_H
#define TWEEN_MANAGER_H

#include "Core/Singleton.h"
#include "Scene/Component/Transform.h"
#include "Rendering/MaterialInstance.h"
#include "Math/Color.h"

NS_CG_BEGIN

class Tween;

class CGKIT_EXPORT TweenManager : public Singleton<TweenManager> {
    friend class Singleton<TweenManager>;
public:
    /*
     * Initializing tween-related information.
     */
    void Initialize();

    /*
     * releases all resources in the Tween manager.
     */
    void Uninitialize();

    /*
     * The Tween information is updated in each frame.
     * After the Tween execution is complete, the Tween is released.
     */
    void Update(f32 delta);

    /*
     * Interface for implementing the moving animation effect.
     */
    Tween* GetTweenTransMove(
        Transform& trans, const Vector3& to, f32 duration, f32 startTime = 0, bool isFrom = false);

    /*
     * Implements the rotation animation effect interface.
     */
    Tween* GetTweenTransRotate(
        Transform& trans, const Vector3& to, f32 duration, f32 startTime = 0, bool isFrom = false);

    /*
     * Implements the scaling animation effect interface.
     */
    Tween* GetTweenTransScale(
        Transform& trans, const Vector3& to, f32 duration, f32 startTime = 0, bool isFrom = false);

    /*
     * Implements the material color change animation effect interface.
     */
    Tween* GetTweenMaterialsColor(
        MaterialInstance& materialInstance, const Color& to, f32 duration,
        f32 startTime = 0, bool isFrom = false);

    /*
     * Implement the animation effect interface of path curve movement.
     */
    Tween* GetTweenPath(
        Transform& transform, std::vector<Vector3>& to, f32 duration, f32 startTime = 0);

    /*
     * Implement the animation effect interface of material transparency changes.
     */
    Tween* GetTweenDiffuseColor(
        MaterialInstance& materialInstance, const Vector4& to, f32 duration, f32 startTime = 0,
        bool isFrom = false);

    /*
     * Implements the change animation effect interface of user-defined attributes.
     */
    template<typename T1, typename T2>
    Tween* GetTween(
        ValueGetter<T1> getter,  ValueSetter<T1> setter, const T2& to, f32 duration,
        f32 startTime = 0, bool isFrom = false);
public:
    const static u32 TWEENS_MAX = 250;
    std::vector<Tween*> m_tweens;
};

#define gTweenManager TweenManager::GetSingleton()
NS_CG_END

#endif