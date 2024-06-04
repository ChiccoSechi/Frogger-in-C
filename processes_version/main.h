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

// #ifndef directive for variables in the main.c file
#ifndef MAIN_H
#define MAIN_H

// Game window coordinates
#define WIN_X 0             // General X coordinate valid in multiple occasions
#define WIN_Y 1             // General Y coordinate for various windows (WINTITLE, WINNEST 
#define DIVIDER_1_Y 6       // Divider 1 Y coordinate
#define WINLIVES_Y 7        // WINLIVES window Y coordinate
#define DIVIDER_2_Y 12      // Divider 2 Y coordinate
#define WINTIME_Y 13        // WINTIME window Y coordinate
#define DIVIDER_3_Y 14      // Divider 3 Y coordinate
#define WINGAME_Y 15        // WINGAME window Y coordinate
#define SUBWINGAME_X 1      // General X coordinate for subwins of winGame
#define WINSHORE_Y 4        // WINSHORE window Y coordinate
#define WINRIVER_Y 10       // WINRIVER window Y coordinate
#define WINSIDEWALK_Y 34    // WINSIDEWALK window Y coordinate

// Final windows coordinates
#define WINEND_Y 2          // Final windows Y coordinate
#define WINEND_SCORE_Y 8    // Final Score Y coordinate

// Char coordinates
#define HEART_X 27          // HEART char X coordinate
#define NEST1_X 6           // NEST1 char X coordinate
#define NEST2_X  66         // NEST2 char X coordinate
#define NEST3_X 131         // NEST3 char X coordinate
#define NEST4_X 191         // NEST4 char X coordinate
#define NEST5_X 251         // NEST5 char X coordinate
#define PLANT1_X 36         // PLANT1 char X coordinate
#define PLANT2_X 131        // PLANT2 char X coordinate
#define PLANT3_X 221        // PLANT3 char X coordinate
#define HUNDREDS_TIME_X 152 // NUMBERS TIMELEFT hundreds X coordinate
#define HUNDREDS_POINT_X 233// NUMBERS POINTS hundreds X coordinate
#define POINTS_X 205        // POINT char X coordinate

// Game variables
#define STARTFROG_X 131     // Frog starting X coordinate
#define STARTFROG_Y 37      // Frog starting Y coordinate

// Char objects dimensions
#define YOUWIN_W 38         // YOUWIN char width
#define YOULOSE_W 39        // YOULOSE char width

// Game window dimensions
#define WINMENU_H 32        // WINMENU window height 
#define WINLEVEL_H 30       // WINLEVEL window height
#define WIN_H 15            // WIN window height
#define WINTITLE_H 5        // WINTITLE window height
#define WINLIVES_H 5        // WINLIVES window height
#define WINTIME_H 1         // WINTIME window height
#define WINGAME_H 41        // WINGAME window height
#define WINNEST_H 3         // WINNEST window height
#define WINSHORE_H 6        // WINSHORE window height
#define WINRIVER_H 24       // WINRIVER window height
#define WINSIDEWALK_H 6     // WINSIDEWALK window height
#define WINEND_H 12         // Final windows height
#define TOTAL_W 262         // WIN and WINGAME window width
#define WINEND_W 50         // Final windows width   

// DEFINITION OF KEYS AND GAME CONSTANTS
#define KEY_SPACE 32        // Space key
#define TIME_E 300          // Time for each game round (EASY mode)
#define TIME_N 150          // Time for each game round (NORMAL mode)
#define TIME_H 75           // Time for each game round (HARD mode)
#define N_NEST 5            // Total number of nests
#define HEART_SEPARATOR 3   // Distance between HEART chars 
#define STARTLIVES 3        // Initial number of lives

// Screen limits
#define LIMITFROG_UP 1      // FROG_UP limit
#define LIMITFROG_DOWN 37   // FROG_DOWN limit
#define LIMITFROG_LEFT 1    // FROG_LEFT limit
#define LIMITFROG_RIGHT 256 // FROG_RIGHT limit

// Frog structure
struct Frog{        
    short x, y;             // Coordinates
    bool bullet;            // Bullet management (bool = true indicates that the bullet has been shot, bool = false indicates the opposite)
};

// GameSet structure
struct GameSet{
    bool nestActive[N_NEST];// Array of booleans to check if the nests are Open or Closed (bool = true indicates the nest is open, bool = false indicates the opposite)
    int LivesLeft;          // Remaining lives
    int Point;              // Points of the round
};

// WINDOW variable
extern WINDOW  *winEnd;

// Functions
void StartGame(struct GameSet *gameset);
void Match (struct GameSet *gameset, int difficulty);
void FrogFunction(int Pipe, int ReadPipe);
void PlantFunction(int Pipe, int id, int difficulty);
void FatherFunction(int PipeFrog, int (*PipePlants)[2], struct GameSet *gameset, int PipeCommunicateFrog, int difficulty);

// Char objects
extern char YOUWIN[TITLE_H][YOUWIN_W + 1];
extern char YOULOSE[TITLE_H][YOULOSE_W + 1];

#endif
