// utils.c

#include "utils.h"

// Fonction utilitaire pour vérifier les pointeurs et gérer les erreurs
void CheckPointer(void *ptr, const char *errorMessage) {
    if (ptr == NULL) {
        fprintf(stderr, "Erreur: %s\n", errorMessage);
        exit(EXIT_FAILURE); 
    }
}

// Fonction pour vérifier la carte
void CheckMap(void *map) {
    CheckPointer(map, "La carte est invalide.");
    // Cast explicite pour accéder aux membres spécifiques de 'Map'
    Map *actualMap = (Map*)map; 
    CheckPointer(actualMap->Grille, "La grille de la carte est invalide.");
}

// Fonction pour vérifier les joueurs
void CheckPlayers(void **players, int player_count) {
    if (players == NULL) {
        fprintf(stderr, "Erreur : Tableau de joueurs invalide.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < player_count; i++) {
        if (players[i] == NULL) {
            char message[100];
            snprintf(message, sizeof(message), "Informations du joueur %d invalides.", i + 1);
            CheckPointer(players[i], message);  
        }
    }
}

// Fonction pour vérifier les joueurs et la carte ensemble
void CheckPlayerAndMap(void **players, int nbPlayer, void *map) {
    CheckPlayers(players, nbPlayer);
    CheckMap(map);
}
