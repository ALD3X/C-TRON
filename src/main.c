#include "../include/game.h"
#include "../include/display.h"
#include "../include/player.h"
#include "../include/map.h"
#include "../include/input.h"
#include <stdio.h>

// Fonction principale du programme
int main() {
    DisplayContext display;
    int choix; 

    // Demander a l'utilisateur de choisir le type d'affichage
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
        printf("Choix invalide, par defaut SDL sera utilise.\n");
        display.type = DISPLAY_SDL;
    }

    // Initialiser l'affichage
    InitDisplay(&display);

    // Initialiser la carte et les joueurs
    Map map;
    Player player1, player2;
    InitializeGame(&player1, &player2, &map);

    // Gerer la boucle de jeu
    HandleGameLoop(&display, &player1, &player2, &map);

    // Terminer l'affichage
    EndDisplay(&display);

    return 0;
}
