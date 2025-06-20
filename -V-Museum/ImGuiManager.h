/*
    --------------------------------------------------------------------------------
    Archivo de cabecera para la gestión del contexto de ImGui, inicialización y limpieza.
    Header file for ImGui context management, initialization, and cleanup.
    --------------------------------------------------------------------------------
*/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

// Function to apply custom ImGui style
// Función para aplicar estilo personalizado de ImGui
extern ImFont* G_Font_H1;

// Estructura para el contexto de ImGui
// Structure for ImGui context
extern ImFont* G_Font_Default;

void InitImGui(GLFWwindow* window);
void CleanupImGui();
