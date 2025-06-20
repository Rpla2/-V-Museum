// --------------------------------------------------------------------------------
// Archivo de cabecera para la declaración de AABBs globales y listas de colisión.
// Header file for declaration of global AABBs and collision lists.
// --------------------------------------------------------------------------------
#pragma once
#include "AABB.h"
#include <vector>

// AABB de la galería principal / Main gallery AABB
extern AABB gallery01AABB;
// Lista de AABB para bancas / List of AABBs for benches
extern std::vector<AABB> benchAABBs;
// Lista de AABB para estatuas / List of AABBs for statues
extern std::vector<AABB> statueAABBs;
