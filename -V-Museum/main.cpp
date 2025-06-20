#pragma execution_character_set("utf-8")
/*
    --------------------------------------------------------------------------------
    Main entry point for the V-Museum application.
    Handles window creation, OpenGL context setup, main loop, and scene management.

    Punto de entrada principal para la aplicación V-Museum.
    Gestiona la creación de la ventana, configuración del contexto OpenGL, bucle principal y gestión de la escena.
    --------------------------------------------------------------------------------
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include <irrKlang.h>
#include <vector>
#include <string>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "ImGuiManager.h"
#include "Menu.h"
#include "Model.h"
#include "Camera.h"
#include "shaderClass.h"
#include "AABB.h"
#include "AABBDefs.h"

using namespace irrklang;

// Objetos globales de la escena 3D / Global objects for the 3D scene
Camera* g_camera = nullptr;
Shader* g_shaderProgram = nullptr;

ISoundEngine* g_soundEngine = nullptr;// Engine de sonido global / Global sound engine
ISound* g_music = nullptr;// Referencia a la música ambiental / Reference to ambient music

// Lista de reproducción de música / Music playlist
std::vector<std::string> g_playlist = {
    "Music/Fly_Me_to_the_Moon.mp3",
    "Music/Jazz_Relajante.mp3",
    "Music/Morning_Café_Jazz.mp3",
};

// Índice de la pista actual en la lista de reproducción / Current track index in the playlist
int g_currentTrack = 0;

// 3D Models
Model* g_model = nullptr;
Model* g_statue_1 = nullptr;
Model* g_statue_2 = nullptr;
Model* g_statue_3 = nullptr;
Model* g_statue_4 = nullptr;
Model* g_statue_5 = nullptr;
Model* g_statue_6 = nullptr;
Model* g_statue_7 = nullptr;

struct WorkInfo {
    std::string Name;
    std::string Author;
    std::string Year;
    std::string Description;
    glm::vec3 position;
    float interactionRadius;
};

std::vector<WorkInfo> works = {
    {
        "Venus de Milo (Greek: Aphrodite of Milos).",
        "Alexandros of Antioch.\nThe authorship is attributed to him, although there is no absolute certainty. This attribution is based on an inscription found on the plinth (the base) of the statue, which was unfortunately lost shortly after its discovery. For a long time, it was mistakenly attributed to Praxiteles to increase its value, associating it with the Classical period.",
        "Hellenistic Period. It is estimated to have been sculpted between 130 BC and 100 BC.",
        "One of the most famous sculptures of Ancient Greece and an icon of classical feminine beauty.\n\nRepresentation: Depicts Aphrodite (Venus to the Romans), the Greek goddess of love, beauty, and fertility.\n\nPhysical Characteristics: Sculpted in Parian marble and measures approximately 203 cm in height. The goddess is depicted semi-nude, with a drape or himation covering her legs and hips, leaving the torso exposed in a gesture of great sensuality and naturalism.\n\nThe Lost Arms: Its most distinctive feature is the absence of its arms, which were lost in antiquity and have never been found. This mystery has generated endless speculation about its original posture. Some theories suggest she may have held an apple (alluding to the Judgment of Paris), a mirror, or was leaning on a pillar.\n\nPosture and Style: The statue presents a subtle contrapposto, a technique that gives it naturalness and dynamism. The body's weight rests on one leg, creating an elegant S-shaped curve in her figure. Its style combines elements of classical idealism (the serenity and impassiveness of the face) with the drama and complexity of the Hellenistic period (the twist of the body and the texture of the garments).\n\nDiscovery: Discovered in 1820 by a farmer named Yorgos Kentrotas on the Greek island of Milos (or Milo), from which it gets its name. Shortly after, it was acquired by France and today is one of the star pieces of the Louvre Museum in Paris.",
        glm::vec3(3.3f, 3.34f, -3.88f), 2.0f
    },
    {
        "Discobolus of Myron (El Discóbolo de Mirón)",
        "Myron of Eleutherae.\nHe was one of the most important sculptors of the Greek Classical period, known for his ability to capture movement and anatomical realism.",
        "The original bronze work was created around 450 BC (Greek Classical Period).\nIt is important to note that the original bronze has been lost. All the statues we know today are Roman marble copies made centuries later.",
        "One of the masterpieces of Greek art, celebrated for its depiction of movement and athletic tension.\n\nRepresentation: The sculpture shows a nude athlete at the precise moment of maximum concentration and torsion, just before throwing the discus. It is not a portrait of a specific athlete, but rather the representation of the athletic ideal.\n\nInnovation and Style: Its great innovation was to capture a fleeting instant of violent action, freezing the movement at its peak. The athlete's body is composed in a series of arcs and curves that convey enormous potential energy, like a spring about to be released. This concept of balance in motion is known in Greek as rhythmos.\n\nContrast and Composition: Despite the incredible tension of the body, the athlete's face remains calm and expressionless, a typical feature of the Severe Style (the transition between the Archaic and Classical periods). This contrast highlights the Greek ideal of self-control and mental discipline even during maximum physical effort.\n\nRoman Copies: The Roman marble copies, being more fragile than the original bronze, often required structural support, such as a tree trunk, which did not exist in Myron's work. The most famous and considered the most faithful copy is the Discobolus Lancellotti, located in the National Roman Museum in Rome. Another well-known version is the Townley Discobolus, exhibited in the British Museum in London.",
        glm::vec3(-2.45f, 3.0f, -4.0f), 2.0f
    },
    {
        "Napoleon",
        "Charles Émile Seurre.",
        "1833.",
        "This imposing bronze statue represents Napoleon Bonaparte idealized in the style of a Roman emperor, seeking to establish a symbolic link between his empire and the greatness of Ancient Rome. He wears a toga and a laurel crown, symbols of victory and power. In his right hand, he holds the imperial orb (a globe with a cross), and in his left, a scepter. The work was originally created to crown the Vendôme Column, but today it stands in the Cour d'Honneur of the Hôtel des Invalides in Paris, where Napoleon's tomb is also located.",
        glm::vec3(-0.20, 3.0, 3.0), 2.0f
    },
    {
        "Statue of Julius Caesar",
        "Anonymous. It is a Roman work from the Imperial period.",
        "It is believed to be a posthumous copy from the 1st or early 2nd century AD.",
        "This marble statue is one of the best-known representations of Julius Caesar. It is important to note that it is not a portrait made during his lifetime, but a later creation that idealizes his figure. He is depicted as a military leader and statesman (imperator). He wears a muscular cuirass (armor) under a paludamentum (the general's cloak). His contrapposto stance and raised arm in an oratorical gesture (adlocutio) convey authority, charisma, and power. Although his face is an idealized reconstruction, it is based on portraits from coins minted in his era.",
        glm::vec3(0.04, 3.0, 15.21), 2.0f
    },
    {
        "Monument to William Shakespeare (in Poets' Corner, Westminster Abbey)",
        "Designed by William Kent and sculpted by Peter Scheemakers.",
        "1740.",
        "Located in the most sacred place of English literature, Poets' Corner in Westminster Abbey, this marble monument presents Shakespeare life-size. He is depicted standing, dressed in the clothing of his era, and casually leaning on a pedestal of books symbolizing his work. With his right hand, he points to a scroll containing a quote from his play The Tempest: \"The cloud-capp'd towers, the gorgeous palaces...\". The sculpture consolidates him not only as a literary genius but as a national icon of Britain.",
        glm::vec3(0.18, 3.0,-16.12), 2.0f
    },
    {
        "Statue of Hans Christian Andersen",
        "August Saabye.",
        "1880.",
        "This famous bronze statue is located in the King's Garden (Kongens Have) in Copenhagen, Denmark. It depicts the celebrated fairy tale author seated, with a book in his hand, in a pose suggesting he is about to tell one of his stories. The sculpture perfectly captures his image as a beloved storyteller for children and adults. Interestingly, the most famous statue inspired by his work is not this one, but The Little Mermaid (1913), also in Copenhagen, which has become the city's symbol.",
        glm::vec3(-10.46, 3.0, -13.91), 2.0f
    },
    {
        "Monument to Miguel de Cervantes",
        "The main sculptor was Lorenzo Coullaut Valera and the architect, Rafael Martínez Zapatero.",
        "Mainly built between 1925 and 1930, with later additions.",
        "More than a single statue, it is a grand monumental complex in Plaza de España, Madrid. The main figure is a stone statue of Cervantes, seated and holding a quill, thoughtfully observing his work from atop a pedestal. However, the most famous and photographed part of the monument are the bronze statues of his most universal characters: Don Quixote riding his horse Rocinante and Sancho Panza on his loyal donkey. The complex also includes representations of Dulcinea del Toboso and a globe as a symbol of the universality of the Spanish language.",
        glm::vec3(10.02, 3.0, -13.84), 2.0f
    }
};

glm::vec4 g_lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec3 g_lightPos = glm::vec3(0.5f, 2.0f, 2.0f);

void SetClearColor(AppState state);
void RenderState(AppState& currentState, GLFWwindow* window, AppState& nextStateAfterLoading, float deltaTime);
void ShowNearestWorkInfo(const glm::vec3& camPos, GLFWwindow* window);
void Init3DScene(int screenWidth, int screenHeight);
void Cleanup3DScene();
static glm::mat4 ComputeTransform(const glm::vec3& translate, const glm::vec3& rotDeg, float scale);

// Función para comprobar colisión entre un punto y un AABB
// Checks collision between a point and an AABB
bool PointInAABB(const glm::vec3& point, const AABB& box) {
    return (point.x >= box.min.x && point.x <= box.max.x &&
            point.y >= box.min.y && point.y <= box.max.y &&
            point.z >= box.min.z && point.z <= box.max.z);
}

// Función para comprobar colisión de la cámara con todos los AABB
// Checks camera collision against all AABBs
bool CameraCollides(const glm::vec3& camPos) {
    // Galería / Gallery
    if (!PointInAABB(camPos, gallery01AABB)) return true; // Si está fuera de la galería, colisiona / If outside the gallery, it collides
    // Bancas / Benches
    for (const auto& bench : benchAABBs) {
        if (PointInAABB(camPos, bench)) return true;
    }
    // Estatuas / Statues
    for (const auto& statue : statueAABBs) {
        if (PointInAABB(camPos, statue)) return true;
    }
    return false;
}

// Función principal de la aplicación / Main application function
int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "V-Museum", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Deshabilitar cursor para free look continuo
    // Disable cursor for continuous free look
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Inicializar irrKlang (NO reproducir música aún)
    g_soundEngine = createIrrKlangDevice();
    if (!g_soundEngine) {
        std::cerr << "No se pudo inicializar irrKlang" << std::endl;
    }

    // Inicialización de GLAD / GLAD initialization
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Load and set the icon / Cargar y establecer el icono
    GLFWimage icon;
    icon.pixels = stbi_load("models/icon/museum_roman_icon.png", &icon.width, &icon.height, nullptr, 4);
    if (icon.pixels) {
        glfwSetWindowIcon(window, 1, &icon);
        stbi_image_free(icon.pixels);
    }
    else {
        std::cerr << "Failed to load window icon" << std::endl;
    }

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);

    Init3DScene(screenWidth, screenHeight);
    InitImGui(window);

	// Inicializar el estado de la aplicación / Initialize application state
    AppState currentState = AppState::MENU;
    AppState nextStateAfterLoading = AppState::MENU;
    AppState prevState = currentState;

	// Variables para el control de tiempo / Variables for time control
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

	// Bucle principal de la aplicación / Main application loop
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

        // Control de música según estado / Music control according to state
        if (g_soundEngine) {
            if (currentState == AppState::PLAYING) {
                if (!g_music) {
                    g_music = g_soundEngine->play2D(g_playlist[g_currentTrack].c_str(), false, false, true);
                } else if (g_music->isFinished()) {
                    g_music->drop();
                    g_currentTrack = (g_currentTrack + 1) % g_playlist.size();
                    g_music = g_soundEngine->play2D(g_playlist[g_currentTrack].c_str(), false, false, true);
                } else if (g_music->getIsPaused()) {
                    g_music->setIsPaused(false);
                }
            } else if (currentState != AppState::PLAYING && g_music && !g_music->getIsPaused()) {
                g_music->setIsPaused(true);
            }
        }
    }
    Cleanup3DScene();
    CleanupImGui();
    glfwDestroyWindow(window);
    glfwTerminate();

    // Liberar engine de sonido / Release sound engine
    if (g_music) g_music->drop();
    if (g_soundEngine) {
        g_soundEngine->drop();
    }
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

    g_camera = new Camera(screenWidth, screenHeight, glm::vec3(5.96f, 3.00f, 19.79f));
    
    try {
        g_model = new Model("models/gallery_01/scene.gltf");
        g_statue_1 = new Model("models/venus_de_milo/scene.gltf");
		g_statue_2 = new Model("models/the_discobolus_of_myron/scene.gltf");
        g_statue_3 = new Model("models/napoleon/scene.gltf");
        g_statue_4 = new Model("models/julio_cesar/scene.gltf");
        g_statue_5 = new Model("models/william_shakespeare_statue/scene.gltf");
        g_statue_6 = new Model("models/hans_christian_andersen/scene.gltf");
		g_statue_7 = new Model("models/busto_de_cervantes/scene.gltf");
		std::cout << "MODELOS CARGADOS CORRECTAMENTE" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR AL CARGAR EL MODELO: " << e.what() << std::endl;
    }
}

// Libera los recursos de la escena 3D / Releases 3D scene resources
void Cleanup3DScene()
{
    delete g_model;
    delete g_statue_1;
    delete g_statue_2;
    delete g_statue_3;
    delete g_statue_4;
    delete g_statue_5;
	delete g_statue_6;
	delete g_statue_7;
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
        
        ShowNearestWorkInfo(g_camera->Position, window);

        g_camera->Inputs(window, deltaTime);
        g_camera->Position.y = 3.0f;
        g_camera->updateMatrix(65.0f, 0.1f, 100.0f);

        if (g_model && g_shaderProgram)
        {
            // Edificio principal/ Main building
            glm::mat4 modelMatrix = ComputeTransform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 180.0f), 2.0f);
            g_model->Draw(*g_shaderProgram, *g_camera, modelMatrix);

            // Estatua Venus de Milo/ Statue Venus de Milo
            glm::mat4 statuaMatrix1 = ComputeTransform(glm::vec3(-3.0f, 0.0f, 7.6f), glm::vec3(0.0f, 90.0f, 180.0f), 20.0f);
            g_statue_1->Draw(*g_shaderProgram, *g_camera, statuaMatrix1);

            // Estatua Discóbolo de Mirón/ Statue Discobolus of Myron
            glm::mat4 statuaMatrix2 = ComputeTransform(glm::vec3(3.5f, 0.0f, 6.6f), glm::vec3(180.0f, 0.0f, 90.0f), 2.5f);
            g_statue_2->Draw(*g_shaderProgram, *g_camera, statuaMatrix2);

            // Estatua Napoleón/ Statue Napoleon
            glm::mat4 statuaMatrix3 = ComputeTransform(glm::vec3(0.0f, 0.0f, -8.4f), glm::vec3(360.0f, 0.0f, -90.0f), 0.06f);
            g_statue_3->Draw(*g_shaderProgram, *g_camera, statuaMatrix3);

            // Estatua Julio César/ Statue Julius Caesar
            glm::mat4 statuaMatrix4 = ComputeTransform(glm::vec3(0.0f, -2.5f, -12.8f), glm::vec3(0.0f, -90.0f, 180.0f), 2.5f);
            g_statue_4->Draw(*g_shaderProgram, *g_camera, statuaMatrix4);

            // Estatua William Shakespeare/ Statue William Shakespeare
            glm::mat4 statuaMatrix5 = ComputeTransform(glm::vec3(0.0f, 0.0f, 18.4f), glm::vec3(0.0f, -90.0f, 180.0f), 3.05f);
            g_statue_5->Draw(*g_shaderProgram, *g_camera, statuaMatrix5);

            // Estatua Hans Christian Andersen/ Statue Hans Christian Andersen
            glm::mat4 statuaMatrix6 = ComputeTransform(glm::vec3(6.836f, -3.422f, 17.550f), glm::vec3(-2.0f, 78.0f, -179.3f), 0.15f);
            g_statue_6->Draw(*g_shaderProgram, *g_camera, statuaMatrix6);

            // Estatua Miguel de Cervantes/ Statue Miguel de Cervantes
            glm::mat4 statueMatrix7 = ComputeTransform(glm::vec3(-9.2f, -1.685f, 13.341f), glm::vec3(-161.053f, 0.0f, 83.448f), 1.0f);
            g_statue_7->Draw(*g_shaderProgram, *g_camera, statueMatrix7);
        }
        break;
    }
}

// Muestra la información de la obra de arte más cercana si el usuario está dentro del rango y presiona la tecla L
// Shows the info window for the nearest artwork if the user is within range and presses the L key
void ShowNearestWorkInfo(const glm::vec3& camPos, GLFWwindow* window) {
    for (const auto& work : works) {
        float distanceToWork = glm::distance(camPos, work.position);

        ImVec2 windowSize = ImVec2(420, 480);
        ImVec2 windowPos = ImVec2(20, 40);

        ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);

        if (distanceToWork < work.interactionRadius && glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            ImGui::Begin("Work Information", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
            ImGui::Text("Name:");
            ImGui::PopFont();
            ImGui::TextWrapped("%s", work.Name.c_str());
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
            ImGui::Text("Author:");
            ImGui::PopFont();
            ImGui::TextWrapped("%s", work.Author.c_str());
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
            ImGui::Text("Year:");
            ImGui::PopFont();
            ImGui::TextWrapped("%s", work.Year.c_str());
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
            ImGui::Text("Description:");
            ImGui::PopFont();
            ImGui::TextWrapped("%s", work.Description.c_str());
            ImGui::PopStyleColor();
            ImGui::End();
            break;
        }
    }
}

// Función helper para transformaciones: traslación, rotación (grados en X,Y,Z) y escala
// Helper function for transformations: translation, rotation (degrees in X,Y,Z), and scale
static glm::mat4 ComputeTransform(const glm::vec3& translate, const glm::vec3& rotDeg, float scale) {
    glm::mat4 m(1.0f);
    m = glm::translate(m, translate);
    m = glm::rotate(m, glm::radians(rotDeg.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m = glm::rotate(m, glm::radians(rotDeg.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m = glm::rotate(m, glm::radians(rotDeg.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m = glm::scale(m, glm::vec3(scale));
    return m;
}