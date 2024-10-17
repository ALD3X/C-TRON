// player->c

#include "player.h"
#include "map.h"
#include "elements.h"

// Initialise le Joueur choisi avec id
void InitPLayer(Player *player, Map *map,int x, int y, int id){
    player->x = x ;
    player->y = y ;
    player->id = id ;
    map->Grille[x][y] = id ; // Definir le joueur 
    player->isAlive = 1 ; // Initialiser l'etat du joueur a vivant
} // InitPlayer 

// Fonction pour faire apparaître les joueurs à des positions opposées
void SpawnPlayers(Player *player1, Player *player2, Map *map) {
    // Coordonnées de spawn pour le joueur 1 (coin supérieur gauche)
    int x1 = 1;
    int y1 = 1;

    // Coordonnées de spawn pour le joueur 2 (coin inférieur droit)
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


void MovePlayer(Player *player, Map *map, Direction direction) {
    // Vérifie si le joueur est encore en vie
    if (!player->isAlive) {
        return; // Ne déplace pas le joueur s'il est mort
    }

    // Coordonnées de la prochaine position
    int nextX = player->x;
    int nextY = player->y;

    // Détermine les coordonnees de la prochaine position en fonction de la direction
    switch (direction) {
        case TOP:
            nextX--;
            break;
        case DOWN:
            nextX++;
            break;
        case LEFT:
            nextY--;
            break;
        case RIGHT:
            nextY++;
            break;
        default:
            return; // Direction invalide, ne rien faire
    }

    // Vérifie si la nouvelle position est valide
    if (!IsCoordValide(nextX, nextY) || !CrashTest(map, nextX, nextY)) {
        player->isAlive = 0; // Le joueur est mort s'il se déplace sur une case invalide ou un obstacle
        return;
    }

    // Crée une ligne à l'ancienne position du joueur
    CreateLigne(map, player, player->x, player->y);

    // Met à jour la position du joueur
    player->x = nextX;
    player->y = nextY;

    // Place le joueur sur la nouvelle case
    map->Grille[player->x][player->y] = player->id;
}


