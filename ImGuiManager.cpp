/*
    ImGuiManager.cpp
    --------------------------------------------------------------------------------
    Implementation of ImGui context management for initialization and cleanup.
    Provides functions for ImGui context and backend setup, custom style, and font loading.

    --------------------------------------------------------------------------------
    Implementación de la gestión del contexto de ImGui para inicialización y limpieza.
    Proporciona funciones para la configuración del contexto y backends de ImGui, estilo personalizado y carga de fuentes.
*/

#include "ImGuiManager.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>

ImFont* G_Font_H1 = nullptr;
ImFont* G_Font_Default = nullptr;

void ApplyCustomStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    colors[ImGuiCol_Text] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.28f, 0.27f, 0.27f, 0.54f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.56f, 0.79f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.56f, 0.79f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.67f, 0.85f, 0.99f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.22f, 0.45f, 0.78f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.53f, 0.86f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.22f, 0.45f, 0.78f, 0.31f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.28f, 0.53f, 0.86f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.15f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.15f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.15f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.49f, 0.80f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.28f, 0.53f, 0.86f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.15f, 0.40f, 0.75f, 0.95f);
    colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.09f, 0.18f, 0.29f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.56f, 0.79f, 0.98f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.67f, 0.85f, 0.99f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

    style.WindowPadding = ImVec2(8.00f, 8.00f);
    style.FramePadding = ImVec2(5.00f, 2.00f);
    style.CellPadding = ImVec2(6.00f, 6.00f);
    style.ItemSpacing = ImVec2(6.00f, 6.00f);
    style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    style.IndentSpacing = 25;
    style.ScrollbarSize = 15;
    style.GrabMinSize = 10;
    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = 1;
    style.TabBorderSize = 1;
    style.WindowRounding = 7;
    style.ChildRounding = 4;
    style.FrameRounding = 12;
    style.PopupRounding = 4;
    style.ScrollbarRounding = 9;
    style.GrabRounding = 3;
    style.LogSliderDeadzone = 4;
    style.TabRounding = 4;
}

void InitImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    G_Font_Default = io.Fonts->AddFontFromFileTTF("Roboto-Regular.ttf", 20.0f);
    G_Font_H1 = io.Fonts->AddFontFromFileTTF("Roboto-Bold.ttf", 48.0f);

    if (G_Font_Default == nullptr || G_Font_H1 == nullptr) {
        std::cerr << "Error: No se pudieron cargar las fuentes." << std::endl;
        std::cerr << "Asegurate de tener 'Roboto-Regular.ttf' y 'Roboto-Bold.ttf' en el directorio del ejecutable." << std::endl;
    }

    ApplyCustomStyle();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void CleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}