
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
    { glm::vec3(-8.0f, 0.0f, -0.0f), glm::vec3(-7.0f, 1.0f, 4.0f) },
    { glm::vec3(7.0f, 0.11f,  0.0f), glm::vec3(8.0f, 1.0f, 4.0f) },
    { glm::vec3(-1.7f, 0.11f,  1.0f), glm::vec3(1.7f, 1.0f,  3.0f) },
    { glm::vec3(-2.0f, 0.11f,  18.6f), glm::vec3(2.0f, 1.0f,  20.0f) },
    { glm::vec3(-8.2f, 0.11f, -15.35f), glm::vec3(-4.6f, 1.0f, -14.2f) },
    { glm::vec3(-1.7f, 0.11f, -15.34f), glm::vec3(1.7f, 1.0f, -14.2f) },
    { glm::vec3(4.7f, 0.11f, -15.34f), glm::vec3(8.2f, 1.0f, -14.2f) },
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

// Dibuja un AABB como líneas con color
void DrawAABB(const AABB& box, const glm::mat4& view, const glm::mat4& proj, const glm::vec3& color, Shader& shader) {
    static GLuint VAO = 0, VBO = 0, EBO = 0;
    if (VAO == 0) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }
    glm::vec3 min = box.min;
    glm::vec3 max = box.max;
    glm::vec3 vertices[8] = {
        {min.x, min.y, min.z},
        {max.x, min.y, min.z},
        {max.x, max.y, min.z},
        {min.x, max.y, min.z},
        {min.x, min.y, max.z},
        {max.x, min.y, max.z},
        {max.x, max.y, max.z},
        {min.x, max.y, max.z}
    };
    GLuint indices[24] = {
        0,1, 1,2, 2,3, 3,0, // bottom / fondo
        4,5, 5,6, 6,7, 7,4, // top / arriba
        0,4, 1,5, 2,6, 3,7  // sides / lados
    };
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    shader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, &proj[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);
    glUniform3fv(glGetUniformLocation(shader.ID, "color"), 1, &color[0]);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
