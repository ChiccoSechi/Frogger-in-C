// ifndef delle librerie per evitare una ripetizione
#ifndef LIBRERIE_H
#define LIBRERIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ncurses.h>
#include <pthread.h>
#include <semaphore.h>

#endif

// ifndef dei define delle difficoltà di gioco per evitare una ripetizione
#ifndef DIFFICULT_ID_H
#define DIFFICULT_ID_H

#define EASY_ID 3           // Id per la stampa di EASY
#define NORMAL_ID 4         // Id per la stampa di NORMAL
#define HARD_ID 5           // Id per la stampa di HARD

#endif


//ifndef del file processi.c
#ifndef PROCESSI_H
#define PROCESSI_H

// Costanti di gioco
#define KEY_SPACE 32        // Tasto spazio
#define TIME_E 300          // Tempo di ogni manche di gioco (Modalita EASY)
#define TIME_N 150          // Tempo di ogni manche di gioco (Modalita NORMAL)
#define TIME_H 75           // Tempo di ogni manche di gioco (Modalita HARD)

// Limiti Rana
#define LIMITFROG_UP 1      // Limite FROG_UP
#define LIMITFROG_DOWN 37   // Limite FROG_DOWN
#define LIMITFROG_LEFT 1    // Limite FROG_LEFT
#define LIMITFROG_RIGHT 256 // Limite FROG_RIGHT

// variabili globali
extern int difficulty, whatcroco;

void *FrogFunction(void* arg);
void *PlantFunction(void* arg);
void *FrogBulletFunction(void* arg);
void *PlantBulletFunction(void* arg);
void *RiverFunction(void* arg);
void *CrocodileFunction(void *arg);
void *GameTimeFunction (void *arg);

#endif