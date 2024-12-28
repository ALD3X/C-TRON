#include "../include/player.h"
#include "../include/elements.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ==============================
// Section: Fonctions utiles
// ==============================

// Verifie si les coordonnees donnees sont valides sur la carte
int CheckCollision(Map *map, int x, int y) {
    CheckMultiplePointers(map, map->Grille, NULL);
    if (!IsCoordinateValid(x, y)) {
        LOG("Erreur: Coordonnees hors limites.\n");
        return 0; 
    }
    return (map->Grille[x][y] == VIDE);
}

// Verifie si les coordonnees (x, y) sont valides (dans les limites de la carte)
int IsCoordinateValid(int x, int y) {
    return (x >= 0 && x < Rows && y >= 0 && y < Cols);
}

// ==============================
// Section: Fonctions de gestion du joueur
// ==============================

// Initialise un joueur avec un ID unique
void InitializePlayer(Player *player, int id) {
    CheckMultiplePointers(player, NULL);
    player->id = id;
    player->score = 0;
    player->isAlive = 1;
    player->vitesse = SPEED;
    player->direction = (Direction)(rand() % DIRECTION_COUNT);
    player->lastMoveTime = clock();
    LOG("Joueur %d initialise a la position (%d, %d) avec la direction %d.\n", id, player->x, player->y, player->direction);
}

// Reinitialise la vie du joueur
void ResetPlayerLive(Player *player) { 
    CheckMultiplePointers(player, NULL);
    player->isAlive = 1;
    LOG("Vie du joueur %d reinitialisee.\n", player->id);
}

// Marque la mort du joueur
void SetPlayerDeath(Player *player) {
    CheckMultiplePointers(player, NULL);
    player->isAlive = 0;
    LOG("Joueur %d est mort.\n", player->id);
}

// Reinitialise les scores des joueurs
void ResetScores(Player *player1, Player *player2) {
    CheckMultiplePointers(player1, player2, NULL);
    player1->score = 0;
    player2->score = 0;
    LOG("Scores des joueurs reinitialises.\n");
}

// Incremente le score du joueur
void AddPlayerScore(Player *player) {
    CheckMultiplePointers(player, NULL);
    player->score++;
    LOG("Score du joueur %d incremente a %d.\n", player->id, player->score);
}

// Retourne le score actuel du joueur
int GetPlayerScore(const Player *player) {
    CheckMultiplePointers((void *)player, NULL);
    return player->score;
}

// Met a jour la position du joueur sur la carte
void SetPlayerCoordinate(Player *player, Map *map, int x, int y) {
    CheckMultiplePointers(player, NULL);
    player->x = x;
    player->y = y;
    map->Grille[x][y] = player->id;
    LOG("Joueur %d deplace a la position (%d, %d).\n", player->id, x, y);
}

// Change la direction du joueur
void SwitchPlayerDirection(Player *player, Direction direction_) {
    CheckMultiplePointers(player, NULL);
    player->direction = direction_;
    LOG("Joueur %d a change de direction pour %d.\n", player->id, direction_);
}

// ==============================
// Section: Fonctions de gestion du mouvement
// ==============================

// Met a jour le mouvement du joueur en fonction de sa vitesse et du temps ecoule
void UpdatePlayerMovement(Player *player, Map *map) {
    CheckMultiplePointers(map, map->Grille, player, NULL);
    clock_t currentTime = clock();
    double elapsedTime = (double)(currentTime - player->lastMoveTime) / CLOCKS_PER_SEC;
    double movementDelay = FRAME_TIME / player->vitesse;
    if (elapsedTime >= movementDelay) {
        MovePlayerInDirection(player, map);
        player->lastMoveTime = currentTime;
        LOG("Joueur %d deplace apres %f secondes.\n", player->id, elapsedTime);
    }
}

// Deplace le joueur dans la direction actuelle, en verifiant la validite du mouvement
void MovePlayerInDirection(Player *player, Map *map) {
    CheckMultiplePointers(map, map->Grille, player, NULL);
    if (!player->isAlive) return;
    int newX = player->x, newY = player->y;
    CalculateNewPosition(player->direction, &newX, &newY);
    CreatePlayerWall(map, player); 
    UpdatePlayerPosition(player, map, newX, newY); 
    LOG("Joueur %d deplace dans la direction %d a la position (%d, %d).\n", player->id, player->direction, newX, newY);
}

// Calcule la nouvelle position du joueur en fonction de la direction
void CalculateNewPosition(Direction direction, int *x, int *y) {
    switch (direction) {
        case TOP:    (*x)--; break;
        case DOWN:   (*x)++; break;
        case LEFT:   (*y)--; break;
        case RIGHT:  (*y)++; break;
        case DIRECTION_COUNT: break;
    }
}

// Cree un mur de lumiere derriere le joueur
void CreatePlayerWall(Map *map, Player *player) {
    CheckMultiplePointers(map, map->Grille, player, NULL);
    if (!IsCoordinateValid(player->x, player->y) || !player->isAlive) return;
    DrawLineOnMap(map, player->id, player->x, player->y);
    LOG("Joueur %d a cree un mur a la position (%d, %d).\n", player->id, player->x, player->y);
}

// Met a jour la position du joueur sur la carte, en verifiant les collisions
void UpdatePlayerPosition(Player *player, Map *map, int newX, int newY) {
    CheckMultiplePointers(map, map->Grille, player, NULL);
    if (!IsCoordinateValid(newX, newY) || !player->isAlive) return;
    if (CheckCollision(map, newX, newY)) {
        SetPlayerCoordinate(player, map, newX, newY);
    } else {
        SetPlayerDeath(player);
    }
    LOG("Position du joueur %d mise a jour a (%d, %d).\n", player->id, newX, newY);
}

// ==============================
// Section: Fonctions d'apparition des joueurs
// ==============================

// Fait apparaitre deux joueurs sur la carte a des positions initiales
void SpawnTwoPlayers(Player *player1, Player *player2, Map *map) {
    CheckMultiplePointers(map, map->Grille, player1, player2, NULL);
    int x1 = Rows / 2, y1 = Cols / 4;
    int x2 = Rows / 2, y2 = 3 * Cols / 4;
    if (!IsCoordinateValid(x1, y1) || !IsCoordinateValid(x2, y2)) {
        LOG("Erreur: Coordonnees hors limites.\n");
        return;
    }
    UpdatePlayerPosition(player1, map, x1, y1);
    UpdatePlayerPosition(player2, map, x2, y2);
    LOG("Joueurs apparus aux positions (%d, %d) et (%d, %d).\n", x1, y1, x2, y2);
}
