// player->c

#include "player.h"
#include "map.h"
#include "elements.h"

// Initialiser le joueur avec une position et un identifiant
void InitPlayer(Player *player, Map *map, int x, int y, int id) {
    if (IsCoordValide(x, y) && map->Grille[x][y] == VIDE) {
        player->x = x;
        player->y = y;
        player->id = id;
        player->isAlive = 1;
        map->Grille[x][y] = id; // Mettre le joueur sur la carte
    } else {
        printf("Erreur: Impossible d'initialiser le joueur aux coordonnees (%d, %d).\n", x, y);
    }
} // InitPlayer 

// Fonction pour faire apparaître les joueurs à des positions opposées
void SpawnPlayers(Player *player1, Player *player2, Map *map) {
    // Coordonnées de spawn pour le joueur 1 (coin superieur gauche)
    int x1 = 1;
    int y1 = 1;

    // Coordonnées de spawn pour le joueur 2 (coin inferieur droit)
    int x2 = Rows - 2;
    int y2 = Cols - 2;

    // Initialisation des deux joueurs sur les coordonnées respectives
    InitPLayer(player1, map, x1, y1, JOUEUR_1);
    InitPLayer(player2, map, x2, y2, JOUEUR_2);
}// SpawnPlayer


// Retourne 1 si la case est libre, 0 sinon
int CrashTest(Map *map, int x, int y) {
    return (map->Grille[x][y] == VIDE);
}// CrashTest

// Retourne 1 si les coordonnées sont valides, 0 sinon
int IsCoordValide(int x, int y) {
    return (x >= 0 && x < Rows && y >= 0 && y < Cols);
}// isCoordValide

// creer la ligne derriere le joueur 
void CreateLigne(Map *map, Player *player, int x, int y)
{
    map->Grille[x][y] = player->id * 2 ;
}


// Déplacer le joueur dans une direction donnée
void MovePlayer(Player *player, Map *map, Direction direction) {
    if (!player->isAlive) return;

    int newX = player->x;
    int newY = player->y;

    // Calculer la nouvelle position en fonction de la direction
    switch (direction) {
        case TOP:    newX--; break;
        case DOWN:   newX++; break;
        case LEFT:   newY--; break;
        case RIGHT:  newY++; break;
    }

    // Vérifier si le mouvement est valide
    if (IsCoordValide(newX, newY) && CrashTest(map, newX, newY)) {
        CreateLigne(map, player, player->x, player->y);
        player->x = newX;
        player->y = newY;
        map->Grille[newX][newY] = player->id;
    } else {
        player->isAlive = 0;
        printf("Le joueur %d s'est ecrase.\n", player->id);
    }
}


