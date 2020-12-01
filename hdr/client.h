#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <netdb.h>
#include <string.h>
#include <limits.h>
#include "database.h"
#include "commands.h"

#ifndef __CLIENT_H__
#define __CLIENT_H__

struct sockaddr_in address;

void init (char *hostname, int noport, int *clientsocket);

void server_interaction(int clientsocket);

void wait_response (int clientsocket, char buffer[1024]);

#endif // !__CLIENT_H__