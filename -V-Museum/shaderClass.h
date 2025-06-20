/*
    shaderClass.h
    --------------------------------------------------------------------------------
    Archivo de cabecera para la declaración de la clase Shader, utilizada para la gestión de shaders en OpenGL.
    Header file for the declaration of the Shader class, used for shader management in OpenGL.
*/

#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader {

// Loads and compiles the shader from the given vertex and fragment files.
// Carga y compila el shader a partir de los archivos de vértices y fragmentos dados.
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
};
#endif

