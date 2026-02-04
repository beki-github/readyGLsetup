#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include<VBO.h>

class VAO{
    public:
     GLuint ID;
     VAO();
     
     void linkAttrib(VBO& VBO, GLuint layout, GLuint numComponent, GLenum type, GLsizeiptr stride, void *offset);
     void Bind();
     void Unbind();
     void Delete();
};

#endif