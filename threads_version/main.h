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

// ifndef del main.c
#ifndef MAIN_H
#define MAIN_H

// coordinate oggetti char e finestre di gioco
#define WIN_X 0             // Coordinata X generale valida in più occasioni
#define WIN_Y 1             // Coordinata Y generale di varie finestre (WINTITLE, WINNEST 
#define DIVIDER_1_Y 6       // Coordinata Y Divider 1
#define WINLIVES_Y 7        // Coordinata Y finestra WINLIVES
#define DIVIDER_2_Y 12      // Coordinata Y Divider 2
#define WINTIME_Y 13        // Coordinata Y finestra WINTIME
#define DIVIDER_3_Y 14      // Coordinata Y Divider 3
#define WINGAME_Y 15        // Coordinata Y finestra di WINGAME
#define SUBWINGAME_X 1      // Coordinata X generale delle subwin di winGame
#define WINSHORE_Y 4        // Coordinata Y finestra WINSHORE
#define WINRIVER_Y 10       // Coordinata Y finestra WINRIVER
#define WINSIDEWALK_Y 34    // Coordinata Y finestra WINSIDEWALK
#define WINEND_Y 2          // Coordinata Y char finestre finali
#define WINEND_SCORE_Y 8    // Coordinata Y Score finale
#define HEART_X 27          // Coordinata X char HEART
#define NEST1_X 6           // Coordinata X char NEST1
#define NEST2_X  66         // Coordinata X char NEST2
#define NEST3_X 131         // Coordinata X char NEST3
#define NEST4_X 191         // Coordinata X char NEST4
#define NEST5_X 251         // Coordinata X char NEST5
#define STARTFROG_X 131     // Coordinata X partenza Frog
#define STARTFROG_Y 37      // Coordinata Y partenza Frog
#define PLANT1_X 36         // Coordinata X char PLANT1
#define PLANT2_X 131        // Coordinata X char PLANT2
#define PLANT3_X 221        // Coordinata X char PLANT3
#define HUNDREDS_TIME_X 152 // Coordinata X char NUMBERS TIMELEFT centinaia
#define HUNDREDS_POINT_X 233// Coordinata X char NUMBERS POINTS centinaia
#define TENS_POINT_X 240    // Coordinata X char NUMBERS POINTS decine
#define UNIT_POINT_X 247    // Coordinata X char NUMBERS POINTS unità
#define POINTS_X 205        // Coordinata X char POINT

// larghezza oggetti char
#define YOUWIN_W 38         // Larghezza char YOUWIN
#define YOULOSE_W 39        // Larghezza char YOULOSE

// dimensioni finsetre di gioco
#define WINMENU_H 32        // Altezza finestra WINMENU 
#define WINLEVEL_H 30       // Altezza finestra WINLEVEL
#define WIN_H 15            // Altezza finestra WIN
#define WINTITLE_H 5        // Altezza finestra WINTITLE
#define WINLIVES_H 5        // Altezza finestra WINLIVES
#define WINTIME_H 1         // Altezza finestra WINTIME
#define WINGAME_H 41        // Altezza finestra di WINGAME
#define WINNEST_H 3         // Altezza finestra WINNEST
#define WINSHORE_H 6        // Altezza finestra WINSHORE
#define WINRIVER_H 24       // Altezza finestra WINRIVER
#define WINSIDEWALK_H 6     // Altezza finestra WINSIDEWALK
#define WINEND_H 12         // Altezza finestre finali
#define TOTAL_W 262         // Larghezza finestra WIN e WINGAME
#define WIN_W 260           // Larghezza finestra generale       
#define WINEND_W 50         // Larghezza finestre finali  

// variabili di gioco
#define HEART_SEPARATOR 3   // Distanza tra char HEART 
#define STARTLIVES 3        // Numero di vite iniziali

// variabili globali char
extern char YOUWIN[5][YOUWIN_W + 1];
extern char YOULOSE[5][YOULOSE_W + 1];

// variabili globali finestre
extern WINDOW *winEnd;

void StartGame();
void Match ();
void FatherFunction();

#endif