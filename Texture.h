/*
    Texture.h
    --------------------------------------------------------------------------------
    Archivo de cabecera para la declaración de la clase Texture, utilizada para la gestión de texturas en OpenGL.
    Header file for the declaration of the Texture class, used for texture management in OpenGL.
*/

#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	const char* type;
	GLuint unit;

	Texture(const char* image, const char* texType, GLuint slot);

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
};
#endif

