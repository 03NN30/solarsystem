#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glewInc.hpp"
#include "utils.hpp"
#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// move camera
enum m_Camera { m_forwards, m_backwards, m_down, m_up, m_left, m_right };

// follow camera
enum f_Camera { f_behind, f_front, f_left, f_right, f_top, f_bottom };

class Camera {

public:
  glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 up;
  glm::vec3 right;
  float yaw = -90.0f;
  float pitch = 0.0f;
  float sensitivity = 0.06f;
  float fov = 45.0f;

  static Camera &get() {
    static Camera instance;
    return instance;
  }

  void proessKeyboard(m_Camera direction, float cameraSpeed);
  void processMouseMotion(float xoffset, float yoffset);

  void follow(glm::fmat4 &mat, f_Camera direction, float size);
  void neutralizeAngles();

  glm::mat4 getViewMatrix() {
    return glm::lookAt(position, position + front, up);
  }
  glm::mat4 getProjectionMatrix() {
    return glm::perspective(glm::radians(fov),
                            (float)screenWidth / (float)screenHeight, 0.1f,
                            100.0f);
  }

private:
  Camera();
  void updateCameraVectors();
};

#endif