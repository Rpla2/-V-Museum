#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// Lee el contenido de un archivo y lo devuelve como string
// Reads the contents of a file and returns it as a string
std::string get_file_contents(const char* filename);

// Clase para gestionar programas de shader en OpenGL
// Class for managing OpenGL shader programs
class Shader
{
public:
	GLuint ID; // Identificador del programa de shader
	// Shader program identifier

// Constructor: compila y enlaza los shaders de vértices y fragmentos
// Constructor: compiles and links vertex and fragment shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activa el programa de shader
	// Activates the shader program
	void Activate();

	// Elimina el programa de shader
	// Deletes the shader program
	void Delete();
};

#endif
