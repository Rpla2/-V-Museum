// ImGui initialization and cleanup interface for the application
#pragma once
#include <GLFW/glfw3.h>
#include "imgui.h" // Incluir imgui.h para ImFont

// Declaraciones de fuentes globales que se usarán en la aplicación
extern ImFont* G_Font_H1;
extern ImFont* G_Font_Default;

void InitImGui(GLFWwindow* window); // Initializes ImGui context and backends
void CleanupImGui(); // Cleans up ImGui resources and backends