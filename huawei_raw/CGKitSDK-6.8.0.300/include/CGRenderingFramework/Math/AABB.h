/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: A mesh bounding box (BBox) class used to assign values to and compare objects in a BBox, and obtain the
 * minimum, maximum, center, and corner coordinates of the BBox.
 */

#ifndef AABB_H
#define AABB_H

#include "Math/Vector3.h"

NS_CG_BEGIN

/*
 * Enumeration of the eight corners of the mesh bounding box.
 */
enum CornerType {
    CORNER_TYPE_BACK_LEFT_BOTTOM = 0,
    CORNER_TYPE_BACK_LEFT_TOP = 1,
    CORNER_TYPE_FRONT_LEFT_BOTTOM = 2,
    CORNER_TYPE_FRONT_LEFT_TOP = 3,
    CORNER_TYPE_BACK_RIGHT_BOTTOM = 4,
    CORNER_TYPE_BACK_RIGHT_TOP = 5,
    CORNER_TYPE_FRONT_RIGHT_BOTTOM = 6,
    CORNER_TYPE_FRONT_RIGHT_TOP = 7,

    CORNER_TYPE_MAX,
};

class CGKIT_EXPORT AABB {
public:
    /*
     * A constructor used to initialize the minimum and maximum coordinates and the pointers to the eight corner
     * coordinates of the BBox.
     */
    AABB();

    /*
     * A copy constructor.
     */
    AABB(const AABB& other);

    /*
     * A destructor used to free memory.
     */
    ~AABB();

    /*
     * Overloads the assignment operator to assign an AABB object to the current object.
     */
    AABB& operator = (const AABB& other);

    /*
     * Overloads the == operator and returns true if the current object equals the specified AABB object.
     */
    bool operator == (const AABB& other) const;

    /*
     * Overloads the != operator and returns true if the current object does not equal the specified AABB object.
     */
    bool operator != (const AABB& other) const;

    /*
     * Obtains the vertex in the specified direction. For a dimension in the normal argument greater than 0, the
     * corresponding dimension is set to the maximum value of the dimension based on the center coordinates of the BBox.
     */
    Vector3 GetMinDistanceVertex(const Vector3& normal) const;

    /*
     * Obtains the vertex in the opposite direction of the specified direction. For a dimension in the normal argument
     * less than 0, the corresponding dimension is set to the maximum value of the dimension based on the center
     * coordinates of the BBox.
     */
    Vector3 GetMaxDistanceVertex(const Vector3& normal) const;

    /*
     * Obtains the minimum coordinates of the BBox.
     */
    const Vector3& GetMinimum() const;

    /*
     * Obtains the maximum coordinates of the BBox.
     */
    const Vector3& GetMaximum() const;

    /*
     * Sets the minimum coordinates of the BBox.
     */
    void SetMinimum(const Vector3& vec);

    /*
     * Sets the maximum coordinates of the BBox.
     */
    void SetMaximum(const Vector3& vec);

    /*
     * Obtains the eight corner coordinates of the BBox.
     */
    const Vector3* GetCorners() const;

    /*
     * Obtains the center coordinates of the BBox.
     */
    Vector3 GetCenter() const;

    /*
     * Obtains the sizes of the three dimensions of the BBox.
     */
    Vector3 GetSize() const;

    /*
     * Obtains the half sizes of the three dimensions of the BBox.
     */
    Vector3 GetHalfSize() const;

    /*
     * Adds an internal point in the BBox and updates the minimum and maximum coordinates of the BBox accordingly.
     */
    void AddInternalPoint(const Vector3& p);

    /*
     * Adds an internal BBox in the BBox and updates the minimum and maximum coordinates of the original BBox
     * accordingly.
     */
    void AddInternalBox(const AABB& b);

    /*
     * Converts the BBox to a string formatted "(BBox minimum value, BBox maximum value)".
     */
    String ToString() const;

    /*
     * Contained in Bounding Box.
     */
    bool Contains(const AABB& other) const;

private:
    Vector3 m_minimum;
    Vector3 m_maximum;
    mutable Vector3* m_corners;
};

NS_CG_END

#endif