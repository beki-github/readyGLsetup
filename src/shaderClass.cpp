#include "shaderClass.h"

std::string get_file_content(const char* filename) {
    // 1. Open in binary mode to prevent unexpected line-ending translations
    std::ifstream in(filename, std::ios::binary);
    
    if (in) {
        std::string contents;
        // 2. Seek to end to find size
        in.seekg(0, std::ios::end);
        size_t size = in.tellg();
        
        if (size > 0) {
            contents.resize(size);
            in.seekg(0, std::ios::beg);
            // 3. Read directly into the string's buffer
            in.read(&contents[0], size);
        }
        
        in.close();
        return contents;
    }
    
    // 4. Handle errors gracefully
    std::cerr << "Could not open file: " << filename << " (errno: " << errno << ")" << std::endl;
    throw(errno);
}

Shader::Shader(const char *vertexShaderFile, const char *fragmentShaderFile){

    std::string vCode = get_file_content(vertexShaderFile);
    std::string fCode = get_file_content(fragmentShaderFile);

    const char *vertexShaderSource = vCode.c_str();
    const char *fragmentShaderSource = fCode.c_str();

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
        std::cout<<"FRAGMENT SHADER COMPILATION FAILED "<<infoLog<<std::endl;
    }


    ID=glCreateProgram();
    glAttachShader(ID,vertexShader);
    glAttachShader(ID,fragmetShader);
    glLinkProgram(ID);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmetShader);


}

void Shader::Activate(){
    glUseProgram(ID);
}

void Shader::Delete(){
    glDeleteProgram(ID);
}