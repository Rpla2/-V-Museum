/*
    --------------------------------------------------------------------------------
    Archivo de cabecera para la declaración de la clase Camera, utilizada para la navegación 3D y gestión de la vista de cámara.
    Header file for the declaration of the Camera class, used for 3D navigation and camera view management.
    --------------------------------------------------------------------------------
*/

#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "shaderClass.h"

// Clase Camera para navegación y vista 3D
// Camera class for 3D navigation and view
class Camera
{
public:
    glm::vec3 Position; // Posición de la cámara / Camera position
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f); // Orientación / Orientation
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f); // Vector arriba / Up vector
    glm::mat4 cameraMatrix = glm::mat4(1.0f); // Matriz de cámara / Camera matrix

    bool firstClick = true; // Primer clic / First click

    int width;   // Ancho de la ventana / Window width
    int height;  // Alto de la ventana / Window height

    float speed = 5.0f;        // Velocidad de movimiento / Movement speed
    float sensitivity = 100.0f; // Sensibilidad del ratón / Mouse sensitivity

    // Constructor
    // Constructor
    Camera(int width, int height, glm::vec3 position);

    // Actualiza la matriz de cámara
    // Updates the camera matrix
    void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
    // Exporta la matriz de cámara al shader
    // Exports the camera matrix to the shader
    void Matrix(Shader& shader, const char* uniform);
    // Maneja las entradas del usuario para mover la cámara
    // Handles user input to move the camera
    void Inputs(GLFWwindow* window, float deltaTime);
};

#endif
