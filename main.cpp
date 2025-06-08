#include <GLFW/glfw3.h>
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "ImGuiManager.h"
#include "Menu.h"

// Establece el color de fondo según el estado de la aplicación
void SetClearColor(AppState state);
// Renderiza el estado actual (menú, instrucciones, cargando, jugando)
void RenderState(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading);

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "V-Museum", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    InitImGui(window);

    AppState currentState = AppState::MENU;
    AppState nextStateAfterLoading = AppState::MENU;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        RenderState(currentState, window, nextStateAfterLoading);

        SetClearColor(currentState);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    CleanupImGui();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void SetClearColor(AppState state) {
    // Usamos el mismo color de fondo que el de la ventana de ImGui para una apariencia integrada
    ImVec4 clear_color = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
    if (state == AppState::PLAYING) {
        // Un color diferente para el fondo del "juego"
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    }
    else {
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    }
}

void RenderState(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading) {
    switch (currentState) {
    case AppState::MENU:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        RenderMainMenu(currentState, window, nextStateAfterLoading);
        break;
    case AppState::INSTRUCTIONS:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        RenderInstructions(currentState, window, nextStateAfterLoading);
        break;
    case AppState::LOADING:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        RenderLoadingScreen(currentState, window, nextStateAfterLoading);
        break;
    case AppState::PLAYING:
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            nextStateAfterLoading = AppState::MENU;
            currentState = AppState::LOADING; // Volver al menú a través de la pantalla de carga
        }
        break;
    case AppState::EXIT:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    }
}