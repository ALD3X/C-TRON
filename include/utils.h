#ifndef UTILS_H
#define UTILS_H

// ====================================================
//                     MACROS
// ====================================================

#ifdef DEBUG
    #define LOG(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
    #define LOG(fmt, ...) // Ne fait rien si DEBUG n'est pas defini
#endif

#define CheckMultiplePointers(...) CheckMultiplePointersHelper(__FILE__, __LINE__, __VA_ARGS__, NULL)

// ====================================================
//                    FONCTIONS
// ====================================================

// Verifie plusieurs pointeurs a la fois
void CheckMultiplePointersHelper(const char *file, int line, void *first_ptr, ...);
void CheckSDLError(int line);
void CheckTTFError(int line);
void CheckNcursesError(int result, int line);

#endif // UTILS_H
