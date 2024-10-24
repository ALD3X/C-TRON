#include "display.h"
#include "map.h"
#include "game.h"
#include "input.h"
#include "player.h"

int main() {
    DisplayContext display;
    display.type = DISPLAY_SDL; // Choisir le type d'affichage ici (DISPLAY_SDL ou DISPLAY_NCURSES)

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

        if (display.type == DISPLAY_NCURSES){
            // Gérer les entrées des joueurs avec ncurses
            HandlePlayerInputNcurses(&player1, &player2, &map);
        }

        // Si l'affichage est de type SDL, mettre à jour l'affichage et limiter la fréquence
        if (display.type == DISPLAY_SDL) {
            HandlePlayerInputSDL(&player1, &player2, &map);
            SDL_RenderPresent(display.renderer); // Mettre à jour le rendu SDL
            SDL_Delay(16); // Limiter à environ 60 FPS
        }

                // Vérifier l'état du jeu
        if (CheckGameState(&player1, &player2) != GAME_ONGOING) {
            running = 0; // Arrêter le jeu
        }
    }

    // Terminer l'affichage
    EndDisplay(&display);

    return 0;
}
