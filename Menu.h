/*
    --------------------------------------------------------------------------------
    Archivo de cabecera para la definición de estados de la aplicación y funciones de renderizado de menús.
    Header file for application state definitions and menu rendering functions.
    --------------------------------------------------------------------------------
*/

#pragma once

// Declaración adelantada de GLFWwindow para evitar incluir la cabecera completa de GLFW aquí.
// Forward-declare GLFWwindow to avoid including the full GLFW header here.
// Esto mejora los tiempos de compilación y evita problemas de orden de inclusión.
// This improves compilation times and avoids inclusion order issues.
struct GLFWwindow;

// Representa los diferentes estados de la aplicación
// Represents the different application states
enum class AppState {
    MENU,         // Menú principal / Main menu
    INSTRUCTIONS, // Pantalla de instrucciones / Instructions screen
    LOADING,      // Pantalla de carga / Loading screen
    PLAYING,      // Juego / Playing
    EXIT          // Salir de la aplicación / Exit application
};

// Funciones para renderizar los menús
// Functions to render menus
void RenderMainMenu(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);
void RenderInstructions(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);
void RenderLoadingScreen(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);