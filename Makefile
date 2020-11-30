# Compilateur utilisé
CC=gcc

# Options du compilateur
CFLAGS=-Wall -std=c11

# Listes des dépendances et des fichiers objets
DEPS=hdr/server.h
OBJS=obj/server.o

# Nom de l'exécutable
EXEC=server

all: $(EXEC)

obj/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o $(OBJS)

mrproper: clean
	rm -f $(EXEC)