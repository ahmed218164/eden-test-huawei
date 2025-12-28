/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Define Matrix4 type for 3D space translations, scale and rotation operations.
 */

#ifndef MATRIX4_H
#define MATRIX4_H

#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Quaternion.h"

NS_CG_BEGIN

/*
 * Matrix row count.
 */
static const u32 MATRIX4_ROW_SIZE = 4;

/*
 * Matrix column count.
 */
static const u32 MATRIX4_COLUMN_SIZE = 4;

/*
 * Matrix size.
 */
static const u32 MATRIX4_SIZE = MATRIX4_ROW_SIZE * MATRIX4_COLUMN_SIZE;

/*
 * 4x4 matrix. Mostly used as transformation matrix for 3d calculations.
 * The matrix is a left hand matrix, row major with translations in the 4th row.
 * v * M1 * M2 * M3
*/
class CGKIT_EXPORT Matrix4 {
public:
    /*
     * A constructor used to initialize a 4 x 4 matrix to an identity matrix.
     */
    Matrix4();

    /*
     * A destructor.
     */
    ~Matrix4();

    /*
     * A constructor used to initialize a 4 x 4 matrix using 16 arguments.
     */
    Matrix4(f32 m00, f32 m01, f32 m02, f32 m03,
        f32 m10, f32 m11, f32 m12, f32 m13,
        f32 m20, f32 m21, f32 m22, f32 m23,
        f32 m30, f32 m31, f32 m32, f32 m33);

    /*
     * Obtains the value of (row, col) in a 4 x 4 matrix. The value range of row or col is 0-3.
     */
    f32& operator()(u32 row, u32 col);

    /*
     * Obtains the value of (row, col) in a 4 x 4 matrix. The value range of row or col is 0-3.
     */
    const f32& operator()(u32 row, u32 col) const;

    /*
     * Obtains the indexth element in a 4 x 4 matrix. The value range of index is 0-15.
     */
    f32& operator[](u32 index);

    /*
     * Obtains the indexth element in a 4 x 4 matrix. The value range of index is 0-15.
     */
    const f32& operator[](u32 index) const;

    /*
     * Overloads the = operator to assign a Matrix4 object to the current object.
     */
    Matrix4& operator=(const Matrix4& other);

    /*
     * Overloads the = operator to assign a floating-point number to the 4 x 4 matrix object,
     * with each element assigned a scalar.
     */
    Matrix4& operator=(const f32& scalar);

    /*
     * Overloads the + operator to add a Matrix4 object to the current object.
     */
    Matrix4 operator+(const Matrix4& other) const;

    /*
     * Overloads the += operator to add a Matrix4 object to the current object.
     */
    Matrix4& operator+=(const Matrix4& other);

    /*
     * Overloads the - operator to subtract a Matrix4 object from the current object.
     */
    Matrix4 operator-(const Matrix4& other) const;

    /*
     * Overloads the -= operator to subtract a Matrix4 object from the current object.
     */
    Matrix4& operator-=(const Matrix4& other);

    /*
     * Overloads the * operator to multiply a 4 x 4 matrix object by a Matrix4 object.
     */
    Matrix4 operator*(const Matrix4& other) const;

    /*
     * Overloads the *= operator to multiply the current object by a Matrix4 object.
     */
    Matrix4& operator*=(const Matrix4& other);

    /*
     * Overloads the * operator to rotate and translate a 3D vector using a 4 x 4 matrix object,
     * with the first three rows and first three columns as a rotation matrix and the first three
     * columns of the fourth row as a translation vector.
     */
    Vector3 operator*(const Vector3& v) const;

    /*
     * Overloads the * operator to transform a 4D vector using a 4 x 4 matrix object as the
     * transformation matrix.
     */
    Vector4 operator*(const Vector4& v) const;

    /*
     * Overloads the * operator to multiply a 4 x 4 matrix object by scalar element-wise.
     * The result Matrix4 object is returned.
     */
    Matrix4 operator*(const f32& scalar) const;

    /*
     * Overloads the *= operator to multiply a 4 x 4 matrix object by scalar element-wise.
     * The reference to the result matrix object is returned.
     */
    Matrix4& operator*=(const f32& scalar);

    /*
     * Overloads the == operator and returns true if the current object equals
     * the specified Matrix4 object.
     */
    bool operator==(const Matrix4& other) const;

    /*
     * operator!=(const Matrix4& other) constOverloads the != operator and returns true if the
     * current object does not equal the specified Matrix4 object.
     */
    bool operator!=(const Matrix4& other) const;

    /*
     * Sets a 4 x 4 matrix to an identity matrix.
     */
    Matrix4& MakeIdentity();

    /*
     * Computes the determinant of a 4 x 4 matrix.
     */
    f32 Determinant() const;

    /*
     * Computes the inverse of a 4 x 4 matrix. The result Matrix4 object is returned.
     */
    Matrix4 Inversed() const;

    /*
     * Computes the inverse of a 4 x 4 matrix. The reference to the result Matrix4 object
     * is returned.
     */
    Matrix4& Inverse();

    /*
     * Transposes a 4 x 4 matrix. The result Matrix4 object is returned.
     */
    Matrix4 Transposed() const;

    /*
     * Transposes a 4 x 4 matrix. The reference to the result matrix object is returned.
     */
    Matrix4& Transpose();

    /*
     * Sets a 3D translation vector in a 4 x 4 matrix.
     */
    Matrix4& SetTrans(const Vector3& v);

    /*
     * Obtains the 3D translation vector in a 4 x 4 matrix.
     */
    Vector3 GetTrans() const;

    /*
     * Sets a 3D scaling vector in a 4 x 4 matrix.
     */
    Matrix4& SetScale(const Vector3& scale);

    /*
     * Obtains the 3D scaling vector in a 4 x 4 matrix.
     */
    Vector3 GetScale() const;

    /*
     * Obtains the up vector in a 4 x 4 matrix.
     */
    Vector3 GetUpVector() const;

    /*
     * Obtains the up vector in a 4 x 4 matrix.
     */
    Vector3 GetRightVector() const;

    /*
     * Obtains the up vector in a 4 x 4 matrix.
     */
    Vector3 GetForwardVector() const;

    /*
     * Obtains a 3 x 3 rotation matrix of type Matrix4 based on a quaternion.
     * Since the rotation matrix is 3 x 3, the fourth row and fourth column of the Matrix4
     * object are padded with 0 and the diagonal is padded with 1.
     */
    Matrix4 GetRotationMatrix(const Quaternion& rot);

    /*
     * Obtains an Euler angle using the first three rows and first three columns of a 4 x 4 matrix
     * as the rotation matrix.
     */
    Vector3 GetRotation() const;

    /*
     * Sets first three columns and the first three rows of a 4 x 4 matrix to the rotation matrix
     * converted using an Euler angle, with the fourth row and the fourth column unchanged.
     */
    Matrix4& SetRotation(const Vector3& rotation);

    /*
     * Obtains a rotation matrix from an axis-angle pair and stores the result rotation matrix in
     * the first three rows and three columns of a 4 x 4 matrix.
     */
    Matrix4& MakeRotationAxisAngle(f32 radianAngle, const Vector3& axis);

    /*
     * Rotates a 4 x 4 matrix around by radianAngle around the axis.
     */
    Matrix4& Rotate(const Vector3& axis, f32 radianAngle);

    /*
     * Obtains a rotation matrix by rotating a 4 x 4 matrix an Euler angle, with the first three
     * columns and first three rows scaled based on scale and the first three columns in the fourth
     * row translated to position.
     */
    void MakeTransform(const Vector3& position, const Vector3& scale, const Vector3& rotate);

    /*
     * Obtains a rotation matrix from a quaternion orientation, with the first three columns and
     * first three rows scaled based on scale and the first three columns in the fourth row
     * translated to position.
     */
    void MakeTransform(const Vector3& position, const Vector3& scale, const Quaternion& orientation);

    /*
     * Obtains a translation vector position, a scaling vector scale, and an Euler angle rotate
     * from a 4 x 4 matrix.
     */
    void Decomposition(Vector3* position, Vector3* scale, Vector3* rotate) const;

    /*
     * Obtains a translation vector position, a scaling vector scale, and a quaternion rotation
     * from a 4 x 4 matrix.
     */
    void Decomposition(Vector3* position, Vector3* scale, Quaternion* rotation) const;

    /*
     * Rotates a 3D vector with the first three rows and first three columns of a 4 x 4 matrix as
     * the rotation matrix.
     */
    void Rotate(Vector3& vect) const;

    /*
     * Translates a 3D vector with the first three columns in the fourth row of a 4 x 4 matrix as
     * the translation vector.
     */
    void Translate(Vector3& vect) const;

    /*
     * Rotates and translates a 3D vector with the first three rows and first three columns
     * of a 4 x 4 matrix as the rotation matrix and the first three columns in the fourth row of
     * the matrix as the translation vector. The result 3D vector is saved in vec.
     */
    void Transform(Vector3& vect) const;

    /*
     * Rotates and translates a 3D vector with the first three rows and first three columns
     * of a 4 x 4 matrix as the rotation matrix and the first three columns in the fourth row
     * of the matrix as the translation vector. The result 3D vector is returned.
     */
    Vector3 Transform(const Vector3& in) const;

    /*
     * Rotates a 4D vector with a 4 x 4 matrix as the rotation matrix.
     */
    Vector4 Transform(const Vector4& in) const;

    /*
     * Converts a 4 x 4 matrix to a string formatted as:
     * [0.0, 0.0, 0.0, 0.0,
     * 0.0, 0.0, 0.0, 0.0,
     * 0.0, 0.0, 0.0, 0.0,
     * 0.0, 0.0, 0.0, 0.0]
     */
    String ToString() const;

public:
    union {
        /*
         * 4 x 4 matrix in 1D format.
         */
        f32 m[MATRIX4_ROW_SIZE * MATRIX4_COLUMN_SIZE];

        /*
         * 4 x 4 matrix in row and column format
         */
        f32 M[MATRIX4_ROW_SIZE][MATRIX4_COLUMN_SIZE];
    };

    /*
     * Zero matrix.
     */
    static const Matrix4 ZERO;

    /*
     * Identity matrix.
     */
    static const Matrix4 IDENTITY;
};

NS_CG_END

#endif