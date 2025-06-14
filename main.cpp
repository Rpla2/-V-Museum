/*
    main.cpp
    --------------------------------------------------------------------------------
    Main entry point for the V-Museum application.
    Handles window creation, OpenGL context setup, main loop, and scene management.

    --------------------------------------------------------------------------------
    Punto de entrada principal para la aplicación V-Museum.
    Gestiona la creación de la ventana, configuración del contexto OpenGL, bucle principal y gestión de la escena.
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

// Modelos 3D
Model* g_model = nullptr;
Model* g_statua_1 = nullptr;
Model* g_statua_2 = nullptr;
Model* g_statua_3 = nullptr;
Model* g_statua_4 = nullptr;
Model* g_statua_5 = nullptr;

struct ObraInfo {
    std::string nombre;
    std::string autor;
    std::string año;
    std::string descripcion;
    glm::vec3 posicion;
    float radioInteraccion;
};


std::vector<ObraInfo> obras = {
    {"Venus de Milo", "Alexandros de Antioquía", "Siglo II a.C.", "Una de las esculturas más famosas de la antigua Grecia, expuesta en el Museo del Louvre.", 
    glm::vec3(3.3f, 3.34f, -3.88f), 2.0f},
    {"Discóbolo de Mirón", "Mirón", "Siglo V a.C.", "Escultura clásica que representa a un atleta lanzando un disco.", 
    glm::vec3(-2.45f, 3.34f, -4.0f), 2.0f},
    
};


glm::vec4 g_lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec3 g_lightPos = glm::vec3(0.5f, 2.0f, 2.0f);


void SetClearColor(AppState state);
void RenderState(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading, float deltaTime);
void MostrarInfoObraCercana(const glm::vec3& camPos, GLFWwindow* window);
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

    g_camera = new Camera(screenWidth, screenHeight, glm::vec3(7.89f, 1.45f, -18.07f));

    try {
        g_model = new Model("models/gallery_01/scene.gltf");
        g_statua_1 = new Model("models/venus_de_milo/scene.gltf");
		g_statua_2 = new Model("models/the_discobolus_of_myron/scene.gltf");
        g_statua_3 = new Model("models/napoleon/scene.gltf");
        g_statua_4 = new Model("models/julio_cesar/scene.gltf");
        g_statua_5 = new Model("models/william_shakespeare_statue/scene.gltf");
     
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
    delete g_statua_1;
    delete g_statua_2;
    delete g_statua_3;
    delete g_statua_4;
    delete g_statua_5;
   
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

    currentState = AppState::PLAYING;
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
        
        MostrarInfoObraCercana(g_camera->Position, window);

        g_camera->Inputs(window, deltaTime);
        g_camera->updateMatrix(65.0f, 0.1f, 100.0f);

        if (g_model && g_shaderProgram)
        {
			//edificio
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::rotate(modelMatrix, glm::radians(-180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f));
            g_model->Draw(*g_shaderProgram, *g_camera, modelMatrix);

			//estatua venus_de_milo
			glm::mat4 statueMatrix1 = glm::mat4(1.0f);
			statueMatrix1 = glm::translate(statueMatrix1, glm::vec3(-3.0f, 0.0f, 7.6f));
            statueMatrix1 = glm::scale(statueMatrix1, glm::vec3(20.0f));
			statueMatrix1 = glm::rotate(statueMatrix1, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            statueMatrix1 = glm::rotate(statueMatrix1, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			g_statua_1->Draw(*g_shaderProgram, *g_camera, statueMatrix1);

			// estatua discobolo
            glm::mat4 statuaMatrix2 = glm::mat4(1.0f);
			statuaMatrix2 = glm::translate(statuaMatrix2, glm::vec3(3.5f, 0.0f, 6.6f));
			statuaMatrix2 = glm::rotate(statuaMatrix2, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			statuaMatrix2 = glm::rotate(statuaMatrix2, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			statuaMatrix2 = glm::scale(statuaMatrix2, glm::vec3(2.5f));
			g_statua_2->Draw(*g_shaderProgram, *g_camera, statuaMatrix2);

			// Napoleon
            glm::mat4 statuaMatrix3 = glm::mat4(0.5f);
            statuaMatrix3 = glm::translate(statuaMatrix3, glm::vec3(0.0f, 0.0f, -17.6f));
            statuaMatrix3 = glm::rotate(statuaMatrix3, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            statuaMatrix3 = glm::rotate(statuaMatrix3, glm::radians(-360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            statuaMatrix3 = glm::scale(statuaMatrix3, glm::vec3(0.1f));
            g_statua_3->Draw(*g_shaderProgram, *g_camera, statuaMatrix3);

            // Cesar
            glm::mat4 statuaMatrix4 = glm::mat4(1.0f);
            statuaMatrix4 = glm::translate(statuaMatrix4, glm::vec3(0.0f, -2.5f, -13.6f));
            statuaMatrix4 = glm::rotate(statuaMatrix4, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            statuaMatrix4 = glm::rotate(statuaMatrix4, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            statuaMatrix4 = glm::scale(statuaMatrix4, glm::vec3(2.5f));
            g_statua_4->Draw(*g_shaderProgram, *g_camera, statuaMatrix4);
           
            // william_shakespeare_statue
            glm::mat4 statuaMatrix5 = glm::mat4(1.0f);
            statuaMatrix5 = glm::translate(statuaMatrix5, glm::vec3(0.0f, 0.0f, 18.6f));
            statuaMatrix5 = glm::rotate(statuaMatrix5, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            statuaMatrix5 = glm::rotate(statuaMatrix5, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            statuaMatrix5 = glm::scale(statuaMatrix5, glm::vec3(2.05f));
            g_statua_5->Draw(*g_shaderProgram, *g_camera, statuaMatrix5);

            



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

// Muestra la información de la obra de arte más cercana si el usuario está dentro del rango y presiona la tecla L
// Shows the info window for the nearest artwork if the user is within range and presses the L key
void MostrarInfoObraCercana(const glm::vec3& camPos, GLFWwindow* window) {
    for (const auto& obra : obras) {
        float distancia = glm::distance(camPos, obra.posicion);

        ImVec2 ventanaSize = ImVec2(350, 220);
        ImVec2 ventanaPos = ImVec2(20, 40);  

        ImGui::SetNextWindowSize(ventanaSize, ImGuiCond_Always);
        ImGui::SetNextWindowPos(ventanaPos, ImGuiCond_Always);
        
        if (distancia < obra.radioInteraccion && glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            ImGui::Begin("Información de la Obra", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
            ImGui::Text("Nombre: %s", obra.nombre.c_str());
            ImGui::Text("Autor: %s", obra.autor.c_str());
            ImGui::Text("Año: %s", obra.año.c_str());
            ImGui::TextWrapped("%s", obra.descripcion.c_str());
            ImGui::End();
            break;
        }
    }
}