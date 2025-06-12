#version 330 core

// Color de salida del fragmento
// Output color of the fragment
out vec4 FragColor;

// Color interpolado recibido desde el vertex shader
// Interpolated color received from the vertex shader
in vec3 color;

// Función principal del fragment shader
// Main function of the fragment shader
void main()
{
    // Asigna el color recibido con opacidad total al fragmento
    // Assigns the received color with full opacity to the fragment
    FragColor = vec4(color, 1.0);
}
