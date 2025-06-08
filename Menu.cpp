#include "Menu.h"
#include "imgui.h"
#include "ImGuiManager.h" 
#include <GLFW/glfw3.h>
#include <cmath> 

#ifndef IM_PI
#define IM_PI 3.14159265358979323846f 
#endif

// Función de ayuda para centrar texto
void TextCentered(const char* text) {
    auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth = ImGui::CalcTextSize(text).x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text("%s", text);
}

// Renderiza la ventana del menú principal y gestiona la interacción del usuario
void RenderMainMenu(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading) {
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    ImVec2 displaySize((float)screenWidth, (float)screenHeight);

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(displaySize);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f); 
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.08f, 0.09f, 0.10f, 1.00f)); 

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

    ImGui::Begin("Menu Principal", nullptr, window_flags);

    // --- Título ---
    ImGui::PushFont(G_Font_H1);
    ImGui::SetCursorPosY(displaySize.y * 0.2f);
    TextCentered("V-Museum");
    ImGui::PopFont();

    ImGui::PushFont(G_Font_Default);
    ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);
    TextCentered("An Immersive Virtual Experience");
    ImGui::PopStyleColor();
    ImGui::PopFont();

    // --- Botones del Menú ---
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + displaySize.y * 0.15f);
    ImGui::PushFont(G_Font_Default);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10)); 

    float buttonWidth = 280.0f;
    float buttonHeight = 50.0f;
    float totalButtonsHeight = buttonHeight * 3 + ImGui::GetStyle().ItemSpacing.y * 2;
    float startY = (displaySize.y - totalButtonsHeight) * 0.5f;
    ImGui::SetCursorPosY(startY);

    float centerX = (displaySize.x - buttonWidth) * 0.5f;
    ImGui::SetCursorPosX(centerX);
    if (ImGui::Button("Play", ImVec2(buttonWidth, buttonHeight))) {
        nextStateAfterLoading = AppState::PLAYING;
        currentState = AppState::LOADING;
    }

    ImGui::SetCursorPosX(centerX);
    if (ImGui::Button("Instructions", ImVec2(buttonWidth, buttonHeight))) {
        nextStateAfterLoading = AppState::INSTRUCTIONS;
        currentState = AppState::LOADING;
    }

    ImGui::SetCursorPosX(centerX);
    if (ImGui::Button("EXIT", ImVec2(buttonWidth, buttonHeight))) {
        nextStateAfterLoading = AppState::EXIT;
        currentState = AppState::LOADING;
    }
    ImGui::PopStyleVar();
    ImGui::PopFont();

    // --- Footer ---
    ImGui::SetCursorPosY(displaySize.y - 40.0f);
    ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);
    TextCentered("Virtual Museum Project - 2025");
    ImGui::PopStyleColor();

    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

// Renderiza la ventana de instrucciones y permite volver al menú
void RenderInstructions(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading) {
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 center = ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(500, 350), ImGuiCond_Appearing);

    ImGui::Begin("Instructions", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::PushFont(G_Font_Default);

    ImGui::TextWrapped("Welcome to the Virtual Museum");
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ImGui::TextWrapped("Navigation Controls:");
    ImGui::BulletText("Use the W, A, S, D keys to move through the rooms.");
    ImGui::BulletText("Move the mouse to orient your view.");
    ImGui::BulletText("Press the ESC key at any time to return to the main menu.");
    ImGui::Dummy(ImVec2(0.0f, 20.0f));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    // Volver al menú: loading -> MENU
    if (ImGui::Button("Return to Menu", ImVec2(-1, 40))) {
        nextStateAfterLoading = AppState::MENU;
        currentState = AppState::LOADING;
    }

    ImGui::PopFont();
    ImGui::End();
}

// Renderiza la pantalla de carga con un spinner animado
void RenderLoadingScreen(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading) {
    // La pantalla de carga ahora dura un tiempo variable según el destino
    static float loadTimer = 0.0f;
    float loadDuration = 1.5f; // Duración estándar

    // Si el siguiente estado es INSTRUCTIONS o MENU, reducir la duración
    if (nextStateAfterLoading == AppState::INSTRUCTIONS || nextStateAfterLoading == AppState::MENU) {
        loadDuration = 0.3f; // Duración más corta para instrucciones o volver al menú
    }

    loadTimer += ImGui::GetIO().DeltaTime;

    if (loadTimer >= loadDuration) {
        loadTimer = 0.0f; // Reiniciar timer
        currentState = nextStateAfterLoading;
        if (currentState == AppState::PLAYING) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        if (nextStateAfterLoading == AppState::EXIT) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        return;
    }

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    ImVec2 displaySize((float)screenWidth, (float)screenHeight);

    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(displaySize);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.08f, 0.09f, 0.10f, 1.00f));
    ImGui::Begin("Loading", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

    // --- Animación de Spinner ---
    ImGui::PushFont(G_Font_Default);
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    float time = (float)glfwGetTime();
    ImVec2 center(displaySize.x * 0.5f, displaySize.y * 0.5f);
    float radius = 40.0f;
    float thickness = 5.0f;
    int num_segments = 12;

    for (int i = 0; i < num_segments; i++) {
        float a0 = (IM_PI * 2.0f) * ((float)i / num_segments) + time * 8;
        float a1 = (IM_PI * 2.0f) * ((float)(i + 1) / num_segments) - 0.1f + time * 8; // Pequeño espacio
        float alpha = 1.0f - (sin(time * 2 + i) * 0.5f + 0.5f); // Efecto de pulso
        ImU32 color = ImColor(ImVec4(0.56f, 0.79f, 0.98f, alpha * 0.7f));
        draw_list->AddLine(
            ImVec2(center.x + cos(a0) * radius, center.y + sin(a0) * radius),
            ImVec2(center.x + cos(a1) * radius, center.y + sin(a1) * radius),
            color,
            thickness
        );
    }

    ImGui::SetCursorPosY(center.y + radius + 30.0f);
    TextCentered("Loading...");
    ImGui::PopFont();

    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}
