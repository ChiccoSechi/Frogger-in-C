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

#ifndef CONDIVISE_H
#define CONDIVISE_H

// Variabili di gioco
#define N_NEST 5            // Numero totale di tane
#define N_PLANTS 3          // Numero totale di piante
#define MAX_BULLET_FROG 2   // Numero massimo proiettili rana 
#define MAX_BULLET_PLANT 3  // Numero massimo proiettili pianta (Modalita NORMAL)
#define FLOWS 8             // Numero totali di flussi del fiume
#define MAX_CROCODILES 6    // Numero massimo di coccodrilli per corso (EASY - NORMAL)

// Dimensioni oggetti char
#define OBJECT_H 3          // Altezza generale oggetti di gioco
#define OBJECT_W 5          // Larghezza oggetti di gioco
#define WIN_W 260           // Larghezza finestra generale 

#endif

// ifndef delle variabili per il file grafica.c
#ifndef GRAFICA_H
#define GRAFICA_H

// Identificativi DrawMenu
#define EASY_ID 3           // Id per la stampa di EASY
#define NORMAL_ID 4         // Id per la stampa di NORMAL
#define HARD_ID 5           // Id per la stampa di HARD
// Identificativi DrawDecorations()
#define TITLE_ID 0          // Identificativo char TITLE
#define LIVES_ID 1          // Identificativo char LIVES
#define HEART_ID 2          // Identificativo char HEART
#define TIMESLEFT_ID 3      // Identificativo char TIMESLEFT
#define POINTS_ID 4         // Identificativo char POINTS
// Identificativi DrawObjects()
#define NESTOPEN_ID 0       // Identificativo char NESTOPEN
#define NESTCLOSED_ID 1     // Identificativo char NESTCLOSED
#define FROG_ID 2           // Identificativo char FROG
#define PLANTV1_ID 3        // Identificativo char PLANTV1
#define PLANTV2_ID 4        // Identificativo char PLANTV2
#define PLANTV3_ID 5        // Identificativo char PLANTV3
//Identificativi DrawCrocodile()
#define GOODCROCODX 0       // Identificativo char CRCODILE GOOD da DX verso SX
#define BADCROCODX 1        // Identificativo char CROCODILE BAD da DX verso SX
#define GOODCROCOSX 2       // Identificativo char CROCODILE GOOD da SX verso DX 
#define BADCROCOSX 3        // Identificativo char CROCODILE BAD da SX verso DX

// Dimensioni oggetti char
#define TITLE_H 5           // Altezza char generale delle scritte
#define CROCO_H 3           // Altezza char CROCODILE
#define NUMBER_W 7          // Larghezza char NUMBERS
#define CROCO_W 30          // Larghezza char CROCODILE
#define TITLE_W 95          // Larghezza char TITLE
#define LIVES_W 24          // Larghezza char LIVES
#define HEART_W 11          // Larghezza char HEART
#define TIMESLEFT_W 44      // Larghezza char TIMESLEFT
#define NEST_W 11           // Larghezza char NEST
#define POINTS_W 26         // Larghezza char POINTS

// Coordinate oggetti char
#define GENERAL_Y 0         // Coordinata Y generale di vari CHAR
#define PLANT_Y 7           // Coordinata Y char PLANT

// funzioni
void Color();
void DrawDecorations(int y, int x, int id, WINDOW *win);
void DrawNumber(int number, int x, WINDOW *win);
void DrawCrocodile(int y, int x, int id, WINDOW *win);
void DrawObjects(int y, int x, int id, WINDOW *win);
void PlantsMovements(int x, WINDOW *win);
void Reset(pthread_t ThreadFrogBullet[MAX_BULLET_FROG], pthread_t ThreadPlantBullet[MAX_BULLET_PLANT * N_PLANTS], pthread_t ThreadGameTime, pthread_t ThreadCrocodile[MAX_CROCODILES * FLOWS], WINDOW *winGame, WINDOW *win);


// Oggetti char
extern char TITLE[TITLE_H][TITLE_W + 1];
extern char LIVES[TITLE_H][LIVES_W + 1];
extern char HEART[TITLE_H][HEART_W + 1];
extern char TIMESLEFT[TITLE_H][TIMESLEFT_W + 1];
extern char NESTOPEN[OBJECT_H][NEST_W + 1];
extern char NESTCLOSED[OBJECT_H][NEST_W + 1];
extern char FROG[OBJECT_H][OBJECT_W + 1];
extern char PLANTV1[OBJECT_H][OBJECT_W + 1];
extern char PLANTV2[OBJECT_H][OBJECT_W + 1];
extern char PLANTV3[OBJECT_H][OBJECT_W + 2];
extern char G_CROCODILE_DX[CROCO_H][CROCO_W + 1];
extern char B_CROCODILE_DX[CROCO_H][CROCO_W + 1];
extern char G_CROCODILE_SX[CROCO_H][CROCO_W + 1];
extern char B_CROCODILE_SX[CROCO_H][CROCO_W + 1];
extern char ZERO[TITLE_H][NUMBER_W + 1];
extern char ONE[TITLE_H][NUMBER_W + 1];
extern char TWO[TITLE_H][NUMBER_W + 1];
extern char THREE[TITLE_H][NUMBER_W + 1];
extern char FOUR[TITLE_H][NUMBER_W + 1];
extern char FIVE[TITLE_H][NUMBER_W + 1];
extern char SIX[TITLE_H][NUMBER_W + 1];
extern char SEVEN[TITLE_H][NUMBER_W + 1];
extern char EIGHT[TITLE_H][NUMBER_W + 1];
extern char NINE[TITLE_H][NUMBER_W + 1];
extern char POINTS[TITLE_H][POINTS_W + 1];

#endif