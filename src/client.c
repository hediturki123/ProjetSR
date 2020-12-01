#include "client.h"

void init (char *hostname, int noport, int *clientsocket) {

    // On vérifie que le numéro de port est valide, i.e. il doit être entre 0 et 65535 (USHRT_MAX).
    if (noport < 0 || noport >= USHRT_MAX) {
        fprintf(stderr, "Le numéro du port (%d) est incorrect !\n", noport);
        exit(EXIT_FAILURE);
    }

    // On vérifie que le socket se crée correctement.
    *clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (*clientsocket < 0) {
        fprintf(stderr, "Le socket d'écoute n'a pas pu être créé !\n");
        exit(EXIT_FAILURE);
    } else if (*clientsocket == 0) {
        fprintf(stderr, "Timeout lors de la création du socket.\n");
        close(*clientsocket);
        exit(EXIT_FAILURE);
    }

    // Récupération de l'adresse de l'hôte à partir de son nom.
    struct hostent *h;
    if ((h = gethostbyname(hostname)) == NULL) {
        perror("Récupération de l'adresse de l'hôte impossible.\n");
        exit(EXIT_FAILURE);
    }

    // Préparation de l'adresse du socket.
    address.sin_family = AF_INET;
    address.sin_port = htons(noport);
    memcpy(&address.sin_addr.s_addr, h->h_addr_list[0], sizeof(struct in_addr));

    // On essaye de se connecter au serveur à l'aide des informations précédentes.
    if (connect(*clientsocket, (struct sockaddr *) &address, sizeof(struct sockaddr)) == -1) {
        fprintf(stderr, "Erreur de connexion au serveur...\n");
        exit (EXIT_FAILURE);
    } else {
        printf("Connexion au serveur %s:%d établie !\n", hostname, noport);
    }

}

void server_interaction(int clientsocket) {
    char cmdname[CMDNAME_MAXSIZE];

    printf("Veuillez taper le nom de la commande à exécuter :\n> ");

    // On demande le nom de la commande à exécuteur à l'utilisateur.
    scanf("%s", cmdname);

    // On envoie ce nom au serveur pour traitement.
    write(clientsocket, cmdname, sizeof(cmdname));

    // On attend une réponse du serveur puis s'en suit un dialogue éventuel pour mener à bien l'exécution de la commande.
    wait_response(clientsocket, cmdname);
}

void wait_response (int clientsocket, char cmdname[CMDNAME_MAXSIZE]) {

    book_t book; // Livre à afficher vis-à-vis de la commande passée.

    if (!strcmp(cmdname, "reference") || !strcmp(cmdname, "ref")) {
        int ref;

        printf("Indiquez la référence du livre voulu : ");

        // On récupère la référence du livre voulu.
        scanf("%d", &ref);

        // On l'envoie au serveur.
        write(clientsocket, &ref, sizeof(int));

        printf("\n");

        // On récupère le livre correspondant à la référence.
        read(clientsocket, &book, sizeof(book_t));

        // On affiche ce livre.
        printf("==== LIVRE [%d] ====\n", ref);
        if (book.ref != ref) {
            printf("Le livre que vous cherchez n'existe pas. :(\n");
        } else {
            printf("Titre : %s\nAuteur : %s\nGenre : %s\n", book.title, book.author, book.genre);
        }
        printf("=====================\n");

    } else if (!strcmp(cmdname, "author")) {

        char aut[BOOK_AUT_SIZE]; // Nom de l'auteur dont on cherche les livres.
        char temp; // Variable temporaire pour la lecture.
        int booknumber; // Nombre de livre écrits par l'auteur.

        // Récupération du nom de l'auteur.
        printf("Auteur : ");
        scanf("%c", &temp);
        scanf("%[^\n]", aut);

        // Transmission du nom de l'auteur au serveur.
        write(clientsocket, aut, BOOK_AUT_SIZE);

        // Récupération du nombre de livres écrit par l'auteur pour préparer la boucle de lecture.
        read(clientsocket, &booknumber, sizeof(int));

        // S'il n'y a pas de livre, c'est que l'auteur n'existe pas dans la BDD.
        if (booknumber == 0) {
             printf("Cet auteur n'a aucun livre dans la base de données.\n");
        } else { // Sinon, on affiche la liste de ses livres.
            int i;
            for (i = 0; i < booknumber; i++) {
                read(clientsocket, &book, sizeof(book_t));
                printf("%s (%s)\n", book.title, book.genre);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int clientsocket, noport;
    char *hostname;

    // On vérifie que la commande comporte bien le nombre d'argument minimal.
    if (argc < 3) {
        fprintf(stderr, "Il faut au moins un hôte et un port pour se connecter.\nUsage : ./client <nom hôte> <port>\n");
        return 1;
    }

    hostname = argv[1]; // Nom de l'hôte du serveur.
    noport = atoi(argv[2]); // Numéro du port.

    // Initialisation du client.
    init (hostname, noport, &clientsocket);

    // Interaction du client avec le serveur (envoie d'une commande).
    server_interaction (clientsocket);

    // Fermeture du socket après utilisation.
    close(clientsocket);

    return 0;
}