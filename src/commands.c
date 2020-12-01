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

int get_author(char author[64], book_t *books, int *tab) {

    int i;
    int count = 0;
    
    for (i = 0; i < sizeof(*books); i++) {
        if (!strcmp(books[i].author, author)) {
            tab[count] = i;
            count++;        
        }
    }
    return count;
}