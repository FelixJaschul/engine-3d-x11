#pragma once

namespace Engine
{
    namespace Window
    {
        inline const char* appWindowTitle = "X11";
        inline int appDefaultWindowX = 1200;
        inline int appDefaultWindowY = 800;
        inline int appDesiredFPS = 60;

        inline const char* GetWindowTitle() { return appWindowTitle; }
        inline int GetDefaultWindowX() { return appDefaultWindowX; }
        inline int GetDefaultWindowY() { return appDefaultWindowY; }
        inline int GetDesiredFPS() { return appDesiredFPS; }

        inline void SetWindowTitle(const char* title) { appWindowTitle = title; }
        inline void SetDefaultWindowX(int width) { appDefaultWindowX = width; }
        inline void SetDefaultWindowY(int height) { appDefaultWindowY = height; }
        inline void SetDesiredFPS(int fps) { appDesiredFPS = fps; }
    }

    namespace Rendering
    {
        inline bool appWireframeMode = false;

        inline bool GetWireframeMode() { return appWireframeMode; }
        inline void SetWireframeMode(bool mode) { appWireframeMode = mode; }
    }

    inline float appMovementSpeed = 200.0f;
    inline float appRotationSpeed = 2.0f;
    inline int appMovementJumpHeight = 700;
    inline int appCurrentGroundHeight = 400;
    inline int appPlayerHeight = 50;
    inline int appGravityValue = 2000;
    inline bool appEnableGroundCheck = false;

    inline float GetMovementSpeed() { return appMovementSpeed; }
    inline float GetRotationSpeed() { return appRotationSpeed; }
    inline int GetMovementJumpHeight() { return appMovementJumpHeight; }
    inline int GetCurrentGroundHeight() { return appCurrentGroundHeight; }
    inline int GetPlayerHeight() { return appPlayerHeight; }
    inline int GetGravityValue() { return appGravityValue; }
    inline bool GetGroundCheck() { return appEnableGroundCheck; }

    inline void SetMovementSpeed(float speed) { appMovementSpeed = speed; }
    inline void SetRotationSpeed(float speed) { appRotationSpeed = speed; }
    inline void SetMovementJumpHeight(int jump) { appMovementJumpHeight = jump; }
    inline void SetCurrentGroundHeight(int height) { appCurrentGroundHeight = height; }
    inline void SetPlayerHeight(int height) { appPlayerHeight = height; }
    inline void setGravityValue(int value) { appGravityValue = value; }
    inline void SetGroundCheck(bool mode) { appEnableGroundCheck = mode; }
}
