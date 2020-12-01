#include "database.h"

char *getfield(char *line, int num) {
    char *tok;
    for (tok = strtok(line, "#"); tok && *tok; tok = strtok(NULL, "#\n")) {
        if (!--num)
            return tok;
    }
    return NULL;
}

int linesnb(FILE *f) {
    int count = 0; // Compteur de lignes.
    char c;  // Variable de stockage du caractère courant.

    // Vérification de l'existence du fichier.
    if (f == NULL) {
        fprintf(stderr, "Le fichier n'a pas pu être lu.\n");
        return -1;
    }

    // Boucle de parcours des caractères du fichier.
    for (c = getc(f); c != EOF; c = getc(f))
        if (c == '\n') // On incrément le compteur à chaque saut de ligne.
            count += 1;

    // On ferme le fichier.
    fclose(f);

    return count;
}