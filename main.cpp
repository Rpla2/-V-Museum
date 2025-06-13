/*
    main.cpp
    --------------------------------------------------------------------------------
    Archivo principal de entrada para la aplicación V-Museum. Se encarga de la inicialización de la ventana, configuración del contexto OpenGL, ciclo principal de la aplicación y gestión de la escena y recursos globales.
    Aquí se coordinan los estados de la aplicación, la integración de ImGui, la carga de modelos y la interacción principal del usuario.

    --------------------------------------------------------------------------------
    Main entry point for the V-Museum application. Responsible for window initialization, OpenGL context setup, main application loop, and management of the scene and global resources.
    This file coordinates application states, ImGui integration, model loading, and main user interaction.
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "ImGuiManager.h"
#include "Menu.h"
#include "Model.h"
#include "Camera.h"
#include "shaderClass.h"

// Objetos globales de la escena 3D
// Global objects for the 3D scene
Camera* g_camera = nullptr;
Shader* g_shaderProgram = nullptr;
Model* g_model = nullptr;
glm::vec4 g_lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec3 g_lightPos = glm::vec3(0.5f, 2.0f, 2.0f);


void SetClearColor(AppState state);
void RenderState(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading, float deltaTime);
void Init3DScene(int screenWidth, int screenHeight);
void Cleanup3DScene();

// Función principal de la aplicación
// Main application function
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

    // Inicialización de GLAD
    // GLAD initialization
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    Init3DScene(screenWidth, screenHeight);
    InitImGui(window);
    AppState currentState = AppState::MENU;
    AppState nextStateAfterLoading = AppState::MENU;
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        // Cálculo de deltaTime para animaciones y lógica dependiente del tiempo
        // DeltaTime calculation for animations and time-dependent logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        SetClearColor(currentState);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RenderState(currentState, window, nextStateAfterLoading, deltaTime);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    Cleanup3DScene();
    CleanupImGui();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// Inicializa la escena 3D: shaders, cámara y modelo
// Initializes the 3D scene: shaders, camera, and model
void Init3DScene(int screenWidth, int screenHeight)
{
    g_shaderProgram = new Shader("default.vert", "default.frag");
    g_shaderProgram->Activate();
    glUniform4f(glGetUniformLocation(g_shaderProgram->ID, "lightColor"), g_lightColor.x, g_lightColor.y, g_lightColor.z, g_lightColor.w);
    glUniform3f(glGetUniformLocation(g_shaderProgram->ID, "lightPos"), g_lightPos.x, g_lightPos.y, g_lightPos.z);

    g_camera = new Camera(screenWidth, screenHeight, glm::vec3(0.0f, 1.0f, 5.0f));

    try {
        g_model = new Model("models/gallery_01/scene.gltf");
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR AL CARGAR EL MODELO: " << e.what() << std::endl;
    }
}

// Libera los recursos de la escena 3D
// Releases 3D scene resources
void Cleanup3DScene()
{
    delete g_model;
    delete g_camera;
    g_shaderProgram->Delete();
    delete g_shaderProgram;
}

// Establece el color de fondo según el estado de la aplicación
// Sets the background color according to the application state
void SetClearColor(AppState state) {
    if (state == AppState::PLAYING) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    }
    else {
        ImVec4 clear_color = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    }
}

// Renderiza el estado actual de la aplicación (menú, instrucciones, carga, juego, salir)
// Renders the current application state (menu, instructions, loading, playing, exit)
void RenderState(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading, float deltaTime) {
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
        // Permite volver al menú presionando ESC
        // Allows returning to menu by pressing ESC
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            nextStateAfterLoading = AppState::MENU;
            currentState = AppState::LOADING;
        }

        g_camera->Inputs(window, deltaTime);
        g_camera->updateMatrix(65.0f, 0.1f, 1000.0f);

        if (g_model && g_shaderProgram)
        {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::rotate(modelMatrix, glm::radians(-180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

            g_model->Draw(*g_shaderProgram, *g_camera, modelMatrix);
        }

        // Ventana de información de depuración
        // Debug info window
        ImGui::Begin("Debug Info");
        ImGui::Text("Estado: PLAYING");
        ImGui::Text("Pos: (%.2f, %.2f, %.2f)", g_camera->Position.x, g_camera->Position.y, g_camera->Position.z);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();

        break;
    case AppState::EXIT:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    }
}