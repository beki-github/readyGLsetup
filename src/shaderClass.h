#pragma once
#ifndef SHADER_H
#define SHADER_H
//
#include<glad/glad.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

//glm setup
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Shader {
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragPath);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, glm::vec3 objColor) const;
	void setMat4(const GLuint location, GLboolean transpose , glm::mat4 matrix);
	
private:
	void checkCompilationError(unsigned int shader, const std::string& type);
};


#endif
