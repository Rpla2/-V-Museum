// Interfaz para la inicialización y limpieza de ImGui en la aplicación
// Interface for ImGui initialization and cleanup in the application
#pragma once

#include <glad/glad.h> // GLAD debe incluirse primero / GLAD must be included first
#include <GLFW/glfw3.h>
#include "imgui.h" // Incluir imgui.h para ImFont / Include imgui.h for ImFont

// Declaración de fuentes globales utilizadas en la interfaz gráfica
// Declaration of global fonts used in the graphical interface
extern ImFont* G_Font_H1;
extern ImFont* G_Font_Default;

// Inicializa el contexto y los backends de ImGui
// Initializes the ImGui context and backends
void InitImGui(GLFWwindow* window);

// Libera los recursos de ImGui y sus backends
// Cleans up ImGui resources and backends
void CleanupImGui();
