#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <netdb.h>
#include <string.h>
#include <limits.h>
#include "database.h"
#include "commands.h"

#ifndef __CLIENT_H__
#define __CLIENT_H__

// Adresse du socket du client.
struct sockaddr_in address;

/**
 * Fonction d'intialisation du client. On récupère l'adresse à partir du nom de l'hôte et on vérifie que son numéro de port est correct.
 * @param hostname Nom de l'hôte du serveur.
 * @param noport Numéro de port sur lequel envouyer les requêtes au serveur.
 * @param clientsocket Socket à créer pour le client.
 */
void init (char *hostname, int noport, int *clientsocket);

/**
 * Fonction permettant d'amorcer le contact avec le serveur. On lui transmet ainsi le nom de la commande pour que le serveur puisse la préparer en conséquence.
 * @param clientsocket Socket du client pour converser avec le serveur.
 */
void server_interaction(int clientsocket);

/**
 * Fonction garantissant l'interaction entre le client et le serveur lors de l'exécution du commande. Celle-ci récupère la première réponse du serveur et avise quoi faire ensuite en fonction de la commande passée.
 * @param clientsocket Socket du client pour converser avec le serveur.
 * @param cmdname Commande entrée dans le client qui a été passée au serveur.
 */
void wait_response (int clientsocket, char cmdname[CMDNAME_MAXSIZE]);

#endif // !__CLIENT_H__