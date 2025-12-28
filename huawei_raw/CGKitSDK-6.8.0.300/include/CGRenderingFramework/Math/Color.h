/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: A color class used to assign values to color objects, compare color objects, and set fixed color values.
 */

#ifndef COLOR_H
#define COLOR_H

#include "Core/Types.h"

NS_CG_BEGIN

class CGKIT_EXPORT Color {
public:
    Color() = default;
    ~Color() = default;

    /*
     * A constructor used to initialize the RGBA channel values. Each channel is 8 bits (the lower 8 bits of the 32
     * bits). The default value of channel A is 255.
     */
    Color(u32 red, u32 green, u32 blue, u32 alpha = 255)
        : color((red & 0xff) | ((green & 0xff) << 8) | ((blue & 0xff) << 16) | ((alpha & 0xff) << 24))
    {}

    /*
     * Overloads the assignment operator to assign a Color object to the current object.
     */
    Color& operator = (const Color& other);

    /*
     * Overloads the - operator and returns Returns the subtraction of two colors.
     */
    Color operator - (const Color& other);

    /*
     * Overloads the == operator and returns true if the current object equals the specified Color object.
     */
    bool operator == (const Color& other) const;

    /*
     * Overloads the != operator and returns true if the current object does not equal the specified Color object.
     */
    bool operator != (const Color& other) const;

    String ToString() const;

public:
    union {
        u32 color;
        struct {
            u8 r;
            u8 g;
            u8 b;
            u8 a;
        };
    };

    static const Color WHITE;
    static const Color BLACK;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color YELLOW;
    static const Color ORANGE;
    static const Color CYAN;
    static const Color MAGENTA;
};

NS_CG_END

#endif