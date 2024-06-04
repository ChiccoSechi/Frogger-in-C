#include "graphics.h"
#include "global.h"

// Funzione per la creazione coppie di colori
void Color(){
    // Coppia di colori (testo - sfondo)
    init_pair(1, COLOR_WHITE, COLOR_GREEN);         // Colori delle zone d'erba 
	init_pair(2, COLOR_WHITE, COLOR_CYAN);          // Colori del fiume
	init_pair(3, COLOR_WHITE, COLOR_YELLOW);        // Colori delle tane

    init_pair(4, COLOR_BLUE, COLOR_CYAN);           // Colore coccodrilli buoni
    init_pair(5, COLOR_RED, COLOR_CYAN);            // Colore coccodrilli cattivi
    init_pair(6, COLOR_BLACK, COLOR_YELLOW);        // Colore tane
    init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);     // Colore proiettili pianta
    init_pair(8, COLOR_MAGENTA, COLOR_GREEN);       // Colore piante
    init_pair(9, COLOR_WHITE, COLOR_WHITE);         // Colore proiettili rana

    // La rana viene visualizzata in bianco
}

// Funzione per la visualizzazione a schermo degli oggetti char "Decorazioni"
// In tutti i casi si utilizza un ciclo for per iterare lungo le righe dell'oggetto char in questione
// viene stampato riga per riga aumentando ad ogni iterazione la y della stampa
void DrawDecorations(int y, int x, int id, WINDOW *win){
    // Switch case basato sull'id univoco per ottenere il tipo di oggetto char
    switch(id){
    // Caso di print dell'oggetto char TITLE
    case TITLE_ID:
        for(size_t i = 0; i < TITLE_H; i++){
            mvwprintw(win, y + i, x, "%s", TITLE[i]);
        } 
        break;
    // Caso di print dell'oggetto char EXIT_LEVEL
    case LIVES_ID:
        for(size_t i = 0; i < TITLE_H; i++){
            mvwprintw(win, y + i, x, "%s", LIVES[i]);
        } 
        break;
    // Caso di print dell'oggetto char FLOWERS
    case HEART_ID:
        for(size_t i = 0; i < TITLE_H; i++){
            mvwprintw(win, y + i, x, "%s", HEART[i]);
        }
        break;
    // Caso di print dell'oggetto char TIMESLEFT
    case TIMESLEFT_ID:
        for (size_t i = 0; i < TITLE_H; i++){
            mvwprintw(win, y + i, x, "%s", TIMESLEFT[i]);
        }
        break;
    // Caso di print dell'oggetto char POINTS
    case POINTS_ID:
        for (size_t i = 0; i < TITLE_H; i++){
            mvwprintw(win, y + i, x, "%s", POINTS[i]);
        }
        break;
    default:
        break;
    }
}

// Print degli oggetti char NUMBERS
// In tutti i casi si utilizza un ciclo for per iterare lungo le righe dell'oggetto char in questione
// viene stampato riga per riga aumentando ad ogni iterazione la y della stampa
void DrawNumber(int number, int x, WINDOW *win){
    // Ricavo le centinaia, le decine e le unità per stampare
    int centinaia = number / 100;
    int decine = (number % 100) / 10;
    int unità = number % 10;
    // Attravero uno switch case si decide che numero stampare
    switch(centinaia){
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
    // Si effettua la stessa cosa sulle decine, aumentando la x della lunghezza dei numeri
    switch(decine){
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
    // Si effettua la stessa cosa sulle unità, aumentando la x della lunghezza dei numeri (x2)
    switch(unità){
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

// Funzione per la gestione dei movimenti delle piante (per simulare il fatto che le piante seguano lea rana a seconda di dove si muove)
void PlantsMovements(int x, WINDOW *win){
    // Itera per ogni pianta
    for(size_t i = 0; i < N_PLANTS; i++){
        // Se la pianta è attiva
        if(plant[i].active){
            pthread_mutex_lock(&mutex_plant[i]);
            // Se la rana è a sinistra della pianta
            if(x < plant[i].x){
                // Si stampa la pianta che guerda verso sinistra
                DrawObjects(PLANT_Y, plant[i].x, PLANTV1_ID, win);
            }
            // Se la rana è sotto la pianta
            else if(x == plant[i].x){
                // Si stampa la pianta che guerda verso il basso
                DrawObjects(PLANT_Y, plant[i].x, PLANTV3_ID, win);
            }
            // Se la rana è a destra della pianta 
            else{
                // Si stampa la pianta che guerda verso destra
                DrawObjects(PLANT_Y, plant[i].x, PLANTV2_ID, win);
            }
            pthread_mutex_unlock(&mutex_plant[i]);
        }
    }
}

// Funzione per la visualizzazione a schermo degli oggetti char "Oggetti"
// In tutti i casi si utilizza un ciclo for per iterare lungo le righe dell'oggetto char in questione
// viene stampato riga per riga aumentando ad ogni iterazione la y della stampa
void DrawObjects(int y, int x, int id, WINDOW *win){
    // Switch case basato sull'id univoco per ottenere il tipo di oggetto char
    switch(id){
    // Caso di print dell'oggetto char NESTOPEN
    case NESTOPEN_ID:
        for(size_t i = 0; i < OBJECT_H; i++){
            mvwprintw(win, y + i, x, "%s", NESTOPEN[i]);
        } 
        break;
    // Caso di print dell'oggetto char NESTCLOSED
    case NESTCLOSED_ID:
        for(size_t i = 0; i < OBJECT_H; i++){
            mvwprintw(win, y + i, x, "%s", NESTCLOSED[i]);
        } 
        break;
    // Caso di print dell'oggetto char FROG
    case FROG_ID:
        for(size_t i = 0; i < OBJECT_H; i++){
            mvwprintw(win, y + i, x, "%s", FROG[i]);
        }
        break;
    case PLANTV1_ID:
    // Caso di print dell'oggetto char PLANT versione 1
        for (size_t i = 0; i < OBJECT_H; i++){
            mvwprintw(win, y + i, x, "%s", PLANTV1[i]);
        }
        break;
    case PLANTV2_ID:
    // Caso di print dell'oggetto char PLANT versione 2
        for (size_t i = 0; i < OBJECT_H; i++){
            mvwprintw(win, y + i, x, "%s", PLANTV2[i]);
        }
        break;
    case PLANTV3_ID:
    // Caso di print dell'oggetto char PLANT versione 3
        for (size_t i = 0; i < OBJECT_H; i++){
            mvwprintw(win, y + i, x, "%s", PLANTV3[i]);
        }
        break;
    default:
        break;
    }
}

// Funzione per la visualizzazione a schermo degli oggetti char Coccodrillo
// La stampa è strutturata in modo tale che l'oggetto compaia o scompaia gradualmente dallo schermo
// In tutti i casi si utilizza un ciclo for per iterare lungo le righe dell'oggetto char in questione
// viene stampato riga per riga aumentando ad ogni iterazione la y della stampa
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

// Funzione per il reset della situazione
void Reset(pthread_t ThreadFrogBullet[MAX_BULLET_FROG], pthread_t ThreadPlantBullet[MAX_BULLET_PLANT * N_PLANTS], pthread_t ThreadGameTime, pthread_t ThreadCrocodile[MAX_CROCODILES * FLOWS], WINDOW *winGame, WINDOW *win){
    // Chiamata a pthread_cancel sui thread FrogBullet
    for (size_t i = 0; i < MAX_BULLET_FROG; i++) {
        if(frogbullet[i]. active){
            if (pthread_cancel(ThreadFrogBullet[i]) != 0) {
                perror("Thread cancel Error");
                exit(EXIT_FAILURE);
            }
        }
    }
    // Chiamata a pthread_cancel sui thread PlantBullet
    for (size_t i = 0; i < MAX_BULLET_PLANT * N_PLANTS; i++) {
        if(plantbullet[i].active){
            if (pthread_cancel(ThreadPlantBullet[i]) != 0) {
                perror("Thread cancel Error");
                exit(EXIT_FAILURE);
            }
        }
    }
    // Chiamata a pthread_cancel sui thread Crocodile
    for(size_t i = 0; i < MAX_CROCODILES * FLOWS; i++){
        if(crocodile[i].active){
            if(pthread_cancel(ThreadCrocodile[i]) != 0) {
                perror("Thread cancel Error");
                exit(EXIT_FAILURE);
            }
        }
    } 
    // Chiamata a pthread_cancel sul thread GameTime
    if (pthread_cancel(ThreadGameTime) != 0) {
        perror("Thread cancel Error");
        exit(EXIT_FAILURE);
    }

    delwin(winGame);
    delwin(win);
    wrefresh(winGame);
    wrefresh(win);
}

// Titolo del gioco
char TITLE[TITLE_H][TITLE_W + 1] = {
" _____ ____   ___   ____  ____ _____ ____                ____  _        _    _   _ _____ ____  ", 
"|  ___|  _ \\ / _ \\ / ___|/ ___| ____|  _ \\  __   _____  |  _ \\| |      / \\  | \\ | |_   _/ ___| ",
"| |_  | |_) | | | | |  _| |  _|  _| | |_) | \\ \\ / / __| | |_) | |     / _ \\ |  \\| | | | \\___ \\ ",
"|  _| |  _ <| |_| | |_| | |_| | |___|  _ <   \\ V /\\__ \\ |  __/| |___ / ___ \\| |\\  | | |  ___) |",
"|_|   |_| \\_\\\\___/ \\____|\\____|_____|_| \\_\\   \\_/ |___/ |_|   |_____/_/   \\_\\_| \\_| |_| |____/ ",
};
// Scritta Vite
char LIVES[TITLE_H][LIVES_W + 1] = {
    " _     _                ",
    "| |   (_)_   _____  ___ ",
    "| |   | \\ \\ / / _ \\/ __|",
    "| |___| |\\ V /  __/\\__ \\",
    "|_____|_| \\_/ \\___||___/"
};
// Decorazione cuore
char HEART[TITLE_H][HEART_W + 1] = {
    "// \\\\ // \\\\",
    "||  \\V/  ||",
    "\\\\       //",
    "  \\\\   //  ",      
    "    \\V/    ",  
};
// Scritta Tempo rimanente
char TIMESLEFT[TITLE_H][TIMESLEFT_W + 1] = {
    " _____ _                  _          __ _   ",
    "|_   _(_)_ __ ___   ___  | |    ___ / _| |_ ",
    "  | | | | '_ ` _ \\ / _ \\ | |   / _ \\ |_| __|",
    "  | | | | | | | | |  __/ | |__|  __/  _| |_ ",
    "  |_| |_|_| |_| |_|\\___| |_____\\___|_|  \\__|"
};
//Decorazione Tana Aperta
char NESTOPEN[OBJECT_H][NEST_W + 1] = {
    " //+++++\\\\ ",
    "//       \\\\",
    "||       ||"
};
// Decorazione Tana Chiusa
char NESTCLOSED[OBJECT_H][NEST_W + 1] = {
    " //+++++\\\\ ",
    "//XXXXXXX\\\\",
    "||XXXXXXX||"
};
// Oggetto Rana
char FROG[OBJECT_H][OBJECT_W + 1] = {
    " 0-0 ",
    "( ~ )",
	"^^ ^^"
};
// Oggetto Pianta Versione 1
char PLANTV1[OBJECT_H][OBJECT_W + 1] = {
    "(\\__ ",
    ":=)_)",
    "(/   "
};
// Oggetto Pianta Versione 2
char PLANTV2[OBJECT_H][OBJECT_W + 1] = {
    " __/)",
    "(_(=:",
    "   \\)"
};
// Oggetto Pianta Versione 3
char PLANTV3[OBJECT_H][OBJECT_W + 2] = {
    " |°| ",
    "/~|~\\",
    " .*. "
};
// Oggetto Coccodrillo Buono verso destra
char G_CROCODILE_DX[CROCO_H][CROCO_W + 1] = {
	"~~~~~~~~~~~~~~~(0 0       _ _ ",
	"GGGGGGGGGGGGGGG    ``----(.).)",
	"GGGGGGGGGGGGGGG^V^v^V^V^v(___)" 
};
// Oggetto Coccodrillo Cattivo verso destra
char B_CROCODILE_DX[CROCO_H][CROCO_W + 1] ={
	"~~~~~~~~~~~~~~~(X X       _ _ ",
	"BBBBBBBBBBBBBBB    ``----(.).)",
	"BBBBBBBBBBBBBBB^V^v^V^V^v(___)" 
};
// Oggetto Coccodrillo Buono verso sinistra
char G_CROCODILE_SX[CROCO_H][CROCO_W + 1] = {
	" _ _       0 0)~~~~~~~~~~~~~~~",
	"(.(.)----'`    GGGGGGGGGGGGGGG",
	"(___)v^V^V^v^V^GGGGGGGGGGGGGGG"
};
// Oggetto Coccodrillo Cattivo verso sinistra
char B_CROCODILE_SX[CROCO_H][CROCO_W + 1] ={
	" _ _       X X)~~~~~~~~~~~~~~~",
	"(.(.)----'`    BBBBBBBBBBBBBBB",
	"(___)v^V^V^v^V^BBBBBBBBBBBBBBB"
};
// Numero 0
char ZERO[TITLE_H][NUMBER_W + 1] = {
    "  ___  ",
    " / _ \\ ",
    "| | | |",
    "| |_| |",
    " \\___/ "
};
// Numero 1
char ONE[TITLE_H][NUMBER_W + 1] = {
    "     _ ",
    "    / |",
    "    | |",
    "    | |",
    "    |_|" 
};
// Numero 2
char TWO[TITLE_H][NUMBER_W + 1] = {
    " ____  ",
    "|___ \\ ",
    "  __) |",
    " / __/ ",
    "|_____|"
};
// Numero 3
char THREE[TITLE_H][NUMBER_W + 1] = {
    " _____ ",
    "|___ / ",
    "  |_ \\ ",
    " ___) |",
    "|____/ "
};
// Numero 4
char FOUR[TITLE_H][NUMBER_W + 1] = {
    " _  _  ", 
    "| || | ", 
    "| || |_", 
    "|__  _|",
    "   |_| " 
};
// Numero 5
char FIVE[TITLE_H][NUMBER_W + 1] = {
    " ____  ",
    "| ___| ",
    "|___ \\ ",
    " ___) |",
    "|____/ "
};
// Numero 6
char SIX[TITLE_H][NUMBER_W + 1] = {
    "  __   ",
    " / /_  ",
    "| '_ \\ ",
    "| (_) |",
    " \\___/ "
};
// Numero 7
char SEVEN[TITLE_H][NUMBER_W + 1] = {
    " _____ ",
    "|___  |",
    "   / / ",
    "  / /  ",
    " /_/   "
};
// Numero 8
char EIGHT[TITLE_H][NUMBER_W + 1] = {
    "  ___  ",
    " ( _ ) ",
    " / _ \\ ",
    "| (_) |",
    " \\___/ "
};
// Numero 9
char NINE[TITLE_H][NUMBER_W + 1] = {
    "  ___  ",
    " / _ \\ ",
    "| (_) |",
    " \\__, |",
    "   /_/ "
};
// Scritta Punti
char POINTS[TITLE_H][POINTS_W + 1] = {
    " ____                     ",
    "/ ___|  ___ ___  _ __ ___ ",
    "\\___ \\ / __/ _ \\| '__/ _ \\",
    " ___) | (_| (_) | | |  __/",
    "|____/ \\___\\___/|_|  \\___|"
};
