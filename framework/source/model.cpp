#include "model.hpp"
#include "utils.hpp"

#include <sstream>
#include <fstream>
#include <iostream>

vertexInfo split(const std::string& str) {
    std::istringstream iss(str);
    std::vector<float> temp;
    do {
        std::string subs;
        iss >> subs;
        temp.push_back(::atof(subs.c_str()));
    } while (iss);
    
    return {temp.at(0), temp.at(1), temp.at(2)};
}

void Model::splitF(const std::string& str) {
    unsigned int length = str.length();
    std::vector<float> temp;
    bool flag1 = 1, flag2 = 0, flag3 = 0;
    for (int j = 0, k = 0; j < length; j++) {        
        if (str[j] == '/') {
            std::string ch = str.substr(k, j - k);
            k = j+1;
            if (flag1) {
                vertexIndex.push_back(std::stoi(ch));
                flag1 = 0;
                flag2 = 1;
            } else if (flag2) {
                textureIndex.push_back(std::stoi(ch));
                flag2 = 0;
                flag3 = 1;
            } else if (flag3) {
                normalIndex.push_back(std::stoi(ch));
                flag3 = 0;
                flag1 = 1;
            }
        }
        if (j == length - 1) {
            std::string ch = str.substr(k, j - k+1);
            if (flag1) {
                vertexIndex.push_back(std::stoi(ch));
                flag1 = 0;
                flag2 = 1;
            } else if (flag2) {
                textureIndex.push_back(std::stoi(ch));
                flag2 = 0;
                flag3 = 1;
            } else if (flag3) {
                normalIndex.push_back(std::stoi(ch));
                flag3 = 0;
                flag1 = 1;
            }
        }
    }
}

void Model::sort() {
    if (gotPosition && gotTexture && gotNormal && gotIndex) {
        for (unsigned int i = 0; i < vertexIndex.size(); i++) {
            unsigned int vertIndex = vertexIndex[i];
            unsigned int texIndex = textureIndex[i];
            unsigned int normIndex = normalIndex[i];

            glm::vec3 vertex = vertexPos[vertIndex-1];
            glm::vec2 uv = texturePos[texIndex-1];
            glm::vec3 normal = normalPos[normIndex-1];

            out_vertices.push_back(vertex);
            out_textures.push_back(uv);
            out_normals.push_back(normal);
        }
    } else {
        std::cerr << "ERROR::MODEL_LOADER::INDEXING FAILED" << std::endl;
    }
}

Model::Model(const std::string &path) {
    file_path = path;
    unsigned int found = path.find(".");
    if (found!=std::string::npos) {
        if (path.substr(found) == ".obj") {
            parseObj(resource_path + "models/" + path);
        }
        else {
            std::cerr << "ERROR::MODEL_LOADER::FILE FORMAT " << path.substr(found) << " NOT SUPPORTED" << std::endl;
        }
    }
}

Model::Model(unsigned short amount) {
    vertexAttribs = amount;
}

void Model::parseObj(const std::string path) {
    std::ifstream myfile(path);
	std::string line = "";
    if (myfile.is_open()) {
	    while (getline(myfile, line)) {
            // vertex coords
	      	if (line[0] == 'v' && line[1] == ' ') { 
                gotPosition = true;
                vertexInfo v = split(line.substr(1));
                glm::vec3 temp;
                temp.x = v.x;
                temp.y = v.y;
                temp.z = v.z;
                vertexPos.push_back(temp);
	      	}
            // normal coords
            else if (line[0] == 'v' && line[1] == 'n') {
                gotNormal = true;
                vertexInfo vn = split(line.substr(2));
                glm::vec3 temp;
                temp.x = vn.x;
                temp.y = vn.y;
                temp.z = vn.z;
                normalPos.push_back(temp);

            }
            // tex coords
            else if (line[0] == 'v' && line[1] == 't') {
                gotTexture = true;
                vertexInfo vt = split(line.substr(2));
                glm::vec3 temp;
                temp.x = vt.x;
                temp.y = vt.y;
                texturePos.push_back(temp);
            } 
            // indices
            else if (line[0] == 'f' && line[1] == ' ') {
                gotIndex = true;
                // split by " "
                std::istringstream iss(line.substr(1));
                std::vector<std::string> temp;

                do {
                    std::string subs;
                    iss >> subs;
                    temp.push_back(subs);
                } while (iss);

                for (auto& it : temp) {
                    splitF(it);
                }
            }		
        }
    } else {
        myfile.close();
        std::cerr << "ERROR::MODEL_LOADER::CANT OPEN FILE:\n" << path << std::endl; 
        throw std::exception();
    }
    myfile.close();
    sort();
}

void Model::setGeometry(GLenum draw_mode) {
    glGenVertexArrays(1, &model_object.VAO);
    glBindVertexArray(model_object.VAO);
     
    if (gotPosition && gotTexture && gotNormal && gotIndex) {
        glGenBuffers(1, &model_object.VBO);
	    glBindBuffer(GL_ARRAY_BUFFER, model_object.VBO);
        glBufferData(GL_ARRAY_BUFFER, out_vertices.size() * sizeof(glm::vec3), &out_vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &model_object.TBO);
	    glBindBuffer(GL_ARRAY_BUFFER, model_object.TBO);
        glBufferData(GL_ARRAY_BUFFER, out_textures.size() * sizeof(glm::vec2), &out_textures[0], GL_STATIC_DRAW);

	    glGenBuffers(1, &model_object.NBO);
	    glBindBuffer(GL_ARRAY_BUFFER, model_object.NBO);
        glBufferData(GL_ARRAY_BUFFER, out_normals.size() * sizeof(glm::vec3), &out_normals[0], GL_STATIC_DRAW);
    }
    else {
        std::cerr << "ERROR::MODEL::VERTEX BUFFER" << std::endl;
    }
    model_object.num_elements = out_vertices.size();
    model_object.draw_mode = draw_mode;
}

void Model::setVertexAttributes() {
    glBindVertexArray(model_object.VAO);
    if (gotIndex && gotNormal && gotTexture && gotPosition) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, model_object.VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, model_object.TBO);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, model_object.NBO);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    } else {
        std::cerr << "ERROR::MODEL::NOT ENOUGH VERTEX ATTRIBUTES" << std::endl;
    }
    
    model_object.num_elements = out_vertices.size();
}

void Model::draw() {
    glBindVertexArray(model_object.VAO);
    glDrawArrays(model_object.draw_mode, 0, model_object.num_elements);

    if (gotPosition && gotTexture && gotNormal && gotIndex) {
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
    } else {
        std::cerr << "ERROR::MODEL::DISABLE VERTEX ATTRIBUTES" << std::endl;
    }
}

void Model::instanceDraw(int amount) {
    glBindVertexArray(model_object.VAO);
    glDrawArraysInstanced(model_object.draw_mode, 0, model_object.num_elements, amount);

    if (gotPosition && gotTexture && gotNormal && gotIndex) {
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
    } else {
        std::cerr << "ERROR::MODEL::DISABLE VERTEX ATTRIBUTES" << std::endl;
    }
}

modelObject &Model::getModelObject() {
    return model_object;
}