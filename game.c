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
void ResetPlayerLive(Player *player) { // Attention à la faute de frappe
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
    CheckPointer(player1, "Informations du joueur 1 invalides.");
    CheckPointer(player2, "Informations du joueur 2 invalides.");
    CheckPointer(map, "La carte est invalide.");
    CheckPointer(map->Grille, "La grille de la carte est invalide.");

    ResetPlayerLive(player1); // Assurez-vous que cette fonction existe
    ResetPlayerLive(player2); // Assurez-vous que cette fonction existe
    ResetMap(map); // Assurez-vous que cette fonction existe
    SpawnTwoPlayers(player1, player2, map); // Assurez-vous que cette fonction existe
}
