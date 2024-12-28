#ifndef MAP_H
#define MAP_H

#define Rows 50 // Nombre de lignes
#define Cols 50 // Nombre de colonnes

typedef struct {
    int Grille[Rows][Cols]; // Grille de la carte
} Map;

// ====================================================
//                    FONCTIONS
// ====================================================

// Initialise la carte
void InitializeMap(Map *map);

// Reinitialise la carte
void ResetMap(Map *map);

// Dessine une ligne sur la carte
void DrawLineOnMap(Map *map, int id, int x, int y);

// Affiche la carte
void DisplayMap(Map *map);

// Efface une ligne sur la carte
void ClearLineOnMap(Map *map, int x, int y);

#endif // MAP_H

