#include "../include/game.h"
#include "../include/display.h"
#include "../include/map.h"
#include "../include/player.h"
#include "../include/elements.h"
#include "../include/utils.h"
#include <ncurses.h>
#include <unistd.h>

// ==============================
// Section: Initialisation et terminaison de ncurses
// ==============================

// Fonction d'initialisation pour ncurses
void InitNcurses() {
    initscr();
    InitColors();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(0);
    clear();
    displayCountdownNcurses();
}

// Fonction de terminaison pour ncurses
void EndNcurses() {
    endwin();
    clear();
}

// ==============================
// Section: Initialisation des couleurs
// ==============================

// Fonction pour initialiser les couleurs
void InitColors() {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_RED);
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(5, COLOR_CYAN, COLOR_CYAN);
    init_pair(6, COLOR_BLACK, COLOR_BLACK);
}

// ==============================
// Section: Fonctions d'affichage de compte a rebours
// ==============================

// Fonction pour afficher un compte a rebours avec ncurses
void displayCountdownNcurses() {
    for (int i = 3; i > 0; i--) {
        clear();
        printw("Commence dans: %d", i);
        refresh();
        usleep(1000000);
    }
    clear();
    printw("C'est parti !");
    refresh();
    usleep(1000000);
}

// ==============================
// Section: Fonctions de dessin de la carte
// ==============================

// Fonction pour dessiner la carte avec ncurses
void DrawNcurses(DisplayContext *display, Map *map) {
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            int gridValue = map->Grille[i][j];
            switch (gridValue) {
                case MUR: 
                    CheckNcursesError(attron(COLOR_PAIR(1)), __LINE__);
                    CheckNcursesError(mvaddch(i, j, ' '), __LINE__);
                    CheckNcursesError(attroff(COLOR_PAIR(1)), __LINE__);
                    break;
                case JOUEUR_1: 
                    CheckNcursesError(attron(COLOR_PAIR(2)), __LINE__);
                    CheckNcursesError(mvaddch(i, j, ' '), __LINE__);
                    CheckNcursesError(attroff(COLOR_PAIR(2)), __LINE__);
                    break;
                case JOUEUR_2: 
                    CheckNcursesError(attron(COLOR_PAIR(3)), __LINE__);
                    CheckNcursesError(mvaddch(i, j, ' '), __LINE__);
                    CheckNcursesError(attroff(COLOR_PAIR(3)), __LINE__);
                    break;
                case LIGNE_JOUEUR_1: 
                    CheckNcursesError(attron(COLOR_PAIR(4)), __LINE__);
                    CheckNcursesError(mvaddch(i, j, ' '), __LINE__);
                    CheckNcursesError(attroff(COLOR_PAIR(4)), __LINE__);
                    break;
                case LIGNE_JOUEUR_2: 
                    CheckNcursesError(attron(COLOR_PAIR(5)), __LINE__);
                    CheckNcursesError(mvaddch(i, j, ' '), __LINE__);
                    CheckNcursesError(attroff(COLOR_PAIR(5)), __LINE__);
                    break;
                default: 
                    CheckNcursesError(attron(COLOR_PAIR(6)), __LINE__);
                    CheckNcursesError(mvaddch(i, j, ' '), __LINE__);
                    CheckNcursesError(attroff(COLOR_PAIR(6)), __LINE__);
                    break;
            }
        }
    }
    refresh();
}

// ==============================
// Section: Affichage et gestion du menu
// ==============================

// Fonction pour afficher le menu avec ncurses
void DisplayMenuNcurses() {
    int choice;
    int highlight = 0;
    const char *choices[] = { "Jouer", "Quitter" };
    int n_choices = sizeof(choices) / sizeof(char *);

    while (1) {
        clear();
        for (int i = 0; i < n_choices; ++i) {
            if (i == highlight) {
                attron(A_REVERSE);
            }
            mvprintw(i + 1, 1, "%s", choices[i]);
            if (i == highlight) {
                attroff(A_REVERSE);
            }
        }
        choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight = (highlight == 0) ? n_choices - 1 : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == n_choices - 1) ? 0 : highlight + 1;
                break;
            case 10: // Enter key
                if (highlight == 0) {
                    return;
                } else if (highlight == 1) {
                    EndNcurses();
                    exit(0);
                }
                break;
            default:
                break;
        }
        refresh();
    }
}