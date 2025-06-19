#pragma once
#include <glm/glm.hpp>

struct AABB {
    glm::vec3 min;
    glm::vec3 max;

    // Transforma el AABB con una matriz de modelo
    AABB transform(const glm::mat4& model) const {
        glm::vec3 corners[8] = {
            min,
            glm::vec3(max.x, min.y, min.z),
            glm::vec3(min.x, max.y, min.z),
            glm::vec3(min.x, min.y, max.z),
            glm::vec3(max.x, max.y, min.z),
            glm::vec3(min.x, max.y, max.z),
            glm::vec3(max.x, min.y, max.z),
            max
        };
        glm::vec3 newMin = glm::vec3(model * glm::vec4(corners[0], 1.0f));
        glm::vec3 newMax = newMin;
        for (int i = 1; i < 8; ++i) {
            glm::vec3 transformed = glm::vec3(model * glm::vec4(corners[i], 1.0f));
            newMin = glm::min(newMin, transformed);
            newMax = glm::max(newMax, transformed);
        }
        return { newMin, newMax };
    }
};
