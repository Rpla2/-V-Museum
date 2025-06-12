// Definiciones de estado de la aplicación y declaración de interfaces de renderizado de menús
// Application state definitions and menu rendering interface declarations
#pragma once

// Declaración adelantada de GLFWwindow para evitar incluir la cabecera completa de GLFW
// Forward declaration of GLFWwindow to avoid including the full GLFW header
struct GLFWwindow;

// Enumeración de los posibles estados de la aplicación
// Enumeration of possible application states
enum class AppState {
    MENU,         // Menú principal / Main menu
    INSTRUCTIONS, // Pantalla de instrucciones / Instructions screen
    LOADING,      // Pantalla de carga / Loading screen
    PLAYING,      // Juego en curso / Playing
    EXIT          // Salir de la aplicación / Exit application
};

// Funciones para renderizar las diferentes pantallas del menú
// Functions to render the different menu screens
void RenderMainMenu(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);
void RenderInstructions(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);
void RenderLoadingScreen(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);
