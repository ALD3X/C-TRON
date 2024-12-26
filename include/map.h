#ifndef MAP_H
#define MAP_H

#define Rows 50
#define Cols 50

typedef struct {
    int Grille[Rows][Cols];
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
void DisplayMap(const Map *map);

// Efface une ligne sur la carte
void ClearLineOnMap(Map *map, int x, int y);

#endif // MAP_H

