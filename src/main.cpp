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
#include "Camera.h"
#include "Debugger.h"


void processInput(GLFWwindow* window, float currentTime);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//gloabal variable intalization 
float lastFrame=0.0f;
float deltaTime;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

//global intial states for the camera
glm::vec3 cameraPos= glm::vec3(0.0f,0.25f,6.0f);
glm::vec3 cameraUp = glm::vec3(0.0f,1.0f,0.0f);
//setting the intial state of the mouse to the center of the camera
float lastX = 400;
float lastY = 300;
//initial entry to true
bool firstEntry = true;
//first camera offsets 
float yaw = -90.0f;
float pitch = 0.0f;
//
Camera camera = Camera(cameraPos,cameraUp);

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
    EBO EBO1(indices,sizeof(indices));
    
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


    glm::mat4 model=glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection;

    model=glm::translate(model,glm::vec3(0.0f,0.0f,0.0f));
   
    projection = glm::perspective(glm::radians(45.0f),(float)windowWidth/(float)windowHeight,0.1f,100.0f);

    shaderProgram3.use();
    
    

    //trying to implement a camera!!
   
    
    shaderProgram3.setMat4(2,GL_FALSE,projection);

    
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    while(!glfwWindowShouldClose(window)){

        glClearColor(0.039f, 0.059f, 0.122f,0.3f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        processInput(window,glfwGetTime());
        VAO1.Bind();
        model=glm::rotate(model,glm::radians(0.004f),glm::vec3(0.0f,1.0f,0.0f));
        shaderProgram3.setMat4(0,GL_FALSE,model);
        view=camera.GetViewMatrix();
        shaderProgram3.setMat4(1,GL_FALSE,view);
        glDrawElements(GL_TRIANGLES,sizeof(indices)/sizeof(int),GL_UNSIGNED_INT,0);
        
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
void processInput(GLFWwindow* window, float currentTime) {
    
    deltaTime =currentTime-lastFrame;
    lastFrame=currentTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //movement in z axis 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    //movement in x axis
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    const float sensitivity = 0.05f; // Reduced for touchpad
    if (firstEntry) {
        lastX = xPos;
        lastY = yPos;
        firstEntry = false;
        return;
    }
    float xChange = static_cast<float>(sensitivity * (xPos - lastX));
    float yChange = static_cast<float>(sensitivity * (lastY - yPos));
    lastX = xPos;
    lastY = yPos;
    //
    camera.ProcessMouseMovement(xChange, yChange);
    //
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  glViewport(0,0,width,height);
}