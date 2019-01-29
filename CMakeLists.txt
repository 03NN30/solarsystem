cmake_minimum_required(VERSION 3.0.0)
project("Solar System" VERSION 0.1.0)

# openGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
include_directories(external/GLEW/include)
link_directories(external/GLEW/lib/Release/Win32)

# sdl
include_directories(external/SDL/include)
link_directories(external/SDL/lib/x86)

# glm
include_directories(external/GLM)

# IMGUI
include_directories(external/IMGUI)

# application headers
include_directories(framework/include)
include_directories(application/include)

# set header files
set(HEADERS ${HEADERS}
    framework/include/glewInc.hpp
    framework/include/camera.hpp
    framework/include/model.hpp
    framework/include/shader.hpp
    framework/include/texture.hpp
    framework/include/skybox.hpp
    framework/include/controls.hpp
    framework/include/framebuffer.hpp
   
    application/include/application.hpp
    application/include/utils.hpp
    application/include/node.hpp
    application/include/render.hpp
    application/include/sceneGraph.hpp
    application/include/gui.hpp
    )

# set source files
set(SOURCES ${SOURCES}
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

file(GLOB IMGUI_FILES
    "external/IMGUI/*.h"
    "external/IMGUI/*.cpp"
)

# exe 
add_executable(SolarSystem application/source/main.cpp ${SOURCES} ${HEADERS} ${IMGUI_FILES})

# link libraries against exe
target_link_libraries(SolarSystem 
    SDL2main
    SDL2 
    SDL2_image
    ${OPENGL_LIBRARIES}
    glew32s
)
