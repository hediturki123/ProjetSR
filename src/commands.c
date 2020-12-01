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

void get_author(char author[64]) {

}