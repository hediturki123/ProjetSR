#include "client.h"



void init (int noport, int *clientsocket) {
        
    if (!(*clientsocket = socket(AF_INET, SOCK_STREAM, 0))) {
        fprintf(stderr, "Erreur lors de la création du socket\n");
        exit(EXIT_FAILURE);
    }
    
    
    struct hostent *h = gethostbyname("192.168.0.1");

    address.sin_family = AF_INET;
    address.sin_port = htons(noport);
    printf("h : %s\n", h->h_addr_list[0]);
    //address.sin_addr.s_addr = h->h_addr_list[0];
    memcpy(&address.sin_addr.s_addr, h->h_addr_list[0], sizeof(struct in_addr));
     
    
    if (!connect(*clientsocket, (struct sockaddr *)&address, sizeof(struct sockaddr *))) {
        fprintf(stderr, "Erreur de connexion avec le serveur\n");
        exit (EXIT_FAILURE);
    } else {
        printf("-- Connexion serveur client établie -- \n");
    }

}

void server_interaction(int clientsocket) {
    //write and read
    char *buffer = "hello !";

    write(clientsocket, buffer, sizeof(buffer));

    read(clientsocket, buffer, sizeof(buffer));
}




int main(int argc, char *argv[]) {
    int clientsocket, noport;

    noport = atoi(argv[1]);

    init (noport, &clientsocket);

    //server_interaction (clientsocket);

    close(clientsocket);

    return 0;
}