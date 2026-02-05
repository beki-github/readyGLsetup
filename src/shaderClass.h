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


class Shader {
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragPath);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	
private:
	void checkCompilationError(unsigned int shader, const std::string& type);
};


#endif
