// diplayNcuses.c 

#include "display.h"

// Fonction d'initialisation pour ncurses
void InitNcurses() {
    initscr(); // Initialiser ncurses
    InitColors();
    cbreak(); // Passer en mode ligne
    noecho(); // Ne pas afficher les entrees
    keypad(stdscr, TRUE); // Activer les touches speciales
    curs_set(0); // Masquer le curseur
    timeout(0);               // Permet de gérer les entrées sans blocage
    clear(); // Effacer l'ecran
    displayCountdownNcurses();
}


// Fonction pour dessiner la carte avec ncurses
void DrawNcurses(DisplayContext *display, Map *map) {
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            int gridValue = map->Grille[i][j]; // Obtenir la valeur de la grille
            switch (gridValue) {
                case MUR: 
                    attron(COLOR_PAIR(1)); // Activer la couleur pour le mur (ex. rouge)
                    mvaddch(i, j, ' '); // Afficher un espace vide
                    attroff(COLOR_PAIR(1)); // Désactiver la couleur
                    break;
                case JOUEUR_1: 
                    attron(COLOR_PAIR(2)); // Activer la couleur pour le joueur 1 (ex. bleu)
                    mvaddch(i, j, ' '); // Afficher un espace vide
                    attroff(COLOR_PAIR(2)); // Désactiver la couleur
                    break;
                case JOUEUR_2: 
                    attron(COLOR_PAIR(3)); // Activer la couleur pour le joueur 2 (ex. vert)
                    mvaddch(i, j, ' '); // Afficher un espace vide
                    attroff(COLOR_PAIR(3)); // Désactiver la couleur
                    break;
                case LIGNE_JOUEUR_1: 
                    attron(COLOR_PAIR(4)); // Activer une couleur pour la ligne du joueur 1
                    mvaddch(i, j, ' '); // Afficher un espace vide
                    attroff(COLOR_PAIR(4)); // Désactiver la couleur
                    break;
                case LIGNE_JOUEUR_2: 
                    attron(COLOR_PAIR(5)); // Activer une couleur pour la ligne du joueur 2
                    mvaddch(i, j, ' '); // Afficher un espace vide
                    attroff(COLOR_PAIR(5)); // Désactiver la couleur
                    break;
                default: 
                    attron(COLOR_PAIR(6)); // Couleur par défaut pour les espaces vides
                    mvaddch(i, j, ' '); // Afficher un espace vide
                    attroff(COLOR_PAIR(6)); // Désactiver la couleur
                    break;
            }
        }
    }
    refresh(); // Rafraîchir l'écran pour afficher les changements
}

// Fonction de terminaison pour ncurses
void EndNcurses() {
    endwin(); // Terminer ncurses
    clear();
}

// Dans la fonction d'initialisation des couleurs
void InitColors() {
    start_color(); // Initialiser les couleurs
    init_pair(1, COLOR_WHITE, COLOR_WHITE); // Mur
    init_pair(2, COLOR_RED, COLOR_RED); // Joueur 1
    init_pair(3, COLOR_GREEN, COLOR_GREEN); // Joueur 2
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW); // Ligne Joueur 1
    init_pair(5, COLOR_CYAN, COLOR_CYAN); // Ligne Joueur 2
    init_pair(6, COLOR_BLACK, COLOR_BLACK); // Espace vide
}


void displayCountdownNcurses() {
    for (int i = 3; i > 0; i--) {
        clear();  // Efface l'écran
        printw("Commence dans: %d", i);
        refresh();  // Rafraîchit l'écran
        usleep(1000000);  // Attendre 1 seconde (1000000 microsecondes)
    }
    clear();  // Efface l'écran
    printw("C'est parti !");
    refresh();
    usleep(1000000);  // Attendre encore une seconde avant de commencer le jeu
}