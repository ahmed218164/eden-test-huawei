/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: The class used to report touch input events. Defined the constants touch action,
 * the interface get touch pointer info, action, posX and posY.
 */

#ifndef TOUCH_INPUT_EVENT_H
#define TOUCH_INPUT_EVENT_H

#include "Core/Types.h"
#include "Application/Event/InputEvent.h"

NS_CG_BEGIN

/*
 * Defines the touch actions.
 */
enum TouchAction {
    TOUCH_ACTION_UNKNOWN, // Unknown
    TOUCH_ACTION_DOWN, // Touch start
    TOUCH_ACTION_UP, // Touch end
    TOUCH_ACTION_MOVE, // Touch move
    TOUCH_ACTION_CANCEL, // Touch cancel
    TOUCH_ACTION_POINTER_DOWN, // Multi-touch start
    TOUCH_ACTION_POINTER_UP, // Multi-touch end
    TOUCH_ACTION_MAX, // Maximum enum value. A valid enum value is less than this value.
};

/*
 * Defines the coordinates of a touch event.
 */
struct TouchCoord {
    f32 x = 0.0f; // x-coordinate of a touch event
    f32 y = 0.0f; // y-coordinate of a touch event

    TouchCoord(f32 posX, f32 posY)
    {
        x = posX;
        y = posY;
    }
};

class CGKIT_EXPORT TouchInputEvent : public InputEvent {
public:
    TouchInputEvent(u32 touchIndex, const std::vector<u32>& pointers,
        const std::vector<TouchCoord>& touchCoords,
        TouchAction action, u64 eventTime, u64 downTime);
    ~TouchInputEvent();

    /*
     * Obtains the action of a touch event.
     */
    TouchAction GetAction() const;

    /*
     * Obtains the value of the multi-touch event counter.
     */
    u32 GetTouchCount() const;

    /*
     * Obtains the index of a touch event. Data of different touch points is indexed.
     */
    u32 GetTouchIndex() const;

    /*
     * Obtains the touch event source ID of a multi-touch event.
     */
    s32 GetTouchId(u32 touchIndex = 0) const;

    /*
     * Obtains the x-coordinate of a touch event.
     */
    f32 GetPosX(u32 touchIndex = 0) const;

    /*
     * Obtains the y-coordinate of a touch event.
     */
    f32 GetPosY(u32 touchIndex = 0) const;

    /*
     * Obtains the reported time of a touch event.
     */
    u64 GetEventTime() const;

    /*
     * Obtains the start time of a touch event.
     */
    u64 GetDownTime() const;

    /*
     * Obtains the 2D coordinates of a multi-touch event.
     */
    const std::vector<TouchCoord>& GetTouchCoords() const;

    /*
     * Obtains the array of multi-touch event source IDs.
     */
    const std::vector<u32>& GetTouchPointers() const;

private:
    std::vector<TouchCoord> m_touchCoords;
    std::vector<u32> m_pointers;
    TouchAction m_action = TOUCH_ACTION_MAX;
    u32 m_touchIndex = 0;
    u32 m_touchCount = 0;
    u64 m_eventTime = 0;
    u64 m_downTime = 0;
};

NS_CG_END

#endif
