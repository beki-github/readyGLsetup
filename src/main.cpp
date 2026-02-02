#include <iostream>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"

char *vertexShaderSource="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
char *fragmentShaderSource= "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";
char *fragmentShaderSource2= "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(0.902f, 0.224f, 0.275f, 1.0f);\n"
    "}\0";
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
}; 

GLfloat triVertices[]={
       // original vertices
     0.0f,   0.5f,  0.0f,   // 0 = A (top)
    -0.5f,  -0.5f,  0.0f,   // 1 = B (left)
     0.5f,  -0.5f,  0.0f,   // 2 = C (right)

    // midpoints
    -0.25f,  0.0f,  0.0f,  // 3 = AB
     0.25f,  0.0f,  0.0f,  // 4 = AC
     0.0f,  -0.5f,  0.0f   // 5 = BC
};

GLuint triIndecies[]={
    0,3,4,
    1,3,5,
    5,4,2
};

//for compilation status 
int success;
char infoLog[512];

void checkGLError(const char* msg) {
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error after " << msg << ": " << err << std::endl;
    }
}



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

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    //checking compilation status
    //printing the error if compilation failed
    
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cout<<"VERTEX SHADER COMPILATION FAILED"<<infoLog<<std::endl;
    }


    GLuint fragmetShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmetShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmetShader);
    //checking compilation status
    //printing the error if compilation failed 
   
    glGetShaderiv(fragmetShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragmetShader,512,NULL,infoLog);
        std::cout<<"FRAGMENT SHADER COMPILATION FAILED"<<infoLog<<std::endl;
    }


    GLuint shaderProgram =glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmetShader);
    glLinkProgram(shaderProgram);

    //creating two different shader programs for second exersice 
    //we only need to create and compile the fragment shader and also create a new program

    GLuint fragmetShader2=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmetShader2,1,&fragmentShaderSource2,NULL);
    glCompileShader(fragmetShader2);
    //checking compilation status
    //printing the error if compilation failed 
   
    glGetShaderiv(fragmetShader2,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragmetShader2,512,NULL,infoLog);
        std::cout<<"FRAGMENT SHADER COMPILATION FAILED"<<infoLog<<std::endl;
    }
    
    GLuint shaderProgram2 =glCreateProgram();
    glAttachShader(shaderProgram2,vertexShader);
    glAttachShader(shaderProgram2,fragmetShader2);
    glLinkProgram(shaderProgram2);
    
   
    glGetProgramiv(shaderProgram2,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(shaderProgram2,512,NULL,infoLog);
        std::cout<<"LINKING FAILLED ERROR::"<<infoLog<<std::endl;
    }
     
    glDeleteShader(vertexShader);
    glDeleteShader(fragmetShader);
    glDeleteShader(fragmetShader2);

    VAO VAO2;
    VAO2.Bind();

    VBO VBO2(triVertices,sizeof(triVertices));
    EBO EBO2(triIndecies,sizeof(triIndecies));
   
    VAO2.linkVBO(VBO2,0);
   
    VAO2.Unbind();
    VBO2.Unbind();


    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices,sizeof(vertices));
    VAO1.linkVBO(VBO1,0);
    VAO1.Unbind();
    VBO1.Unbind();
    
    Shader shaderProgram3("shaders/shader.vert","shaders/shader.frag");
    while(!glfwWindowShouldClose(window)){

        glClearColor(0.039f, 0.059f, 0.122f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram3.Activate();
        VAO2.Bind();
        glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
        VAO2.Unbind();

        glUseProgram(shaderProgram);
        VAO1.Bind();
        glDrawArrays(GL_LINE_LOOP,0,4);
        VAO1.Unbind();
        
        glfwSwapBuffers(window);

        glfwPollEvents();

    }


    VAO1.Delete();
    VBO1.Delete();
    VAO2.Delete();
    VBO2.Delete();
    EBO2.Delete();
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgram2);
    

    //terminate glfw 
    glfwTerminate();
    glfwDestroyWindow(window);

    return 0;
}