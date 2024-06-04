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

// #ifndef directive for difficulty level defines to avoid repetition
#ifndef DIFFICULT_ID_H
#define DIFFICULT_ID_H

#define EASY_ID 3           // Id for the printing of EASY
#define NORMAL_ID 4         // Id for the printing of NORMAL
#define HARD_ID 5           // Id for the printing of HARD

#endif

// #ifndef directive for variables in the menu.c file
#ifndef MENU_H
#define MENU_H

// Identifiers for DrawMenu
#define NEWGAME 0           // Id for the printing of NEW_GAME
#define EXITLEVEL 1         // Id for the printing of EXIT_LEVEL
#define FLOWERS 2           // Id for the printing of FLOWERS

// Game window dimensions
#define WINMENU_W 67        // WINMENU window width  

// Window coordinates
#define NEWGAME_Y 4         // Y coordinate for char NEW_GAME 
#define EXIT_Y 12           // Y coordinate for char EXIT_LEVEL
#define FLOWERS_Y 20        // Y coordinate for char FLOWERS

// Char objects dimensions
#define NEWGAME_W 50        // Width of char NEW_GAME
#define EXIT_W 18           // Width of char EXIT_LEVEL
#define FLOWER_W 65         // Width of char FLOWERS
#define EASY_W 26           // Width of char EASY
#define NORMAL_W 40         // Width of char NORMAL
#define HARD_W 27           // Width of char HARD
#define CHAR_H 5            // Height of char 
#define FLOWER_H 9          // Height of char FLOWERS

// Window variables
extern WINDOW *winMenu, *winLevel;

// Functions
int MenuFunction();
void SelectMenuChoice(int id);
void CreateWindowMenu();
int LevelFunction();
void SelectLevelChoice(int id);
void CreateWindowLevel();
void DrawMenu(int y, int x, int id, WINDOW *win);

// Char objects
extern char NEW_GAME[CHAR_H][NEWGAME_W + 1];
extern char EXIT_LEVEL[CHAR_H][EXIT_W + 1];
extern char FLOWER[FLOWER_H][FLOWER_W + 1];
extern char EASY[CHAR_H][EASY_W + 1];
extern char NORMAL[CHAR_H][NORMAL_W + 1];
extern char HARD[CHAR_H][HARD_W + 1];

#endif
