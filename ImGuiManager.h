/*
    ImGuiManager.h
    --------------------------------------------------------------------------------
    Archivo de cabecera para la gestión del contexto de ImGui, inicialización y limpieza.
    Header file for ImGui context management, initialization, and cleanup.
*/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

extern ImFont* G_Font_H1;
extern ImFont* G_Font_Default;

void InitImGui(GLFWwindow* window);
void CleanupImGui();
