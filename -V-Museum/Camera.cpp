/*
    --------------------------------------------------------------------------------
    Archivo de implementación de la clase Camera. Gestiona la navegación 3D, el movimiento, la orientación y la matriz de vista de la cámara en la aplicación.
    Proporciona métodos para actualizar la matriz de la cámara, manejar entradas del usuario y exportar la matriz para su uso en shaders.
    
    Implementation file for the Camera class. Manages 3D navigation, movement, orientation, and the camera view matrix in the application.
    Provides methods to update the camera matrix, handle user input, and export the matrix for use in shaders.
	--------------------------------------------------------------------------------
*/

#include "Camera.h"
#include "imgui.h"
#include "AABBDefs.h"

// Referencia externa para la función de colisión de la cámara
// External reference for camera collision function
extern bool CameraCollides(const glm::vec3& camPos);

// Constructor de la cámara
// Camera constructor
Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

// Actualiza la matriz de la cámara
// Updates the camera matrix
void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::lookAt(Position, Position + Orientation, Up);
	glm::mat4 projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
	cameraMatrix = projection * view;
}

// Exporta la matriz de la cámara al shader
// Exports the camera matrix to the shader
void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

// Maneja las entradas del usuario para mover la cámara
// Handles user input to move the camera
void Camera::Inputs(GLFWwindow* window, float deltaTime)
{
	// Deshabilita captura del ratón por ImGui para evitar parpadeo del cursor
	// Disable ImGui mouse capture to prevent cursor flickering
#if 0
	if (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard)
	{
		if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_HIDDEN)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstClick = true;
		}
		return;
	}
#endif

	float currentSpeed = speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		currentSpeed *= 2.0f;

	glm::vec3 move(0.0f);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		move += Orientation;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move -= Orientation;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move -= glm::normalize(glm::cross(Orientation, Up));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move += glm::normalize(glm::cross(Orientation, Up));
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		move += Up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		move -= Up;

	if (glm::length(move) > 0.0f)
	{
		move = glm::normalize(move) * currentSpeed * deltaTime;
		glm::vec3 tryPos = Position + glm::vec3(move.x, 0, 0);
		if (!CameraCollides(tryPos))
			Position.x += move.x;
		tryPos = Position + glm::vec3(0, move.y, 0);
		if (!CameraCollides(tryPos))
			Position.y += move.y;
		tryPos = Position + glm::vec3(0, 0, move.z);
		if (!CameraCollides(tryPos))
			Position.z += move.z;
	}

	// Free look continuo: bloquear y ocultar cursor
	// Continuous free-look: disable and hide cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (firstClick)
	{
		glfwSetCursorPos(window, (width / 2), (height / 2));
		firstClick = false;
	}
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	// Calcular rotación según movimiento del ratón
	// Calculate and apply rotation based on mouse movement
	float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
	float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;
	glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));
	if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		Orientation = newOrientation;
	}
	Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
	// Recentrar cursor al centro de la ventana
	// Recenter cursor to window center
	glfwSetCursorPos(window, (width / 2), (height / 2));
}

// Deshabilitar restauración del cursor al soltar el botón para free look continuo
// Disable cursor restoration on button release for continuous free look
#if 0
else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    firstClick = true;
}
#endif