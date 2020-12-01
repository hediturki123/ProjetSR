#include "commands.h"

int get_reference(int reference, book_t *books) {
    int i;
    for(i = 0; i < sizeof(*books); i++) {
        if (books[i].ref == reference) {
            return i;
        }
    }
    return -1;
}

int get_author(char author[BOOK_AUT_SIZE], book_t *books, int *tab) {

    int i;
    int count = 0; // Compteur du nombre d'auteurs.

    // Pour tout livre d'un auteur, on ajoute son indice dans le tableau tab.
    for (i = 0; i < sizeof(*books); i++) {
        if (!strcmp(books[i].author, author)) {
            tab[count] = i;
            count++;
        }
    }
    return count;
}