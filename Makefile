# Compilateur utilisé
CC=gcc

# Options du compilateur
CFLAGS=-Wall -std=c11 -Ihdr

# Listes des fichiers objets
OBJS_S=obj/server.o
OBJS_C=obj/client.o

# Nom de l'exécutable
EXEC=server client

all: $(EXEC)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

server:
	$(CC) -o $@ obj/server.o

client:
	$(CC) -o $@ obj/client.o

clean:
	rm -f *.o $(OBJS)

mrproper: clean
	rm -f $(EXEC)