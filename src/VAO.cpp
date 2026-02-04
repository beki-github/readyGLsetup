#include "VAO.h"

VAO::VAO(){
    glGenVertexArrays(1,&ID);
}

void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponent, GLenum type, GLsizeiptr stride, void *offset){
    VBO.Bind();
    glVertexAttribPointer(layout,numComponent,type,GL_FALSE,stride,offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}
void VAO::Bind(){
    glBindVertexArray(ID);
}
void VAO::Unbind(){
    glBindVertexArray(0);

}

void VAO::Delete(){
    glDeleteVertexArrays(1,&ID);
}