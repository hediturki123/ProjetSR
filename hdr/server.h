#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //On a fait cet import pour vérifier que la valeur du port passée en entrée ne dépasse pas sa limite de taille.


//WT_CONN est le nombre de connexions en attente du serveur.
#define WT_CONN 10

//On déclare l'adresse du serveur.
struct sockaddr_in address;

/*
* Cette fonction d'initialisation permet de préparer la socket d'écoute (création avec "socket()" et attachement avec "bind()"), et l'ouverture du service avec "listen()".
* A chaque appel de fonction, on vérfie si tout se passe bien, sinon on affiche un message d'erreur sur la sortie standard.
* @param noport Numéro de port du socket d'écoute.
* @param lsocket Descripteur de fichier du socket d'écoute.
*/
void init (int noport, int *lsocket);

/*
* Cette fonction contient la boucle de service qui garantit la connexion avec un ou plusieurs clients et le traitement des informations envoyées par ceux-ci.
* Le traitement s'effectue dans un sous-processus pour permettre à d'autres clients de se connecter au serveur.
* @param lsocket Descripteur de fichier du socket d'écoute.
* @param clientlen Taille de l'adresse du socket.
*/
void service_loop (int lsocket, socklen_t *clientlen);