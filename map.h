// map.h 

#ifndef MAP_H
#define MAP_H

// Declaration de la taille de la carte 
#define Rows 25
#define Cols 25

typedef struct{
    int Grille[Rows][Cols];
} Map;

void InitMap(Map *map);
void DrawMap(Map *map);


#endif // MAP_H