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
        if (c == '\n') // On incrémente le compteur à chaque saut de ligne.
            count = count + 1;

    rewind(f);
    return count;
}


FILE *open_database(char *filename) {
    FILE *f;

    f = fopen(filename, "r");

    if (f == NULL) {
        fprintf(stderr, "Le fichier BDD n'a pas pu être lu.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Fichier BDD lu sans problème.\n");
    }

    return f;
}


void populate_books(FILE *dbfile, book_t *books) {
    char *line = (char *)malloc(MAX_LINE);
    char * g;
    int count;

    while ((g = fgets(line, MAX_LINE, dbfile)) != NULL) {
        int i = 0;
        for (i = 1; i < DB_COL_NB + 1; i++) {
            char *field = strdup(line);
            switch (i) {
                case 1:
                    books[count].ref = atoi(getfield(field, i));
                    break;
                case 2:
                    strcpy(books[count].author, getfield(field, i));
                    break;
                case 3:
                    strcpy(books[count].title, getfield(field, i));
                    break;
                case 4:
                    strcpy(books[count].genre, getfield(field, i));
                    break;
                default:
                    break;
            }
        }
        count++;
    }
    fclose(dbfile);
}