#ifndef GAME_H
#define GAME_H

typedef enum {
    GAME_ONGOING, // jeu en cours
    PLAYER1_WON,  // joueur 1 a gagne
    PLAYER2_WON,  // joueur 2 a gagne
    GAME_WAITING  // jeu en attente
} GameState;

#include "display.h"   
#include "player.h"    
#include "input.h"   

// ====================================================
//                    FONCTIONS
// ====================================================

// Redemarre le jeu
void RestartGame(Player *player1, Player *player2, Map *map);

// Initialise le jeu
void InitializeGame(Player *player1, Player *player2, Map *map);

// Met a jour le jeu
void UpdateGame(Player *player1, Player *player2, Map *map);

// Affiche l'etat du jeu
void DisplayGameState(const Player *player1, const Player *player2);

// Gere la boucle principale du jeu
void HandleGameLoop(DisplayContext *display, Player *player1, Player *player2, Map *map);

// Definie le mode de jeu
GameState ModeDeJeu(int mode, Player *player1, Player *player2, Map *map, DisplayContext *display);

#endif // GAME_H
