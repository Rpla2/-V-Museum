#include <iostream>
// GLAD debe incluirse antes que GLFW / GLAD must be included before GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "ImGuiManager.h"
#include "Menu.h"
#include "shaderClass.h"
#include "Camera.h"

// Declaración de prototipos de funciones principales
// Main function prototypes declaration
void SetClearColor(AppState state);
void RenderState(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading, Camera& camera);

int main() {
    // Inicialización de GLFW y configuración de la ventana
    // GLFW initialization and window setup
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    // Creación de la ventana principal de la aplicación
    // Main application window creation
    GLFWwindow* window = glfwCreateWindow(1280, 720, "V-Museum", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Inicialización de GLAD para la gestión de funciones OpenGL
    // GLAD initialization for OpenGL function management
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    // Inicialización de ImGui para la interfaz gráfica
    // ImGui initialization for graphical interface
    InitImGui(window);

    // Configuración del shader principal de la escena
    // Main scene shader setup
    Shader shaderProgram("default.vert", "default.frag");

    // Definición de los vértices y colores de un cubo de demostración
    // Definition of vertices and colors for a demo cube
    GLfloat vertices[] = {
        // POSITIONS           // COLORS
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
    };
    GLuint indices[] = {
        0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7,
        0, 4, 7, 0, 7, 3, 1, 5, 6, 1, 6, 2,
        0, 1, 5, 0, 5, 4, 3, 2, 6, 3, 6, 7
    };

    // Generación y configuración de buffers y arrays para el cubo
    // Generation and setup of buffers and arrays for the cube
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Obtención del tamaño real de la ventana para la cámara
    // Get actual window size for camera setup
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    // Creación de la cámara principal de la escena
    // Main scene camera creation
    Camera camera(screenWidth, screenHeight, glm::vec3(0.0f, 0.0f, 2.0f));

    // Variables de estado de la aplicación
    // Application state variables
    AppState currentState = AppState::MENU;
    AppState nextStateAfterLoading = AppState::MENU;

    // Bucle principal de la aplicación
    // Main application loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Limpieza de la pantalla y configuración del color de fondo
        // Screen clearing and background color setup
        SetClearColor(currentState);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Renderizado 3D solo en modo PLAYING
        // 3D rendering only in PLAYING mode
        if (currentState == AppState::PLAYING) {
            shaderProgram.Activate();
            camera.Matrix(shaderProgram, "camMatrix");
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        // Renderizado de la interfaz gráfica con ImGui
        // Graphical interface rendering with ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        RenderState(currentState, window, nextStateAfterLoading, camera);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Liberación de recursos y cierre de la aplicación
    // Resource cleanup and application shutdown
    shaderProgram.Delete();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    CleanupImGui();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// Establece el color de limpieza de la pantalla según el estado de la aplicación
// Sets the screen clear color based on the application state
void SetClearColor(AppState state) {
    if (state == AppState::PLAYING) {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    }
    else {
        ImVec4 clear_color = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    }
}

// Gestiona el renderizado y la lógica de cada estado de la aplicación
// Handles rendering and logic for each application state
void RenderState(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading, Camera& camera) {
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
        // Procesamiento de entradas y retorno al menú si se presiona ESC
        // Input processing and return to menu if ESC is pressed
        camera.Inputs(window);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            nextStateAfterLoading = AppState::MENU;
            currentState = AppState::LOADING;
            camera.ResetFirstClick();
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        break;
    case AppState::EXIT:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    }
}
