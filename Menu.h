// Application state definitions and menu rendering interfaces
#pragma once
#include <GLFW/glfw3.h>

// Representa los diferentes estados de la aplicaci�n
enum class AppState {
    MENU,         // Men� principal
    INSTRUCTIONS, // Pantalla de instrucciones
    LOADING,      // Pantalla de carga
    PLAYING,      // Juego
    EXIT          // Salir de la aplicaci�n
};

// Renders
void RenderMainMenu(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);
void RenderInstructions(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);
// Pantalla de carga con destino configurable (simplificada)
void RenderLoadingScreen(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);