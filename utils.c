// utils.c

#include "utils.h"

// Fonction utilitaire pour vérifier les pointeurs et gérer les erreurs
void CheckPointer(void *ptr, const char *errorMessage) {
    if (ptr == NULL) {
        // Ouvrir ou créer un fichier de log
        FILE *logFile = fopen("error_log.txt", "a"); // 'a' pour ajouter à la fin du fichier
        if (logFile != NULL) {
            fprintf(logFile, "Erreur: %s\n", errorMessage);
            fclose(logFile); // Fermer le fichier
        } else {
            fprintf(stderr, "Erreur: Impossible d'ouvrir le fichier de log.\n");
        }
        exit(EXIT_FAILURE); // Sortir du programme en cas d'erreur
    }
}
