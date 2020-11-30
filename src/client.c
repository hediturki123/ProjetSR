#include "client.h"



void init (int noport, int *clientsocket) {
    if (!(*clientsocket = socket(AF_INET, SOCK_STREAM, 0))) {
        fprintf(stderr, "Erreur lors de la création du socket\n");
        exit(EXIT_FAILURE);
    }

    struct hostent *h = gethostbyname(h->h_name);
    address.sin_family = AF_INET;
   // address.sin_port = h->h_addr;
    address.sin_addr.s_addr = htons(noport);

    connect(clientsocket, (struct sockaddr *)&address, sizeof(struct sockaddr *));


}

void server_interaction(int clientsocket) {
    //write and read
}




int main(int argc, char *argv[]) {
    int clientsocket, noport;

    init (noport, &clientsocket);

    server_interaction (clientsocket);

    return 0;
}