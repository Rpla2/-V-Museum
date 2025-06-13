/*
    VBO.cpp
    --------------------------------------------------------------------------------
    Archivo de implementación de la clase VBO. Gestiona la creación, configuración y manipulación de Vertex Buffer Objects en OpenGL, permitiendo el almacenamiento eficiente de datos de vértices.
    Incluye métodos para enlazar, desenlazar y eliminar VBOs, así como para inicializarlos con datos de vértices personalizados.

    --------------------------------------------------------------------------------
    Implementation file for the VBO class. Manages creation, setup, and manipulation of Vertex Buffer Objects in OpenGL, enabling efficient storage of vertex data.
    Includes methods to bind, unbind, and delete VBOs, as well as to initialize them with custom vertex data.
*/

#include"VBO.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(std::vector<Vertex>& vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

// Binds the VBO
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
