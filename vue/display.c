#include "../include/game.h"
#include "../include/display.h"
#include "../include/map.h"
#include "../include/player.h"
#include <stdlib.h>
#include <stdio.h>

// ==============================
// Section: Initialisation et terminaison de l'affichage
// ==============================

// Fonction d'initialisation de l'affichage
void InitDisplay(DisplayContext *display) {
    switch (display->type) {
        case DISPLAY_NCURSES:
            InitNcurses();
            DisplayMenuNcurses();
            break;
        case DISPLAY_SDL:
            if (!InitSDL(display)) {
                fprintf(stderr, "Erreur lors de l'initialisation de SDL.\n");
                exit(EXIT_FAILURE);
            }
            break;
    }
}

// Fonction de terminaison de l'affichage
void EndDisplay(DisplayContext *display) {
    switch (display->type) {
        case DISPLAY_NCURSES:
            EndNcurses();
            break;
        case DISPLAY_SDL:
            EndSDL(display);
            break;
    }
}

// ==============================
// Section: Fonctions de dessin de la carte
// ==============================

// Fonction pour dessiner la carte
void DrawMap(DisplayContext *display, Map *map) {
    switch (display->type) {
        case DISPLAY_NCURSES:
            DrawNcurses(display, map);
            break;
        case DISPLAY_SDL:
            DrawSDL(display->renderer, map, Rows, Cols);
            SDL_RenderPresent(display->renderer);
            break;
    }
}
