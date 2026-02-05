#pragma once 
#include "stb/stb_image.h"
#include <glad/glad.h>
#include "ShaderClass.h"
#include<iostream>


/*this header file is for
texture class that is used to bind multiple 2D textures at once
*/
class Texture
{
public:
	GLuint ID;
	GLenum type;
	GLenum textureSlot;
	Texture(const char* imagePath, GLenum texType, GLenum slot, GLenum pixelType);

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
};
