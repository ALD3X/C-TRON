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
    erase();
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
void DisplayCountdownNcurses() {
    for (int i = 3; i > 0; i--) {
        clear();
        int rows, cols;
        getmaxyx(stdscr, rows, cols);
        mvprintw(rows / 2, (cols - strlen("X")) / 2, "%d", i);
        refresh();
        usleep(1000000);
    }
    clear();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    mvprintw(rows / 2, (cols - strlen("C'est parti !")) / 2, "C'est parti !");
    refresh();
    usleep(1000000);
    clear();
}

// ==============================
// Section: Fonctions de dessin de la carte
// ==============================

// Fonction pour dessiner la carte avec ncurses
void DrawNcurses(DisplayContext *display, Map *map) {
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols); // Obtenir la taille du terminal

    int startRow = (maxRows - Rows) / 2;
    int startCol = (maxCols - Cols) / 2;

    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            int gridValue = map->Grille[i][j];
            switch (gridValue) {
                case MUR: 
                    attron(COLOR_PAIR(1));
                    mvaddch(startRow + i, startCol + j, ' ');
                    attroff(COLOR_PAIR(1));
                    break;
                case JOUEUR_1: 
                    attron(COLOR_PAIR(2));
                    mvaddch(startRow + i, startCol + j, ' ');
                    attroff(COLOR_PAIR(2));
                    break;
                case JOUEUR_2: 
                    attron(COLOR_PAIR(3));
                    mvaddch(startRow + i, startCol + j, ' ');
                    attroff(COLOR_PAIR(3));
                    break;
                case LIGNE_JOUEUR_1: 
                    attron(COLOR_PAIR(4));
                    mvaddch(startRow + i, startCol + j, ' ');
                    attroff(COLOR_PAIR(4));
                    break;
                case LIGNE_JOUEUR_2: 
                    attron(COLOR_PAIR(5));
                    mvaddch(startRow + i, startCol + j, ' ');
                    attroff(COLOR_PAIR(5));
                    break;
                default: 
                    attron(COLOR_PAIR(6));
                    mvaddch(startRow + i, startCol + j, ' ');
                    attroff(COLOR_PAIR(6));
                    break;
            }
        }
    }
    refresh();
}

// ==============================
// Section: Affichage et gestion du menu
// ==============================

// Fonction pour afficher le menu principal
void DisplayMenuNcurses(int selectedOption) {
    clear();  // Effacer l'écran
    int middleX = COLS / 2;
    int middleY = LINES / 2;

    // Afficher le titre
    mvprintw(middleY - 2, middleX - strlen("Tron Game") / 2, "Tron Game");

    // Affichage des options avec surbrillance sur l'option sélectionnée
    if (selectedOption == 1) {
        attron(A_REVERSE);  // Activer la surbrillance
        mvprintw(middleY, middleX - strlen("Jouer") / 2, "Jouer");
        attroff(A_REVERSE);  // Désactiver la surbrillance
        mvprintw(middleY + 1, middleX - strlen("Quitter") / 2, "Quitter");
    } else {
        mvprintw(middleY, middleX - strlen("Jouer") / 2, "Jouer");
        attron(A_REVERSE);
        mvprintw(middleY + 1, middleX - strlen("Quitter") / 2, "Quitter");
        attroff(A_REVERSE);
    }

    refresh();  // Actualiser l'affichage
}

// Fonction pour gerer les evenements du menu principal
int HandleMenuEventsNcurses() {
    int choice = 1;  // 0 pour Quitter, 1 pour Jouer
    int quit = 0;
    int selectedOption = 1;  // Commence avec "Jouer" sélectionné

    // Premier affichage du menu
    DisplayMenuNcurses(selectedOption);

    while (!quit) {
        int ch = getch();  // Attendre une entrée utilisateur

        switch (ch) {
            case KEY_UP:
            case KEY_DOWN:
                // Alterner entre les choix
                selectedOption = !selectedOption;

                // Réafficher le menu avec l'option sélectionnée
                DisplayMenuNcurses(selectedOption);
                break;

            case 10:  // Touche 'Enter'
                choice = selectedOption; 
                quit = 1;
                break;
        }
    }

    return choice;
}

// Fonction pour afficher le mode de jeu
void DisplayModeDeJeuNcurses(int selectedOption) {
    clear();  // Effacer l'écran
    int middleX = COLS / 2;
    int middleY = LINES / 2;

    // Afficher le titre
    mvprintw(middleY - 2, middleX - strlen("Selectionnez le mode de jeu") / 2, "Selectionnez le mode de jeu");

    // Affichage des options avec surbrillance sur l'option sélectionnée
    if (selectedOption == 0) {
        attron(A_REVERSE);  // Activer la surbrillance
        mvprintw(middleY, middleX - strlen("Bo3") / 2, "Bo3");
        attroff(A_REVERSE);  // Désactiver la surbrillance
        mvprintw(middleY + 1, middleX - strlen("Bo5") / 2, "Bo5");
        mvprintw(middleY + 2, middleX +1 - strlen("Retour") / 2, "Retour");
        mvprintw(middleY + 4, middleX - strlen("Le premier a 2 points gagne") / 2, "Le premier a 2 points gagne");
    } else if (selectedOption == 1) {
        mvprintw(middleY, middleX - strlen("Bo3") / 2, "Bo3");
        attron(A_REVERSE);
        mvprintw(middleY + 1, middleX - strlen("Bo5") / 2, "Bo5");
        attroff(A_REVERSE);
        mvprintw(middleY + 2, middleX +1 - strlen("Retour") / 2, "Retour");
        mvprintw(middleY + 4, middleX - strlen("Le premier a 3 points gagne") / 2, "Le premier a 3 points gagne");

    }else{
        mvprintw(middleY, middleX - strlen("Bo3") / 2, "Bo3");
        mvprintw(middleY + 1, middleX - strlen("Bo5") / 2, "Bo5");
        attron(A_REVERSE);
        mvprintw(middleY + 2, middleX +1 - strlen("Retour") / 2, "Retour");
        attroff(A_REVERSE);
        mvprintw(middleY + 4, middleX - strlen("Retour au menu principal") / 2, "Retour au menu principal");
    }

    refresh();  // Actualiser l'affichage
}

// Fonction pour gerer les evenements du mode de jeu
int HandleModeDeJeuEventsNcurses() {
    int choice = 0;
    int quit = 0;
    int selectedOption = 0;

    // Premier affichage du menu
    DisplayModeDeJeuNcurses(selectedOption);

    while (!quit) {
        int ch = getch();  // Attendre une entrée utilisateur

        switch (ch) {
            case KEY_UP:
                // Alterner entre les choix
                selectedOption = (selectedOption - 1 + 3) % 3;

                // Réafficher le menu avec l'option sélectionnée
                DisplayModeDeJeuNcurses(selectedOption);
                break;
            case KEY_DOWN:
                // Aller vers le choix suivant (circulaire)
                selectedOption = (selectedOption + 1) % 3;
                // Réafficher l'écran en fonction du choix
                DisplayModeDeJeuNcurses(selectedOption);
                break;
            case 10:  // Touche 'Enter'
                choice = selectedOption; 
                quit = 1;
                break;
        }
    }

    return choice;
}

// ==============================
// Section: Affichage de l'ecran de fin
// ==============================

// Fonction pour afficher l'ecran de fin
void DisplayEndScreenNcurses(GameState gameState, Player *player1, Player *player2, int selectedOption) {
    erase();  // Effacer l'écran

    const char* winnerText;
    if (gameState == PLAYER1_WON) winnerText = "Joueur 1 gagne la partie !";
    if (gameState == PLAYER2_WON) winnerText = "Joueur 2 gagne la partie !";
    
    int middleX = COLS / 2;
    int middleY = LINES / 2;

    // Afficher les scores des joueurs
    char scoreText[50];
    sprintf(scoreText, "Joueur 1 [ %d ] - [ %d ] Joueur 2", GetPlayerScore(player1), GetPlayerScore(player2));
    mvprintw(middleY - 3, middleX - strlen(scoreText) / 2, "%s", scoreText);
    // Afficher le texte du gagnant
    mvprintw(middleY - 2, middleX - strlen(winnerText) / 2, "%s", winnerText);

    // Affichage des options avec surbrillance sur l'option sélectionnée
    if (selectedOption == 1) {
        attron(A_REVERSE);  // Activer la surbrillance
        mvprintw(middleY, middleX - strlen("Rejouer") / 2, "Rejouer");
        attroff(A_REVERSE);  // Désactiver la surbrillance
        mvprintw(middleY + 1, middleX - strlen("Retour au Menu") / 2, "Retour au Menu");
    } else {
        mvprintw(middleY, middleX - strlen("Rejouer") / 2, "Rejouer");
        attron(A_REVERSE);
        mvprintw(middleY + 1, middleX - strlen("Retour au Menu") / 2, "Retour au Menu");
        attroff(A_REVERSE);
    }

    refresh();  // Actualiser l'affichage
}

// Fonction pour gerer les evenements de l'ecran de fin
int HandleEndScreenEventsNcurses(GameState gameState, Player *player1, Player *player2) {
    int choice = 1;
    int quit = 0;
    int selectedOption = 1;

    // Premier affichage du menu
    DisplayEndScreenNcurses(gameState, player1, player2, selectedOption);

    while (!quit) {
        int ch = getch();  // Attendre une entrée utilisateur

        switch (ch) {
            case KEY_UP:
            case KEY_DOWN:
                // Alterner entre les choix
                selectedOption = !selectedOption;

                // Réafficher le menu avec l'option sélectionnée
                DisplayEndScreenNcurses(gameState, player1, player2, selectedOption);
                break;
            case 10:  // Touche 'Enter'
                choice = selectedOption; 
                quit = 1;
                break;
        }
    }

    return choice;
}

// ==============================
// Section: Affichage des scores et des controles
// ==============================

// Fonction pour afficher les scores des joueurs
void DisplayScoreNcurses(Player *player1, Player *player2) {
    char scoreText[50];
    sprintf(scoreText, "Joueur 1 [ %d ] - [ %d ] Joueur 2", GetPlayerScore(player1), GetPlayerScore(player2));

    clear(); // Effacer l'écran
    int middleX = COLS / 2;
    int middleY = LINES / 2;

    // Afficher le titre
    mvprintw(middleY - 2, middleX - strlen("Score des Joueurs") / 2, "Score des Joueurs");

    // Afficher les scores des joueurs
    mvprintw(middleY, middleX - strlen(scoreText) / 2, "%s", scoreText);

    refresh(); // Actualiser l'affichage
    usleep(2500000); // Pause de 2.5 secondes
}

// Fonction pour afficher les controles du jeu
void DisplayControlsNcurses() {
    clear(); // Effacer l'écran

    int middleX = COLS / 2;
    int middleY = LINES / 2;

    // Affichage des touches pour le joueur 1
    mvprintw(middleY - 10, middleX / 2 - (strlen("Joueur 1") / 2), "Joueur 1");
    mvprintw(middleY - 5, middleX / 2, "Z");
    mvprintw(middleY, middleX / 2 - 5, "Q");
    mvprintw(middleY, middleX / 2, "S");
    mvprintw(middleY, middleX / 2 + 5, "D");

    // Affichage des touches pour le joueur 2
    mvprintw(middleY - 10, 3 * middleX / 2 - (strlen("Joueur 2") / 2), "Joueur 2");
    mvprintw(middleY - 5, 3 * middleX / 2, "^");
    mvprintw(middleY, 3 * middleX / 2 - 5, "<");
    mvprintw(middleY, 3 * middleX / 2, "v");
    mvprintw(middleY, 3 * middleX / 2 + 5, ">");

    mvprintw(middleY + 10, middleX - (strlen("ESPACE pour continuer") / 2), "ESPACE pour continuer");

    refresh(); // Actualiser l'affichage

    // Attendre que l'utilisateur appuie sur ESPACE
    int ch; while ((ch = getch()) != ' ') {}
}