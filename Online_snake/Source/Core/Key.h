#pragma once

#include <GLFW/glfw3.h>
#include <stdint.h>

enum class Input_action : int32_t
{
    unkown = -1,
    press = GLFW_PRESS,
    release = GLFW_RELEASE,
    hold = GLFW_REPEAT
};

enum class Input_key : int32_t
{
    unkown = GLFW_KEY_UNKNOWN,
    space = GLFW_KEY_SPACE,
    apostrophe = GLFW_KEY_APOSTROPHE,
    comma = GLFW_KEY_COMMA,
    minus = GLFW_KEY_MINUS,
    period = GLFW_KEY_PERIOD,
    slash = GLFW_KEY_SLASH,
    num0 = GLFW_KEY_0,
    num1 = GLFW_KEY_1,
    num2 = GLFW_KEY_2,
    num3 = GLFW_KEY_3,
    num4 = GLFW_KEY_4,
    num5 = GLFW_KEY_5,
    num6 = GLFW_KEY_6,
    num7 = GLFW_KEY_7,
    num8 = GLFW_KEY_8,
    num9 = GLFW_KEY_9,
    semicolon = GLFW_KEY_SEMICOLON,
    equal = GLFW_KEY_EQUAL,
    A = GLFW_KEY_A,
    B = GLFW_KEY_B,
    C = GLFW_KEY_C,
    D = GLFW_KEY_D,
    E = GLFW_KEY_E,
    F = GLFW_KEY_F,
    G = GLFW_KEY_G,
    H = GLFW_KEY_H,
    I = GLFW_KEY_I,
    J = GLFW_KEY_J,
    K = GLFW_KEY_K,
    L = GLFW_KEY_L,
    M = GLFW_KEY_M,
    N = GLFW_KEY_N,
    O = GLFW_KEY_O,
    P = GLFW_KEY_P,
    Q = GLFW_KEY_Q,
    R = GLFW_KEY_R,
    S = GLFW_KEY_S,
    T = GLFW_KEY_T,
    U = GLFW_KEY_U,
    V = GLFW_KEY_V,
    W = GLFW_KEY_W,
    X = GLFW_KEY_X,
    Y = GLFW_KEY_Y,
    Z = GLFW_KEY_Z
};
