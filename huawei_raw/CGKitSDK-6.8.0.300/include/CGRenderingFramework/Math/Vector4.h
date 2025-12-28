/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Define Vector4 type for 3D point and vector operations.
 */

#ifndef VECTOR4_H
#define VECTOR4_H

#include "Math/Math.h"

NS_CG_BEGIN

/*
 * A 4D vector class for negation, addition, subtraction, multiplication, division, and dot product
 * of 4D vectors.
 */
class CGKIT_EXPORT Vector4 {
public:
    /*
     * A constructor used to initialize the X, Y, Z, and W components of a 4D vector to 0,
     * respectively.
     */
    Vector4();

    /*
     * A constructor used to initialize the X, Y, Z, and W components of a 4D vector to
     * nx, ny, nz, and nw, respectively.
     */
    Vector4(f32 nx, f32 ny, f32 nz, f32 nw);

    /*
     * A destructor.
     */
    ~Vector4();

    /*
     * Overloads the - operator to obtain the negative values of the X, Y, Z, and W components of
     * the current object.
     */
    inline Vector4 operator-() const;

    /*
     * Overloads the assignment operator to assign a Vector4 object to the current object.
     */
    inline Vector4& operator=(const Vector4& other);

    /*
     * Overloads the + operator to add a Vector4 object to the current object.
     */
    inline Vector4 operator+(const Vector4& other) const;

    /*
     * Overloads the += operator to add a Vector4 object to the current object.
     */
    inline Vector4& operator+=(const Vector4& other);

    /*
     * Overloads the - operator to subtract a Vector4 object from the current object.
     */
    inline Vector4 operator-(const Vector4& other) const;

    /*
     * Overloads the -= operator to subtract a Vector4 object from the current object.
     */
    inline Vector4& operator-=(const Vector4& other);

    /*
     * Overloads the * operator to multiply the current object by a floating-point object.
     */
    inline Vector4 operator*(f32 v) const;

    /*
     * Overloads the *= operator to multiply the current object by a floating-point object.
     */
    inline Vector4& operator*=(f32 v);

    /*
     * Overloads the / operator to divide the current object by the specified floating-point object.
     */
    inline Vector4 operator/(f32 v) const;

    /*
     * Overloads the /= operator to divide the current object by the specified floating-point object.
     */
    inline Vector4& operator/=(f32 v);

    /*
     * Overloads the == operator and returns true if the current object equals the specified
     * Vector4 object.
     */
    inline bool operator==(const Vector4& other) const;

    /*
     * Overloads the != operator and returns true if the current object does not equal the
     * specified Vector4 object.
     */
    inline bool operator!=(const Vector4& other) const;

    /*
     * Computes the modulus of a 4D vector.
     */
    f32 Length() const;

    /*
     * Computes the dot product of two 4D vectors.
     */
    f32 Dot(const Vector4& v) const;

    /*
     * Returns the reference to a normalized 4D vector.
     */
    Vector4& Normalize();

    /*
     * Returns a normalized 4D vector.
     */
    Vector4 Normalized() const;

    /*
     * Converts a 4D vector to a string formatted "(x, y, z, w)".
     */
    String ToString() const;

public:
    /*
     * X component of a 4D vector.
     */
    f32 x;

    /*
     * y component of a 4D vector.
     */
    f32 y;

    /*
     * z component of a 4D vector.
     */
    f32 z;

    /*
     * w component of a 4D vector.
     */
    f32 w;

    /*
     * Zero vector.
     */
    static const Vector4 ZERO;

    /*
     * All components equal to 1.
     */
    static const Vector4 ONE;
};

NS_CG_END

#include "Math/Vector4.inl"

#endif