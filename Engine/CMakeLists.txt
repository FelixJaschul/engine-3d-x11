cmake_minimum_required(VERSION 3.10)
project(Engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(X11 REQUIRED)

set(ENGINE_SOURCES
        src/Rendering/Window.cpp
        src/Rendering/Renderer.cpp
        src/Rendering/Camera.cpp
        src/Rendering/Canvas.cpp
        src/Rendering/Triangle.cpp
        src/Rendering/Primitive.cpp
        src/Rendering/Config.cpp
        src/Math/Math.cpp
        src/Math/Vec.cpp
        src/Input/Input.cpp
        src/Util/Time.cpp
        src/Util/Light.cpp
        src/World/Level.cpp
        src/World/Wall.cpp
        src/App/App.cpp
)

add_library(Engine STATIC ${ENGINE_SOURCES})

target_include_directories(Engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${X11_INCLUDE_DIR}
)

target_link_libraries(Engine PUBLIC ${X11_LIBRARIES})

if(APPLE)
    message(STATUS "Engine: macOS detected. Install XQuartz, log out/in, start XQuartz, and ensure DISPLAY is set.")
elseif(WIN32)
    message(STATUS "Engine: Windows detected. Use WSL with WSLg or an X server.")
else()
    message(STATUS "Engine: Ensure X server is running and DISPLAY is set.")
endif()
