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

// ifndef delle variabili per il file menu.c
#ifndef MENU_H
#define MENU_H

// Identificativi Drawmenu
#define NEWGAME 0           // Id per la stampa di NEW_GAME
#define EXITLEVEL 1         // Id per la stampa di EXIT_LEVEL
#define FLOWERS 2           // Id per la stampa di FLOWERS

// Dimensioni finestre di gioco
#define WINMENU_W 67        // Larghezza finestra WINMENU  

// Coordinate finestre
#define NEWGAME_Y 4         // Coordinata Y char NEW_GAME 
#define EXIT_Y 12           // Coordinata Y char EXIT_LEVEL
#define FLOWERS_Y 20        // Coordinata Y char FLOWERS

// Dimensioni oggetti char
#define NEWGAME_W 50        // Larghezza char NEW_GAME
#define EXIT_W 18           // Larghezza char EXIT_LEVEL
#define FLOWER_W 65         // Larghezza char FLOWERS
#define EASY_W 26           // Larghezza char EASY
#define NORMAL_W 40         // Larghezza char NORMAL
#define HARD_W 27           // Larghezza char HARD
#define FLOWER_H 9          // Altezza char FLOWERS
#define CHAR_H 5           // Altezza char generale delle scritte

// Variabili globali finestre
extern WINDOW *winMenu, *winLevel;

// Funzioni
int MenuFunction();
void SelectMenuChoice(int id);
void CreateWindowMenu();
int LevelFunction();
void SelectLevelChoice(int id);
void CreateWindowLevel();
void DrawMenu(int y, int x, int id, WINDOW *win);

// Oggetti char
extern char NEW_GAME[CHAR_H][NEWGAME_W + 1];
extern char EXIT_LEVEL[CHAR_H][EXIT_W + 1];
extern char FLOWER[FLOWER_H][FLOWER_W + 1];
extern char EASY[CHAR_H][EASY_W + 1];
extern char NORMAL[CHAR_H][NORMAL_W + 1];
extern char HARD[CHAR_H][HARD_W + 1];

#endif