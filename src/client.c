#include "client.h"



void init (int noport, int *clientsocket) {

    if ((*clientsocket = socket(AF_INET, SOCK_STREAM, 0)) < 1) {
        fprintf(stderr, "Erreur lors de la création du socket\n");
        exit(EXIT_FAILURE);
    }

    struct hostent *h;
    if ((h = gethostbyname("localhost")) == NULL) {
        perror("recuperation de h impossible\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(noport);
    //address.sin_addr.s_addr = h->h_addr_list[0];
    memcpy(&address.sin_addr.s_addr, h->h_addr_list[0], sizeof(struct in_addr));


    if (connect(*clientsocket, (struct sockaddr *) &address, sizeof(struct sockaddr)) == -1) {
        fprintf(stderr, "Erreur de connexion avec le serveur\n");
        exit (EXIT_FAILURE);
    } else {
        printf("-- Connexion serveur client établie -- \n");
    }

}

void server_interaction(int clientsocket) {
    char cmdname[128];

    printf("Nom de la commande : ");
    scanf("%s", cmdname);

    write(clientsocket, cmdname, sizeof(cmdname));
    wait_response(clientsocket, cmdname);
}

void wait_response (int clientsocket, char cmdname[128]) {
    if (!strcmp(cmdname, "reference")) {
        int ref;
        book_t book;

        printf("Référence : ");
        scanf("%d", &ref);

        write(clientsocket, &ref, sizeof(int));

        read(clientsocket, &book, sizeof(book_t));
        if (book.ref != ref) {
            printf("Le livre que vous cherchez n'existe pas.\n");
        } else {
            printf("%s de %s (%s)\n", book.title, book.author, book.genre);
        }

    } else if (!strcmp(cmdname, "author")){
        // TODO
    }
}

int main(int argc, char *argv[]) {
    int clientsocket, noport;

    noport = atoi(argv[1]);

    init (noport, &clientsocket);

    server_interaction (clientsocket);

    close(clientsocket);

    return 0;
}