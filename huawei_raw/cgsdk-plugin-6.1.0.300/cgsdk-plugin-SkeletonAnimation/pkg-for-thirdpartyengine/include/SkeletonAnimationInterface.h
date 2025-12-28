#ifndef SKELETON_ANIMATION_INTERFACE_H
#define SKELETON_ANIMATION_INTERFACE_H

#include "SkeletonAnimationDefine.h"

#ifdef __ANDROID__
#define EXPORT __attribute__((visibility("default")))
#else
#define EXPORT _declspec(dllexport)
#endif // __ANDROID__

class SekletonAnimationInterface {
public:
    SekletonAnimationInterface() {}
    virtual ~SekletonAnimationInterface() {}

    virtual bool InitSkeletonAnimation() = 0;
    virtual void DeinitSkeletonAnimation() = 0;
    virtual void UpdateBlendState(JoystickInfo* stickInfo, CharacterStateInfo* characterInfo,
        BlendWeight* weight, int weightNum) = 0;
    // foot ik
    virtual void UpdateFootIKState(JoystickInfo *stickInfo, SkeletonInfos *skeletonInfo) = 0;
};

extern "C" EXPORT SekletonAnimationInterface *CreateSkeletonAnimationInstance();
#endif