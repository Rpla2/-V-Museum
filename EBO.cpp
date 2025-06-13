/*
    EBO.cpp
    --------------------------------------------------------------------------------
    Archivo de implementación de la clase EBO. Encargado de la gestión de Element Buffer Objects en OpenGL, permitiendo el renderizado indexado eficiente.
    Incluye métodos para crear, enlazar, desenlazar y eliminar EBOs.

    --------------------------------------------------------------------------------
    Implementation file for the EBO class. Handles the management of Element Buffer Objects in OpenGL, enabling efficient indexed rendering.
    Includes methods to create, bind, unbind, and delete EBOs.
*/

#include "EBO.h"

// Constructor that generates a Elements Buffer Object and links it to indices
EBO::EBO(std::vector<GLuint>& indices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

// Binds the EBO
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
