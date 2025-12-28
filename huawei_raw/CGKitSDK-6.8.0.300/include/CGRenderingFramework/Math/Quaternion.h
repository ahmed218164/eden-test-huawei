/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Define quaternion for rotation operations.
 */

#ifndef QUATERNION_H
#define QUATERNION_H

#include "Math/Vector3.h"
#include "Math/Vector4.h"

NS_CG_BEGIN

/*
 * A quaternion class for assignment, comparison, addition, subtraction, multiplication, division,
 * dot product, inversion, normalization, conversion to axis-angle pairs,
 * and conversion to Euler angles.
 */
class CGKIT_EXPORT Quaternion {
public:
    /*
     * A constructor used to initialize the X, Y, and Z components of a quaternion to 0 and the W
     * component to 1, respectively.
     */
    Quaternion();

    /*
     * A destructor.
     */
    ~Quaternion();

    /*
     * A constructor used to initialize the X, Y, Z, and W components of a quaternion to nx, ny, nz,
     * and nw, respectively.
     */
    Quaternion(f32 nx, f32 ny, f32 nz, f32 nw);

    /*
     * A constructor used Vector4 to initialize the X, Y, Z, and W components of a quaternion.
     */
    Quaternion(const Vector4& vec);

    /*
     * Overloads the assignment operator to assign a Quaternion object to the current object.
     */
    Quaternion& operator=(const Quaternion& other);

    /*
     * Overloads the + operator to add a Quaternion object to the current object.
     */
    Quaternion operator+(const Quaternion& other) const;

    /*
     * Overloads the - operator to subtract a Quaternion object from the current object.
     */
    Quaternion operator-(const Quaternion& other) const;

    /*
     * Overloads the * operator to multiply the current object by a Quaternion object.
     */
    Quaternion operator*(const Quaternion& other) const;

    /*
     * Overloads the *= operator to subtract a Quaternion object from the current object.
     */
    Quaternion& operator*=(const Quaternion& other);

    /*
     * Overloads the * operator to rotate a 3D vector by the radian represented by a quaternion
     * around the axis represented by a quaternion.
     */
    Vector3 operator*(const Vector3& value) const;

    /*
     * Overloads the * operator to multiply the current object by a floating-point number.
     */
    Quaternion operator*(f32 s) const;

    /*
     * Overloads the *= operator to multiply the current object by a floating-point number.
     */
    Quaternion& operator*=(f32 s);

    /*
     * Overloads the == operator and returns true if the current object equals the specified
     * Quaternion object.
     */
    bool operator==(const Quaternion& other) const;

    /*
     * Overloads the != operator and returns true if the current object does not equal the
     * specified Quaternion object.
     */
    bool operator!=(const Quaternion& other) const;

    /*
     * Sets the component values of a Quaternion object.
     */
    Quaternion& Set(f32 nx, f32 ny, f32 nz, f32 nw);

    /*
     * Sets a new quaternion based on an Euler angle. The argument is in radians.
     */
    Quaternion& Set(const Vector3& euler);

    /*
     * Returns the reference to the inversion of a quaternion.
     */
    Quaternion& Inverse();

    /*
     * Returns the inversion of a quaternion.
     */
    Quaternion Inversed() const;

    /*
     * Returns the reference to the normalized quaternion.
     */
    Quaternion& Normalize();

    /*
     * Returns the normalized quaternion.
     */
    Quaternion Normalized() const;

    /*
     * Performs dot product on two quaternions.
     */
    f32 Dot(const Quaternion& other) const;

    /*
     * Converts an axis-angle pair to a quaternion.
     */
    Quaternion& FromAngleAxisToQuat(f32 radianAngle, const Vector3& axis);

    /*
     * Converts a quaternion into an axis-angle pair.
     */
    void FromQuatToAngleAxis(f32& angradianAnglele, Vector3& axis) const;

    /*
     * Flip z axis.
     */
    Quaternion& ReverseZ();

    /*
     * Converts a quaternion into an Euler angle.
     */
    Vector3 ToEuler() const;

    /*
     * Converts a quaternion to a string formatted "(x, y, z, w)".
     */
    String ToString() const;

public:
    /*
     * X component, imaginary part of a quaternion.
     */
    f32 x;

    /*
     * Y component, imaginary part of a quaternion.
     */
    f32 y;

    /*
     * Z component, imaginary part of a quaternion.
     */
    f32 z;

    /*
     * W component, imaginary part of a quaternion.
     */
    f32 w;

    /*
     * The real part and the imaginary part both equal to 0.
     */
    static const Quaternion ZERO;

    /*
     * The imaginary part equals to 0, and the real part equals to 1.
     */
    static const Quaternion IDENTITY;
};

NS_CG_END

#endif
