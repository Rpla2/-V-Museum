#version 330 core

// Entrada de posici�n del v�rtice (atributo 0)
// Vertex position input (attribute 0)
layout (location = 0) in vec3 aPos;

// Entrada de color del v�rtice (atributo 1)
// Vertex color input (attribute 1)
layout (location = 1) in vec3 aColor;

// Salida del color interpolado hacia el fragment shader
// Output of interpolated color to the fragment shader
out vec3 color;

// Matriz de c�mara para transformar la posici�n del v�rtice
// Camera matrix to transform the vertex position
uniform mat4 camMatrix;

// Funci�n principal del vertex shader
// Main function of the vertex shader
void main()
{
    // Calcula la posici�n final del v�rtice en el espacio de recorte
    // Calculates the final vertex position in clip space
    gl_Position = camMatrix * vec4(aPos, 1.0);

    // Pasa el color del v�rtice al fragment shader
    // Passes the vertex color to the fragment shader
    color = aColor;
}
