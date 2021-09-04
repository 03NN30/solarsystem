#include "node.hpp"
#include "sceneGraph.hpp"
#include "utils.hpp"

#include <SDL2/SDL.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>

bool isMoving = true;
float timer = 0.0f;
float speedSlider = 1.0f;

Node *foundNode;

Node::Node(std::string aName, float aDistance, float aRotationSpeed,
           float aSize, float aSelfRotSpeed, std::string aTexturePath) {
  name = aName;
  distanceFromOrigin = aDistance;
  rotationSpeed = aRotationSpeed;
  selfRotSpeed = aSelfRotSpeed;
  size = aSize;
  texturePath = aTexturePath;
  setTexture();
}

void Node::setName(std::string aName) { name = aName; }

void Node::addChild(Node *node) {
  node->setParent(this);
  children.emplace_back(node);
}

Node *&Node::getChild(std::string aName) {
  int size = children.size();

  for (int i = 0; i < size; i++) {
    if (children.at(i)->getName() == aName) {
      return children.at(i);
    }
  }
  std::cerr << aName + " is not a child of " + name << std::endl;
  throw std::exception();
}

void recursSearch(Node &it, std::string aName) {

  if (it.getName() == aName) {
    foundNode = &it;
  }

  if (!it.getChildrenList().empty()) {

    for (Node *itChild : it.getChildrenList()) {
      recursSearch(*itChild, aName);
    }
  }
}

Node *&Node::getAnyChild(std::string aName) {
  recursSearch(*this, aName);
  if (foundNode->getName() == aName) {
    return foundNode;
  } else {
    std::cerr << aName + " is not a child" << std::endl;
    throw std::exception();
  }
}

void Node::setParent(Node *node) {
  parent = node;
  // std::clog << node->getName() << " <-- " << name << std::endl;
}

void Node::setLocalTransform(glm::fmat4 &mat) {
  localTransform = mat * localTransform;
}

void Node::setWorldTransform(glm::fmat4 &mat) {
  timer = float(SDL_GetTicks()) / 1000.0f;

  glm::fmat4 trans = glm::fmat4(1.0f);

  static float rot, selfRot;

  if (isMoving) {
    rot = timer * rotationSpeed * speedSlider;
    selfRot = timer * selfRotSpeed * speedSlider;
    trans = glm::rotate(trans, rot, glm::fvec3{0.0f, 1.0f, 0.0f});
    trans = glm::translate(trans, glm::fvec3{0.0f, 0.0f, distanceFromOrigin});
    trans = glm::rotate(trans, selfRot,
                        glm::fvec3{0.0f, 1.0f, 0.0f}); // self rotation
    trans = glm::scale(trans, glm::fvec3{size, size, size});
  } else {
    trans = glm::rotate(trans, rot, glm::fvec3{0.0f, 1.0f, 0.0f});
    trans = glm::translate(trans, glm::fvec3{0.0f, 0.0f, distanceFromOrigin});
    trans = glm::rotate(trans, selfRot,
                        glm::fvec3{0.0f, 1.0f, 0.0f}); // self rotation
    trans = glm::scale(trans, glm::fvec3{size, size, size});
  }

  worldTransform = mat * localTransform * trans;
}

void Node::setTexture() {
  std::vector<std::string> texturePaths;

  unsigned int length = texturePath.length();
  for (int j = 0, k = 0; j < length; j++) {
    if (texturePath[j] == ',') {
      std::string ch = texturePath.substr(k, j - k);
      k = j + 1;
      texturePaths.push_back(ch);
    }
    if (j == length - 1) {
      std::string ch = texturePath.substr(k, j - k + 1);
      texturePaths.push_back(ch);
    }
  }

  for (const std::string &str : texturePaths) {
    Texture *ptr = new Texture();
    ptr->setTexturePath(str);
    ptr->set2DTexture(GL_REPEAT, GL_LINEAR);
    allTexVec.emplace_back(ptr);
  }
}

void Node::setVisibility(bool flag) { isVisible = flag; }

void Node::toString() {
  std::cout << "\nName: " << name << std::endl;

  if (children.empty()) {
    std::cout << "No children\n";
  } else {
    std::cout << "Children: ";
    for (auto it : children) {
      std::cout << it->getName() << " ";
    }
    std::cout << "\n";
  }
  std::cout << "Local transform: " << glm::to_string(localTransform)
            << std::endl;
  std::cout << "World transform: " << glm::to_string(worldTransform)
            << std::endl;
  std::cout << "D: " << distanceFromOrigin;
  std::cout << "  |  R: " << rotationSpeed;
  std::cout << "  |  S: " << size;
}