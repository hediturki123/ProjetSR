#include "database.h"

#ifndef __COMMANDS_H__
#define __COMANNDS_H__

#define CMDNAME_MAXSIZE 128 // Taille maximum d'un nom de commande.

/**
 * Fonction permettant d'obtenir l'indice d'un livre dans le tableau books par rapport à se référence.
 * @param reference Référence du livre dont on souhaite avoir les informations.
 * @param books Tableau des livres.
 */
int get_reference(int reference, book_t *books);

/**
 * Fonction permettant d'obtenir la liste des indices des livres d'un auteur dans le tableau books.
 * @param author Nom de l'auteur de qui on cherche les livres.
 * @param books Tableau des livres.
 * @param tab Tableau d'entiers pour recueillir les indices des livres.
 */
int get_author(char author[BOOK_AUT_SIZE], book_t *books, int *tab);

#endif // !__COMMANDS_H__