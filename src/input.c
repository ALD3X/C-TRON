#include "input.h"

// Fonction pour gérer les entrées des joueurs
void HandlePlayerInputNcurses(Player *player1, Player *player2, Map *map) {
    CheckALL(2, map, player1, player2);

    int input = getch(); 

    // Gestion des entrées pour le joueur 1
    switch (input) {
        case 'z': // Haut
            switchPlayerDirection(player1, TOP);
            break;
        case 's': // Bas
            switchPlayerDirection(player1, DOWN);
            break;
        case 'q': // Gauche
            switchPlayerDirection(player1, LEFT);
            break;
        case 'd': // Droite
            switchPlayerDirection(player1, RIGHT);
            break;
        default:
            break; // Ignorer les autres entrées
    }

    // Gestion des entrées pour le joueur 2
    switch (input) {
        case KEY_UP: // Flèche Haut
            switchPlayerDirection(player2, TOP);
            break;
        case KEY_DOWN: // Flèche Bas
            switchPlayerDirection(player2, DOWN);
            break;
        case KEY_LEFT: // Flèche Gauche
            switchPlayerDirection(player2, LEFT);
            break;
        case KEY_RIGHT: // Flèche Droite
            switchPlayerDirection(player2, RIGHT);
            break;
        case 'e': // Quitter le jeu
            endwin();
            exit(0);
        default:
            break; // Ignorer les autres entrées
    }
   
}


void HandlePlayerInputSDL(Player *player1, Player *player2, Map *map) {
    CheckALL(2, map, player1, player2);

    SDL_Event event;

    // Gestion des événements SDL
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            printf("Jeu quitte.\n");
            exit(0); // Sortie du programme
        }

        // Vérifier si une touche est pressée
        if (event.type == SDL_KEYDOWN) {
            // Gestion des entrées pour le joueur 1
            switch (event.key.keysym.sym) {
                case SDLK_z: // Haut
                    switchPlayerDirection(player1, TOP);
                    break;
                case SDLK_s: // Bas
                    switchPlayerDirection(player1, DOWN);
                    break;
                case SDLK_q: // Gauche
                    switchPlayerDirection(player1, LEFT);
                    break;
                case SDLK_d: // Droite
                    switchPlayerDirection(player1, RIGHT);
                    break;
                default:
                    break; // Ignorer les autres entrées
            }

            // Gestion des entrées pour le joueur 2
            switch (event.key.keysym.sym) {
                case SDLK_UP: // Flèche Haut
                    switchPlayerDirection(player2, TOP);
                    break;
                case SDLK_DOWN: // Flèche Bas
                    switchPlayerDirection(player2, DOWN);
                    break;
                case SDLK_LEFT: // Flèche Gauche
                    switchPlayerDirection(player2, LEFT);
                    break;
                case SDLK_RIGHT: // Flèche Droite
                    switchPlayerDirection(player2, RIGHT);
                    break;
                case SDLK_e: // Quitter le jeu
                    printf("Jeu quitte.\n");
                    exit(0); // Sortie du programme
                default:
                    break; // Ignorer les autres entrées
            }
        }
    }
}
