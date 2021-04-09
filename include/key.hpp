/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** key
*/

#ifndef KEY_HPP_
#define KEY_HPP_

namespace arcade
{
    typedef enum keys
    {
        UNKNOWN = -1,

        CTRL,
        SHIFT_L,
        ALT_L,
        SUPER_L,
        SHIFT_R,
        ALT_R,
        SUPER_R,
        CAPS_LOCK,

        ESC,
        TAB,
        SPACE,
        RETURN,
        BACKSPACE,

        DEL,
        INSERT,

        HOME,
        END,

        PAGE_UP,
        PAGE_DOWN,

        ARROW_UP,
        ARROW_DOWN,
        ARROW_LEFT,
        ARROW_RIGHT,

        NUM_0,
        NUM_1,
        NUM_2,
        NUM_3,
        NUM_4,
        NUM_5,
        NUM_6,
        NUM_7,
        NUM_8,
        NUM_9,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        BRACKET_LEFT,
        BRACKET_RIGHT,

        SEMICOLON,
        COMMA,
        PERIOD,
        QUOTE,
        SLASH,
        BACKSLASH,
        TILDE,
        EQUAL,
        HYPHEN,

        ADD,
        SUBSTRACT,
        MULTIPLY,
        DIVIDE
    } keys_e;
}

#endif /* !KEY_HPP_ */
