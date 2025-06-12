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

// Clase para gestionar la c�mara 3D y su interacci�n con el usuario
// Class for managing the 3D camera and user interaction
class Camera
{
public:
	// Posici�n y orientaci�n de la c�mara en el espacio 3D
	// Camera position and orientation in 3D space
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// Indica si es el primer clic para evitar saltos bruscos del rat�n
	// Indicates if it's the first click to avoid abrupt mouse jumps
	bool firstClick = true;

	// Dimensiones de la ventana de renderizado
	// Render window dimensions
	int width;
	int height;

	// Par�metros de velocidad y sensibilidad de la c�mara
	// Camera speed and sensitivity parameters
	float speed = 0.1f;
	float sensitivity = 100.0f;

	// Constructor: inicializa la c�mara con tama�o de ventana y posici�n
	// Constructor: initializes the camera with window size and position
	Camera(int width, int height, glm::vec3 position);

	// Calcula y env�a la matriz de la c�mara al shader
	// Calculates and sends the camera matrix to the shader
	void Matrix(Shader& shader, const char* uniform);

	// Procesa la entrada del usuario para movimiento y rotaci�n
	// Processes user input for movement and rotation
	void Inputs(GLFWwindow* window);

	// Restablece el estado de primer clic para el control del rat�n
	// Resets the first click state for mouse control
	void ResetFirstClick();
};
#endif
