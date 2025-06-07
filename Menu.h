// Application state definitions and menu rendering interfaces
#pragma once
#include <GLFW/glfw3.h>

// Represents the different states of the application
enum class AppState {
    MENU,         // Main menu
    INSTRUCTIONS, // Instructions screen
    PLAYING       // Gameplay
};

// Renders the main menu and handles menu logic
void RenderMainMenu(AppState& currentState, GLFWwindow* window);
// Renders the instructions screen and handles its logic
void RenderInstructions(AppState& currentState, GLFWwindow* window);
