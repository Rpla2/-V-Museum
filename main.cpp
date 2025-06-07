#include <GLFW/glfw3.h>
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "ImGuiManager.h"
#include "Menu.h"

// Sets the background color based on the application state
void SetClearColor(AppState state);
// Renders the current state (menu, instructions, playing)
void RenderState(AppState& currentState, GLFWwindow* window);

int main() {
    // Initialize GLFW library
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n"; // Error initializing GLFW
        return -1;
    }

    // Set OpenGL version to 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Start the window maximized on launch
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 800, "V-Museum", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";  // Error creating window
        glfwTerminate();
        return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);

    // ImGui initialization
    InitImGui(window);

    // Set initial application state to MENU
    AppState currentState = AppState::MENU;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // Process events

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Menu/Instructions/Game state logic and rendering
        RenderState(currentState, window);

        // Set background color based on state
        SetClearColor(currentState);

        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

        ImGui::Render(); // Render ImGui
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup ImGui and GLFW resources
    CleanupImGui();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// Sets the background color based on the application state
void SetClearColor(AppState state) {
    if (state == AppState::INSTRUCTIONS) {
        glClearColor(0.274f, 0.318f, 0.384f, 0.95f); // Instructions background
    }
    else {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);  // Default background
    }
}

// Renders the current application state
void RenderState(AppState& currentState, GLFWwindow* window) {
    switch (currentState) {
    case AppState::MENU:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);// Show cursor
        RenderMainMenu(currentState, window); // Render main menu
        break;
    case AppState::INSTRUCTIONS:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        RenderInstructions(currentState, window);
        break;
    case AppState::PLAYING:
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            currentState = AppState::MENU;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        break;
    }
}