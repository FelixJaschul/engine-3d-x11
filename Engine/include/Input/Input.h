#pragma once

#include <cstdint>

namespace Engine::Input
{
    enum class Key : uint16_t
    {
        Unknown = 0,

        Escape, Space, Enter, 
        Tab, Backspace,

        Left, Right, 
        Up, Down,

        A, B, C, D, E, 
        F, G, H, I, J, 
        K, L, M, N, O, 
        P, Q, R, S, T, 
        U, V, W, X, Y, 
        Z,

        Num0, Num1, Num2, 
        Num3, Num4, Num5, 
        Num6, Num7, Num8, 
        Num9,

        LeftShift, RightShift, 
        LeftControl, RightControl,

        LeftAlt, RightAlt, 
        LeftSuper, RightSuper,

        F1, F2,
        COUNT
    };

    void UpdateFrame();
    void SetKey(Key key, bool down);
    bool IsKeyDown(Key key);
    bool IsKeyPressed(Key key);
    bool IsKeyReleased(Key key);
}
