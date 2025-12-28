#ifndef SKELETON_ANIMATION_DEFINE_H
#define SKELETON_ANIMATION_DEFINE_H

struct Vector3d {
    float x;
    float y;
    float z;

    Vector3d(float xIn, float yIn, float zIn): x(xIn), y(yIn), z(zIn){}
};

struct Quaternion {
    float w;
    float x;
    float y;
    float z;

    Quaternion(float wIn, float xIn, float yIn, float zIn) : w(wIn), x(xIn), y(yIn), z(zIn) {}
};

// blend
enum JoystickButton {
    JOYSTICK_BUTTON_X,
    JOYSTICK_BUTTON_Y,
    JOYSTICK_BUTTON_A,
    JOYSTICK_BUTTON_B,
    JOYSTICK_BUTTON_NUM,
};

enum CharacterState {
    CHARACTER_STATE_IDLE = 0,
    CHARACTER_STATE_WALK = 1,
    CHARACTER_STATE_RUN = 2,
    CHARACTER_STATE_JUMP = 3,
    CHARACTER_STATE_OTHER = 4,
};

struct JoystickInfo {
    float horizontalAxis;
    float verticalAxis;
    bool buttons[JOYSTICK_BUTTON_NUM];
};

struct CharacterStateInfo {
    bool isJump;
    float jumpTime;
    int state;
};

struct BlendWeight {
    float streamWeight;
    float playSpeed;
    float clipLength;
};

// foot ik
struct Skeleton {
    int index;
    Vector3d position;
    Quaternion gRotation;
    Quaternion lRotation;
};

struct RayHitInfo {
    bool hit;
    Vector3d hitPoint;
    Vector3d hitNormal;
};

const int SKELETON_JOINT_NUM = 6;
const int SKELETON_LEG_NUM = 2;
struct SkeletonInfos {
    Skeleton skeletonData[SKELETON_JOINT_NUM];
    RayHitInfo rayInfo[SKELETON_LEG_NUM];
    Vector3d targetPoint[SKELETON_LEG_NUM];
    float footHeight;
    float footAngle;
    Vector3d pelvisOffset;
    bool isLeftFootIK;
};
#endif