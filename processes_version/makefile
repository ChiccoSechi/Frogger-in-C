# Target principale e dipendenze
all: a.out

# Regola per compilare l'eseguibile
a.out: main.o menu.o processi_nipote.o grafica.o
	gcc -o a.out main.o menu.o processi_nipote.o grafica.o -lncurses

# Regole per compilare i file oggetto
main.o: main.c main.h menu.h processi_nipote.h grafica.h
	gcc -c main.c -o main.o

menu.o: menu.c menu.h
	gcc -c  menu.c -o menu.o

processi_nipote.o: processi_nipote.c processi_nipote.h
	gcc -c processi_nipote.c -o processi_nipote.o 

grafica.o: grafica.c grafica.h
	gcc -c grafica.c -o grafica.o

# Pulizia dei file oggetto e dell'eseguibile
clean:
	rm -f *.o a.out
