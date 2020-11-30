# Compilateur utilisé
CC=gcc

# Options du compilateur
CFLAGS=-Wall -Ihdr

# Listes des fichiers objets
OBJS_S=obj/server.o
OBJS_C=obj/client.o

# Nom de l'exécutable
EXEC=server client

all: $(EXEC)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

server: $(OBJS_S)
	$(CC) -o $@ $^

client: $(OBJS_C)
	$(CC) -o $@ $^

clean:
	rm -f obj/*.o

mrproper: clean
	rm -f $(EXEC)