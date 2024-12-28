#ifndef UTILS_H
#define UTILS_H

// ====================================================
//                     MACROS
// ====================================================

// Affiche un message d'erreur et quitte le programme
#ifdef DEBUG
    #define LOG(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
    #define LOG(fmt, ...) // Ne fait rien si DEBUG n'est pas defini
#endif

// Verifie si un pointeur est NULL
#define CheckMultiplePointers(...) CheckMultiplePointersHelper(__FILE__, __LINE__, __VA_ARGS__, NULL)

// ====================================================
//                    FONCTIONS
// ====================================================

// Verifie plusieurs pointeurs a la fois
void CheckMultiplePointersHelper(const char *file, int line, void *first_ptr, ...);

// Verifie si un pointeur est NULL
void CheckSDLError(int line);

// Verifie si un pointeur est NULL
void CheckTTFError(int line);

// Verifie si un pointeur est NULL
void CheckNcursesError(int result, int line);

#endif // UTILS_H
