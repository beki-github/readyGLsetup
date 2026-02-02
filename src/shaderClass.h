#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <cerrno>

std::string get_file_content(const char *filename);

class Shader {
    private:
      int success;
      char infoLog[512];
    public:
      GLuint ID;//a reference 
      Shader(const char *vertexShaderFile, const char *fragmentShaderFile);

      void Activate();
      void Delete();

};
#endif