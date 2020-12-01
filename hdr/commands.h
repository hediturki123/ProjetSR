#include "database.h"

#ifndef __COMMANDS_H__
#define __COMANNDS_H__

#define CMDNAME_MAXSIZE 128

int get_reference(int reference, book_t *books);

int get_author(char author[64], book_t *books);

#endif // !__COMMANDS_H__