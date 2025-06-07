// Implements menu and instructions rendering for the application
#include "Menu.h"
#include "imgui.h"

// Renders the main menu window and handles user interaction
void RenderMainMenu(AppState& currentState, GLFWwindow* window) {
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    // Configure main menu window to cover the entire screen
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2((float)screenWidth, (float)screenHeight), ImGuiCond_Always);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.15f, 0.20f, 0.28f, 0.85f));

    // Window flags for a clean, fixed menu window
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Menu Principal", nullptr, window_flags);

    // Title positioning and styling 
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.32f);
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 200) * 0.5f);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.93f, 1.0f, 1.0f));
    ImGui::TextWrapped("%s", "Bienvenido al Museo Virtual");
    ImGui::PopStyleColor();

    // Position buttons
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 220) * 0.5f);

    ImGui::BeginGroup(); 
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f); // Rounded buttons
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.45f, 0.65f, 0.95f, 0.85f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.55f, 0.75f, 1.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.35f, 0.55f, 0.85f, 1.0f));
    ImGui::PushItemWidth(220);

    // Play button: starts the game
    if (ImGui::Button("Play", ImVec2(220, 48))) {
        currentState = AppState::PLAYING;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    // Instructions button: shows instructions
    ImGui::Spacing();
    if (ImGui::Button("Instrucciones", ImVec2(220, 48))) {
        currentState = AppState::INSTRUCTIONS;
    }
    // Exit button: closes the application
    ImGui::Spacing();
    if (ImGui::Button("Salir", ImVec2(220, 48))) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    ImGui::PopItemWidth();
    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar();
    ImGui::EndGroup();

    // Footer with project info
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 40);
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 200) * 0.5f);
    ImGui::TextColored(ImVec4(0.7f, 0.8f, 0.9f, 0.7f), "Proyecto Museo Virtual - 2025");

    ImGui::End();
    ImGui::PopStyleColor();
}

// Renders the instructions window and handles return to menu
void RenderInstructions(AppState& currentState, GLFWwindow* window) {
    ImGuiIO& io = ImGui::GetIO();

    // Center the instructions window
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::Begin("Instrucciones", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);

    // Instructions content
    ImGui::TextWrapped("Bienvenido al Museo Virtual!");
    ImGui::Separator();
    ImGui::TextWrapped("Controles:");
    ImGui::BulletText("W, A, S, D: Moverse.");
    ImGui::BulletText("Mouse: Mirar alrededor (haz clic izquierdo para activar).");
    ImGui::BulletText("ESC (durante el juego): Volver al menu.");
    ImGui::Separator();

    // Button to return to main menu
    if (ImGui::Button("Volver al Menu", ImVec2(-1, 0))) {
        currentState = AppState::MENU;
    }
    ImGui::End();
}
