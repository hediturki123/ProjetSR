# Compilateur utilisé
CC=gcc

# Options du compilateur
CFLAGS=-Wall -std=c11

# Listes des dépendances et des fichiers objets
DEPS_S=hdr/server.h
OBJS_S=obj/server.o

DEPS_C=hdr/client.h
OBJS_C=obj/client.o

# Nom de l'exécutable
EXEC=server client

all: $(EXEC)

obj/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJS_S)
	$(CC) -o $@ $^ $(CFLAGS)

client: $(OBJS_C)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o $(OBJS)

mrproper: clean
	rm -f $(EXEC)