// ImGui initialization and cleanup interface for the application
#pragma once
#include <GLFW/glfw3.h>

void InitImGui(GLFWwindow* window); // Initializes ImGui context and backends
void CleanupImGui(); // Cleans up ImGui resources and backends
