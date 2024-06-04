// Include l'header file grafica.h contenente tutti i #define, le funzioni e le strutture char.
#include "menu.h"

// Definizione variabili globali WINDOW *winMenu, *winLevel per la gestione della stampa finale
WINDOW *winMenu, *winLevel;

// Funzione che si occupa di far vedere a schermo la scelta selezionata dall'utente
int MenuFunction(){
    // Inizializzazione id (= 0 per impostarlo inizialmente su NEW GAME), e creazione variabile choice (scelta dell'utente)
    int id = 0, choice;
    // Chiamata alla funzione SelectMenuChoice per la selezione di una delle scelte del Menu
    SelectMenuChoice(id);
    // Chiamata alla funzione wrefresh() nella finestra WinMenu per rendere le modifiche visibili
    wrefresh(winMenu);
    // Ciclo do...while per la gestione dell'input dell'utente
    do{
        // Input dell'utente
        choice = getch();
        // Switch case  basato sull'input utente per gestire i vari casi
        switch(choice){
            // Caso tasto direzionale verso l'alto 
            case KEY_UP:
                // Se l'id è maggiore di zero si decrementa
                if(id > NEWGAME){
                    --id;
                }
                // Se l'id è minore o uguale a zero si reimposta a uno (EXITLEVEL)
                else if(id <= NEWGAME){
                    id = EXITLEVEL;
                }
                break;
            // Caso tasto direzionale verso il basso
            case KEY_DOWN:
                // Se l'id è minore di uno si incrementa 
                if(id < EXITLEVEL){
                    ++id;
                }
                // Se l'id è maggiore o uguale a uno si reimposta a zero (NEWGAME)
                else if(id >= EXITLEVEL){
                    id = NEWGAME;
                }
                break;
            // Caso tasto ENTER (a capo)
            case '\n':
                // Se l'id è uguale a zero si attiva la funzione di inizio Gioco
                if(id == NEWGAME){
                    clear();
                    return LevelFunction();
                }
                // Se l'id è uguale a due si esce dal programma ritornado la scelta dell'utente
                else if(id == EXITLEVEL){
                    clear();
                    return EXITLEVEL;
                }
            break;
        }
        // Chiamata alla funzione SelectMenuChoice per la selezione di una delle scelte del Menu
        SelectMenuChoice(id);
        // Chiamata alla funzione wrefresh() nella finestra WinMenu per rendere le modifiche visibili
        wrefresh(winMenu);
    }while(choice != '\n');
}

// Funzione per la selezione di una delle scelte (NEW GAME o EXIT)
void SelectMenuChoice(int id){
    // Chiamata alla funzione CreateWindowMenu per ripristinare la finestra del Menu
    CreateWindowMenu();
    // Attivazione coppia di colori
    wattron(winMenu, COLOR_PAIR(2));
    // Switch case basato sull'id univoco per ottenere il tipo di oggetto char
    switch(id){
    // Caso di selezione dell'oggetto char NEW_GAME
    case NEWGAME:
        DrawMenu(NEWGAME_Y, (WINMENU_W - NEWGAME_W) / 2, NEWGAME, winMenu);
        break;
    // Caso di selezione dell'oggetto char EXIT_LEVEL
    case EXITLEVEL:
        DrawMenu(EXIT_Y, (WINMENU_W - EXIT_W) / 2, EXITLEVEL, winMenu);
        break;
    }
}

// Funzione per la creazione grafica del menu per scegliere se giocare o uscire
void CreateWindowMenu(){
    // Attivazione coppia di colori
    wattron(winMenu, COLOR_PAIR(1));
    // Print delle scelte del menu con richiamo alla funzione Drawmenu
    // Print NEWGAME
    DrawMenu(NEWGAME_Y, (WINMENU_W - NEWGAME_W) / 2, NEWGAME, winMenu);
    // Print EXIT
    DrawMenu(EXIT_Y, (WINMENU_W - EXIT_W) / 2, EXITLEVEL, winMenu);
    // Print FLOWERS (decorazione) 
    DrawMenu(FLOWERS_Y, (WINMENU_W - FLOWER_W) / 2, FLOWERS, winMenu);
    // Disattivazione coppia di colori
    wattroff(winMenu, COLOR_PAIR(1));
    // Disegno del contorno della finestra
    box(winMenu, ACS_VLINE, ACS_HLINE);
    // refresh() della finestra per attivare le modifiche
    refresh();
}

// Funzione identica alla MenuFunction(), l'unica differenza sono gli oggetti rappresentati
int LevelFunction(){
    // Inizializzazione id, e creazione variabile choice
    int id = 4, choice;
    // Chiamata alla funzione SelectMenuChoiceDifficulty per la selezione di una delle scelte 
    SelectLevelChoice(id);
    // Chiamata alla funzione wrefresh() nella finestra winDifficulty per rendere le modifiche visibili
    wrefresh(winLevel);
    // Ciclo do...while per la gestione dell'input dell'utente
    do{
        // Input dell'utente
        choice = getch();
        // Switch case  basato sull'input utente per gestire i vari casi
        switch(choice){
            // Caso tasto direzionale verso l'alto 
            case KEY_UP:
                // Se l'id è maggiore di tre di decrementa
                if(id > EASY_ID){
                    --id;
                }
                // Se l'id è minore di tre si imposta a sei (HARD)
                else{
                    id = HARD_ID;
                }
                break;
            // Caso tasto direzionale verso il basso
            case KEY_DOWN:
                // Se l'id è uguale a cinque si imposta l'id a tre (EASY)
                if(id == HARD_ID){
                    id = EASY_ID;
                }
                // Se l'id è minore di minore si incrementa
                else{
                    ++id;
                }
                break;
            // Caso tasto ENTER (a capo)
            case '\n':
                if(id == EASY_ID){
                    // Livello facile
                    clear();
                    return EASY_ID;
                }
                else if(id == NORMAL_ID){
                    // Livello normale
                    clear();
                    return NORMAL_ID;
                }
                else if(id == HARD_ID){
                    // Livello difficile
                    clear();
                    return HARD_ID;
                }
            break;
        }
        // Chiamata alla funzione SelectMenuChoiceDifficulty per la selezione di una delle scelte 
        SelectLevelChoice(id);
        // Chiamata alla funzione wrefresh() nella finestra winDifficulty per rendere le modifiche visibili
        wrefresh(winLevel);
    }while(choice != '\n');
}

// Funzione identica alla SelectMenuChoice(), l'unica differenza sono gli oggetti rappresentati
void SelectLevelChoice(int id){
    // Chiamata alla funzione CreateWindowDifficulty per ripristinare la finestra della selzione della difficoltà
    CreateWindowLevel();
    // Attivazione coppia di colori
    wattron(winLevel, COLOR_PAIR(2));
    // Switch case basato sull'id univoco per ottenere il tipo di oggetto char
    switch(id){
    // Caso di selezione dell'oggetto char EASY
    case EASY_ID:
        DrawMenu(NEWGAME_Y, (WINMENU_W - EASY_W) / 2, EASY_ID, winLevel);
        break;
    // Caso di selezione dell'oggetto char NORMAL
    case NORMAL_ID:
        DrawMenu(EXIT_Y, (WINMENU_W - NORMAL_W) / 2, NORMAL_ID, winLevel);
        break;
    // Caso di selezione dell'oggetto char HARD
    case HARD_ID:
        DrawMenu(FLOWERS_Y, (WINMENU_W - HARD_W) / 2, HARD_ID, winLevel);
        break;
    }
}

// Funzione identica alla CreateWindowMenu, l'unica differenza sono gli oggetti rappresentati
void CreateWindowLevel(){
    // Attivazione coppia di colori
    wattron(winLevel, COLOR_PAIR(1));
    // Print delle scelte del menu difficoltà con richiamo alla funzione Drawmenu
    DrawMenu(NEWGAME_Y, (WINMENU_W - EASY_W) / 2, EASY_ID, winLevel);
    DrawMenu(EXIT_Y, (WINMENU_W - NORMAL_W) / 2, NORMAL_ID, winLevel);
    DrawMenu(FLOWERS_Y, (WINMENU_W - HARD_W) / 2, HARD_ID, winLevel);
    // Disattivazione coppia di colori
    wattroff(winLevel, COLOR_PAIR(1));
    // Disegno del contorno della finestra
    box(winLevel, ACS_VLINE, ACS_HLINE);
    // Chiamata alla funzione refresh per rendere visibile le operazioni svolte
    refresh();
}

// Funzione per la visualizzazione a schermo degli oggetti char (riceve le coordinate di stampa, l'id univoco dell'oggetto char da stampare e la finestra dove stampare)
// Per stampare si utilizza un ciclo for che itera lungo le righe dell'oggetto char selezionato stampando una riga per volta. 
void DrawMenu(int y, int x, int id, WINDOW *win){
    // Switch case basato sull'id univoco per ottenere il tipo di oggetto char
    switch(id){
    // Caso di print dell'oggetto char NEW_GAME
    case NEWGAME:
        for(size_t i = 0; i < CHAR_H; i++){
            mvwprintw(win, y + i, x, "%s", NEW_GAME[i]);
        } 
        break;
    // Caso di print dell'oggetto char EXIT_LEVEL
    case EXITLEVEL:
        for(size_t i = 0; i < CHAR_H; i++){
            mvwprintw(win, y + i, x, "%s", EXIT_LEVEL[i]);
        } 
        break;
    // Caso di print dell'oggetto char FLOWERS
    case FLOWERS:
        for(size_t i = 0; i < FLOWER_H; i++){
            mvwprintw(win, y + i, x, "%s", FLOWER[i]);
        }
        break;
    // Caso di print dell'oggetto char EASY
    case EASY_ID:
        for(size_t i = 0; i < CHAR_H; i++){
            mvwprintw(win, y + i, x, "%s", EASY[i]);
        }
        break;
    // Caso di print dell'oggetto char NORMAL
    case NORMAL_ID:
        for(size_t i = 0; i < CHAR_H; i++){
            mvwprintw(win, y + i, x, "%s", NORMAL[i]);
        }
        break;
    // Caso di print dell'oggetto char HARD
    case HARD_ID:
        for(size_t i = 0; i < CHAR_H; i++){
            mvwprintw(win, y + i, x, "%s", HARD[i]);
        }
        break;
    }
}

// Scritta New Game
char NEW_GAME[CHAR_H][NEWGAME_W + 1] = {
    " _   _                  ____                      ",
    "| \\ | | _____      __  / ___| __ _ _ __ ___   ___ ",
    "|  \\| |/ _ \\ \\ /\\ / / | |  _ / _` | '_ ` _ \\ / _ \\",
    "| |\\  |  __/\\ V  V /  | |_| | |_| | | | | | |  __/",
    "|_| \\_|\\___| \\_/\\_/    \\____|\\__,_|_| |_| |_|\\___|"
};
// Scritta Exit 
char EXIT_LEVEL[CHAR_H][EXIT_W + 1] = {
    " _____      _ _   ",
    "| ____|_  _(_) |_ ",
    "|  _| \\ \\/ / | __|",
    "| |___ >  <| | |_ ",
    "|_____/_/\\_\\_|\\__|"
};
// Decorazione Fiori
char FLOWER[FLOWER_H][FLOWER_W + 1] = {
    "                    _                                            ",            
    "                  _(_)_                          wWWWw   _       ",                       
    "      @@@@       (_)@(_)   vVVVv     _     @@@@  (___) _(_)_     ",                 
    "     @@()@@ wWWWw  (_)\\    (___)   _(_)_  @@()@@   Y  (_)@(_)    ",               
    "      @@@@  (___)     `|/    Y    (_)@(_)  @@@@   \\|/   (_)\\     ",      
    "       /      Y       \\|    \\|/    /(_)    \\|      |/      |     ",                
    "    \\ |     \\ |/       | / \\ | /  \\|/       |/    \\|      \\|/    ",           
    "    \\\\|//   \\\\|///  \\\\\\|//\\\\\\|/// \\|///  \\\\\\|//  \\\\|//  \\\\\\|//   ",                  
    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
};
// Scritta Easy
char EASY[CHAR_H][EASY_W + 1] = {
    " _____    _    ______   __",
    "| ____|  / \\  / ___\\ \\ / /",
    "|  _|   / _ \\ \\___ \\\\ V / ",
    "| |___ / ___ \\ ___) || |  ",
    "|_____/_/   \\_\\____/ |_|  "
};
// Scritta Normale
char NORMAL[CHAR_H][NORMAL_W + 1] = {
    " _   _  ___  ____  __  __    _    _     ",
    "| \\ | |/ _ \\|  _ \\|  \\/  |  / \\  | |    ",
    "|  \\| | | | | |_) | |\\/| | / _ \\ | |    ",
    "| |\\  | |_| |  _ <| |  | |/ ___ \\| |___ ",
    "|_| \\_|\\___/|_| \\_\\_|  |_/_/   \\_\\_____|"
    };
// Scritta Hard
char HARD[CHAR_H][HARD_W + 1] = {
    " _   _    _    ____  ____  ",
    "| | | |  / \\  |  _ \\|  _ \\ ",
    "| |_| | / _ \\ | |_) | | | |",
    "|  _  |/ ___ \\|  _ <| |_| |",
    "|_| |_/_/   \\_\\_| \\_\\____/ "
};