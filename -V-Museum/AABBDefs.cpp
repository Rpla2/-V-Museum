
// --------------------------------------------------------------------------------
// Archivo de implementación para definiciones de AABB y funciones relacionadas.
// Implementation file for AABB definitions and related functions.
// --------------------------------------------------------------------------------

#include "AABBDefs.h"
#include <vector>
#include <glm/glm.hpp>
#include "shaderClass.h"
#include <glad/glad.h>

// AABB de la galería principal
// Main gallery AABB
AABB gallery01AABB = {
    glm::vec3(-11.8f, 0.2f, -19.8f),
    glm::vec3(11.8f, 12.8f, 19.8f)
};

// Lista de AABB para bancas
// List of AABBs for benches
std::vector<AABB> benchAABBs = {
    { glm::vec3(-8.0f, 0.0f, -0.0f), glm::vec3(-7.0f, 5.0f, 4.0f) },
    { glm::vec3(7.0f, 0.11f,  0.0f), glm::vec3(8.0f, 5.0f, 4.0f) },
    { glm::vec3(-1.7f, 0.11f,  1.0f), glm::vec3(1.7f, 5.0f,  3.0f) },
    { glm::vec3(-2.0f, 0.11f,  18.6f), glm::vec3(2.0f, 5.0f,  20.0f) },
    { glm::vec3(-8.2f, 0.11f, -15.35f), glm::vec3(-4.6f, 5.0f, -14.2f) },
    { glm::vec3(-1.7f, 0.11f, -15.34f), glm::vec3(1.7f, 5.0f, -14.2f) },
    { glm::vec3(4.7f, 0.11f, -15.34f), glm::vec3(8.2f, 5.0f, -14.2f) },
    { glm::vec3(-8.0f, 0.11f, -8.6f), glm::vec3(8.0f, 6.0f, -7.4f) },
    { glm::vec3(-4.0f, 0.11f, 11.0f), glm::vec3(4.0f, 6.0f, 12.4f) },
    { glm::vec3(-4.0f, 5.0f, 12.0f), glm::vec3(4.0f, 6.0f, 19.9f) },
};

// Lista de AABB para estatuas
// List of AABBs for statues
std::vector<AABB> statueAABBs = {
    { glm::vec3(2.0f, 0.0f, -7.0f), glm::vec3(3.5f, 5.0f, -5.6f) },
    { glm::vec3(-4.5f, 0.0f, -7.0f), glm::vec3(-2.2f, 5.0f, -5.6f) },
    { glm::vec3(-1.2f, 0.0f, 5.0f), glm::vec3(1.5f, 5.0f, 11.0f) },
    { glm::vec3(-1.2f, 0.0f, 12.4f), glm::vec3(1.5f, 5.0f, 13.5f) },
    { glm::vec3(-1.7f, 0.11f, -19.8f), glm::vec3(1.7f, 5.0f, -17.0f) },
    { glm::vec3(8.5f, 0.11f, -19.8f), glm::vec3(11.8f, 5.0f, -17.0f) },
    { glm::vec3(-11.8f, -0.11f, -19.8f), glm::vec3(-8.15f, 8.0f, -16.2f) } 
};
