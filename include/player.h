#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include <time.h>

#define SPEED 0.25
#define TARGET_FPS 60
#define FRAME_TIME (1.0 / TARGET_FPS)

// ====================================================
//                     ENUMS
// ====================================================

typedef enum {
    TOP,    
    RIGHT,  
    DOWN,     
    LEFT,
    DIRECTION_COUNT  
} Direction;

// ====================================================
//                     STRUCTURES
// ====================================================

typedef struct {
    int x, y;                // Position X et Y du joueur
    int id;                  // ID du joueur 
    int score;               // Score du joueur
    int isAlive;             // Etat du joueur (1: vivant, 0: mort)
    float vitesse;           // Vitesse du joueur
    Direction direction;     // Direction du joueur
    clock_t lastMoveTime;    // Temps du dernier mouvement
} Player;

// ====================================================
//                    FONCTIONS UTILES
// ====================================================

// Verifie si une coordonnee est valide
int IsCoordinateValid(int x, int y);

// Verifie la collision sur la carte
int CheckCollision(Map *map, int x, int y);

// ====================================================
//                FONCTIONS DE GESTION DU JOUEUR
// ====================================================

// Initialise un joueur avec un ID
void InitializePlayer(Player *player, int id);

// Reinitialise l'etat de vie du joueur
void ResetPlayerLive(Player *player);

// Definie l'etat de mort du joueur
void SetPlayerDeath(Player *player);

// Ajoute un point au score du joueur
void AddPlayerScore(Player *player);

// Recupere le score du joueur
int GetPlayerScore(const Player *player);

// Definie les coordonnees du joueur sur la carte
void SetPlayerCoordinate(Player *player, Map *map, int x, int y);

// Change la direction du joueur
void SwitchPlayerDirection(Player *player, Direction direction_);

// Reinitialise les scores des deux joueurs
void ResetScores(Player *player1, Player *player2);

// ====================================================
//              FONCTIONS DE GESTION DU MOUVEMENT
// ====================================================

// Met a jour le mouvement du joueur
void UpdatePlayerMovement(Player *player, Map *map);

// Deplace le joueur dans la direction actuelle
void MovePlayerInDirection(Player *player, Map *map);

// Calcule la nouvelle position en fonction de la direction
void CalculateNewPosition(Direction direction, int *x, int *y);

// Cree un mur derriere le joueur
void CreatePlayerWall(Map *map, Player *player);

// Met a jour la position du joueur sur la carte
void UpdatePlayerPosition(Player *player, Map *map, int newX, int newY);

// ====================================================
//              FONCTIONS D'APPARITION DES JOUEURS
// ====================================================

// Fait apparaitre deux joueurs sur la carte
void SpawnTwoPlayers(Player *player1, Player *player2, Map *map);

#endif // PLAYER_H