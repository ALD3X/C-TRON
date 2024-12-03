#include "display.h"
#include "map.h"
#include "game.h"
#include "input.h"
#include "player.h"
#include <stdio.h>

int main() {
    DisplayContext display;
    int choix; 

    // Demander à l'utilisateur de choisir le type d'affichage
    printf("Choisissez le type d'affichage:\n");
    printf("1. SDL\n");
    printf("2. Ncurses\n");
    printf("Entrez 1 pour SDL ou 2 pour Ncurses: ");
    scanf("%d", &choix);

    // Initialiser le type d'affichage selon le choix de l'utilisateur
    if (choix == 1) {
        display.type = DISPLAY_SDL;
    } else if (choix == 2) {
        display.type = DISPLAY_NCURSES;
    } else {
        printf("Choix invalide, par défaut SDL sera utilisé.\n");
        display.type = DISPLAY_SDL;
    }

    // Initialiser l'affichage
    InitDisplay(&display);

    // Initialiser la carte
    Map map;
    Player player1, player2;
    InitializeMap(&map);
    InitializePlayer(&player1, JOUEUR_1);
    InitializePlayer(&player2, JOUEUR_2);
    SpawnTwoPlayers(&player1, &player2, &map);

    // Boucle principale du jeu
    int running = 1;
    while (running) {

        // Afficher la carte selon le type d'affichage
        DrawMap(&display, &map);

        if (display.type == DISPLAY_NCURSES) {
            // Gérer les entrées des joueurs avec ncurses
            HandlePlayerInputNcurses(&player1, &player2, &map);
            UpdatePlayerMovement(&player1, &map);
            UpdatePlayerMovement(&player2, &map);
            usleep(1000);  // 16.67 ms pour ~60 FPS
        }

        if (display.type == DISPLAY_SDL) {
            // Gérer les entrées des joueurs avec SDL
            HandlePlayerInputSDL(&player1, &player2, &map);
            UpdatePlayerMovement(&player1, &map);
            UpdatePlayerMovement(&player2, &map);
            SDL_RenderPresent(display.renderer); // Mettre à jour le rendu SDL
            SDL_Delay(12); // Limiter à environ 60 FPS
        }

        // Vérifier l'état du jeu
        if (CheckGameState(&player1, &player2) != GAME_ONGOING) {
            int replay;
            if (display.type == DISPLAY_SDL){
                displayEndScreen(display.renderer, CheckGameState(&player1, &player2));
                replay = handleEndScreenEvents(display.renderer); // Gérer l'événement de clic

                if (replay) {
                    // Rejouer : réinitialiser les joueurs et la carte
                    RestartGame(&player1, &player2, &map);
                } else {
                    // Quitter le jeu
                    EndSDL(&display);
                    break;
                }
            } else {
                //NCurses
                break;
            }
        }
    }

    // Terminer l'affichage
    EndDisplay(&display);

    return 0;
}
