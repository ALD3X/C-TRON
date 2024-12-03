#include "game.h"

// Vérifie l'état du jeu en fonction de la vie des joueurs
GameState CheckGameState(const Player *player1, const Player *player2) {
    CheckPointer((void *)player1, "Informations du joueur 1 invalides.");
    CheckPointer((void *)player2, "Informations du joueur 2 invalides.");

    if (!player1->isAlive) return PLAYER2_WON;
    if (!player2->isAlive) return PLAYER1_WON;
    return GAME_ONGOING;
}

// Incrémente le score du joueur
void AddPlayerScore(Player *player) {
    CheckPointer(player, "Pointeur du joueur invalide.");
    player->score++;
}

// Fonction pour réinitialiser la vie d'un joueur
void ResetPlayerLive(Player *player) { 
    CheckPointer(player, "Pointeur du joueur invalide.");
    player->isAlive = 1;
}

// Retourne le score du joueur
int GetPlayerScore(const Player *player) {
    CheckPointer((void *)player, "Pointeur du joueur invalide.");
    return player->score;
}

// Reset map 
void RestartGame(Player *player1, Player *player2, Map *map) {
    CheckALL(2, map, player1, player2);

    ResetPlayerLive(player1);
    ResetPlayerLive(player2); 
    ResetMap(map); 
    SpawnTwoPlayers(player1, player2, map); 
}
