/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Define Vector2 type for 2D point and vector operations.
 */

#ifndef VECTOR2_H
#define VECTOR2_H

#include "Math/Math.h"

NS_CG_BEGIN

/*
 * A 2D vector class for negation, addition, subtraction, multiplication, division, and dot product
 * of 2D vectors.
 */
class CGKIT_EXPORT Vector2 {
public:
    /*
     * A constructor used to initialize the X and Y components of a 2D vector to 0, respectively.
     */
    Vector2();

    /*
     * A constructor used to initialize the X and Y components of a 2D vector to nx and ny,
     * respectively.
     */
    Vector2(f32 nx, f32 ny);

    /*
     * A destructor.
     */
    ~Vector2();

    /*
     * Overloads the - operator to obtain the negative values of the X and Y components of the
     * current object.
     */
    inline Vector2 operator-() const;

    /*
     * Overloads the assignment operator to assign a Vector2 object to the current object.
     */
    inline Vector2& operator=(const Vector2& other);

    /*
     * Overloads the + operator to add a Vector2 object to the current object.
     */
    inline Vector2 operator+(const Vector2& other) const;

    /*
     * Overloads the += operator to add a Vector2 object to the current object.
     */
    inline Vector2& operator+=(const Vector2& other);

    /*
     * Overloads the - operator to subtract a Vector2 object from the current object.
     */
    inline Vector2 operator-(const Vector2& other) const;

    /*
     * Overloads the -= operator to subtract a Vector2 object from the current object.
     */
    inline Vector2& operator-=(const Vector2& other);

    /*
     * Overloads the * operator to multiply the current object by a floating-point object.
     */
    inline Vector2 operator*(f32 v) const;

    /*
     * Overloads the *= operator to multiply the current object by a floating-point object.
     */
    inline Vector2& operator*=(f32 v);

    /*
     * Overloads the / operator to divide the current object by the specified floating-point object.
     */
    inline Vector2 operator/(f32 v) const;

    /*
     * Overloads the /= operator to divide the current object by a floating-point object.
     */
    inline Vector2& operator/=(f32 v);

    /*
     * Overloads the == operator and returns true if the current object equals the specified
     * Vector2 object.
     */
    inline bool operator==(const Vector2& other) const;

    /*
     * Overloads the != operator and returns true if the current object does not equal the
     * specified Vector2 object.
     */
    inline bool operator!=(const Vector2& other) const;

    /*
     * Computes the modulus of a 2D vector.
     */
    f32 Length() const;

    /*
     * Computes the dot product of two 2D vectors.
     */
    f32 Dot(const Vector2& other) const;

    /*
     * Normalizes a 2D vector.
     */
    Vector2& Normalize();

    /*
     * Converts a 2D vector to a string formatted "(x, y)".
     */
    String ToString() const;

 public:
    /*
     * X component of a 2D vector.
     */
    f32 x;

    /*
     * Y component of a 2D vector.
     */
    f32 y;

    /*
     * Zero vector.
     */
    static const Vector2 ZERO;

    /*
     * Both components equal to 1.
     */
    static const Vector2 ONE;

    /*
     * X component equal to 0 and the Y component equal to 1.
     */
    static const Vector2 UP;

    /*
     * X component equal to 0 and the Y component equal to -1.
     */
    static const Vector2 DOWN;

    /*
     * X component equal to �C1 and the Y component equal to 0.
     */
    static const Vector2 LEFT;

    /*
     * X component equal to 1 and the Y component equal to 0
     */
    static const Vector2 RIGHT;

    /*
     * Unit vector on the x-axis.
     */
    static const Vector2 UNIT_X;

    /*
     * Unit vector on the y-axis.
     */
    static const Vector2 UNIT_Y;

    /*
     * Unit vector in the negative direction of the x-axis.
     */
    static const Vector2 NEGATIVE_UNIT_X;

    /*
     * Unit vector in the negative direction of the y-axis.
     */
    static const Vector2 NEGATIVE_UNIT_Y;
};

NS_CG_END

#include "Math/Vector2.inl"

#endif