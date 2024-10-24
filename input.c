#include "input.h"

// Fonction pour gérer les entrées des joueurs
void HandlePlayerInputNcurses(Player *player1, Player *player2, Map *map) {
    CheckPointer(player1, "Informations du joueur 1 invalides.");
    CheckPointer(player2, "Informations du joueur 2 invalides.");
    CheckPointer(map, "La carte est invalide.");
    CheckPointer(map->Grille, "La grille de la carte est invalide.");

    int input = getch(); // Lire un caractère

    // Gestion des entrées pour le joueur 1
    switch (input) {
        case 'z': // Haut
            MovePlayerInDirection(player1, map, TOP);
            break;
        case 's': // Bas
            MovePlayerInDirection(player1, map, DOWN);
            break;
        case 'q': // Gauche
            MovePlayerInDirection(player1, map, LEFT);
            break;
        case 'd': // Droite
            MovePlayerInDirection(player1, map, RIGHT);
            break;
    }

    // Gestion des entrées pour le joueur 2
    switch (input) {
        case KEY_UP: // Flèche Haut
            MovePlayerInDirection(player2, map, TOP);
            break;
        case KEY_DOWN: // Flèche Bas
            MovePlayerInDirection(player2, map, DOWN);
            break;
        case KEY_LEFT: // Flèche Gauche
            MovePlayerInDirection(player2, map, LEFT);
            break;
        case KEY_RIGHT: // Flèche Droite
            MovePlayerInDirection(player2, map, RIGHT);
            break;
        case 'e': // Quitter le jeu
            printf("Jeu quitte.\n");
            exit(0); // Sortie du programme
        default:
            break; // Ignorer les autres entrées
    }
   
}


void HandlePlayerInputSDL(Player *player1, Player *player2, Map *map) {
    CheckPointer(player1, "Informations du joueur 1 invalides.");
    CheckPointer(player2, "Informations du joueur 2 invalides.");
    CheckPointer(map, "La carte est invalide.");
    CheckPointer(map->Grille, "La grille de la carte est invalide.");

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
                    MovePlayerInDirection(player1, map, TOP);
                    break;
                case SDLK_s: // Bas
                    MovePlayerInDirection(player1, map, DOWN);
                    break;
                case SDLK_q: // Gauche
                    MovePlayerInDirection(player1, map, LEFT);
                    break;
                case SDLK_d: // Droite
                    MovePlayerInDirection(player1, map, RIGHT);
                    break;
            }

            // Gestion des entrées pour le joueur 2
            switch (event.key.keysym.sym) {
                case SDLK_UP: // Flèche Haut
                    MovePlayerInDirection(player2, map, TOP);
                    break;
                case SDLK_DOWN: // Flèche Bas
                    MovePlayerInDirection(player2, map, DOWN);
                    break;
                case SDLK_LEFT: // Flèche Gauche
                    MovePlayerInDirection(player2, map, LEFT);
                    break;
                case SDLK_RIGHT: // Flèche Droite
                    MovePlayerInDirection(player2, map, RIGHT);
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
