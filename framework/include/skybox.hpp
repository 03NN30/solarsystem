#include "glewInc.hpp"
#include "model.hpp"
#include <string>
#include <vector>

class Skybox {
public:
    Skybox();
    Skybox(const std::string& a, const std::string& b, const std::string& c, 
           const std::string& d, const std::string& e, const std::string& f, 
           const GLenum& wrapper = GL_CLAMP_TO_EDGE, const GLenum& filter = GL_LINEAR);

    void setGeometry();
    
    void setPaths(const std::string& a, const std::string& b, const std::string& c, 
                  const std::string& d, const std::string& e, const std::string& f);
    void setTexture();
    void bind();

    unsigned int &getID() { return ID; }
    float &getSize() { return size; }
    std::vector<std::string> &getPathsList() { return pathsList; }

private:
    unsigned int ID;
    std::string img1, img2, img3, img4, img5, img6;
    std::vector<std::string> pathsList;
    float size = 100.0f;
};