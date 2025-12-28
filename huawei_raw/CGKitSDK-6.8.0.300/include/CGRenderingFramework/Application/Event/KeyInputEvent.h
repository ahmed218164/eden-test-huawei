/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: The class used to report key and button events. Defined the constants input key code,
 * and the interface for get key code or key action.
 */

#ifndef KEY_INPUT_EVENT_H
#define KEY_INPUT_EVENT_H

#include "Application/Event/InputEvent.h"

NS_CG_BEGIN

/*
 * Defines the key codes.
 */
enum KeyCode {
    KEY_CODE_UNKNOWN, // Unknown
    KEY_CODE_SPACE, // Space key
    KEY_CODE_APOSTROPHE, // Apostrophe (')
    KEY_CODE_COMMA, // Comma (,)
    KEY_CODE_MINUS, // Hyphen (-)
    KEY_CODE_PERIOD, // Period (.)
    KEY_CODE_SLASH, // Forward slash (/)
    KEY_CODE_0, // 0
    KEY_CODE_1, // 1
    KEY_CODE_2, // 2
    KEY_CODE_3, // 3
    KEY_CODE_4, // 4
    KEY_CODE_5, // 5
    KEY_CODE_6, // 6
    KEY_CODE_7, // 7
    KEY_CODE_8, // 8
    KEY_CODE_9, // 9
    KEY_CODE_SEMICOLON, // Semicolon (:)
    KEY_CODE_EQUAL, // Equality sign (=)
    KEY_CODE_A, // A
    KEY_CODE_B, // B
    KEY_CODE_C, // C
    KEY_CODE_D, // D
    KEY_CODE_E, // E
    KEY_CODE_F, // F
    KEY_CODE_G, // G
    KEY_CODE_H, // H
    KEY_CODE_I, // I
    KEY_CODE_J, // J
    KEY_CODE_K, // N
    KEY_CODE_L, // L
    KEY_CODE_M, // M
    KEY_CODE_N, // N
    KEY_CODE_O, // O
    KEY_CODE_P, // P
    KEY_CODE_Q, // Q
    KEY_CODE_R, // R
    KEY_CODE_S, // S
    KEY_CODE_T, // T
    KEY_CODE_U, // U
    KEY_CODE_V, // V
    KEY_CODE_W, // W
    KEY_CODE_X, // X
    KEY_CODE_Y, // Y
    KEY_CODE_Z, // Z
    KEY_CODE_LEFT_BRACKET, // Left square bracket ([)
    KEY_CODE_BACKSLASH, // Backslash (\)
    KEY_CODE_RIGHT_BRACKET, // Right square bracket (])
    KEY_CODE_GRAVE_ACCENT, // Grave accent (`)
    KEY_CODE_ESCAPE, // Esc
    KEY_CODE_ENTER, // Enter
    KEY_CODE_TAB, // Tab
    KEY_CODE_BACKSPACE, // Backspace
    KEY_CODE_INSERT, // Insert
    KEY_CODE_DELETE, // Delete
    KEY_CODE_RIGHT, // Right arrow
    KEY_CODE_LEFT, // Left arrow
    KEY_CODE_DOWN, // Down arrow
    KEY_CODE_UP, // Up arrow
    KEY_CODE_PAGE_UP, // Page Up
    KEY_CODE_PAGE_DOWN, // Page Down
    KEY_CODE_HOME, // Home
    KEY_CODE_END, // End
    KEY_CODE_BACK, // Back
    KEY_CODE_CAPS_LOCK, // Caps Lock
    KEY_CODE_SCROLL_LOCK, // Scroll Lock
    KEY_CODE_NUM_LOCK, // Num Lock
    KEY_CODE_PRINT_SCREEN, // Print Screen
    KEY_CODE_PAUSE, // Pause
    KEY_CODE_F1, // F1
    KEY_CODE_F2, // F2
    KEY_CODE_F3, // F3
    KEY_CODE_F4, // F4
    KEY_CODE_F5, // F5
    KEY_CODE_F6, // F6
    KEY_CODE_F7, // F7
    KEY_CODE_F8, // F8
    KEY_CODE_F9, // F9
    KEY_CODE_F10, // F10
    KEY_CODE_F11, // F11
    KEY_CODE_F12, // F12
    KEY_CODE_KP_0, // Numpad 0
    KEY_CODE_KP_1, // Numpad 1
    KEY_CODE_KP_2, // Numpad 2
    KEY_CODE_KP_3, // Numpad 3
    KEY_CODE_KP_4, // Numpad 4
    KEY_CODE_KP_5, // Numpad 5
    KEY_CODE_KP_6, // Numpad 6
    KEY_CODE_KP_7, // Numpad 7
    KEY_CODE_KP_8, // Numpad 8
    KEY_CODE_KP_9, // Numpad 9
    KEY_CODE_KP_DECIMAL, // Numpad decimal point (.)
    KEY_CODE_KP_DIVIDE, // Numpad division symbol (/)
    KEY_CODE_KP_MULTIPLY, // Numpad multiplication symbol (*)
    KEY_CODE_KP_SUBTRACT, // Numpad subtraction symbol (-)
    KEY_CODE_KP_ADD, // Numpad addition symbol (+)
    KEY_CODE_KP_ENTER, // Numpad Enter
    KEY_CODE_KP_EQUAL, // Numpad equality symbol (=)
    KEY_CODE_LEFT_SHIFT, // Left Shift
    KEY_CODE_LEFT_CONTROL, // Left Ctrl
    KEY_CODE_LEFT_ALT, // Left Alt
    KEY_CODE_RIGHT_SHIFT, // Right Shift
    KEY_CODE_RIGHT_CONTROL, // Right Ctrl
    KEY_CODE_RIGHT_ALT, // Right Alt
    KEY_CODE_MAX = KEY_CODE_RIGHT_ALT // Maximum enum value. A valid enum value is less than this value.
};

/*
 * Defines the key actions.
 */
enum KeyAction {
    KEY_ACTION_DOWN, // Keydown
    KEY_ACTION_UP, // Keyup
    KEY_ACTION_REPEAT, // Keyhold
    KEY_ACTION_UNKNOWN, // Unknown
    KEY_ACTION_MAX = KEY_ACTION_UNKNOWN // Maximum enum value. A valid enum value is less than this value.
};

class CGKIT_EXPORT KeyInputEvent : public InputEvent {
public:
    KeyInputEvent(KeyCode code, KeyAction action);
    ~KeyInputEvent();

    /*
     * Obtains the key code of a key event.
     */
    KeyCode GetCode() const;

    /*
     * Obtains the key action of a key event, such as keydown, keyup, or keyhold.
     */
    KeyAction GetAction() const;

private:
    KeyCode m_code;
    KeyAction m_action;
};

NS_CG_END

#endif