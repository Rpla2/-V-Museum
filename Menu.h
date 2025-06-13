/*
    Menu.h
    --------------------------------------------------------------------------------
    Archivo de cabecera para la definición de estados de la aplicación y funciones de renderizado de menús.
    Header file for application state definitions and menu rendering functions.
*/

// Application state definitions and menu rendering interfaces
#pragma once

// Forward-declare GLFWwindow para evitar incluir la cabecera completa de GLFW aqu�.
// Esto mejora los tiempos de compilaci�n y evita problemas de orden de inclusi�n.
struct GLFWwindow;

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
void RenderLoadingScreen(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);