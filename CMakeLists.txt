cmake_minimum_required(VERSION 3.0.0)
project("Solar System" VERSION 0.1.0)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# GLEW
find_package(GLEW REQUIRED)

# SDL2
find_package(SDL2 REQUIRED)

# GLM
include_directories(external/GLM)

# IMGUI
include_directories(external/IMGUI)

# libs
link_directories(external/libs)

# application include
include_directories(framework/include)
include_directories(application/include)

file (GLOB HEADERS
    "application/include/*.hpp"
    "framework/include/*.hpp"
)

# application source
set (SOURCES ${SOURCES}
    framework/source/camera.cpp
    framework/source/model.cpp
    framework/source/shader.cpp
    framework/source/texture.cpp
    framework/source/skybox.cpp
    framework/source/controls.cpp
    framework/source/framebuffer.cpp

    application/source/application.cpp
    application/source/node.cpp
    application/source/render.cpp
    application/source/sceneGraph.cpp
    application/source/gui.cpp
)

file (GLOB IMGUI_FILES
    "external/IMGUI/*.h"
    "external/IMGUI/*.cpp"
)

# exe 
add_executable(SolarSystem application/source/main.cpp ${SDL2_INCLUDE_DIRS} ${SOURCES} ${HEADERS} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${IMGUI_FILES})

message(${OPENGL_LIBRARIES})

# link libraries against exe
target_link_libraries (SolarSystem 
    ${SDL2_LIBRARIES}
    libSDL2_image.so
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${CMAKE_DL_LIBS}
)
