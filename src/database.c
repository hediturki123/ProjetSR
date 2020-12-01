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

    rewind(f); // On remet le curseur au début pour permettre la lecture des champs de chaque ligne (cf. populate_books).
    return count;
}


FILE *open_database(char *filename) {
    FILE *f;

    f = fopen(filename, "r");

    // Vérification de la bonne lecture du fichier BDD.
    if (f == NULL) {
        fprintf(stderr, "Le fichier BDD n'a pas pu être lu.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Fichier BDD lu sans problème.\n");
    }

    return f;
}


void populate_books(FILE *dbfile, book_t *books) {
    char *line = (char *)malloc(MAX_LINE); // Une ligne du fichier BDD.
    char * g;
    int count; // Compteur pour ajout dans le tableau de livres.

    // On parcourt chaque ligne du fichier BDD pour en récupérer chaque champ.
    while ((g = fgets(line, MAX_LINE, dbfile)) != NULL) {
        int i;
        for (i = 1; i < DB_FIELD_NB + 1; i++) {
            char *field = strdup(line); // Champ à ajouter dans un livre.
            switch (i) { // Remplissage d'un champ du livre.
                case 1: // Cas de la référence.
                    books[count].ref = atoi(getfield(field, i));
                    break;
                case 2: // Cas de l'auteur.
                    strcpy(books[count].author, getfield(field, i));
                    break;
                case 3: // Case du titre.
                    strcpy(books[count].title, getfield(field, i));
                    break;
                case 4: // Cas du genre.
                    strcpy(books[count].genre, getfield(field, i));
                    break;
                default:
                    break;
            }
        }
        count++; // On passe au livre suivant.
    }
    fclose(dbfile); // On oublie pas de fermer le fichier BDD, qui ne nous servira plus.
}