#include "skybox.hpp"
#include "utils.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

#include <iostream>

Skybox::Skybox() {}

Skybox::Skybox(const std::string& a, const std::string& b, const std::string& c, 
               const std::string& d, const std::string& e, const std::string& f, 
               const GLenum& wrapper, const GLenum& filter) 
{
    img1 = a; img2 = b; img3 = c; img4 = d; img5 = e; img6 = f;
}

void Skybox::setPaths(const std::string& a, const std::string& b, const std::string& c, 
                      const std::string& d, const std::string& e, const std::string& f) 
{
    std::string texture_path = resource_path + "textures/";
    img1 = a; img2 = b; img3 = c; img4 = d; img5 = e; img6 = f;
    pathsList.push_back(texture_path + img1);
    pathsList.push_back(texture_path + img2);
    pathsList.push_back(texture_path + img3);
    pathsList.push_back(texture_path + img4);
    pathsList.push_back(texture_path + img5);
    pathsList.push_back(texture_path + img6);
    setTexture();
}

void Skybox::setTexture() {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < pathsList.size(); i++) {
        unsigned char *data = stbi_load(pathsList[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else  {
            std::cout << "ERROR::SKYBOX::FAILED TO LOAD TEXTURE::" << pathsList[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}  

void Skybox::bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}
