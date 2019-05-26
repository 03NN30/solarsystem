cmake_minimum_required(VERSION 3.0.0)
project("Solar System" VERSION 0.1.0)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# GLEW
#include_directories(external/GLEW/include)

# SDL2
include_directories(external/SDL/include)

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

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})


# exe 
add_executable(SolarSystem application/source/main.cpp ${SOURCES} ${HEADERS} ${IMGUI_FILES})

# link libraries against exe
target_link_libraries (SolarSystem 
    #SDL2main
    #SDL2
    SDL2_image
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    #glew32s
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)
