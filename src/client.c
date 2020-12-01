#include "client.h"

void init (char *hostname, int noport, int *clientsocket) {

    // On vérifie que le numéro de port est valide, i.e. il doit être entre 0 et 65535 (USHRT_MAX).
    if (noport < 0 || noport >= USHRT_MAX) {
        fprintf(stderr, "Le numéro du port (%d) est incorrect !\n", noport);
        exit(EXIT_FAILURE);
    }

    if ((*clientsocket = socket(AF_INET, SOCK_STREAM, 0)) < 1) {
        fprintf(stderr, "Erreur lors de la création du socket\n");
        exit(EXIT_FAILURE);
    }

    struct hostent *h;
    if ((h = gethostbyname(hostname)) == NULL) {
        perror("Récupération de l'adresse de l'hôte impossible.\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(noport);
    memcpy(&address.sin_addr.s_addr, h->h_addr_list[0], sizeof(struct in_addr));


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
    scanf("%s", cmdname);

    write(clientsocket, cmdname, sizeof(cmdname));
    wait_response(clientsocket, cmdname);
}

void wait_response (int clientsocket, char cmdname[CMDNAME_MAXSIZE]) {
    
    book_t book;
    
    if (!strcmp(cmdname, "reference") || !strcmp(cmdname, "ref")) {
        int ref;

        printf("Indiquez la référence du livre voulu :\n> ");
        scanf("%d", &ref);

        write(clientsocket, &ref, sizeof(int));

        printf("\n");

        read(clientsocket, &book, sizeof(book_t));

        printf("==== LIVRE [%d] ====\n", ref);
        if (book.ref != ref) {
            printf("Le livre que vous cherchez n'existe pas. :(\n");
        } else {
            printf("Titre : %s\nAuteur : %s\nGenre : %s\n", book.title, book.author, book.genre);
        }
        printf("=====================\n");

    } else if (!strcmp(cmdname, "author")) {
       
        char aut[64];
        char temp;
        int booknumber;
        printf("Auteur : ");
        scanf("%c", &temp);
        scanf("%[^\n]", aut);
        
        write(clientsocket, aut, 64);
        printf("%s\n", aut);
        read(clientsocket, &booknumber, sizeof(int));

        if (booknumber == 0) {
             printf("Cet auteur n'existe pas.\n");
        } else {
            for (int i = 0; i < booknumber; i++) {
                read(clientsocket, &book, sizeof(book_t));
                printf("%s (%s)\n", book.title, book.genre);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int clientsocket, noport;
    char *hostname;

    if (argc < 3) {
        fprintf(stderr, "Il faut au moins un hôte et un port pour se connecter.\nUsage : ./client <nom hôte> <port>\n");
        return 1;
    }

    hostname = argv[1];
    noport = atoi(argv[2]);

    init (hostname, noport, &clientsocket);

    server_interaction (clientsocket);

    close(clientsocket);

    return 0;
}