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

// #ifndef directive for difficulty level defines to avoid repetition
#ifndef DIFFICULT_ID_H
#define DIFFICULT_ID_H

#define EASY_ID 3           // Id for the printing of EASY
#define NORMAL_ID 4         // Id for the printing of NORMAL
#define HARD_ID 5           // Id for the printing of HARD

#endif

// #ifndef directive for variables in the processi_nipote.c file
#ifndef PROCESSI_NIPOTE_H
#define PROCESSI_NIPOTE_H

// Functions
void RiverFunction(int pipe, int rivertime, int difficulty);
void GameTimeFunction(int pipe, int time);
void FrogBulletFunction(int pipe, int y, int x);
void PlantBulletFunction(int pipe, int y, int x);
void CrocodileFunction(int Pipe, int y, int time_crocodile, bool direction, int ReadPipe, int difficulty);
void TimerFunction(int pipe, bool plantsactive);

#endif
