#include "server.h"

void end_child(int signo) {
    wait(NULL);
}

void init (int noport, int *lsocket) {

    printf("Tentative de démarrage du serveur sur le port %d...\n", noport);

    struct sigaction ac;

    ac.sa_handler = end_child;
    ac.sa_flags = SA_RESTART;

    sigaction(SIGCHLD, &ac, NULL);

    // On vérifie que le numéro de port est valide, i.e. il doit être entre 0 et 65535 (USHRT_MAX).
    printf("Validité du numéro de port : ");
    if (noport < 0 || noport >= USHRT_MAX) {
        fprintf(stderr, "le numéro du port (%d) est incorrect !\n", noport);
        exit(EXIT_FAILURE);
    } else {
        printf("OK\n");
    }

    // On vérifie que le socket se crée correctement.
    printf("Création du socket d'écoute : ");
    if (!(*lsocket = socket(AF_INET, SOCK_STREAM, 0))) {
        fprintf(stderr, "le socket n'a pas pu être créé !\n");
        exit(EXIT_FAILURE);
    } else {
        printf("OK\n");
    }

    // On prépare l'adresse du socket d'écoute.
    printf("Préparation de l'adresse du socket d'écoute...\n");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(noport);

    // On vérifie que l'attachement se fait correctement.
    printf("Attachement de l'adresse au socket : ");
    if (bind(*lsocket, (struct sockaddr *) &address, sizeof(struct sockaddr_in)) == -1) {
        fprintf(stderr, "l'attachement ne s'est pas effectué correctement !\n");
        exit(EXIT_FAILURE);
    } else {
        printf("OK\n");
    }

    // On vérifie que l'ouverture du service se fait correctement.
    printf("Ouverture du service : ");
    if (listen(*lsocket, WT_CONN) == -1) {
        fprintf(stderr, "le service n'a pas pu être ouvert !\n");
        exit(EXIT_FAILURE);
    } else {
        printf("OK\n");
    }

}


void service_loop (int lsocket, socklen_t *clientlen) {
    //char *buffer;

    while (1) {

        // On vérifie que l'acceptation de la connexion se fait correctement.
        if (!(accept(lsocket, (struct sockaddr *) &address, clientlen))) {
            fprintf(stderr, "Erreur lors de l'acceptation de la connexion (accept).\n");
            exit(EXIT_FAILURE);
        }

        // Création du sous-processus de traitement du client.
        if (fork() == 0) { // Si on est dans le fils, on traite l'information.
            char buffer[4];
            int len = 0;
            ioctl(lsocket, FIONREAD, &len);

            printf("Taille pouvant être lue : %d\n",len);
            if (len > 0) {
                read(lsocket, buffer, len);
                printf("Lu : %s\n", buffer);
            }
            

            // Le sous-processus se termine quand il a fait tout ce qu'il avait à faire.
            exit(EXIT_SUCCESS);
        }
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

    // Fermeture du socket d'écoute.
    close(lsocket);
    
    return 0;
 }
