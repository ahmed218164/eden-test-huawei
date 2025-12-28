/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Plane utils.
 */

#ifndef PLANE_H
#define PLANE_H

#include "Math/Vector3.h"

NS_CG_BEGIN

/*
 * A plane class used to assign values to and compare Plane objects, and set normal vectors of
 * planes and the distances from the origin to planes.
 */
class CGKIT_EXPORT Plane {
public:
    Plane() = default;
    ~Plane() = default;

    /*
     * Overloads the assignment operator to assign a Plane object to the current object.
     */
    Plane& operator=(const Plane& other);

    /*
     * Overloads the == operator and returns true if the current object equals to the specified
     * Plane object.
     */
    bool operator==(const Plane& plane) const;

    /*
     * Overloads the != operator and returns true if the current object does not equal the
     * specified Plane object.
     */
    bool operator!=(const Plane& plane) const;

    /*
     * Sets the normal vector of a plane and the distance from the origin to the plane.
     */
    void Set(const Vector3& normal, f32 distance);

    /*
     * Sets the normal line of a plane and calculates the distance from the origin to the plane
     * based on the coordinates of the specified point.
     */
    void Set(const Vector3& normal, const Vector3& point);

    /*
     * Obtains the normal vector of a plane and the distance from the origin to the plane. The
     * arguments are the coordinates of three points that determine a plane.
     */
    void Set(const Vector3& point1, const Vector3& point2, const Vector3& point3);

    /*
     * Converts the Plane type to a string, formatted "Plane(Normal: (a, b, c); Distance: origin
     * to plane)".
     */
    String ToString() const;

public:
    /*
     * Normal vector of a plane.
     */
    Vector3 m_normal = Vector3::ZERO;

    /*
     * Distance from the origin to a plane.
     */
    f32 m_distance = 0.0f;
};

NS_CG_END

#endif