#include "Camera.h"

// Constructor de la c�mara: inicializa el tama�o de la ventana y la posici�n de la c�mara
// Camera constructor: initializes window size and camera position
Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

// Calcula y env�a la matriz de vista-proyecci�n al shader
// Calculates and sends the view-projection matrix to the shader
void Camera::Matrix(Shader& shader, const char* uniform)
{
	if (width == 0 || height == 0) return;

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

	cameraMatrix = projection * view;

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

// Gestiona la entrada del usuario para el movimiento y rotaci�n de la c�mara
// Handles user input for camera movement and rotation
void Camera::Inputs(GLFWwindow* window)
{
	// Movimiento con teclas WASD, espacio y control
	// Movement with WASD keys, space and control
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Position += speed * Orientation;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position += speed * -Orientation;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		Position += speed * Up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		Position += speed * -Up;

	// Ajuste de velocidad con la tecla Shift
	// Speed adjustment with Shift key
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		speed = 0.4f;
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		speed = 0.1f;

	// Obtenci�n de la posici�n actual del cursor
	// Get current mouse cursor position
	double mouseX;
	double mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	// Centra el cursor la primera vez para evitar saltos bruscos
	// Center the cursor the first time to avoid abrupt jumps
	if (firstClick)
	{
		glfwSetCursorPos(window, (width / 2.0), (height / 2.0));
		firstClick = false;
	}

	// C�lculo de la rotaci�n de la c�mara seg�n el movimiento del rat�n
	// Calculate camera rotation based on mouse movement
	float rotX = sensitivity * (float)(mouseY - (height / 2.0)) / height;
	float rotY = sensitivity * (float)(mouseX - (width / 2.0)) / width;

	glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

	// Limita la rotaci�n vertical para evitar invertir la c�mara
	// Limit vertical rotation to prevent camera inversion
	if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		Orientation = newOrientation;
	}

	Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

	// Restaura el cursor al centro de la ventana tras procesar la entrada
	// Restore cursor to window center after processing input
	glfwSetCursorPos(window, (width / 2.0), (height / 2.0));
}

// Restablece el estado de primer clic para el control del rat�n
// Resets the first click state for mouse control
void Camera::ResetFirstClick()
{
	firstClick = true;
}
