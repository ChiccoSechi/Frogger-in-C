// #ifndef directive for libraries to avoid repetition
#ifndef LIBRERIE_H
#define LIBRERIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/select.h>

#endif

// #ifndef directive for structres to avoid repetition
#ifndef STRUTTURE_H
#define STRUTTURE_H

// Plant structure
struct Plant{
    short x, y, id;         // Coordinates and id (necessary for recognition)
    bool bullet;            // Bullet management (bool = true indicates that the bullet has been shot, bool = false indicates the opposite)
};

// Frog Bullet structure
struct FrogBullet{      
    short x, y;             // Coordinates
};

// Plant Bullet structure
struct PlantBullet{
    short x, y;             // Coordinates
};

// Crocodile structure
struct Crocodile{
    int x, y;               // Coordinates
    bool direction;         // Direction of the crocodile in the river flow (bool = true indicates from Left to Right, bool = false indicates the opposite)
    bool type;              // Type (bool = true indicates that the crocodile is Good, bool = false indicates the opposite)
};

// Time structure
struct Time{
    int barLengthTime;      // Length of the remaining time bar for the round
    int timeLeft;           // Remaining time in seconds
};

#endif

// #ifndef directive for common variables with other .c files to avoid repetitions
#ifndef VARIABILI_COMUNI_H
#define VARIABILI_COMUNI_H

// Char objects dimensions
#define OBJECT_W 5          // Width of game objects
#define WIN_W 260           // General window width 

#endif

// #ifndef directive for variables in the grafica.c file
#ifndef GRAFICA_H
#define GRAFICA_H

// Game variables
#define MAX_BULLET_FROG 2   // Maximum number of frog bullets
#define MAX_BULLET_PLANT 3  // Maximum number of plant bullets (NORMAL mode)
#define N_PLANTS 3          // Total number of plants
#define FLOWS 8             // Total number of river flows
#define MAX_CROCODILES 6    // Maximum number of crocodiles per course (EASY - NORMAL)

// Identifiers for DrawDecorations()
#define TITLE_ID 0          // Identifier for char TITLE
#define LIVES_ID 1          // Identifier for char LIVES
#define HEART_ID 2          // Identifier for char HEART
#define TIMESLEFT_ID 3      // Identifier for char TIMESLEFT
#define POINTS_ID 4         // Identifier for char POINTS

// Identifiers for DrawObjects()
#define NESTOPEN_ID 0       // Identifier for char NESTOPEN
#define NESTCLOSED_ID 1     // Identifier for char NESTCLOSED
#define FROG_ID 2           // Identifier for char FROG
#define PLANTV1_ID 3        // Identifier for char PLANTV1
#define PLANTV2_ID 4        // Identifier for char PLANTV2
#define PLANTV3_ID 5        // Identifier for char PLANTV3

// Identifiers for DrawCrocodile()
#define GOODCROCODX 0       // Identifier for char GOOD CROCODILE from right to left
#define BADCROCODX 1        // Identifier for char BAD CROCODILE from right to left
#define GOODCROCOSX 2       // Identifier for char GOOD CROCODILE from left to right
#define BADCROCOSX 3        // Identifier for char BAD CROCODILE from left to right

// Char objects dimensions
#define TITLE_H 5           // General height of text chars
#define OBJECT_H 3          // General height of game objects
#define CROCO_H 3           // Height of char CROCODILE
#define NUMBER_W 7          // Width of char NUMBERS
#define CROCO_W 30          // Width of char CROCODILE
#define TITLE_W 95          // Width of char TITLE
#define LIVES_W 24          // Width of char LIVES
#define HEART_W 11          // Width of char HEART
#define TIMESLEFT_W 44      // Width of char TIMESLEFT
#define NEST_W 11           // Width of char NEST
#define POINTS_W 26         // Width of char POINTS

// Coordinates of char objects
#define GENERAL_Y 0         // General Y coordinate for various CHAR
#define PLANT_Y 7           // Y coordinate for char PLANT

// Functions
void Color();
void Reset(int PipeFrogBullet[MAX_BULLET_FROG][2], pid_t FrogBullet[MAX_BULLET_FROG], int PipePlantsBullet[MAX_BULLET_PLANT * N_PLANTS][2], pid_t PlantBullet[MAX_BULLET_PLANT * N_PLANTS], int PipeCrocodile[MAX_CROCODILES * FLOWS][2], int PipeCommunicateCrocodile[MAX_CROCODILES * FLOWS][2], pid_t CrocodileProcess[MAX_CROCODILES * FLOWS], int PipeRiver[FLOWS][2], bool riveractive[FLOWS], pid_t River[FLOWS], int PipePlant[N_PLANTS][2], pid_t TimerProcess[N_PLANTS], int PipeGameTime[2], pid_t GameTime, WINDOW *win1, WINDOW *win2);
void DrawDecorations(int y, int x, int id, WINDOW *win);
void DrawNumber(int number, int x, WINDOW *win);
void DrawCrocodile(int y, int x, int id, WINDOW *win);
void DrawObjects(int y, int x, int id, WINDOW *win);
void PlantsMovements(int x, bool plantsactive[N_PLANTS], struct Plant plants[N_PLANTS], WINDOW *win);

// char objects
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