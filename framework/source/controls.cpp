#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include "camera.hpp"
#include "controls.hpp"
#include "utils.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

// time
float deltaTime = 0.0f;	
float lastFrame = 0.0f;
float speed = 6.0f;

// mouse
bool firstMouse = true;
float lastX = screenWidth / 2.0f;
float lastY = screenHeight / 2.0f;
bool showMouse = true;
bool mouseEnabled = false;
bool keyboardEnabled = false;

// keyboard
bool forwards = false;
bool backwards = false;
bool left = false;
bool right = false;
bool down = false;
bool up = false;

void mouse_button_callback(SDL_Event& e) {
    if (e.button.button == SDL_BUTTON_RIGHT) {
        forwards = false;
        backwards = false;
        left = false;
        right = false;
        down = false;
        up = false;

        showMouse = !showMouse;
        mouseEnabled = !mouseEnabled;
        keyboardEnabled = !keyboardEnabled;
        firstMouse = true;
    }
}

void mouse_motion_callback(SDL_Event& e) {
    
    static int x;
    static int y;
    SDL_GetMouseState(&x, &y);
    float xpos = float(x);
    float ypos = float(y);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    Camera::get().processMouseMotion(xoffset, yoffset);
}

void key_pressed_callback(SDL_Event& e) {
    if (keyboardEnabled) {
        switch (e.key.keysym.sym) {
        case SDLK_w:
            forwards = true;
        break;
        case SDLK_s:
            backwards = true;
        break;
        case SDLK_a:
            left = true;
        break;
        case SDLK_d:
            right = true;
        break;
        case SDLK_c:
            down = true;
        break;
        case SDLK_SPACE:
            up = true;
        break;
        case SDLK_LSHIFT:
            speed = 10.0f;
        break;
        case SDLK_LCTRL:
            speed = 0.4f;
        break;
        case SDLK_q:
            menu = !menu;
        break;
        case SDLK_ESCAPE:
            menu = !menu;
        break;
        case SDLK_m:
            menu = !menu;
        break;
        }
    } else {
        switch (e.key.keysym.sym) {
        case SDLK_q:
            menu = !menu;
        break;
        case SDLK_ESCAPE:
            menu = !menu;
        break;
        case SDLK_m:
            menu = !menu;
        break;
        }
    }
}

void key_released_callback(SDL_Event &e) {
    switch (e.key.keysym.sym) {
        case SDLK_w:
            forwards = false;
        break;
        case SDLK_s:
            backwards = false;
        break;
        case SDLK_a:
            left = false;
        break;
        case SDLK_d:
            right = false;
        break;
        case SDLK_c:
            down = false;
        break;
        case SDLK_SPACE:
            up = false;
        break;
        case SDLK_LSHIFT:
            speed = 6.0f;
        break;
        case SDLK_LCTRL:
            speed = 6.0f;
        break;
    }
}

void handleEvent() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_KEYDOWN && !isFollowing) {
            key_pressed_callback(event);
        }
        if (keyboardEnabled) {
            if (event.type == SDL_KEYUP && !isFollowing) {
                key_released_callback(event);
            }
        }
        if (event.type == SDL_MOUSEMOTION && !isFollowing) {
            if (mouseEnabled) {
                mouse_motion_callback(event);
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN && !isFollowing) { 
            mouse_button_callback(event);
        }
    }
}

void controller() {
    float currentFrame = float(SDL_GetTicks()) / 1000.0f;
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    float cameraSpeed = speed * deltaTime;

    if (forwards) {
        Camera::get().proessKeyboard(m_forwards, cameraSpeed);       
    }
    if (backwards) {
       Camera::get().proessKeyboard(m_backwards, cameraSpeed);
    }
    if (left) {
        Camera::get().proessKeyboard(m_left, cameraSpeed);
    }
    if (right) {
        Camera::get().proessKeyboard(m_right, cameraSpeed);
    }
    if (up) {
        Camera::get().proessKeyboard(m_up, cameraSpeed);
    }
    if (down) {
        Camera::get().proessKeyboard(m_down, cameraSpeed);
    }
    if (showMouse) {
        SDL_SetRelativeMouseMode(SDL_FALSE);
        SDL_CaptureMouse(SDL_FALSE);
    } else {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        SDL_CaptureMouse(SDL_TRUE);
    }
    handleEvent();
}



