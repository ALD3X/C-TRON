#include <stdio.h>
#include "player.h"
#include "map.h"
#include "elements.h"
#include <conio.h> // Pour _getch()

// Fonction pour gerer les entrees du joueur
void HandlePlayerInput(Player *player, Map *map) {
    char input = _getch(); // Lire une touche sans attendre ENTER
    switch (input) {
        case 'z': // Haut
            MovePlayerInDirection(player, map, TOP);
            break;
        case 's': // Bas
            MovePlayerInDirection(player, map, DOWN);
            break;
        case 'q': // Gauche
            MovePlayerInDirection(player, map, LEFT);
            break;
        case 'd': // Droite
            MovePlayerInDirection(player, map, RIGHT);
            break;
        case 'e': // Quitter le jeu
            printf("Jeu quitte.\n");
            exit(0); // Sortie du programme
        default:
            break; // Ignorer les autres entrées
    }
}

int main() {
    // Initialisation de la carte et des joueurs
    Map map;
    Player player1, player2;

    InitializeMap(&map); // Initialiser la carte
    InitializePlayer(&player1, JOUEUR_1);
    InitializePlayer(&player2, JOUEUR_2);
    SpawnTwoPlayers(&player1, &player2, &map);

    int manche = 0;

    while (GetPlayerScore(&player1) < 3 && GetPlayerScore(&player2) < 3) {
        // Boucle principale du jeu
        while (CheckGameState(&player1, &player2) == GAME_ONGOING) {
            system("cls"); // Effacer l'affichage precedent 
            // Afficher le score final
            printf("Score : Joueur 1 [%d] - [%d] Joueur 2 \n", GetPlayerScore(&player1), GetPlayerScore(&player2));

            DrawMap(&map); // Afficher la carte
            printf("Manche %d!\n", manche + 1);
            
            HandlePlayerInput(&player1, &map); // Gerer les mouvements du joueur 1
        }

        // Verifier qui a gagne
        GameState state = CheckGameState(&player1, &player2);
        if (state == PLAYER1_WON) {
            AddPlayerScore(&player1);
            printf("Joueur 1 a gagne la manche %d!\n", manche + 1);
            resetPLayerlive(&player2);
        } else if (state == PLAYER2_WON) {
            AddPlayerScore(&player2);
            printf("Joueur 2 a gagne la manche %d!\n", manche + 1);
            resetPLayerlive(&player1);
        }

        // Reinitialiser la carte apres la fin de la manche
        ResetMap(&map);
        manche++;
        SpawnTwoPlayers(&player1,&player2,&map);
    }

    // Afficher le score final
    printf("Score final: Joueur 1 [%d] - [%d] Joueur 2 \n", GetPlayerScore(&player1), GetPlayerScore(&player2));

    return 0; 
}
