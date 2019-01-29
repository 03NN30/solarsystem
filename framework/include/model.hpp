#ifndef MODEL_HPP
#define MODEL_HPP

#include "glewInc.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

struct vertexInfo {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct modelObject {
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint NBO = 0;
    GLuint TBO = 0;
    GLuint EBO = 0;
    GLenum draw_mode = GL_NONE;
    GLsizei num_elements = 0;
};

class Model {
public:
    Model() {};
    Model(unsigned short amount);
    Model(const std::string &path);

    void toString();
    modelObject &getModelObject();
    void parseObj(const std::string &path);
    void splitF(const std::string& str);
    void sort();
    void setGeometry(GLenum draw_mode);
    void setVertexAttributes();
    void draw();

private:
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_textures;
    std::vector<glm::vec3> out_normals;
    std::vector<glm::vec3> vertexPos;
    std::vector<glm::vec3> normalPos;
    std::vector<glm::vec2> texturePos;
    std::vector<int> vertexIndex;
    std::vector<int> textureIndex;
    std::vector<int> normalIndex;

    bool gotPosition = false;
    bool gotNormal = false;
    bool gotTexture = false;
    bool gotIndex = false;

    unsigned short vertexAttribs;

    modelObject model_object;
};

#endif