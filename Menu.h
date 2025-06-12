// Definiciones de estado de la aplicaci�n y declaraci�n de interfaces de renderizado de men�s
// Application state definitions and menu rendering interface declarations
#pragma once

// Declaraci�n adelantada de GLFWwindow para evitar incluir la cabecera completa de GLFW
// Forward declaration of GLFWwindow to avoid including the full GLFW header
struct GLFWwindow;

// Enumeraci�n de los posibles estados de la aplicaci�n
// Enumeration of possible application states
enum class AppState {
    MENU,         // Men� principal / Main menu
    INSTRUCTIONS, // Pantalla de instrucciones / Instructions screen
    LOADING,      // Pantalla de carga / Loading screen
    PLAYING,      // Juego en curso / Playing
    EXIT          // Salir de la aplicaci�n / Exit application
};

// Funciones para renderizar las diferentes pantallas del men�
// Functions to render the different menu screens
void RenderMainMenu(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);
void RenderInstructions(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);
void RenderLoadingScreen(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);
