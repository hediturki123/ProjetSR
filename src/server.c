#include "server.h"

void end_child(int signo) {
    wait(NULL);
}

void init (int noport, int *lsocket) {

    printf("Tentative de démarrage du serveur sur le port %d...\n", noport);

    // Prise en compte de la mort des processus de service du serveur.
    struct sigaction ac;
    ac.sa_handler = end_child;
    ac.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &ac, NULL);

    // On vérifie que le numéro de port est valide, i.e. il doit être entre 0 et 65535 (USHRT_MAX).
    if (noport < 0 || noport >= USHRT_MAX) {
        fprintf(stderr, "Le numéro du port (%d) est incorrect !\n", noport);
        exit(EXIT_FAILURE);
    } else {
        printf("Validité du numéro de port : OK\n");
    }

    // On vérifie que le socket se crée correctement.
    *lsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (*lsocket < 0) {
        fprintf(stderr, "Le socket d'écoute n'a pas pu être créé !\n");
        exit(EXIT_FAILURE);
    } else if (*lsocket == 0) {
        fprintf(stderr, "Timeout lors de la création du socket.\n");
        close(*lsocket);
        exit(EXIT_FAILURE);
    } else {
        printf("Création du socket d'écoute : OK\n");
    }

    // On prépare l'adresse du socket d'écoute.
    printf("Préparation de l'adresse du socket d'écoute...");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(noport);
    printf(" OK\n");

    // On vérifie que l'attachement se fait correctement.
    if (bind(*lsocket, (struct sockaddr *) &address, sizeof(struct sockaddr_in)) == -1) {
        fprintf(stderr, "L'attachement de l'addresse ne s'est pas effectué correctement !\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Attachement de l'adresse au socket : OK\n");
    }

    // On vérifie que l'ouverture du service se fait correctement.
    if (listen(*lsocket, WT_CONN) == -1) {
        fprintf(stderr, "Le service n'a pas pu être ouvert !\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Ouverture du service : OK\n");
    }

}


void service_loop (int lsocket, socklen_t *clientlen) {

    printf("Démarrage de la boucle de service...\n");

    int nlsock;
    char buf[5];
    int rd;

    while (1) {

        // On vérifie que l'acceptation de la connexion se fait correctement.
        if ((nlsock = accept(lsocket, (struct sockaddr *) &address, clientlen)) == -1) {
            fprintf(stderr, "Erreur lors de l'acceptation de la connexion (accept).\n");
            exit(EXIT_FAILURE);
        }

        // Création du sous-processus de traitement du client.
        switch(fork()) {
            case -1:
                perror("La demande du client n'a pas pu être traitée (fork).\n");
                break;

            case 0:
                rd = read(nlsock, buf, sizeof(buf));
                if (rd == -1) {
                    printf("Rien à lire\n");
                }
                printf("Lu (%d) : %s\n", rd, buf);

                // Le sous-processus se termine quand il a fait tout ce qu'il avait à faire.
                exit(EXIT_SUCCESS);

                break;

            default:
                break;
        }
    }
}


int main (int argc, char* argv[]) {

    int lsocket, noport; // Déclaration du socket d'écoute et de son port.
    socklen_t clientlen = (socklen_t)sizeof(address); // On récupère la taille de l'adresse du client.

    // On récupère le numéro de port passé en paramètre.
    noport = atoi(argv[1]);

    // Initialisation du socket d'écoute.
    init(noport, &lsocket);

    // Démarrage de la boucle de service et communication avec les clients.
    service_loop(lsocket, &clientlen);

    // Fermeture du socket d'écoute.
    close(lsocket);

    return 0;
 }
