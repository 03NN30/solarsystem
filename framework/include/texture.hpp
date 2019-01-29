#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "glewInc.hpp"

#include <string>

class Texture {

public:
    Texture();
    Texture(const std::string& aPath);
    std::string &getPath();
    unsigned int &getID();

    void setTexturePath(const std::string& aPath);
    void set2DTexture(const GLenum& wrapper, const GLenum& filter);
    void bind();

private:
    unsigned int texture;
    std::string path;    
};

#endif