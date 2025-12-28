/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: The class used to report mouse input events.
 */

#ifndef MOUSE_INPUT_EVENT_H
#define MOUSE_INPUT_EVENT_H

#include "Core/Types.h"
#include "Application/Event/InputEvent.h"

NS_CG_BEGIN

enum MouseAction {
    MOUSE_ACTION_UNKNOWN,
    MOUSE_ACTION_LEFT_BUTTON_DOWN,
    MOUSE_ACTION_LEFT_BUTTON_UP,
    MOUSE_ACTION_LEFT_BUTTON_DOUBLE_CLICK,
    MOUSE_ACTION_MIDDLE_BUTTON_DOWN,
    MOUSE_ACTION_MIDDLE_BUTTON_UP,
    MOUSE_ACTION_MIDDLE_BUTTON_DOUBLE_CLICK,
    MOUSE_ACTION_RIGHT_BUTTON_DOWN,
    MOUSE_ACTION_RIGHT_BUTTON_UP,
    MOUSE_ACTION_RIGHT_BUTTON_DOUBLE_CLICK,
    MOUSE_ACTION_MOUSE_WHEEL,
    MOUSE_ACTION_MOVE,
    MOUSE_ACTION_MAX,
};

struct MouseCoord {
    u16 x = 0;
    u16 y = 0;

    MouseCoord(u16 posX, u16 posY)
    {
        x = posX;
        y = posY;
    }

    MouseCoord(const MouseCoord& mouseCoord)
    {
        x = mouseCoord.x;
        y = mouseCoord.y;
    }

    MouseCoord& operator=(const MouseCoord& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }
};

class CGKIT_EXPORT MouseInputEvent : public InputEvent {
public:
    MouseInputEvent(const MouseCoord& mouseCoord, MouseAction action, s16 wheelDelta);
    ~MouseInputEvent();

    /*
     * Get mouse action, like MOUSE_ACTION_LEFT_BUTTON_UP etc.
     */
    MouseAction GetAction() const;

    /*
     * Get mouse coordination marked by x and y.
     */
    const MouseCoord& GetMouseCoord() const;

    /*
     * Get mouse wheel delta value in this frame.
     */
    short GetWheelDelta() const;

private:
    MouseCoord m_mouseCoord;
    MouseAction m_action;
    s16 m_wheelDelta;
};

NS_CG_END

#endif