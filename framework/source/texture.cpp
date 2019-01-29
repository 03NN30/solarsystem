#include "texture.hpp"
#include "utils.hpp"

#include "stb_image.hpp"

#include <iostream>

Texture::Texture() {}

Texture::Texture(const std::string& aPath) {
    path = resource_path + "textures/" + aPath;
}

void Texture::setTexturePath(const std::string& aPath) {
    path = resource_path + "textures/" + aPath;
}

std::string &Texture::getPath() {
    return path;
}

unsigned int &Texture::getID() {
    return texture;
}

void Texture::set2DTexture(const GLenum& wrapper, const GLenum& filter) {
 
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapper);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapper);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
   
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "ERROR::TEXTURE::FAILED TO LOAD::" << path << std::endl;
    }
    stbi_image_free(data);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, texture);
}
