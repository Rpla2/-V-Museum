// Handles ImGui initialization and cleanup for the application
#include "ImGuiManager.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

// Initializes ImGui context and backends
void InitImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION(); // Verifies ImGui version
    ImGui::CreateContext(); // Creates ImGui context
    ImGuiIO& io = ImGui::GetIO(); (void)io; // Access ImGui IO (not used)
    ImGui::StyleColorsDark(); // Sets dark style
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Initializes GLFW backend 
    ImGui_ImplOpenGL3_Init("#version 330"); // Initializes OpenGL3 backend
}

// Cleans up ImGui resources and backends
void CleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown(); // Shutdown OpenGL3 backend
    ImGui_ImplGlfw_Shutdown(); // Shutdown GLFW backend
    ImGui::DestroyContext(); // Destroy ImGui context 
}
