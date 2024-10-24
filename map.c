//map.c

#include "map.h"

// Initialiser la carte
void InitializeMap(Map *map) {

    CheckPointer(map, "La carte est invalide.");
    CheckPointer(map->Grille, "La grille de la carte est invalide.");

    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            // Utiliser une condition pour remplir la grille
            map->Grille[i][j] = (i == 0 || j == 0 || i == Rows - 1 || j == Cols - 1) ? MUR : VIDE;
        }
    }
} // InitializeMap

// Réinitialiser la carte
void ResetMap(Map *map) {

    CheckPointer(map, "La carte est invalide.");
    CheckPointer(map->Grille, "La grille de la carte est invalide.");

    InitializeMap(map);
} // ResetMap

// Creer une ligne derrière le joueur
void DrawLineOnMap(Map *map, int id, int x, int y) {

    CheckPointer(map, "La carte est invalide.");
    CheckPointer(map->Grille, "La grille de la carte est invalide.");

    map->Grille[x][y] = id * 2; // Dessiner la ligne
} // DrawLineOnMap


