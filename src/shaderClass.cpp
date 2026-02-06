#include "ShaderClass.h"

Shader::Shader(const char *vertexPath,const char *fragPath) {
	std::string vertCode;
	std::string fragCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragPath);
		std::cout << std::string(vertexPath) << "\n" << std::string(fragPath) << "\n";
		std::stringstream vShaderStream, fShaderStream;
		
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertCode = vShaderStream.str();
		fragCode = fShaderStream.str();
	}
	catch(std::ifstream::failure &e){
		std::cout << "ERROR::FILE_READING_FAILED" << std::endl;
	}
	
	const char* vShaderCode = vertCode.c_str();
	const char* fShaderCode = fragCode.c_str();

	unsigned int vertex, fragment;
	//
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompilationError(vertex, "SHADER");
	//
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompilationError(fragment, "SHADER");
	//
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompilationError(ID, "PROGRAM");

}

void Shader::use() {
	glUseProgram(ID);

}

void Shader::setBool(const std::string& name, bool value)const{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value)const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value)const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()),value);
}

void Shader::setVec3(const std::string& name, glm::vec3 objColor) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()),1,glm::value_ptr(objColor));
}

void Shader::setMat4( const GLuint location, GLboolean transpose , glm::mat4 matrix)  {
	// glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	glUniformMatrix4fv(location, 1,transpose, glm::value_ptr(matrix));

}




void Shader::checkCompilationError(unsigned int shader, const std::string& type) {
		int success;
		char infolog[512];
		if (type == "SHADER") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 512, NULL, infolog);
				std::cout << "OPENGL::ERROR::COMPILATIONFAILLED::\n" << infolog << std::endl;
			}
		} else if (type == "PROGRAM") {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 512, NULL, infolog);
				std::cout << "OPENGL::ERROR::LINKINGFAILLED::\n" << infolog << std::endl;
			}
		}

}