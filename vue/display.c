// display.c

#include "display.h"

// Fonction d'initialisation de l'affichage
void InitDisplay(DisplayContext *display) {
    switch (display->type) {
        case DISPLAY_NCURSES:
            InitNcurses(); // Initialiser ncurses
            break;
        case DISPLAY_SDL:
            if (!InitSDL(display)) { // Initialiser SDL
                fprintf(stderr, "Erreur lors de l'initialisation de SDL.\n");
                exit(EXIT_FAILURE);
            }
            displayCountdownSDL(display->renderer);
            break;
    }
}

// Fonction de terminaison de l'affichage
void EndDisplay(DisplayContext *display) {
    switch (display->type) {
        case DISPLAY_NCURSES:
            EndNcurses(); // Terminer ncurses
            break;
        case DISPLAY_SDL:
            EndSDL(display); // Terminer SDL
            break;
    }
}

// Fonction pour dessiner la carte
void DrawMap(DisplayContext *display, Map *map) {
    switch (display->type) {
        case DISPLAY_NCURSES:
            DrawNcurses(display, map); // Dessiner avec ncurses
            break;
        case DISPLAY_SDL:
            DrawSDL(display->renderer, map, Rows, Cols); // Dessiner avec SDL
            SDL_RenderPresent(display->renderer); // Mettre à jour l'affichage
            break;
    }
}
