#ifndef NODE_HPP
#define NODE_HPP

#include "glewInc.hpp"

#include "texture.hpp"
#include "model.hpp"

#include <vector>

// toggle movement of planets
extern bool isMoving;

class Node {
public:
    Node() {}
    Node(std::string aName, float aDistance, float aRotationSpeed, float aSize, 
         float aSelfRotSpeed, std::string aTexturePath = "");
    
    void setName(std::string aName);    
    std::string &getName() { return name; }

    void addChild(Node* node); 
    Node* &getChild(std::string aName);
    Node* &getAnyChild(std::string aName);
    std::vector<Node*> &getChildrenList() { return children; }

    void setParent(Node* node);
    Node* &getParent() { return parent; }

    void setLocalTransform(glm::fmat4& mat = glm::fmat4(1.0f));
    void setWorldTransform(glm::fmat4& mat = glm::fmat4(1.0f));
    glm::fmat4 &getLocalTransform() { return localTransform; }
    glm::fmat4 &getWorldTransform() { return worldTransform; }
    
    float &getSize() { return size; }
    float &getRotationSpeed() { return rotationSpeed; }
    float &getDistanceFromOrigin() { return distanceFromOrigin; }    

    void setTexture();
    Texture &getTexture() { return texture; }
    std::vector<Texture*> &getTextureList() { return allTexVec; }
    const std::string &getTexturePath() { return texturePath; }

    Model &getModel() { return model; }
    
    bool &getVisibility() { return isVisible; }
    void setVisibility(bool flag);   
    void toString();

private:
    Node* parent;
    std::vector<Node*> children;
   
    glm::fmat4 localTransform = glm::fmat4(1.0f);
    glm::fmat4 worldTransform = glm::fmat4(1.0f);

    std::string name;
    float distanceFromOrigin;
    float rotationSpeed;
    float selfRotSpeed;
    float size;
    bool isVisible = true;

    Model model;
    Texture texture;
    std::string texturePath;
    std::vector<Texture*> allTexVec;
};

#endif