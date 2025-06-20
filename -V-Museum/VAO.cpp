/*
    VAO.cpp
    --------------------------------------------------------------------------------
    Archivo de implementación de la clase VAO. Gestiona la creación, configuración y manipulación de Vertex Array Objects en OpenGL, facilitando la organización de atributos de vértices.
    Incluye métodos para enlazar, desenlazar y eliminar VAOs, así como para vincular atributos de VBOs.

    --------------------------------------------------------------------------------
    Implementation file for the VAO class. Manages creation, setup, and manipulation of Vertex Array Objects in OpenGL, facilitating vertex attribute organization.
    Includes methods to bind, unbind, and delete VAOs, as well as to link VBO attributes.
*/

#include"VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO Attribute such as a position or color to the VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
