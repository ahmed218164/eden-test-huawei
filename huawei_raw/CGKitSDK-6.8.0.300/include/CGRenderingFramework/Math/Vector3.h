/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Define Vector3 type for 3D point and vector operations.
 */

#ifndef VECTOR3_H
#define VECTOR3_H

#include "Math/Math.h"

NS_CG_BEGIN

/*
 * A 3D vector class for negation, addition, subtraction, multiplication, division, dot product,
 * and cross product of 3D vectors.
 */
class CGKIT_EXPORT Vector3 {
public:
    /*
     * A constructor used to initialize the X, Y, and Z components of a 3D vector to 0, respectively.
     */
    Vector3();

    /*
     * A constructor used to initialize the X, Y, and Z components of a 3D vector to nx, ny, and nz,
     * respectively.
     */
    Vector3(f32 nx, f32 ny, f32 nz);

    /*
     * A destructor.
     */
    ~Vector3();

    /*
     * Overloads the - operator to obtain the negative values of the X, Y, and Z components of the
     * current object.
     */
    inline Vector3 operator-() const;

    /*
     * Overloads the assignment operator to assign a Vector3 object to the current object.
     */
    inline Vector3& operator=(const Vector3& other);

    /*
     * Overloads the + operator to add a Vector3 object to the current object.
     */
    inline Vector3 operator+(const Vector3& other) const;

    /*
     * Overloads the += operator to add a Vector3 object to the current object.
     */
    inline Vector3& operator+=(const Vector3& other);

    /*
     * Overloads the - operator to subtract a Vector3 object from the current object.
     */
    inline Vector3 operator-(const Vector3& other) const;

    /*
     * Overloads the -= operator to subtract a Vector3 object from the current object.
     */
    inline Vector3& operator-=(const Vector3& other);

    /*
     * Overloads the * operator to multiply the current object and the specified floating-point
     * object.
     */
    inline Vector3 operator*(f32 v) const;

    /*
     * Overloads the *= operator to multiply the current object and the specified floating-point
     * object.
     */
    inline Vector3& operator*=(f32 v);

    /*
     * Overloads the / operator to divide the current object by the specified floating-point object.
     */
    inline Vector3 operator/(f32 v) const;

    /*
     * Overloads the /= operator to divide the current object by the specified floating-point object.
     */
    inline Vector3& operator/=(f32 v);

    /*
     * Overloads the == operator and returns true if the current object equals the specified
     * Vector3 object.
     */
    inline bool operator==(const Vector3& other) const;

    /*
     * Overloads the != operator and returns true if the current object does not equal the
     * specified Vector3 object.
     */
    inline bool operator!=(const Vector3& other) const;

    /*
    * Overloads the >= operator and returns true if the current objectgreater than or equal to the
    * specified Vector3 object.
    */
    inline bool operator >= (const Vector3& other) const
    {
        return ((x >= other.x) && (y >= other.y) && (z >= other.z));
    }

    /*
     * Computes the modulus of a 3D vector.
     */
    f32 Length() const;

    /*
     * Computes the dot product of two 3D vectors.
     */
    f32 Dot(const Vector3& other) const;

    /*
     * Computes the cross product of two 3D vectors.
     */
    Vector3 Cross(const Vector3& p) const;

    /*
     * Returns the reference to a normalized 3D vector.
     */
    Vector3& Normalize();

    /*
     * Returns a normalized 3D vector.
     */
    Vector3 Normalized() const;

    /*
     * Converts a 3D vector to a string formatted "(x, y, z)".
     */
    String ToString() const;

public:
    /*
     * X component of a 3D vector.
     */
    f32 x;

    /*
     * Y component of a 3D vector.
     */
    f32 y;

    /*
     * Z component of a 3D vector.
     */
    f32 z;

    /*
     * Zero vector.
     */
    static const Vector3 ZERO;

    /*
     * All components equal to 1.
     */
    static const Vector3 ONE;

    /*
     * Unit vector on the x-axis.
     */
    static const Vector3 UNIT_X;

    /*
     * Unit vector on the y-axis.
     */
    static const Vector3 UNIT_Y;

    /*
     * Unit vector on the z-axis.
     */
    static const Vector3 UNIT_Z;

    /*
     * Unit vector in the negative direction of the x-axis.
     */
    static const Vector3 NEGATIVE_UNIT_X;

    /*
     * Unit vector in the negative direction of the y-axis.
     */
    static const Vector3 NEGATIVE_UNIT_Y;

    /*
     * Unit vector in the negative direction of the z-axis.
     */
    static const Vector3 NEGATIVE_UNIT_Z;
};

NS_CG_END

#include "Math/Vector3.inl"

#endif