#include "../hdr/server.h"

void init (int noport, int *lsocket) {

    // On vérifie que le numéro de port est valide, i.e. il doit être entre 0 et 65535 (USHRT_MAX).
    if (noport < 0 || noport >= USHRT_MAX) {
        fprintf(stderr, "Le numéro du port : %d est incorrect\n");
        exit(EXIT_FAILURE);
    }

    // On vérifie que le socket se crée correctement.
    if (!(*lsocket = socket(AF_INET, SOCK_STREAM, 0))) {
        fprintf(stderr, "Erreur lors de la création du socket\n");
        exit(EXIT_FAILURE);
    }

    // On prépare l'adresse du socket d'écoute.
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(noport);

    // On vérifie que l'attachement se fait correctement.
    if (!bind(*lsocket, (struct sockaddr *) &address, sizeof(struct sockaddr_in))) {
        fprintf(stderr, "Erreur lors de l'attachement (bind).\n");
        exit(EXIT_FAILURE);
    }

    // On vérifie que l'ouverture du service se fait correctement.
    if (!listen(*lsocket, WT_CONN)) {
        fprintf(stderr, "Erreur lors de l'ouverture du service (listen).\n");
        exit(EXIT_FAILURE);
    }

}


void service_loop (int lsocket, socklen_t *clientlen) {

    while (1) {

        // On vérifie que l'acceptation de la connexion se fait correctement.
        if (!(accept(lsocket, (struct sockaddr *) &address, clientlen))) {
            fprintf(stderr, "Erreur lors de l'acceptation de la connexin (accept)\n");
            exit(EXIT_FAILURE);
        }
        //TODO
        fork();
    }
}


int main (int argc, char* argv[]) {
    
    int lsocket, noport; //Déclaration du socket d'écoute et de son port.
    socklen_t clientlen = (socklen_t)sizeof(address); //On récupère la taille de l'adresse du client.
    
    // On récupère le numéro de port passé en paramètre.
    noport = atoi(argv[1]);
    
    // Initialisation du socket d'écoute.
    init(noport, &lsocket);

    // Démarrage de la boucle de service et communication avec les clients.
    service_loop(lsocket, &clientlen);
    
    return 0;
 }