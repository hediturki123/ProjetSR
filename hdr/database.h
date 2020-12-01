#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __DATABASE_H__
#define __DATABASE_H__

#define MAX_LINE 4096 // Taille maximum d'une ligne d'un fichier BDD.
#define DB_FIELD_NB 4 // Nombre de champs par ligne dans le fichier BDD.

#define BOOK_AUT_SIZE 64 // Taille maximum d'un nom d'auteur.
#define BOOK_TTL_SIZE 256 // Taille maximum du titre d'un livre.
#define BOOK_GEN_SIZE 32 // Taille maximum du genre d'un livre.

// Structure servant à modéliser un livre. Celle-ci nous servivra à faciliter la transmission des données concernant un livre entre le client et le serveur.
typedef struct book_t {
    int ref; // Référence.
    char author[BOOK_AUT_SIZE]; // Auteur.
    char title[BOOK_TTL_SIZE]; // Titre.
    char genre[BOOK_GEN_SIZE]; // Genre.
} book_t;

/**
 * Fonction permettant de récupérer un champ spécifique dans un fichier BDD.
 * @param line Ligne de laquelle récupérer les champs.
 * @param num Numéro du champ à récupérer (à partir de 1).
 */
char* getfield(char* line, int num);

/**
 * Fonction permettant de donner le nombre de sauts de ligne d'un fichier. On s'en sert ici pour déterminer le nombre d'entrées de la base de données.
 * @param f Fichier dont on doit compter le nombre de lignes.
 */
int linesnb(FILE *f);

/**
 * Fonction permettant l'ouverture propre d'un fichier BDD (qui contient dans notre cas les livres).
 * @param filename Nom du fichier à ouvrir.
 */
FILE *open_database(char *filename);

/**
 * Fonction de remplissage d'un tableau de livres depuis ceux présents dans un fichier de base de données.
 * @param dbfile Fichier base de données contenant tous les livres.
 * @param books Tableau de structures de livre à remplir en conséquence.
 */
void populate_books(FILE *dbfile, book_t *books);

#endif // !__DATABASE_H__
