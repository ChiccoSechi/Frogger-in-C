// Include the header file "graphics.h" containing all the #define directives, necessary structures, functions, and char structures.
#include "graphics.h"

// Function for creating pairs of colors
void Color(){
    // Color pair (text - background)
    init_pair(1, COLOR_WHITE, COLOR_GREEN);         // Grass zones
	init_pair(2, COLOR_WHITE, COLOR_CYAN);          // River zones
	init_pair(3, COLOR_WHITE, COLOR_YELLOW);        // Nests zones

    init_pair(4, COLOR_BLUE, COLOR_CYAN);           // Good Crocodiles
    init_pair(5, COLOR_RED, COLOR_CYAN);            // Bad Crocodiles
    init_pair(6, COLOR_BLACK, COLOR_YELLOW);        // Nests
    init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);     // Plants bullets
    init_pair(8, COLOR_MAGENTA, COLOR_GREEN);       // Plants
    init_pair(9, COLOR_WHITE, COLOR_WHITE);         // Frog bullets

    // The frog is displayed in white
}

// Reset function that terminates processes and closes pipes
void Reset(int PipeFrogBullet[MAX_BULLET_FROG][2], pid_t FrogBullet[MAX_BULLET_FROG], int PipePlantsBullet[MAX_BULLET_PLANT * N_PLANTS][2], pid_t PlantBullet[MAX_BULLET_PLANT * N_PLANTS], int PipeCrocodile[MAX_CROCODILES * FLOWS][2], int PipeCommunicateCrocodile[MAX_CROCODILES * FLOWS][2], pid_t CrocodileProcess[MAX_CROCODILES * FLOWS], int PipeRiver[FLOWS][2], bool riveractive[FLOWS], pid_t River[FLOWS], int PipePlant[N_PLANTS][2], pid_t TimerProcess[N_PLANTS], int PipeGameTime[2], pid_t GameTime, WINDOW *win1, WINDOW *win2){
    // Iterate through frog bullets processes
    for(size_t i = 0; i < MAX_BULLET_FROG; i++){
        // Close the pipes
        close(PipeFrogBullet[i][1]);
        close(PipeFrogBullet[i][0]);
        // If the bullet process is active
        if(FrogBullet[i] != -1){
            // kill the process
            kill(FrogBullet[i], SIGKILL);
        }
    }
    // Iterate through plants bullets processes
    for(size_t i = 0; i < MAX_BULLET_PLANT * N_PLANTS; i++){
        // Close the pipes
        close(PipePlantsBullet[i][1]);
        close(PipePlantsBullet[i][0]);
        // If the plant bullets process is active
        if(PlantBullet[i] != -1){
            // Kill the process
            kill(PlantBullet[i], SIGKILL);
        }
    }
    // Continue to follow the same logic for all active processes and created pipes
    // Iterate through crocodiles processes 
    for(size_t i = 0; i < MAX_CROCODILES * FLOWS; i++){
        close(PipeCrocodile[i][1]);
        close(PipeCrocodile[i][0]);
        close(PipeCommunicateCrocodile[i][1]);
        close(PipeCommunicateCrocodile[i][0]);
        if(CrocodileProcess[i] != -1){
            kill(CrocodileProcess[i], SIGKILL);
        }
    }
    // Iterate through flows processes
    for(size_t i = 0; i < FLOWS; i++){
        close(PipeRiver[i][1]);
        close(PipeRiver[i][0]);
        if(riveractive[i]){
            kill(River[i], SIGKILL);
        }
    }
    // Iterate through plants processes
    for(size_t i = 0; i < N_PLANTS; i++){
        close(PipePlant[i][1]);
        close(PipePlant[i][0]);
        if(kill(TimerProcess[i], 0 ) == 0){
            kill(TimerProcess[i], SIGKILL);
        }
    }
    // Game Time process
    close(PipeGameTime[1]);
    close(PipeGameTime[0]);
    if(kill(GameTime, 0) == 0){
        kill(GameTime, SIGKILL);
    }
    // Elimination of windows to free up memory
    delwin(win1);
    delwin(win2);
}

// Function for displaying "Decorations" char objects on the screen
// In all cases, a for loop is used to iterate over the rows of the char object in question
// Each row is printed, increasing the y coordinate of the print at each iteration
// This function takes as arguments the coordinates where to print, the id of the object to print, and the printing window
void DrawDecorations(int y, int x, int id, WINDOW *win){
    // Switch case based on the unique id for every object
    switch(id){
    // char TITLE
    case TITLE_ID:
        for(size_t i = 0; i < TITLE_H; i++){
            mvwprintw(win, y + i, x, "%s", TITLE[i]);
        } 
        break;
    // char LIVES
    case LIVES_ID:
        for(size_t i = 0; i < TITLE_H; i++){
            mvwprintw(win, y + i, x, "%s", LIVES[i]);
        } 
        break;
    // char HEART
    case HEART_ID:
        for(size_t i = 0; i < TITLE_H; i++){
            mvwprintw(win, y + i, x, "%s", HEART[i]);
        }
        break;
    // char TIMESLEFT
    case TIMESLEFT_ID:
        for (size_t i = 0; i < TITLE_H; i++){
            mvwprintw(win, y + i, x, "%s", TIMESLEFT[i]);
        }
        break;
    // char POINTS
    case POINTS_ID:
        for (size_t i = 0; i < TITLE_H; i++){
            mvwprintw(win, y + i, x, "%s", POINTS[i]);
        }
        break;
    default:
        break;
    }
}

// Function for printing numbers on the screen, works exactly like the DrawDecorations function
void DrawNumber(int number, int x, WINDOW *win){
    // Obtain hundreds, tens, and units for printing
    int hundreds = number / 100;
    int tens = (number % 100) / 10;
    int units = number % 10;
    // Switch case for drawing numbers
    switch(hundreds){
        case 0:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x, "%s", ZERO[i]);
            }
            break;
        case 1:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x, "%s", ONE[i]);
            }
            break;
        case 2:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x, "%s", TWO[i]);
            }
            break;
        case 3:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x, "%s", THREE[i]);
            }
            break;
        case 4:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x, "%s", FOUR[i]);
            }
            break;
        case 5:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x, "%s", FIVE[i]);
            }
            break;
        case 6:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x, "%s", SIX[i]);
            }
            break;
        case 7:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x, "%s", SEVEN[i]);
            }
            break;
        case 8:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x, "%s", EIGHT[i]);
            }
            break;
        case 9:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x, "%s", NINE[i]);
            }
            break;
        default:
            break;
    }
    // Same tings for tens
    switch(tens){
        case 0:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + NUMBER_W , "%s", ZERO[i]);
            }
            break;
        case 1:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + NUMBER_W , "%s", ONE[i]);
            }
            break;
        case 2:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + NUMBER_W , "%s", TWO[i]);
            }
            break;
        case 3:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + NUMBER_W , "%s", THREE[i]);
            }
            break;
        case 4:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + NUMBER_W , "%s", FOUR[i]);
            }
            break;
        case 5:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + NUMBER_W , "%s", FIVE[i]);
            }
            break;
        case 6:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + NUMBER_W , "%s", SIX[i]);
            }
            break;
        case 7:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + NUMBER_W , "%s", SEVEN[i]);
            }
            break;
        case 8:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + NUMBER_W , "%s", EIGHT[i]);
            }
            break;
        case 9:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + NUMBER_W , "%s", NINE[i]);
            }
            break;
        default:
            break;
    }
    // Same thing for units
    switch(units){
        case 0:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + (NUMBER_W * 2), "%s", ZERO[i]);
            }
            break;
        case 1:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + (NUMBER_W * 2), "%s", ONE[i]);
            }
            break;
        case 2:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + (NUMBER_W * 2), "%s", TWO[i]);
            }
            break;
        case 3:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + (NUMBER_W * 2), "%s", THREE[i]);
            }
            break;
        case 4:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + (NUMBER_W * 2), "%s", FOUR[i]);
            }
            break;
        case 5:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + (NUMBER_W * 2), "%s", FIVE[i]);
            }
            break;
        case 6:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + (NUMBER_W * 2), "%s", SIX[i]);
            }
            break;
        case 7:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + (NUMBER_W * 2), "%s", SEVEN[i]);
            }
            break;
        case 8:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + (NUMBER_W * 2), "%s", EIGHT[i]);
            }
            break;
        case 9:
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(win, GENERAL_Y + i, x + (NUMBER_W * 2), "%s", NINE[i]);
            }
            break;
        default:
            break;
    }
}

// Function for managing plant movements (to simulate the plants following the frog based on its movements)
void PlantsMovements(int x, bool plantsactive[N_PLANTS], struct Plant plants[N_PLANTS], WINDOW *win){
    // Itareate trough plants
    for(size_t i = 0; i < N_PLANTS; i++){
        // If the plant is active
        if(plantsactive[i]){
            // If the frog is on the left side of the plant
            if(x < plants[i].x){
                DrawObjects(PLANT_Y, plants[i].x, PLANTV1_ID, win);
            }
            // If the frog is under the plant
            else if(x == plants[i].x){
                DrawObjects(PLANT_Y, plants[i].x, PLANTV3_ID, win);
            }
            // If the frog is on the right side of the plant
            else{
                DrawObjects(PLANT_Y, plants[i].x, PLANTV2_ID, win);
            }
        }
    }
}

// Function for displaying "Objects" char objects on the screen
// In all cases, a for loop is used to iterate over the rows of the char object in question
// Each row is printed, increasing the y coordinate of the print at each iteration
void DrawObjects(int y, int x, int id, WINDOW *win){
    // Switch case based on the unique id to determine the type of char object
    switch(id){
    // Case for printing the char object NESTOPEN
    case NESTOPEN_ID:
        for(size_t i = 0; i < OBJECT_H; i++){
            mvwprintw(win, y + i, x, "%s", NESTOPEN[i]);
        } 
        break;
    // Case for printing the char object NESTCLOSED
    case NESTCLOSED_ID:
        for(size_t i = 0; i < OBJECT_H; i++){
            mvwprintw(win, y + i, x, "%s", NESTCLOSED[i]);
        } 
        break;
    // Case for printing the char object FROG
    case FROG_ID:
        for(size_t i = 0; i < OBJECT_H; i++){
            mvwprintw(win, y + i, x, "%s", FROG[i]);
        }
        break;
    case PLANTV1_ID:
    // Case for printing the char object PLANT version 1
        for (size_t i = 0; i < OBJECT_H; i++){
            mvwprintw(win, y + i, x, "%s", PLANTV1[i]);
        }
        break;
    case PLANTV2_ID:
    // Case for printing the char object PLANT version 2
        for (size_t i = 0; i < OBJECT_H; i++){
            mvwprintw(win, y + i, x, "%s", PLANTV2[i]);
        }
        break;
    case PLANTV3_ID:
    // Case for printing the char object PLANT version 3
        for (size_t i = 0; i < OBJECT_H; i++){
            mvwprintw(win, y + i, x, "%s", PLANTV3[i]);
        }
        break;
    default:
        break;
    }
}

// Function for displaying "Crocodiles" char objects on the screen
// Printing is structured in such a way that the object gradually appears or disappears from the screen
// In all cases, a for loop is used to iterate over the rows of the char object in question
// Each row is printed, increasing the y coordinate of the print at each iteration
void DrawCrocodile(int y, int x, int id, WINDOW *win){
    //DrawHappyCrocoDX
	if(id == GOODCROCODX){
		char temp[CROCO_W + 1];
		if(x == 0){
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, G_CROCODILE_DX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 5]);
			}
		}
		else if(x == 5){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, G_CROCODILE_DX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 10]);
			}
		}
		else if(x == 10){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, G_CROCODILE_DX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 15]);
			}
		}
		else if(x == 15){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, G_CROCODILE_DX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 20]);
			}
		}
		else if(x == 20){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, G_CROCODILE_DX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 25]);
			}
		}
		else if(x == 25){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				mvwprintw(win, y + i, x, "%s", G_CROCODILE_DX[i]);
			}
		}
		else if(x == WIN_W){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.25s", G_CROCODILE_DX[i]);
			} 
		}
		else if(x == WIN_W + 5){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.20s", G_CROCODILE_DX[i]);
			} 
		}
		else if(x == WIN_W + 10){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.15s", G_CROCODILE_DX[i]);
			} 
		}
		else if(x == WIN_W + 15){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.10s", G_CROCODILE_DX[i]);
			} 
		}
		else if(x == WIN_W + 20){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.5s", G_CROCODILE_DX[i]);
			} 
		}
		else if(x == WIN_W + 25){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.0s", G_CROCODILE_DX[i]);
			} 
		}
		else if(x > 25 && x <= WIN_W + 25){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++){
				mvwprintw(win, y + i, x, "%s", G_CROCODILE_DX[i]);
			}
		}
	}

	//DrawAngryCrocoDX
	else if(id == BADCROCODX){
		char temp[CROCO_W + 1];

		if(x == 0){
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, B_CROCODILE_DX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 5]);
			}
		}
		else if(x == 5){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, B_CROCODILE_DX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 10]);
			}
		}
		else if(x == 10){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, B_CROCODILE_DX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 15]);
			}
		}
		else if(x == 15){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, B_CROCODILE_DX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 20]);
			}
		}
		else if(x == 20){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, B_CROCODILE_DX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 25]);
			}
		}
		else if(x == 25){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				mvwprintw(win, y + i, x, "%s", B_CROCODILE_DX[i]);
			}
		}
		else if(x == WIN_W){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.25s", B_CROCODILE_DX[i]);
			} 
		}
		else if(x == WIN_W + 5){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.20s", B_CROCODILE_DX[i]);
			} 
		}
		else if(x == WIN_W + 10){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.15s", B_CROCODILE_DX[i]);
			} 
		}
		else if(x == WIN_W + 15){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.10s", B_CROCODILE_DX[i]);
			} 
		}
		else if(x == WIN_W + 20){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.5s", B_CROCODILE_DX[i]);
			} 
		}
		else if(x == WIN_W + 25){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.0s", B_CROCODILE_DX[i]);
			} 
		}
		else if(x < WIN_W + 25){
			x -= 25;
			for (size_t i = 0; i < CROCO_H; i++){
				mvwprintw(win, y + i, x, "%s", B_CROCODILE_DX[i]);
			}
		}
	}

	//DrawHappyCrocoSX
	else if(id == GOODCROCOSX){
		char temp[CROCO_W + 1];

		if(x == WIN_W - 5){
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.5s", G_CROCODILE_SX[i]);
			}
		}
		else if(x == WIN_W - 10){
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.10s", G_CROCODILE_SX[i]);
			}
		}
		else if(x == WIN_W - 15){
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.15s", G_CROCODILE_SX[i]);
			}
		}
		else if(x == WIN_W - 20){
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.20s", G_CROCODILE_SX[i]);
			}
		}
		else if(x == WIN_W - 25){
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.25s", G_CROCODILE_SX[i]);
			}
		}
		else if(x == -5){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, G_CROCODILE_SX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 25]);
			}
		}
		else if(x == -10){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, G_CROCODILE_SX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 20]);
			}
		}else if(x == -15){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, G_CROCODILE_SX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 15]);
			}
		}
		else if(x == -20){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, G_CROCODILE_SX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 10]);
			}
		}
		else if(x == -25){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, G_CROCODILE_SX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 5]);
			}
		}
		else{
		for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%s", G_CROCODILE_SX[i]);
			} 
		}	
	}

	//DrawAngryCrocoSX
	else if(id == BADCROCOSX){
		char temp[CROCO_W + 1];

		if(x == WIN_W - 5){
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.5s", B_CROCODILE_SX[i]);
			}
		}
		else if(x == WIN_W - 10){
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.10s", B_CROCODILE_SX[i]);
			}
		}
		else if(x == WIN_W - 15){
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.15s", B_CROCODILE_SX[i]);
			}
		}
		else if(x == WIN_W - 20){
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.20s", B_CROCODILE_SX[i]);
			}
		}
		else if(x == WIN_W - 25){
			for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%.25s", B_CROCODILE_SX[i]);
			}
		}
		else if(x == -5){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, B_CROCODILE_SX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 25]);
			}
		}
		else if(x == -10){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, B_CROCODILE_SX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 20]);
			}
		}else if(x == -15){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, B_CROCODILE_SX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 15]);
			}
		}
		else if(x == -20){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, B_CROCODILE_SX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 10]);
			}
		}
		else if(x == -25){
			x = 0;
			for (size_t i = 0; i < CROCO_H; i++){
				strcpy(temp, B_CROCODILE_SX[i]);
				mvwprintw(win, y + i, x, "%s", &temp[CROCO_W - 5]);
			}
		}
		else{
		for (size_t i = 0; i < CROCO_H; i++)
			{
				mvwprintw(win, y + i, x, "%s", B_CROCODILE_SX[i]);
			} 
		}
    }
}

// char objects
char TITLE[TITLE_H][TITLE_W + 1] = {
" _____ ____   ___   ____  ____ _____ ____                ____  _        _    _   _ _____ ____  ", 
"|  ___|  _ \\ / _ \\ / ___|/ ___| ____|  _ \\  __   _____  |  _ \\| |      / \\  | \\ | |_   _/ ___| ",
"| |_  | |_) | | | | |  _| |  _|  _| | |_) | \\ \\ / / __| | |_) | |     / _ \\ |  \\| | | | \\___ \\ ",
"|  _| |  _ <| |_| | |_| | |_| | |___|  _ <   \\ V /\\__ \\ |  __/| |___ / ___ \\| |\\  | | |  ___) |",
"|_|   |_| \\_\\\\___/ \\____|\\____|_____|_| \\_\\   \\_/ |___/ |_|   |_____/_/   \\_\\_| \\_| |_| |____/ ",
};

char LIVES[TITLE_H][LIVES_W + 1] = {
    " _     _                ",
    "| |   (_)_   _____  ___ ",
    "| |   | \\ \\ / / _ \\/ __|",
    "| |___| |\\ V /  __/\\__ \\",
    "|_____|_| \\_/ \\___||___/"
};

char HEART[TITLE_H][HEART_W + 1] = {
    "// \\\\ // \\\\",
    "||  \\V/  ||",
    "\\\\       //",
    "  \\\\   //  ",      
    "    \\V/    ",  
};

char TIMESLEFT[TITLE_H][TIMESLEFT_W + 1] = {
    " _____ _                  _          __ _   ",
    "|_   _(_)_ __ ___   ___  | |    ___ / _| |_ ",
    "  | | | | '_ ` _ \\ / _ \\ | |   / _ \\ |_| __|",
    "  | | | | | | | | |  __/ | |__|  __/  _| |_ ",
    "  |_| |_|_| |_| |_|\\___| |_____\\___|_|  \\__|"
};

char NESTOPEN[OBJECT_H][NEST_W + 1] = {
    " //+++++\\\\ ",
    "//       \\\\",
    "||       ||"
};

char NESTCLOSED[OBJECT_H][NEST_W + 1] = {
    " //+++++\\\\ ",
    "//XXXXXXX\\\\",
    "||XXXXXXX||"
};

char FROG[OBJECT_H][OBJECT_W + 1] = {
    " 0-0 ",
    "( ~ )",
	"^^ ^^"
};

char PLANTV1[OBJECT_H][OBJECT_W + 1] = {
    "(\\__ ",
    ":=)_)",
    "(/   "
};

char PLANTV2[OBJECT_H][OBJECT_W + 1] = {
    " __/)",
    "(_(=:",
    "   \\)"
};

char PLANTV3[OBJECT_H][OBJECT_W + 2] = {
    " |°| ",
    "/~|~\\",
    " .*. "
};

char G_CROCODILE_DX[CROCO_H][CROCO_W + 1] = {
	"~~~~~~~~~~~~~~~(0 0       _ _ ",
	"GGGGGGGGGGGGGGG    ``----(.).)",
	"GGGGGGGGGGGGGGG^V^v^V^V^v(___)" 
};

char B_CROCODILE_DX[CROCO_H][CROCO_W + 1] ={
	"~~~~~~~~~~~~~~~(X X       _ _ ",
	"BBBBBBBBBBBBBBB    ``----(.).)",
	"BBBBBBBBBBBBBBB^V^v^V^V^v(___)" 
};

char G_CROCODILE_SX[CROCO_H][CROCO_W + 1] = {
	" _ _       0 0)~~~~~~~~~~~~~~~",
	"(.(.)----'`    GGGGGGGGGGGGGGG",
	"(___)v^V^V^v^V^GGGGGGGGGGGGGGG"
};

char B_CROCODILE_SX[CROCO_H][CROCO_W + 1] ={
	" _ _       X X)~~~~~~~~~~~~~~~",
	"(.(.)----'`    BBBBBBBBBBBBBBB",
	"(___)v^V^V^v^V^BBBBBBBBBBBBBBB"
};

char ZERO[TITLE_H][NUMBER_W + 1] = {
    "  ___  ",
    " / _ \\ ",
    "| | | |",
    "| |_| |",
    " \\___/ "
};

char ONE[TITLE_H][NUMBER_W + 1] = {
    "     _ ",
    "    / |",
    "    | |",
    "    | |",
    "    |_|" 
};

char TWO[TITLE_H][NUMBER_W + 1] = {
    " ____  ",
    "|___ \\ ",
    "  __) |",
    " / __/ ",
    "|_____|"
};

char THREE[TITLE_H][NUMBER_W + 1] = {
    " _____ ",
    "|___ / ",
    "  |_ \\ ",
    " ___) |",
    "|____/ "
};

char FOUR[TITLE_H][NUMBER_W + 1] = {
    " _  _  ", 
    "| || | ", 
    "| || |_", 
    "|__  _|",
    "   |_| " 
};

char FIVE[TITLE_H][NUMBER_W + 1] = {
    " ____  ",
    "| ___| ",
    "|___ \\ ",
    " ___) |",
    "|____/ "
};

char SIX[TITLE_H][NUMBER_W + 1] = {
    "  __   ",
    " / /_  ",
    "| '_ \\ ",
    "| (_) |",
    " \\___/ "
};

char SEVEN[TITLE_H][NUMBER_W + 1] = {
    " _____ ",
    "|___  |",
    "   / / ",
    "  / /  ",
    " /_/   "
};

char EIGHT[TITLE_H][NUMBER_W + 1] = {
    "  ___  ",
    " ( _ ) ",
    " / _ \\ ",
    "| (_) |",
    " \\___/ "
};

char NINE[TITLE_H][NUMBER_W + 1] = {
    "  ___  ",
    " / _ \\ ",
    "| (_) |",
    " \\__, |",
    "   /_/ "
};

char POINTS[TITLE_H][POINTS_W + 1] = {
    " ____                     ",
    "/ ___|  ___ ___  _ __ ___ ",
    "\\___ \\ / __/ _ \\| '__/ _ \\",
    " ___) | (_| (_) | | |  __/",
    "|____/ \\___\\___/|_|  \\___|"
};