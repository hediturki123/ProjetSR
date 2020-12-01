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
    char *line = "";
    int count;
    while (fgets(line, MAX_LINE, dbfile) != NULL) {
        printf("%s",line);
        int i = 0;
        for (i = 0; i < DB_COL_NB; i++) {
            char *field = getfield(line, i);
            switch (i) {
                case 0:
                    books[count].ref = atoi(field);
                    break;
                case 1:
                    strcpy(books[count].author, field);
                    break;
                case 2:
                    strcpy(books[count].title, field);
                    break;
                case 3:
                    strcpy(books[count].genre, field);
                    break;
                default:
                    break;
            }
        }
        count++;
    }
    fclose(dbfile);
}