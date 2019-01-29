#include "shader.hpp"
#include "utils.hpp"

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

Shader::Shader() {}

Shader::Shader(std::string str) {
    vertexSource = str + ".vert";
    fragmentSource = str + ".frag";
}

void Shader::setSource(std::string str) {
    vertexSource = str + ".vert";
    fragmentSource = str + ".frag";
}

std::string ParseShader(const std::string& filepath) {
	std::ifstream stream(resource_path + "shaders/" + filepath);
	std::string line;
	std::stringstream ss[1];
	
	while (getline(stream, line)) {
		ss[0] << line << '\n';
	}
    //std::cout << ss[0].str() << std::endl;
	return ss[0].str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	GLint success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "Failed to compile shader\n" << infoLog << std::endl;
    }
	return id;
}

 
void Shader::createShader() {
    ID = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, ParseShader(vertexSource));
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, ParseShader(fragmentSource));
    
	glAttachShader(ID, vs);
	glAttachShader(ID, fs);
	glLinkProgram(ID);
	glValidateProgram(ID);
    
	int success;
    char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "Failed to link shader program\n" << infoLog << std::endl;
    }

	glDeleteShader(vs);
	glDeleteShader(fs);
}

unsigned int &Shader::getID() {
    return ID;
}

void Shader::use() { 
    glUseProgram(ID); 
}

void Shader::setBool(const std::string &name, bool value) const {         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const { 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const { 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setfVec2(const std::string &name, const glm::fvec2 &value) const { 
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void Shader::setfVec2(const std::string &name, float x, float y) const { 
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
}

void Shader::setfVec3(const std::string &name, const glm::fvec3 &value) const { 
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void Shader::setfVec3(const std::string &name, float x, float y, float z) const { 
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}

void Shader::setfVec4(const std::string &name, const glm::fvec4 &value) const { 
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void Shader::setfVec4(const std::string &name, float x, float y, float z, float w) { 
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
}

void Shader::setfMat2(const std::string &name, const glm::fmat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setfMat3(const std::string &name, const glm::fmat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setfMat4(const std::string &name, const glm::fmat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setView(const glm::fmat4 &mat) const {
    glUseProgram(ID);
    glUniformMatrix4fv(glGetUniformLocation(ID, "view"), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setProjection(const glm::fmat4 &mat) const {
    glUseProgram(ID);
    glUniformMatrix4fv(glGetUniformLocation(ID, "projection"), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setModel(const glm::fmat4 &mat) const {
    glUseProgram(ID);
    glUniformMatrix4fv(glGetUniformLocation(ID, "model"), 1, GL_FALSE, &mat[0][0]);
}
