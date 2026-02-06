#include <iostream>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "shaderClass.h"
#include "Debugger.h"


GLfloat vertices[] = {
    // coordinates          //colors           //texCoordinates
    -0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Bottom-Left
     0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Bottom-Right
     0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Top-Right
    -0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Top-Left
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    //specfiying which profile it uses, set of functions 
    //we are only using modern functions only!!!
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    //for debugging from learnopengl.com
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    //now to the window itself 
    GLuint windowWidth=800;
    GLuint windowHeight=600;
    GLFWwindow *window = glfwCreateWindow(windowWidth,windowHeight,"test",NULL,NULL);
    if(window==NULL){
        std::cout<<"failed to open the window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    //this line below is self explanitory 
    //context means an object that hold the whole of opengl
    glfwMakeContextCurrent(window);

    gladLoadGL();
    EnableModernDebugging();


    glViewport(0,0,windowWidth,windowHeight);
     
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices,sizeof(vertices));
    EBO EBO1(indecies,sizeof(indecies));
    
    VAO1.linkAttrib(VBO1,0,3,GL_FLOAT,8*sizeof(float),(void*)0);
    VAO1.linkAttrib(VBO1,1,3,GL_FLOAT,8*sizeof(float),(void*)(sizeof(float)*3));
    VAO1.linkAttrib(VBO1,2,2,GL_FLOAT,8*sizeof(float),(void*)(sizeof(float)*6));
    


    VAO1.Unbind();
    VBO1.Unbind();
    
    

    Shader shaderProgram3("shaders/shader.vert","shaders/shader.frag");

    const char* imgPath = "assets/bricks.jpg";
    Texture popCat(imgPath, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram3, "tex0", 0);
    popCat.Bind();


  
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection;

    
    view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));
    projection = glm::perspective(glm::radians(45.0f),(float)windowWidth/(float)windowHeight,0.1f,100.0f);

    shaderProgram3.use();
    
    shaderProgram3.setMat4(1,GL_FALSE,view);
    shaderProgram3.setMat4(2,GL_FALSE,projection);

    
    while(!glfwWindowShouldClose(window)){

        glClearColor(0.039f, 0.059f, 0.122f,0.3f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        VAO1.Bind();
       for(int i=1;i<8;i++){
        for(int j=1;j<24;j++){ 
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model,glm::radians(-55.0f),glm::vec3(1.0f,0.0f,0.0f));
        model =glm::translate(model,glm::vec3((float)i-4,(float)j-1,-2.0f));
        shaderProgram3.setMat4(0,GL_FALSE,model);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        }
       }
        
        
        //
        glfwSwapBuffers(window);

        glfwPollEvents();

    }


    
    
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    popCat.Delete();

    //terminate glfw 
    glfwTerminate();
    glfwDestroyWindow(window);

    return 0;
}