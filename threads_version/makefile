# Target principale e dipendenze
all: a.out

# Regola per compilare l'eseguibile
a.out: main.o menu.o threads.o graphics.o global.o
	gcc -o a.out main.o menu.o threads.o graphics.o global.o -lncurses -lpthread

# Regole per compilare i file oggetto
main.o: main.c main.h menu.h threads.h graphics.h global.h
	gcc -c main.c -o main.o

menu.o: menu.c menu.h
	gcc -c  menu.c -o menu.o

processi.o: threads.c threads.h global.h
	gcc -c threads.c -o threads.o 

graphics.o: graphics.c graphics.h global.h
	gcc -c graphics.c -o graphics.o

global.o: global.c global.h
	gcc -c global.c -o global.o

# Pulizia dei file oggetto e dell'eseguibile
clean:
	rm -f *.o a.out

