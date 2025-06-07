#include <GLFW/glfw3.h>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Definición de los estados de la aplicación
enum class AppState { MENU, INSTRUCTIONS, PLAYING };

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Configurar versión de OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    // Crear ventana
    GLFWwindow* window = glfwCreateWindow(800, 800, "V-Museum", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Inicializar ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Estado inicial
    AppState currentState = AppState::MENU;

    // Bucle principal
    while (!glfwWindowShouldClose(window)) {
        // --- INICIO: FRAME IMGUI ---
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int screenWidth, screenHeight;
        glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

        switch (currentState) {
        case AppState::MENU: {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2((float)screenWidth, (float)screenHeight), ImGuiCond_Always);
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.15f, 0.20f, 0.28f, 0.85f));

            ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar |
                ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus;

            ImGui::Begin("Menu Principal", nullptr, window_flags);

            ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.32f);
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 200) * 0.5f);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.93f, 1.0f, 1.0f));
            ImGui::TextWrapped("%s", "Bienvenido al Museo Virtual");
            ImGui::PopStyleColor();

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 220) * 0.5f);

            ImGui::BeginGroup();
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.45f, 0.65f, 0.95f, 0.85f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.55f, 0.75f, 1.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.35f, 0.55f, 0.85f, 1.0f));
            ImGui::PushItemWidth(220);

            if (ImGui::Button("Play", ImVec2(220, 48))) {
                currentState = AppState::PLAYING;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            ImGui::Spacing();
            if (ImGui::Button("Instrucciones", ImVec2(220, 48))) {
                currentState = AppState::INSTRUCTIONS;
            }
            ImGui::Spacing();
            if (ImGui::Button("Salir", ImVec2(220, 48))) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }

            ImGui::PopItemWidth();
            ImGui::PopStyleColor(3);
            ImGui::PopStyleVar();
            ImGui::EndGroup();

            ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 40);
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 200) * 0.5f);
            ImGui::TextColored(ImVec4(0.7f, 0.8f, 0.9f, 0.7f), "Proyecto Museo Virtual - 2025");

            ImGui::End();
            ImGui::PopStyleColor();
            break;
        }
        case AppState::INSTRUCTIONS: {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
            ImGui::Begin("Instrucciones", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);

            ImGui::TextWrapped("Bienvenido al Museo Virtual!");
            ImGui::Separator();
            ImGui::TextWrapped("Controles:");
            ImGui::BulletText("W, A, S, D: Moverse.");
            ImGui::BulletText("Mouse: Mirar alrededor (haz clic izquierdo para activar).");
            ImGui::BulletText("ESC (durante el juego): Volver al menu.");
            ImGui::Separator();
            if (ImGui::Button("Volver al Menu", ImVec2(-1, 0))) {
                currentState = AppState::MENU;
            }
            ImGui::End();
            break;
        }
        case AppState::PLAYING: {
            // Aquí iría la lógica del juego.
            // Para este ejemplo, solo se permite volver al menú con ESC.
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                currentState = AppState::MENU;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            break;
        }
        }

        // --- FIN: FRAME IMGUI ---

        // Lógica de color de fondo según estado
        if (currentState == AppState::INSTRUCTIONS) {
            glClearColor(0.274f, 0.318f, 0.384f, 0.95f); // Azul para instrucciones
        }
        else {
            glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        }
        glClear(GL_COLOR_BUFFER_BIT);

        // Renderizar ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Limpieza ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
