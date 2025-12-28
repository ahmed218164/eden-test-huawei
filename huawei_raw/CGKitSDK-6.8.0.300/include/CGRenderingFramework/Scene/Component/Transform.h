/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: A coordinate transformation class used to implement vector translation, rotation,
 * and scaling in different coordinate systems and define transformation matrices between different coordinate systems.
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Math/Matrix4.h"
#include "Scene/IComponent.h"

NS_CG_BEGIN

class SceneObject;

class CGKIT_EXPORT Transform : public IComponent {
    friend class SceneObject;
RTTI_DEFINE(CGKit::Transform);

public:
    /*
     * A constructor used to initialize the transform.
     */
    Transform(SceneObject* sceneObject = nullptr);

    /*
     * A destructor used to free memory.
     */
    virtual ~Transform();

    /*
     * Sets translation transformation in the local coordinate system. The argument is a translation vector.
     */
    void Translate(const Vector3& translate);

    /*
     * Sets rotation transformation in the local coordinate system.
     * The first argument is the rotation radian, and the second argument is the rotation axis.
     */
    void Rotate(f32 angle, const Vector3& axis);

    /*
     * Sets scaling transformation in the local coordinate system. The argument is a scaling vector.
     */
    void Scale(const Vector3& scale);

    /*
     * Sets the position of a scene object relative to the parent scene object in the local coordinate system.
     * The argument is a position of the Vector3 type.
     */
    void SetLocalPosition(const Vector3& position);

    /*
     * Sets the rotation vector (relative to the parent scene object) of a scene object in the local coordinate system.
     * The argument is a rotation vector of the Vector3 type, whose components are in radians.
     */
    void SetLocalRotation(const Vector3& rotation);

    /*
     * Sets the scaling vector (relative to the parent scene object) of a scene object in the local coordinate system.
     * The argument is a scaling vector of the Vector3 type.
     */
    void SetLocalScale(const Vector3& scale);

    /*
     * Sets the absolute position of a scene object in the world coordinate system.
     * The argument is a position of the Vector3 type in the given world coordinate system.
     */
    void SetWorldPosition(const Vector3& position);

    /*
     * Sets the rotation vector of a scene object in the world coordinate system. The argument is a rotation vector
     * of the Vector3 type in the given world coordinate system, whose components are in radians.
     */
    void SetWorldRotation(const Vector3& rotation);

    /*
     * Sets the scaling vector of a scene object in the world coordinate system. The argument is a scaling vector of
     * the Vector3 type in the given world coordinate system.
     */
    void SetWorldScale(const Vector3& scale);

    /*
     * Obtains the position of a scene object relative to the parent scene object in the local coordinate system.
     * The components are in radians.
     */
    const Vector3& GetLocalPosition() const;

    /*
     * Obtains the rotation vector of a scene object in the local coordinate system (relative to the parent
     * scene object). Components of the returns are in radians.
     */
    const Vector3& GetLocalRotation() const;

    /*
     * Obtains the scaling vector of a scene object in the local coordinate system (relative to the parent scene
     * object).
     */
    const Vector3& GetLocalScale() const;

    /*
     * Obtains the absolute position of a scene object in the world coordinate system.
     */
    const Vector3& GetWorldPosition() const;

    /*
     * Obtains the rotation vector of a scene object in the world coordinate system.
     * Components of the returns are in radians.
     */
    const Vector3& GetWorldRotation() const;

    /*
     * Obtains the scaling vector of a scene object in the world coordinate system.
     */
    const Vector3& GetWorldScale() const;

    /*
     * Sets the scaling vector (relative to the parent scene object) of a scene object in the local coordinate system.
     * The argument is a scaling vector of the Vector3 type.
     */
    const Matrix4& GetLocalToWorldMatrix() const;

    /*
     * Checks if translation transformation occurs.
     */
    bool IsTransChanged() const;

    /*
     * Clears the transformation flag.
     */
    void ClearTransFlags();

private:
    bool IsPositionChanged() const;
    bool IsRotationChanged() const;
    bool IsScaleChanged() const;

    void SetPositionChanged();
    void SetRotationChanged();
    void SetScaleChanged();

    void UpdateAll();
    void UpdateTransform();

    const Transform* GetParentTransform() const;

private:
    Vector3 m_localPosition;
    Vector3 m_localRotation;
    Vector3 m_localScale;

    Vector3 m_worldPosition;
    Vector3 m_worldRotation;
    Vector3 m_worldScale;

    Matrix4 m_localToWorldMatrix;
    u32 m_transChangeFlag;
};

NS_CG_END

#endif