#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <netdb.h>




struct sockaddr_in address;

void init (int noport, int *clientsocket);

void server_interaction(int clientsocket);