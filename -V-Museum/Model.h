/*
    --------------------------------------------------------------------------------
    Archivo de cabecera para la declaración de la clase Model, utilizada para cargar y gestionar modelos 3D.
    Header file for the declaration of the Model class, used for loading and managing 3D models.
    --------------------------------------------------------------------------------
*/

#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<json/json.h>
#include"Mesh.h"
#include"Camera.h"
#include <glm/glm.hpp>
#include <iostream>       

using json = nlohmann::json;

class Model
{
public:
    Model(const char* file);
    void Draw(Shader& shader, Camera& camera, const glm::mat4& modelMatrix);
    void PrintMinMaxVertexCoords();

private:
    // Variables for easy access
    // Variables para fácil acceso
    const char* file;
    std::vector<unsigned char> data;
    json JSON;

    // All the meshes and transformations
    //Todas las mallas y transformaciones
    std::vector<Mesh> meshes;
    std::vector<glm::vec3> translationsMeshes;
    std::vector<glm::quat> rotationsMeshes;
    std::vector<glm::vec3> scalesMeshes;
    std::vector<glm::mat4> matricesMeshes;

    // Prevents textures from being loaded twice
    // Evita que las texturas se carguen dos veces
    std::vector<std::string> loadedTexName;
    std::vector<Texture> loadedTex;

    // Loads a single mesh by its index
    // Carga una sola malla por su índice
    void loadMesh(unsigned int indMesh);

    // Traverses a node recursively, so it essentially traverses all connected nodes
    // Recorre un nodo de forma recursiva, por lo que esencialmente recorre todos los nodos conectados
    void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

    // Gets the binary data from a file
    // Obtiene los datos binarios de un archivo
    std::vector<unsigned char> getData();

    // Interprets the binary data into floats, indices, and textures
    std::vector<float> getFloats(json accessor);
    std::vector<GLuint> getIndices(json accessor);
    std::vector<Texture> getTextures();

    // Assembles all the floats into vertices
    std::vector<Vertex> assembleVertices
    (
        std::vector<glm::vec3> positions,
        std::vector<glm::vec3> normals,
        std::vector<glm::vec2> texUVs
    );

    // Helps with the assembly from above by grouping floats
    std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
    std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
    std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};
#endif
