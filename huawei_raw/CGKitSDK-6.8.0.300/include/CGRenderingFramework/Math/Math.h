/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Define basic math functions and const data.
 */

#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <climits>

#include "Core/Types.h"
#include "Core/STDHeaders.h"

NS_CG_BEGIN

namespace Math {
/*
 *  Unsigned 32-bit invalid value.
 */
const u32 INVALID_U32 = 0Xffffffff;
/*
 * The smallest 32-bit floating-point number.
 */
const f32 FLOAT_MIN = 1.17549435e-38F;

/*
 * The biggest 32-bit floating-point number.
 */
const f32 FLOAT_MAX = 3.402823466E+38F;

/*
 * The smallest 32-bit floating-point number just greater than 0.
 */
const f32 EPSILON = std::numeric_limits<f32>::epsilon();

/*
 * The smallest 64-bit floating-point number just greater than 0.
 */
const f64 EPSILON_F64 = std::numeric_limits<f64>::epsilon();

/*
 * 32-bit floating-point PI.
 */
const f32 PI = 3.14159265359f;

/*
 * 32-bit floating-point number for the reciprocal of PI.
 */
const f32 RECIPROCAL_PI = 1.0f / PI;

/*
 * Half of PI.
 */
const f32 HALF_PI = PI / 2.0f;

/*
 * Twice of PI.
 */
const f32 TWO_PI = 2.0f * PI;

/*
 * 64-bit floating-point PI.
 */
const f64 PI64 = 3.1415926535897932384626433832795028841971693993751;

/*
 * 64-bit floating-point number for the reciprocal of PI.
 */
const f64 RECIPROCAL_PI64 = 1.0 / PI64;

/*
 * Returns true if a equals b.
 */
template <class T>
inline bool Equals(const T& a, const T& b)
{
    return a == b;
}

/*
 * Returns true if a equals b, taking possible rounding errors into account.
 */
inline bool Equals(const s32 a, const s32 b)
{
    return a == b;
}

/*
 * Returns true if a equals b, taking possible rounding errors into account.
 */
inline bool Equals(const s64 a, const s64 b)
{
    return a == b;
}

/*
 * Returns true if a equals b, taking possible rounding errors into account.
 */
inline bool Equals(const f32 a, const f32 b, const f32 tolerance = EPSILON)
{
    return (a + tolerance >= b) && (a - tolerance <= b);
}

/*
 * Returns true if a equals b, taking possible rounding errors into account.
 */
inline bool Equals(const f64 a, const f64 b, const f64 tolerance = EPSILON_F64)
{
    return (a + tolerance >= b) && (a - tolerance <= b);
}

/*
 * Returns true if a equals b, taking possible rounding errors into account.
 */
inline bool Equals(u32 a, u32 b)
{
    return a == b;
}

/*
 * Returns the square root of a 32-bit floating-point number.
 */
inline f32 Sqrt(const f32 f)
{
    if (f < 0) {
        return FLOAT_MAX;
    }
    return sqrtf(f);
}

/*
 * Returns the square root of a 64-bit floating-point number.
 */
inline f64 Sqrt(const f64 f)
{
    if (f < 0) {
        return FLOAT_MAX;
    }
    return sqrt(f);
}

/*
 * Returns the reciprocal of the square root of a 32-bit floating-point number.
 */
inline f32 ReciprocalSqrt(const f32 x)
{
    f32 sqrtResult = sqrtf(x);
    if (Equals(sqrtResult, 0.0f)) {
        return FLOAT_MAX;
    }

    return 1.0f / sqrtf(x);
}

/*
 * Returns the reciprocal of the square root of a 64-bit floating-point number.
 */
inline f64 ReciprocalSqrt(const f64 x)
{
    f64 sqrtResult = sqrt(x);
    if (Equals(sqrtResult, 0.0)) {
        return FLOAT_MAX;
    }

    return 1.0f / sqrt(x);
}

/*
 * Returns the reciprocal of a 32-bit floating-point number.
 */
inline f32 Reciprocal(const f32 f)
{
    if (Equals(f, 0.0f)) {
        return FLOAT_MAX;
    }
    return 1.0f / f;
}

/*
 * Returns the reciprocal of a 64-bit floating-point number.
 */
inline f64 Reciprocal(const f64 f)
{
    if (Equals(f, 0.0)) {
        return FLOAT_MAX;
    }
    return 1.0f / f;
}

/*
 * Returns a 32-bit floating-point random number within the range 0�1.
 */
inline f32 UnitRandom()
{
    return f32(rand()) / RAND_MAX;
}

/*
 * Returns a 32-bit floating-point random number within a certain range.
 */
inline f32 RangeRandom(f32 low, f32 high)
{
    return (high - low) * UnitRandom() + low;
}

/*
 * Returns a 32-bit floating-point random number within a certain range.
 */
inline f32 Pow(f32 base, f32 exp)
{
    return powf(base, exp);
}

}

NS_CG_END

#endif