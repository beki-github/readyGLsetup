#include <iostream>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "stb/stb_image.h"
#include "shaderClass.h"


GLfloat vertices[] = {
    // coordinates         //colors           //texCoordinates
    -0.5f, -0.5f, 0.0f,   0.5f,0.0f,0.0f,     0.0f,0.0f,
     0.5f, -0.5f, 0.0f,   0.5f,0.0f,0.0f,     0.0f,1.0f,
     0.5f,  0.5f, 0.0f,   0.5f,0.0f,0.0f,     1.0f,1.0f,
    -0.5f,  0.5f, 0.0f,   0.5f,0.0f,0.0f,     1.0f,0.0f
}; 

GLuint indecies[]={
    0,1,2,
    0,2,3
};





int main(){
    //intalize glfw 
    glfwInit();
    std::cout<<"Current working directory: "<< std::filesystem::current_path()<<std::endl;
    //specifying which version of opengl version we are using the minor and major 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    //specfiying which profile it uses, set of functions 
    //we are only using modern functions only!!!
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //now to the window itself 

    GLFWwindow *window = glfwCreateWindow(480,480,"test",NULL,NULL);
    if(window==NULL){
        std::cout<<"failed to open the window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    //this line below is self explanitory 
    //context means an object that hold the whole of opengl
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0,0,480,480);
     
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices,sizeof(vertices));
    EBO EBO1(indecies,sizeof(indecies));
    
    VAO1.linkAttrib(VBO1,0,3,GL_FLOAT,8*sizeof(float),(void*)0);
    VAO1.linkAttrib(VBO1,1,3,GL_FLOAT,8*sizeof(float),(void*)(sizeof(float)*3));
    VAO1.linkAttrib(VBO1,1,2,GL_FLOAT,8*sizeof(float),(void*)(sizeof(float)*6));
    


    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    Shader shaderProgram3("shaders/shader.vert","shaders/shader.frag");

    // time for textures 
    
    int imgWidth,imgHeight,numCloch;

    unsigned char * byte =stbi_load("assets/power.png",&imgWidth,&imgHeight,&numCloch,0);
    if (!byte) {
    std::cout << "FAILED TO LOAD TEXTURE: Check your file path!" << std::endl;
    return -1; // Stop the crash and see the error
}


    GLuint texture;
    glGenTextures(1,&texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imgWidth,imgHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,byte);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(byte);
    glBindTexture(GL_TEXTURE_2D,texture);

    GLuint tex0 = glad_glGetUniformLocation(shaderProgram3.ID,"tex0");
    shaderProgram3.Activate();
    glUniform1i(tex0,0);

    while(!glfwWindowShouldClose(window)){

        glClearColor(0.039f, 0.059f, 0.122f,0.3f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram3.Activate();
        VAO1.Bind();
        glBindTexture(GL_TEXTURE_2D,texture);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        
        glfwSwapBuffers(window);

        glfwPollEvents();

    }


    
    shaderProgram3.Delete();
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    

    //terminate glfw 
    glfwTerminate();
    glfwDestroyWindow(window);

    return 0;
}