/*
    EBO.h
    --------------------------------------------------------------------------------
    Archivo de cabecera para la declaración de la clase EBO, utilizada para la gestión de Element Buffer Objects en OpenGL.
    Header file for the declaration of the EBO class, used for managing Element Buffer Objects in OpenGL.
*/

#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
    GLuint ID;

    EBO(std::vector<GLuint>& indices);

    void Bind();
    void Unbind();
    void Delete();
};

#endif
