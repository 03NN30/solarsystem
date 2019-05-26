#include "gui.hpp"
#include "node.hpp"
#include "utils.hpp"
#include "camera.hpp"
#include "application.hpp"

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

// menu
bool menu = true;

// cam
bool isFollowing = false;
std::string nameOfobjectToFollow;
Node* objectToFollow;
f_Camera defaultDirection = f_behind;

static bool showSettings = false;
static bool showCameraViewer = false;
static bool showPlanetViewer = false;
static bool showDebugViewer = false;
static bool showHelp = false;

void drawPlanetViewer(Node& it) {
    
    if (it.getName() != sg->getName()) {
        glm::mat4 transformation = it.getWorldTransform(); 
        glm::vec3 scale, translation, skew;
        glm::quat rotation;
        glm::vec4 perspective;
        glm::decompose(transformation, scale, rotation, translation, skew, perspective);
        ImGui::Checkbox(("##" + it.getName()).c_str(), &it.getVisibility());
        ImGui::SameLine();
        if (ImGui::Button(it.getName().c_str())) {
            isFollowing = true;
            nameOfobjectToFollow = it.getName();
            objectToFollow = &it;
        }
        ImGui::SameLine(150);
        ImGui::Text("%f", translation[0]);   
        ImGui::SameLine(250); 
        ImGui::Text("%f", translation[1]);   
        ImGui::SameLine(350); 
        ImGui::Text("%f", translation[2]);   
    }

    if (isFollowing) {
        Camera::get().follow(objectToFollow->getWorldTransform(), defaultDirection, objectToFollow->getSize() + 1.0f);
    }

    if (!it.getChildrenList().empty()) {

        for (Node* itChild : it.getChildrenList()) {
            drawPlanetViewer(*itChild);
        }
    }
}

void drawSettings() {
    if (isMoving) {
        if (ImGui::Button("            STOP             ")) {
            isMoving = false;
        }
    } else {
        if (ImGui::Button("            START            ")) {
             isMoving = true;
        }
    }
    ImGui::Spacing();
    ImGui::SliderFloat(" time", &speedSlider, 1.0f, 200.0f);
    ImGui::Text("Camera:");
    ImGui::SliderFloat(" fov", &Camera::get().fov, 45.0f, 100.0f);
    ImGui::Text("Materials:");
    ImGui::SliderFloat(" shiniess", &shininess, 0.0f, 200.0f);
    ImGui::SliderFloat(" reflectivity", &reflectivity, 0.0f, 1.0f);
    ImGui::SliderFloat(" ambient", &ambient, 0.0f, 0.5f);
    ImGui::Text("Light attenuation:");
    ImGui::SliderFloat(" light intensity", &lightIntensity, 0.0f, 10.0f);
    ImGui::SliderFloat(" lightConstant", &lightConstant, 0.0f, 1.0f);
    ImGui::SliderFloat(" lightLinear", &lightLinear, 0.0f, 0.1f);
    ImGui::SliderFloat(" lightQuadratic", &lightQuadratic, 0.0f, 0.05f);
    ImGui::Text("Post processing:");
    ImGui::Checkbox("bloom", &bloomFlag);
    ImGui::Checkbox("planet bloom", &planetBloom);
    ImGui::Checkbox("blur", &blur);
    ImGui::Checkbox("grayscale", &grayscale);
    ImGui::Checkbox("vertical mirror", &verticalMirror);
    ImGui::Checkbox("horizontal mirror", &horizontalMirror);
    ImGui::SliderFloat(" exposure", &exposure, 0.0f, 10.0f);
    ImGui::SliderFloat(" gamma", &gamma_, 0.0f, 10.0f);
    ImGui::SliderFloat(" glow", &glow, 1.0, 3.0);
    ImGui::Separator();
    ImGui::Checkbox("outline", &planetOutline);
    ImGui::Checkbox("show orbits", &orbits);
    ImGui::Checkbox("show stars", &stars);
    ImGui::Checkbox("show ring", &planetRing);
    ImGui::Checkbox("realistic earth", &realism);
}

void drawCameraViewer() {
    ImGui::Text("Pitch:    %f", Camera::get().pitch);
    ImGui::Text("Yaw:      %f", Camera::get().yaw);
    ImGui::Text("Position: %f, %f, %f", Camera::get().position[0], Camera::get().position[1], Camera::get().position[2]);
    ImGui::Text("Front:    %f, %f, %f", Camera::get().front[0], Camera::get().front[1], Camera::get().front[2]);
    ImGui::Text("WorldUp:  %f, %f, %f", Camera::get().worldUp[0], Camera::get().worldUp[1], Camera::get().worldUp[2]);
    ImGui::Text("Up:       %f, %f, %f", Camera::get().up[0], Camera::get().up[1], Camera::get().up[2]);
    ImGui::Text("Right:    %f, %f, %f", Camera::get().right[0], Camera::get().right[1], Camera::get().right[2]);
}

void drawDebugViewer() {
   
}

void drawDeactivateFollowing() {
    ImGui::Begin("deactivate following", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    if (ImGui::Button(("Stop following\n" + nameOfobjectToFollow).c_str())) {
        isFollowing = false;
        Camera::get().neutralizeAngles();
    }
    ImGui::Separator();
    ImGui::Text("Change view");
    if (ImGui::Button("Top   ")) {
        defaultDirection = f_top;
    }
    ImGui::SameLine();
    if (ImGui::Button("Bottom")) {
        defaultDirection = f_bottom;
    }
    if (ImGui::Button("Left  ")) {
        defaultDirection = f_left;
    }
    ImGui::SameLine();
    if (ImGui::Button("Right ")) {
        defaultDirection = f_right;
    }
    if (ImGui::Button("Front ")) {
        defaultDirection = f_front;
    }
    ImGui::SameLine();
    if (ImGui::Button("Behind")) {
        defaultDirection = f_behind;
    }
    ImGui::End();
}

void drawHelp() {

    const char* explanation = 
        "Just right click your screen to swap between the\n"
        "overlay and the controller.";
    const char* credits = 
        "This software was created by me using:            ";
    
    const char* disclaimer =
        "I do NOT own any texture files used in this app.  ";
        
    const char* feedback = 
        "Thank you very much for trying this application.\n"
        "If you want to provide feedback, send a mail to:\n"
        "\n              n30.mail@gmail.com              \n"
        "\nThe software is still work in progress and isn't"
        "\nintended for commercial usage.";

    ImGui::Text("Solar System V%f", appVersion);
    ImGui::Separator();

    ImGui::Text("EXPLANATION");
    ImGui::Text(explanation);
    ImGui::Separator();

    ImGui::Text("DISCLAIMER");
    ImGui::Text(disclaimer);
    ImGui::Separator();

    ImGui::Text("CREDITS");
    ImGui::Text(credits);
    ImGui::BulletText("OpenGL");
    ImGui::BulletText("GLEW");
    ImGui::BulletText("SDL 2.0");
    ImGui::BulletText("Dear ImGui");
    ImGui::Separator();

    ImGui::Text("FEEDBACK");
    ImGui::Text(feedback);
}

void closeCollapsingHeader(const char* label) {
    ImGui::GetStateStorage()->SetInt(ImGui::GetID(label), 0);
}

void openCollapsingHeader(const char* label) {
    ImGui::GetStateStorage()->SetInt(ImGui::GetID(label), 1);
}

bool drawMenu() {
    if (menu) {    
        if (isFollowing) {
            drawDeactivateFollowing();
        }           
        //  | ImGuiWindowFlags_NoMove
        ImGui::Begin("Solar System", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
        // buttons
        if (ImGui::Button("X")) {
            ImGui::End();
            return false;
        }  
        ImGui::SameLine();
        if (ImGui::Button("_")) {
            menu = !menu;
        }  
        ImGui::SameLine();
        if (!showSettings && !showCameraViewer && !showPlanetViewer && !showDebugViewer && !showHelp) {
            if (ImGui::Button("+")) {
                showSettings = true;
                showCameraViewer = true;
                showPlanetViewer = true;
                showDebugViewer = true;
                showHelp = true;
            }
        } else if (showSettings && showCameraViewer && showPlanetViewer && showDebugViewer && showHelp) {
            if (ImGui::Button("-")) {
                showSettings = false;
                showCameraViewer = false;
                showPlanetViewer = false;
                showDebugViewer = false;
                showHelp = false;
            }       
        } else {
            if (ImGui::Button("+")) {
                showSettings = true;
                showCameraViewer = true;
                showPlanetViewer = true;
                showDebugViewer = true;
                showHelp = true; 
            }
        }
        ImGui::Separator();
        // settings
        if (ImGui::CollapsingHeader("Settings##1")) {
            drawSettings();
            ImGui::Separator();
            ImGui::Checkbox("show in new window##1", &showSettings);
        }
        // camera
        if (ImGui::CollapsingHeader("Camera Viewer##1")) {
            drawCameraViewer();
            ImGui::Separator();
            ImGui::Checkbox("show in new window##2", &showCameraViewer);
        }
        // planet
        if (ImGui::CollapsingHeader("Planet Viewer##1")) {
            drawPlanetViewer(*sg);
            ImGui::Separator();
            ImGui::Checkbox("show in new window##3", &showPlanetViewer);
        }
        // debug
        if (ImGui::CollapsingHeader("Debug Viewer##1")) {
            drawDebugViewer();
            ImGui::Separator();
            ImGui::Checkbox("show in new window##4", &showDebugViewer);
        }
        // help
        if (ImGui::CollapsingHeader("Help##1")) {
            drawHelp();
            ImGui::Separator();
            ImGui::Checkbox("show in new window##5", &showHelp);
        }
        // seperate windows
        if (showSettings) {
            closeCollapsingHeader("Settings##1");
            ImGui::Begin("Settings##2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
            drawSettings();
            ImGui::Separator();
            if (ImGui::Button("Close##1")) {
                showSettings = false;
                openCollapsingHeader("Settings##1");
            }
            ImGui::End();
        }
        if (showPlanetViewer) {
            closeCollapsingHeader("Planet Viewer##1");
            ImGui::Begin("Planet Viewer##2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
            drawPlanetViewer(*sg);
            ImGui::Separator();
            if (ImGui::Button("Close##2")) {
                showPlanetViewer = false;
                openCollapsingHeader("Planet Viewer##1");
            }
            ImGui::End();
        }
        if (showCameraViewer) {
            closeCollapsingHeader("Camera Viewer##1");
            ImGui::Begin("Camera Viewer##2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
            drawCameraViewer();
            ImGui::Separator();
            if (ImGui::Button("Close##3")) {
                showCameraViewer = false;
                openCollapsingHeader("Camera Viewer##1");
            }
            ImGui::End();
        }
        if (showDebugViewer) {
            closeCollapsingHeader("Debug Viewer##1");
            ImGui::Begin("Debug Viewer##2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
            drawDebugViewer();
            ImGui::Separator();
            if (ImGui::Button("Close##4")) {
                showDebugViewer = false;
                openCollapsingHeader("Debug Viewer##1");
            }
            ImGui::End();
        }    
        if (showHelp) {
            closeCollapsingHeader("Help##1");
            ImGui::Begin("Help##2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
            drawHelp();
            ImGui::Separator();
            if (ImGui::Button("Close##5")) {
                showHelp = false;
                openCollapsingHeader("Help##1");
            }
            ImGui::End();
        }
        ImGui::End();
    }
    return true;
}