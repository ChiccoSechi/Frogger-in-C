// Inclusion of necessary header files in main.c
#include "menu.h"
#include "graphics.h"
#include "grandchild_processes.h"
#include "main.h"

// Definition of the global variable WINDOW *winEnd for handling the final print
WINDOW *winEnd;

// Main function (start of the program)
int main() {
    // Handling screen lengths with a warning print and to see the dimensions at that moment
    int x, y;
    initscr();
    do {
        getmaxyx(stdscr, y, x);
        clear();
        mvprintw((y / 2) - 1, (x / 2) - strlen("Resize the screen"), "Resize the screen");
        mvprintw(y / 2, (x / 2) - strlen("y=nn x=nn "), "y=%d x=%d", y, x);
        if (x >= 262 && x <= 280) {
            break;
        }
    } while (getch());
    clear();
    endwin();

    // Definition of a GameSet structure named gameset for handling game data
    struct GameSet gameset;
    // Call the StartGame function (responsible for starting the game)
    // Receives a pointer to the gameset structure as an argument
    StartGame(&gameset);
    // Terminate the program
    return 0;
}

// Function that initializes the game menu, receives the player's choice, and selects the correct difficulty
void StartGame(struct GameSet *gameset) {
    // Initialization of the screen and ncurses
    // Initialization of color display
    // Disable user input
    // Disable cursor
    // Activate input reception without waiting for the ENTER character
    // Enable reading of special keys
    initscr();
    start_color();
    noecho();
    curs_set(FALSE);
    cbreak();
    keypad(stdscr, TRUE);

    // Initialization of nests to true (open)
    for (size_t i = 0; i < N_NEST; i++) {
        gameset->nestActive[i] = true;
    }

    // Initialization of lives to 3 (initial lives)
    gameset->LivesLeft = STARTLIVES;
    // Initialization of points to 0
    gameset->Point = 0;

    // Initialization of central screen coordinates and definition of the choice variable
    int center_y = LINES / 2, center_x = COLS / 2, choice;

    // Definition of color pairs
    init_pair(1, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    // Definition of windows centered on the screen
    winMenu = newwin(WINMENU_H, WINMENU_W, center_y - (WINMENU_H / 2), center_x - (WINMENU_W / 2));
    winLevel = newwin(WINLEVEL_H, WINMENU_W, center_y - (WINLEVEL_H / 2), center_x - (WINMENU_W / 2));

    // Activate background for windows
    wbkgd(winMenu, COLOR_PAIR(1));
    wbkgd(winLevel, COLOR_PAIR(1));

    // Initialization of the choice variable, call to the MenuFunction() function that returns the user's choice
    choice = MenuFunction();

    // Delete windows after finishing using them
    delwin(winMenu);
    delwin(winLevel);

    // Terminate ncurses and close the screen
    endwin();

    // If the choice is to exit, end the game
    if (choice == EXITLEVEL) {
        return;
    }
    // Otherwise, start the game
    else {
        // Call the Match() function passing the gameset structure and the difficulty choice
        Match(gameset, choice);
    }
}


// Function for the initialization of processes and the continuation of the game
void Match(struct GameSet *gameset, int difficulty) {
    // Call to the srand() function for random seed initialization
    srand(time(NULL));
    // Initialization of the screen and ncurses
    // Initialization of color display
    // Disable user input
    // Disable cursor
    // Activate input reception without waiting for the ENTER character
    // Enable reading of special keys
    initscr();
    start_color();
    noecho();
    curs_set(FALSE);
    cbreak();
    keypad(stdscr, TRUE);

    // Definition of Pipes
    int PipeFrog[2], PipePlants[N_PLANTS][2], PipeFrogread[2];

    // Initialization of Pipes with custom error message in case of creation failure
    if (pipe(PipeFrog) == -1) {
        perror("Pipe Error");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < N_PLANTS; i++) {
        if (pipe(PipePlants[i]) == -1) {
            perror("Pipe Error");
            exit(EXIT_FAILURE);
        }
    }

    if (pipe(PipeFrogread) == -1) {
        perror("Pipe Error");
        exit(EXIT_FAILURE);
    }

    // Definition of Processes
    pid_t ProcessFrog, ProcessPlant[N_PLANTS];

    // fork() of the Frog process
    ProcessFrog = fork();

    // Error handling in process creation with custom error message
    if (ProcessFrog < 0) {
        perror("Fork Error");
        exit(EXIT_FAILURE);
    }
    // Successful process creation, close Pipes, call to FrogFunction
    else if (ProcessFrog == 0) {
        // Close the Reading side of PipeFrog
        close(PipeFrog[0]);
        // Close the Writing side of PipeFrogRead
        close(PipeFrogread[1]);
        // Call the FrogFunction function with the two Pipes as arguments
        FrogFunction(PipeFrog[1], PipeFrogread[0]);
        // Process termination (success)
        exit(EXIT_SUCCESS);
    }
    // We are in the Parent process
    else {
        // Create the 3 separate Plant processes
        for (size_t i = 0; i < N_PLANTS; i++) {
            // fork() of the Plant process
            ProcessPlant[i] = fork();
            // Error handling in process creation with error message
            if (ProcessPlant[i] < 0) {
                perror("Fork Error");
                exit(EXIT_FAILURE);
            }
            // Successful process creation, close the Pipe in reading, call to PlantFunction
            else if (ProcessPlant[i] == 0) {
                close(PipePlants[i][0]);
                PlantFunction(PipePlants[i][1], i, difficulty);
                exit(EXIT_SUCCESS);
            }
        }

        // Call the FatherFunction_Easy function, which receives three Pipes, the GameSet structure, and the difficulty as arguments
        FatherFunction(PipeFrog[0], PipePlants, gameset, PipeFrogread[1], difficulty);

        // Close both sides of the Pipes to terminate them
        close(PipeFrogread[0]);
        close(PipeFrogread[1]);
        close(PipeFrog[0]);
        close(PipeFrog[1]);

        // Terminate the Frog process
        kill(ProcessFrog, SIGKILL);

        // Terminate the Plant processes and associated Pipes
        for (size_t i = 0; i < N_PLANTS; i++) {
            close(PipePlants[i][0]);
            close(PipePlants[i][1]);
            kill(ProcessPlant[i], SIGKILL);
        }
    }

    // Definition of coordinates at the center of the screen
    int center_y = LINES / 2, center_x = COLS / 2;

    // If there are remaining lives
    if (gameset->LivesLeft > 0) {
        // Initialization of a boolean variable to check if all nests are closed or open
        bool allNestAreFalse = true;

        for (size_t i = 0; i < N_NEST; i++) {
            // If a nest is open
            if (gameset->nestActive[i]) {
                // Not all nests are closed
                allNestAreFalse = false;
                // Exit the loop
                break;
            }
        }

        // If all nests are closed (VICTORY)
        if (allNestAreFalse) {
            // Refresh the screen to activate changes
            refresh();
            // Initialization of a color pair
            init_pair(1, COLOR_BLACK, COLOR_MAGENTA);
            // Create the WINEND window (centered on the screen) for the final print
            winEnd = newwin(WINEND_H, WINEND_W, center_y - (WINEND_H / 2), center_x - (WINEND_W / 2));
            // Activate the background
            wbkgd(winEnd, COLOR_PAIR(1));
            // Activate borders
            box(winEnd, ACS_VLINE, ACS_HLINE);
            
            // Loop to handle the print of the "YOU WIN" message centered on the screen
            for (size_t i = 0; i < TITLE_H; i++) {
                mvwprintw(winEnd, WINEND_Y + i, (WINEND_W - YOUWIN_W) / 2, "%s", YOUWIN[i]);
            }

            // If the points are less than zero, set them to zero (negative scores are not considered)
            if (gameset->Point < 0) {
                gameset->Point = 0;
            }

            // Print the obtained score and the request to press the ENTER key to proceed
            mvwprintw(winEnd, WINEND_SCORE_Y, (WINEND_W - 10) / 2, "Score: %d", gameset->Point);
            mvwprintw(winEnd, WINEND_SCORE_Y + 2, (WINEND_W - 11) / 2, "%s", "Press Enter");

            // Refresh the WINEND window to make the changes visible
            wrefresh(winEnd);

            // getch function in the WINEND window necessary to block the window until the user presses enter
            wgetch(winEnd);

            // Delete the winEnd window to free up memory
            delwin(winEnd);

            // Close ncurses
            endwin();

            // Call the StartGame function with the gameset argument to restart the game
            StartGame(gameset);
        }
        // If there are still open nests and lives are greater than zero, continue
        else {
            // Close ncurses
            endwin();

            // Call the Easy function with the gameset argument to start a new match
            Match(gameset, difficulty);
        }
    }
    // If the remaining lives are less than or equal to zero (DEFEAT)
    else if (gameset->LivesLeft <= 0) {
        // Refresh the screen to activate changes
        refresh();
        // Initialization of a color pair
        init_pair(1, COLOR_BLACK, COLOR_MAGENTA);
        // Create the WINEND window (centered on the screen) for the final print
        winEnd = newwin(WINEND_H, WINEND_W, center_y - (WINEND_H / 2), center_x - (WINEND_W / 2));
        // Activate the background
        wbkgd(winEnd, COLOR_PAIR(1));
        // Activate borders
        box(winEnd, ACS_VLINE, ACS_HLINE);

        // Loop to handle the print of the "YOU LOSE" message centered on the screen
        for (size_t i = 0; i < TITLE_H; i++) {
            mvwprintw(winEnd, WINEND_Y + i, (WINEND_W - YOULOSE_W) / 2, "%s", YOULOSE[i]);
        }

        // If the points are less than zero, set them to zero (negative scores are not considered)
        if (gameset->Point < 0) {
            gameset->Point = 0;
        }

        // Print the obtained score and the request to press the ENTER key (any key actually) to proceed
        mvwprintw(winEnd, WINEND_SCORE_Y, (WINEND_W - 10) / 2, "Score: %d", gameset->Point);
        mvwprintw(winEnd, WINEND_SCORE_Y + 2, (WINEND_W - 11) / 2, "%s", "Press Enter");

        // Refresh the WINEND window to make the changes visible
        wrefresh(winEnd);

        // getch function in the WINEND window necessary to block the window until the user presses enter
        wgetch(winEnd);

        // Delete the window to free up memory
        delwin(winEnd);

        // Close ncurses
        endwin();

        // Call the StartGame function with the gameset argument to restart the game
        StartGame(gameset);
    }
}

// Function for managing the Frog process (movement and coordinate management through Pipe)
void FrogFunction(int Pipe, int ReadPipe) {
    // Definition of the Frog structure
    struct Frog frog;
    // Initialization of coordinates
    frog.x = STARTFROG_X;
    frog.y = STARTFROG_Y;
    // Initialization of the bullet (false)
    frog.bullet = false;
    // Initialization of the variable to indicate how much to increase the frog's position (when jumping on a crocodile)
    int movementpipe;
    // Variable for user input management
    int ch;
    // Write the initial coordinates of the Frog to the pipe
    write(Pipe, &frog, sizeof(frog));
    // Set a timeout of 10ms to make getch() non-blocking
    timeout(1);
    
    // Frog process for position management
    while (1) {
        // Definition of a file descriptor structure named readfds
        fd_set readfds;
        // Initialization of readfds to zero bytes
        FD_ZERO(&readfds);
        // Add ReadPipe to readfds
        FD_SET(ReadPipe, &readfds);
        // Initialization of max_fd (file descriptor with the most bytes) as ReadPipe (the only pipe in the structure)
        int max_fd = ReadPipe;
        // Definition of a timeval structure
        struct timeval timeout;
        // Set a timeout of zero seconds (mandatory, otherwise select() won't work)
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;
        // Definition of a variable ready (indicating whether the structure is valid or not) and call to the select() function
        int ready = select(max_fd + 1, &readfds, NULL, NULL, &timeout);
        // If the select function returns an error
        if (ready == -1) {
            perror("Select Error");
            exit(EXIT_FAILURE);
        }
        // If the pipe is full
        if (FD_ISSET(ReadPipe, &readfds)) {
            // Read from the pipe
            read(ReadPipe, &movementpipe, sizeof(movementpipe));
            // Increase or decrease the Frog's position
            frog.x += movementpipe;
            // If it reaches the limits, keep it inside the screen
            if (frog.x < LIMITFROG_LEFT) {
                frog.x += OBJECT_W;
            }
            if (frog.x > LIMITFROG_RIGHT) {
                frog.x -= OBJECT_W;
            }
        }
        // Call the getch() function to retrieve user input
        ch = getch();
        // If ch is different from no input received (i.e., a key was pressed)
        if (ch != ERR) {
            // Button management
            switch (ch) {
                // Case for the up arrow key (decrement Frog's Y position)
                case KEY_UP:
                    if (frog.y > LIMITFROG_UP) frog.y -= OBJECT_H; // decrease Frog's position
                    break;
                // Case for the down arrow key (increment Frog's Y position)
                case KEY_DOWN:
                    if (frog.y < LIMITFROG_DOWN) frog.y += OBJECT_H; // increase Frog's position
                    break;
                // Case for the left arrow key (decrement Frog's X position)
                case KEY_LEFT:
                    if (frog.x > LIMITFROG_LEFT) frog.x -= OBJECT_W; // decrease Frog's position
                    break;
                // Case for the right arrow key (increment Frog's X position)
                case KEY_RIGHT:
                    if (frog.x < LIMITFROG_RIGHT) frog.x += OBJECT_W; // increase Frog's position
                    break;
                // Case for the space key (activate bullet)
                case KEY_SPACE:
                    // activate bullet
                    frog.bullet = true;
                    break;
            }
        }
        // Write the Frog's coordinates to the pipe
        write(Pipe, &frog, sizeof(frog));
        // Initialize the bullet to false to prevent continuous firing
        frog.bullet = false;
    }
}


// Function for managing the Plant processes
void PlantFunction(int Pipe, int id, int difficulty) {
    // Definition of the Plant structure
    struct Plant plant;
    // Initialization of the bullet (false)
    plant.bullet = false;
    // Initialization of the id
    plant.id = id;
    // Initialization of a random seed for generating random numbers using the unique PID of the process
    srand(time(NULL) + (getpid() ^  difficulty));
    // Initialization of coordinates based on the plant's id
    switch (id) {
        case 0:
            plant.x = PLANT1_X;
            plant.y = PLANT_Y;
            break;
        case 1:
            plant.x = PLANT2_X;
            plant.y = PLANT_Y;
            break;
        case 2:
            plant.x = PLANT3_X;
            plant.y = PLANT_Y;
            break;
    }
    // Definition of the probability variable
    int probability;
    // Switch case based on difficulty defining the probability
    switch (difficulty) {
        case EASY_ID:
            probability = 20;
            break;
        case NORMAL_ID:
            probability = 30;
            break;
        case HARD_ID:
            probability = 40;
            break;
    }

    // Plant process for bullet management
    while (1) {
        // Set the bullet value to true with a probability of 20%
        if (rand() % 100 <= probability) {
            plant.bullet = true;
        } else {
            plant.bullet = false;
        }
        // Write the Plant structure to the pipe to communicate with the parent process
        write(Pipe, &plant, sizeof(plant));
        // Initialize the bullet to false to prevent continuous firing
        plant.bullet = false;
        // Slight delay
        sleep(3);
    }
}


// Funzione per l agestione del processo Padre (si occupa di leggere le pipe, scrivere su pipe, gestire le collisioni, creare sottoprocessi)
void FatherFunction(int PipeFrog, int (*PipePlants)[2], struct GameSet *gameset, int PipeCommunicateFrog, int difficulty){
    // Chiamata alla funzione Color() che si occupa della creazione delle coppie di colori
    Color();
    // Inizializzazione variabili WINDOW
    WINDOW *win, *winTitle, *winLives, *winTime, *winGame, *winNest, *winShore, *winRiver, *winSidewalk;
    // Definizione struttura Rana per la gestione delle coordinate della rana e dei proiettili della rana
    struct Frog frog;
    //Definizione array di N_PLANTS (3) strutture Plant per la gestione delle coordinate delle piante e dei proiettili delle piante
    struct Plant plants[N_PLANTS];
    // Definziione struttura Time per la gestione del tempo di gioco
    struct Time gametime;
    // Definizione array di MAX_BULLET_FROG strutture FrogBullet per la gestione delle coordinate dei proiettili della rana
    struct FrogBullet frogbullet[MAX_BULLET_FROG];
    // Definizione di un array di MAX_BULLET_FROG * N_PLANTS strutture PlantBullet per la gestione delle coordinate dei proiettili delle piante
    struct PlantBullet plantsbullet[MAX_BULLET_PLANT * N_PLANTS];
    // Definizione di un array di MAX_CROCODILES_E * FLOWS strutture Crocodile per la gestione delle coordinate e della comparsa/scomparsa
    struct Crocodile crocodile[MAX_CROCODILES * FLOWS];
    // Definizione di un array di booleani per l'attivazione disattivazione delle piante (utile per la visualizzazione o meno)
    bool plantsactive[N_PLANTS] = {true, true, true};
    // Definizione di un array di booleani necessari per la gestione della comparsa/scomparsa delle piante
    bool plantflag[N_PLANTS] = {false};
    // Definizione di un array di booleani per l'attivazione/disattivazione del corso d'acqua
    bool riveractive[FLOWS] = {false};
    // Definizione di un array per gestire se un coccodrillo ha cambiato posizione o meno (utile per gestire il movimento della rana sui coccodrilli)
    bool Movement[MAX_CROCODILES * FLOWS] = {false};
    // Definizione di una variabile per definire su quale coccodrillo è la rana 
    int whatcroco = -1;
    // Definizione processi proiettileRana, proiettiliPiante, Coccodrilli, Fiume
    pid_t FrogBullet[MAX_BULLET_FROG], PlantBullet[MAX_BULLET_PLANT * N_PLANTS], CrocodileProcess[MAX_CROCODILES * FLOWS];
    // Inizializzazione dei pid dei processi a -1 per semplificarne la gestione (in questo modo risultano inattivi)
    for(size_t i = 0; i < MAX_BULLET_FROG; i++){
        FrogBullet[i] = -1;
    }
    for(size_t i = 0; i < MAX_BULLET_PLANT * N_PLANTS; i++){
        PlantBullet[i] = -1;
    }
    for(size_t i = 0; i < MAX_CROCODILES * FLOWS; i++){
        CrocodileProcess[i] = -1;
    }
    // Definizione dei processi dei corsi d'acqua, del Timer per la gestione della comparsa/scomparsa delle piante e del Tempo di gioco
    pid_t River[FLOWS], TimerProcess[N_PLANTS], GameTime;
    // Definizione delle Pipe per la comunicazione con i processi
    int PipeFrogBullet[MAX_BULLET_FROG][2], PipePlantsBullet[MAX_BULLET_PLANT * N_PLANTS][2], PipeCrocodile[MAX_CROCODILES * FLOWS][2], PipeRiver[FLOWS][2], PipePlant[N_PLANTS][2], PipeGameTime[2], PipeCommunicateCrocodile[MAX_CROCODILES * FLOWS][2];
    // Inizializzazione delle pipe e gestione dell'errore con messaggio personalizzato
    for(int i = 0; i < MAX_BULLET_FROG; i++){ 
        if(pipe(PipeFrogBullet[i]) == -1){
            perror("Pipe Error");
            exit(EXIT_FAILURE);
        }
    }
    for(size_t i = 0; i < MAX_BULLET_PLANT * N_PLANTS; i++){
        if(pipe(PipePlantsBullet[i]) == -1){
            perror("Pipe Error");
            exit(EXIT_FAILURE);
        } 
    }
    for(size_t i = 0; i < MAX_CROCODILES * FLOWS; i++){
        if(pipe(PipeCrocodile[i]) == -1){
            perror("Pipe Error");
            exit(EXIT_FAILURE);
        }
    }
    for(size_t i = 0; i < FLOWS; i++){
        if(pipe(PipeRiver[i]) == -1){
            perror("Pipe Error");
            exit(EXIT_FAILURE);
        }
    }
    for(size_t i = 0; i < N_PLANTS; i++){
        if(pipe(PipePlant[i]) == -1){
            perror("Pipe Error");
            exit(EXIT_FAILURE);
        }
    }
    if(pipe(PipeGameTime) == -1){
        perror("Pipe Error");
        exit(EXIT_FAILURE);
    }
    for(size_t i = 0; i < MAX_CROCODILES * FLOWS; i++){
        if(pipe(PipeCommunicateCrocodile[i]) == -1){
            perror("Pipe Error");
            exit(EXIT_FAILURE);
        }
    }
    // Inizializzazione variabile boolena per gestire la riattivazione dei coccodrilli
    bool CrocodileContinue = true;
    // Array di interi contenente le coordinate delle tane (utile per avere un codice più pulito successivamente)
    int nest_x[N_NEST] = {NEST1_X, NEST2_X, NEST3_X, NEST4_X, NEST5_X};
    // Definizione di due array per il tempo e la direzione di ogni flusso 
    int rivertime[FLOWS];
    bool riverdirection[FLOWS];
    // Inizializzazione dei due array in modo randomico
    // switch case sulla base della difficoltà che definisce i secondi (o millisecondi) di ogni flusso
    switch (difficulty)
    {
    case EASY_ID:
        for(size_t i = 0; i < FLOWS; i++){
            // Genera un valore tra 1 e 5
            rivertime[i] = (rand() % 5 + 1);
        }
        break;
    case NORMAL_ID:
        for(size_t i = 0; i < FLOWS; i++){
            // Genera un valore tra 1 e 3
            rivertime[i] = (rand() % 3 + 1);
        }
        break;
    case HARD_ID:
        for(size_t i = 0; i < FLOWS; i++){
            // Genera un valore tra 1 e 10
            rivertime[i] = (rand() % 10 + 1);
        }
        break;    
    }
    for(size_t i = 0; i < FLOWS; i++){
        // La direzione true indica da SX verso DX, false invece viceversa
        riverdirection[i] = (rand() % 101 < 50) ? false : true;
    }
    // Creazione degli 8 processi per i flussi del fiume
    for(size_t i = 0; i < FLOWS; i++){
        // fork() dei processi Fiume
        River[i] = fork();
        // Gestione dell'errore nella creazione dei processi
        if(River[i] < 0){
            perror("Fork Error");
            exit(EXIT_FAILURE);
        }
        // Chiusura della Pipe in lettura e inizio processo
        else if(River[i] == 0){
            close(PipeRiver[i][0]);
            RiverFunction(PipeRiver[i][1], rivertime[i], difficulty);
        }
    }
    // fork() del processo per la gesione del tempo di gioco
    GameTime = fork();
    // Gestione dell'errore
    if(GameTime < 0){
        perror("Fork Error");
        exit(EXIT_FAILURE);
    }
    // Chiusura Pipe e inizio processo
    else if(GameTime == 0){
        close(PipeGameTime[0]);
        // Chiamata all funzione Gametime differente a seconda della difficoltà
        switch (difficulty)
        {
        case EASY_ID:
            GameTimeFunction(PipeGameTime[1], TIME_E);
            break;
        case NORMAL_ID:
            GameTimeFunction(PipeGameTime[1], TIME_N);
            break;
        case HARD_ID:
            GameTimeFunction(PipeGameTime[1], TIME_H);        
        default:
            break;
        }
        exit(EXIT_SUCCESS);
    }
    // Inizio del ciclo while del processo padre (true finche le vite sono maggiori di 0)
    while(1){
        // Definizione delle finestre (dimensioni e divider)
        win = newwin(WIN_H, TOTAL_W, WIN_X, WIN_X);
        box(win, ACS_VLINE, ACS_HLINE);
        winTitle = subwin(win, WINTITLE_H, WIN_W, WIN_Y, SUBWINGAME_X);
        mvwhline(win, DIVIDER_1_Y, SUBWINGAME_X, ACS_HLINE, WIN_W);
        winLives = subwin(win, WINLIVES_H, WIN_W, WINLIVES_Y, SUBWINGAME_X);
        mvwhline(win, DIVIDER_2_Y, SUBWINGAME_X, ACS_HLINE, WIN_W);
        winTime = subwin(win, WINTIME_H, WIN_W, WINTIME_Y, SUBWINGAME_X);
        mvwhline(win, DIVIDER_3_Y, SUBWINGAME_X, ACS_HLINE, WIN_W);
        winGame = newwin(WINGAME_H, TOTAL_W, WINGAME_Y, WIN_X);
        box(winGame, ACS_VLINE, ACS_HLINE);
        winNest = subwin(winGame, WINNEST_H, WIN_W, WIN_Y + WINGAME_Y, SUBWINGAME_X);
        winShore = subwin(winGame, WINSHORE_H, WIN_W, WINSHORE_Y + WINGAME_Y, SUBWINGAME_X);
        winRiver = subwin(winGame, WINRIVER_H, WIN_W, WINRIVER_Y + WINGAME_Y, SUBWINGAME_X);
        winSidewalk = subwin(winGame, WINSIDEWALK_H, WIN_W, WINSIDEWALK_Y + WINGAME_Y, SUBWINGAME_X);
    
        // La seguente serie di operazioni serve per verificare se le pipe sono piene o meno
        // Definizione di una struttura di file descriptor
        fd_set readfds;
        // Inizializzazione di readfds a 0 bytes (vuoto)
        FD_ZERO(&readfds);
        // Aggiunta della PipeFrog alla struttura fd_set readfds
        FD_SET(PipeFrog, &readfds);
        // Inizializzaizone variabile per determinare il valore massimo tra i file descriptor contenuti in readfds
        int max_fd = PipeFrog;
        // Ciclo per aggiungere PipeFrogBullets alla struttura fd_set readfds
        for(size_t i = 0; i < MAX_BULLET_FROG; i++){
            FD_SET(PipeFrogBullet[i][0], &readfds);
            // Aggiornamento del valore di max_fd se necessario
            if(PipeFrogBullet[i][0] > max_fd){
                max_fd = PipeFrogBullet[i][0];
            }
        }
        // Ciclo per aggiungere PipePlants alla struttura fd_set readfds
        for(size_t i = 0; i < N_PLANTS; i++){
            FD_SET(PipePlants[i][0], &readfds);
            // Aggiornamento del valore di max_fd se necessario
            if(PipePlants[i][0] > max_fd){
                max_fd = PipePlants[i][0];
            }
        }
        // Ciclo per aggiungere PipePlantsBullet alla struttura fd_set readfds
        for(size_t i = 0; i < MAX_BULLET_PLANT * N_PLANTS; i++){
            FD_SET(PipePlantsBullet[i][0], &readfds);
            if(PipePlantsBullet[i][0] > max_fd){
                // Aggiornamento del valore di max_fd se necessario
                max_fd = PipePlantsBullet[i][0];
            }
        }
        // Ciclo per aggiungere PipeCrocodile alla struttura fd_set readfds
        for(size_t i = 0; i < MAX_CROCODILES * FLOWS; i++){
            FD_SET(PipeCrocodile[i][0], &readfds);
            if(PipeCrocodile[i][0] > max_fd){
                // Aggiornamento del valore di max_fd se necessario
                max_fd = PipeCrocodile[i][0];
            }
        }
        // Ciclo per aggiungere PipeRiver alla struttura fd_set readfds
        for(size_t i = 0; i < FLOWS; i++){
            FD_SET(PipeRiver[i][0], &readfds);
            if(PipeRiver[i][0] > max_fd){
                // Aggiornamento del valore di max_fd se necessario
                max_fd = PipeRiver[i][0];
            }
        }
        //Ciclo per aggiungere PipePlant alla struttura fd_set readfds
        for(size_t i = 0; i < N_PLANTS; i++){
            FD_SET(PipePlant[i][0], &readfds);
            if(PipePlant[i][0] > max_fd){
                // Aggiornamento del valore di max_fd se necessario
                max_fd = PipePlant[i][0];
            }
        }
        //Ciclo per aggiungere PipeGameTime alla struttura fd_set readfds
        FD_SET(PipeGameTime[0], &readfds);
        if(PipeGameTime[0] > max_fd){
            // Aggiornamento del valore di max_fd se necessario
            max_fd = PipeGameTime[0];
        }
        // Funzione select() per verificare che almeno una Pipe tra quelle contenute in fd_set readfds è attiva e disponibile alla lettura
        if(select(max_fd + 1, &readfds, NULL, NULL, NULL) == -1){
            perror("Select Error");
            exit(EXIT_FAILURE);
        }
        // Lettura della Pipe dei proiettili della rana
        for(size_t i = 0; i < MAX_BULLET_FROG; i++){
            // Se la Pipe è disponibile alla lettura leggi
            if(FD_ISSET(PipeFrogBullet[i][0], &readfds)){
                read(PipeFrogBullet[i][0], &frogbullet[i], sizeof(frogbullet[i]));
                // Se si riceve il segnale di terminazione libera il processo
                if(frogbullet[i].y == -1){
                    FrogBullet[i] = -1;
                }
            }
        }
        // Lettura della Pipe dei proiettili delle piante
        for(size_t i = 0; i < MAX_BULLET_PLANT * N_PLANTS; i++){
            // Se la Pipe è disponibile alla lettura leggi
            if(FD_ISSET(PipePlantsBullet[i][0], &readfds)){
                read(PipePlantsBullet[i][0], &plantsbullet[i], sizeof(plantsbullet[i]));
                // Se si riceve il segnale di terminazione libera il processo
                if(plantsbullet[i].y == -1){
                    PlantBullet[i] = -1;
                }
            }
        }
        // Lettura della Pipe dei coccodrilli
        for(size_t i = 0; i < MAX_CROCODILES * FLOWS; i++){
            // Se la Pipe è disponibile alla lettura leggi
            if(FD_ISSET(PipeCrocodile[i][0], &readfds)){
                read(PipeCrocodile[i][0], &crocodile[i], sizeof(crocodile[i]));
                // Definisce quale coccodrillo si muove (e se la rana è sopra)
                if(i == whatcroco){
                    Movement[i] = true;
                }
                // Se si riceve il segnale di terminazione libera il processo
                if(crocodile[i].y == -9999){
                    CrocodileProcess[i] = -1;
                }
            }
        }
        // Lettura della Pipe di riattivazione delle piante
        for(size_t i = 0; i < N_PLANTS; i++){
            // Se la Pipe è disponibile alla lettura leggi
            if(FD_ISSET(PipePlant[i][0], &readfds)){
                read(PipePlant[i][0], &plantflag[i], sizeof(plantflag[i]));
                // Se si riceve il segnale true la pianta può ricomparire a schermo
                if(plantflag[i]){
                    plantsactive[i] = true;
                    plantflag[i] = false;
                }
            }
        }
        // lettura della Pipe PipeGameTime per la gestione del tempo di gioco
        if(FD_ISSET(PipeGameTime[0], &readfds)){
            read(PipeGameTime[0], &gametime, sizeof(gametime));
        }

        // Verifica che la PipeFrog è attiva e disponibile alla lettura
        if(FD_ISSET(PipeFrog, &readfds)){
            // Lettura dei dati dalla pipe e salvataggio nella struttura frog
            read(PipeFrog, &frog, sizeof(frog));
            // Se il valore frog.bullet è true si ricerca un proiettile disponibile e si attiva
            if(frog.bullet){
                // Ciclo per trovare un proiettile disponibile
                for(size_t i = 0; i < MAX_BULLET_FROG; i++){
                    // Nel caso in in cui il proiettile è inattivo si inizializza con le coordinate della rana al momento dello sparo
                    if(FrogBullet[i] == -1){
                        frogbullet[i].x = frog.x + 2;
                        frogbullet[i].y = frog.y;
                        // Creazione del processo proiettile
                        FrogBullet[i] = fork();
                        // Gestione della mancata creazione del processo proiettile
                        if(FrogBullet[i] < 0){
                            perror("Fork Error");
                            exit(EXIT_FAILURE);
                        }
                        else if(FrogBullet[i] == 0){
                            // Chiusura del lato di lettura della pipe
                            close(PipeFrogBullet[i][0]);
                            // Chiamata alla funzione proiettile
                            FrogBulletFunction(PipeFrogBullet[i][1], frogbullet[i].y, frogbullet[i].x);
                            exit(EXIT_SUCCESS);
                        }
                        // Chiusura del ciclo in caso di successo 
                        break;
                    }
                } 
            }
        }
        // Verifica che le Pipe delle piante siano attive e disponibili alla lettura
        for(size_t i = 0; i < N_PLANTS; i++){
            if(FD_ISSET(PipePlants[i][0], &readfds)){
                // Lettura dei dati dalla pipe e salvataggio nella struttura plants[i]
                read(PipePlants[i][0], &plants[i], sizeof(plants[i]));
                // Se il valore di plants[i].bullet è true, cerca un proiettile libero (solo se la pianta è attiva)
                if(plants[i].bullet && plantsactive[i]){
                    // Indici per gestire i cicli for() per trovare i proiettili disponibili
                    size_t j_start = plants[i].id * MAX_BULLET_PLANT;
                    size_t j_end = (plants[i].id + 1) * MAX_BULLET_PLANT;
                    // Ciclo per trovare un proiettile disponibile
                    for(size_t j = j_start; j < j_end; j++){
                        // Se il proiettile è disattivo
                        if(PlantBullet[j] == -1){
                            // Inizializzazione coordinate
                            plantsbullet[j].x = plants[i].x + 2;
                            plantsbullet[j].y = plants[i].y + 2;
                            // Creazione del processo proiettile
                            PlantBullet[j] = fork();
                            // Gestione della mancata creazione del processo proiettile
                            if(PlantBullet[j] < 0){
                                perror("Fork Error");
                                exit(EXIT_FAILURE);
                            }else if(PlantBullet[j] == 0){
                                // Chiusura del lato di lettura della pipe
                                close(PipePlantsBullet[j][0]);
                                // Chiamata alla funzione proiettile
                                PlantBulletFunction(PipePlantsBullet[j][1], plantsbullet[j].y, plantsbullet[j].x);
                                exit(EXIT_SUCCESS);
                            }
                            // Chiusura del ciclo in caso di successo
                            break;
                        }
                    }
                }
            }
        }
        // Verifica che le Pipe dei fiumi siano attive e disponibili alla lettura
        for(size_t i = 0; i < FLOWS; i++){
            if(FD_ISSET(PipeRiver[i][0], &readfds)){
                // Lettura dei dati dalla pipe e salvataggio nella struttura riveractive[i]
                read(PipeRiver[i][0], &riveractive[i], sizeof(riveractive[i]));
                // Se il valore di riveractive[i] è true, cerca un coccodrillo libero nel corrispettivo flusso
                if(riveractive[i]){
                    // Indici per gestire i cicli for() per trovare i coccodrilli disponibili
                    size_t j_start = i * MAX_CROCODILES;
                    size_t j_end = (i + 1)* MAX_CROCODILES;
                    // Ciclo per trovare un coccodrillo libero
                    for (size_t j = j_start; j < j_end; j++){
                        // Se il coccodrillo è disattivo
                        if(CrocodileProcess[j] == -1){
                            // fork() del processo Coccodrillo
                            CrocodileProcess[j] = fork();
                            // Gestione degli errori nella creazione del processo
                            if(CrocodileProcess[j] < 0){
                                perror("fork");
                                exit(EXIT_FAILURE);
                            }
                            // Chiusura delle Pipe e chiamata alla funzione CrocodileFunction_N()
                            else if(CrocodileProcess[j] == 0){
                                close(PipeCrocodile[j][0]);
                                close(PipeCommunicateCrocodile[j][1]);
                                CrocodileFunction(PipeCrocodile[j][1], (i * 3), rivertime[i], riverdirection[i], PipeCommunicateCrocodile[j][0], difficulty);
                                exit(EXIT_SUCCESS);
                            }
                            // Uscita dal ciclo in caso di successo
                            break;
                        }
                    }
                } 
            }
        }

        // COLLISIONI

        // Gestione delle collisioni tra Rana e Tane
        // Se la rana si trova sulla coordinata Y delle tane
        if(frog.y == LIMITFROG_UP){
            // Iteriamo tra le tane
            for(size_t i = 0; i < N_NEST; i++){
                // Se la rana si trova sulla stessa coordinata X delle tane
                if(frog.x == nest_x[i]){
                    // Se la tana è aperta
                    if(gameset->nestActive[i]){
                        // La chiudiamo
                        gameset->nestActive[i] = false;
                        // Aggiungiamo i punti
                        gameset->Point += 20;
                        // Resettiamo la scena
                        Reset(PipeFrogBullet, FrogBullet, PipePlantsBullet, PlantBullet, PipeCrocodile, PipeCommunicateCrocodile, CrocodileProcess, PipeRiver, riveractive, River, PipePlant, TimerProcess, PipeGameTime, GameTime, win, winGame);
                        return;
                    }
                    // Se la tana è chiusa 
                    else if(!gameset->nestActive[i]){
                        // Resettiamo la scena
                        Reset(PipeFrogBullet, FrogBullet, PipePlantsBullet, PlantBullet, PipeCrocodile, PipeCommunicateCrocodile, CrocodileProcess, PipeRiver, riveractive, River, PipePlant, TimerProcess, PipeGameTime, GameTime, win, winGame);
                        // Perdo una vita
                        gameset->LivesLeft--;
                        // Perdo Punti
                        gameset->Point -= 5;
                        return;
                    }
                }   
            }
            // Reset della situazione
            Reset(PipeFrogBullet, FrogBullet, PipePlantsBullet, PlantBullet, PipeCrocodile, PipeCommunicateCrocodile, CrocodileProcess, PipeRiver, riveractive, River, PipePlant, TimerProcess, PipeGameTime, GameTime, win, winGame);
            // Perdiamo una vita
            gameset->LivesLeft--;
            // Perdiamo dei punti
            gameset->Point -= 5;
            return;
        }

         

        // Collisione tra i proiettili rana e i proiettili piante
        // Iteriamo tra i proiettili della rana
        for(size_t i = 0; i < MAX_BULLET_FROG; i++){
            // Se il proiettile è attivo
            if(FrogBullet[i] != -1){
                // Iteriamo tra i proiettili delle piante
                for(size_t j = 0; j < MAX_BULLET_PLANT * N_PLANTS; j++){
                    // Se il proiettile è attivo
                    if(PlantBullet[j] != -1){
                        // Se le coordinate combaciano
                        if((frogbullet[i].x == plantsbullet[j].x) & (frogbullet[i].y == plantsbullet[j].y)){
                            // Terminiamo entrambi i processi
                            kill(FrogBullet[i], SIGKILL);
                            FrogBullet[i] = -1;
                            kill(PlantBullet[j], SIGKILL);
                            PlantBullet[j] = -1;
                            // Vinco dei punti
                            gameset->Point += 5;
                        }
                    }
                }
            }
        }

        // Collisione tra proiettili piante e rana
        // Iteriamo tra i proiettili delle piante
        for(size_t i = 0; i < N_PLANTS * MAX_BULLET_PLANT; i++){
            // Se il proiettile è attivo
            if(PlantBullet[i] != -1){
                // Se le coordinate di X combaciano
                if(plantsbullet[i].x == frog.x + 2){
                    // Se le coordinate di Y combaciano
                    if(plantsbullet[i].y >= frog.y && plantsbullet[i].y < frog.y + OBJECT_H - 1){
                        // Terminiamo il processo
                        kill(PlantBullet[i], SIGKILL);
                        PlantBullet[i] = -1;
                        // Resettiamo la scena
                        Reset(PipeFrogBullet, FrogBullet, PipePlantsBullet, PlantBullet, PipeCrocodile, PipeCommunicateCrocodile, CrocodileProcess, PipeRiver, riveractive, River, PipePlant, TimerProcess, PipeGameTime, GameTime, win, winGame);
                        // Perdiamo una vita
                        gameset->LivesLeft--;
                        // Perdiamo dei punti
                        gameset->Point -= 5;
                        return;
                    }
                }
            }
        }

        // Collisione tra i proiettili rana e le piante
        // Iteriamo tra i proiettili della rana
        for(size_t i = 0; i < MAX_BULLET_FROG; i++){
            // Se il proiettile è attivo
            if(FrogBullet[i] != -1){
                // Se la coordinata Y combacia
                if(frogbullet[i].y == PLANT_Y + 2){
                    // Iteriamo tra le piante
                    for(size_t j = 0; j < N_PLANTS; j++){
                        // Se la coordinata x combacia e la pianta è attiva
                        if(frogbullet[i].x == plants[j].x + 2 && plantsactive[j]){
                            // Disattiviamo la pianta
                            plantsactive[j] = false;
                            // Terminiamo il processo proiettile
                            kill(FrogBullet[i], SIGKILL);
                            FrogBullet[i] = -1;
                            // Guadagnamo dei punti
                            gameset->Point += 10;
                            // Facciamo partire il processo Timer per attendere la riattivazione della pianta
                            TimerProcess[j] = fork();
                            // Gestione dell'errore
                            if(TimerProcess[j] == -1){
                                perror("Fork Error");
                                exit(EXIT_FAILURE);
                            }
                            // Chiusura della Pipe e Inizio Processo
                            else if(TimerProcess[j] == 0){
                                close(PipePlant[j][0]);
                                TimerFunction(PipePlant[j][1], plantflag[j]);
                                exit(EXIT_SUCCESS);
                            }
                        }
                    }
                }
            }
        }
        // Collisione tra proiettili rana e coccodrilli 
        int croco_start = 0;
        // Iteriamo tra le coordinate dei flussi
        for(size_t i = 11; i <= 32; i += OBJECT_H){
            // Iteriamo tra i proiettili
            for(size_t j = 0; j < MAX_BULLET_FROG; j++){
                // Se il proiettile è attivo
                if(FrogBullet[j] != -1){
                    // Se la coordinata y corrisponde
                    if(frogbullet[j].y == i){
                        // Iteriamo tra i coccodrilli di quel flusso
                        for(size_t z = croco_start; z < croco_start + MAX_CROCODILES; z++){
                            // Se il coccodrillo è attivo
                            if(CrocodileProcess[z] != -1){
                                // Se il coccodrillo è buono
                                if(crocodile[z].type){
                                    // Se il coccodrillo va da sinistra verso destra
                                    if(crocodile[z].direction){
                                        // Se le coordinate corrispondono
                                        if(frogbullet[j].x >= crocodile[z].x - 25 && frogbullet[j].x <= crocodile[z].x + CROCO_W - 25){
                                            // Terminiamo il processo Proiettile
                                            kill(FrogBullet[j], SIGKILL);
                                            FrogBullet[j] = -1;
                                            // Perdiamo dei punti
                                            gameset->Point -= 2;
                                        }
                                    }
                                    // Stessa cosa se il coccodrillo va da destra verso sinistra
                                    else{
                                        if(frogbullet[j].x >= crocodile[z].x && frogbullet[j].x <= crocodile[z].x + CROCO_W){
                                            kill(FrogBullet[j], SIGKILL);
                                            FrogBullet[j] = -1;
                                            gameset->Point -= 2;
                                        }
                                    }
                                }
                                // Se invece il coccodrillo è cattivo
                                else{
                                    // Se va da sinistra a destra
                                    if(crocodile[z].direction){
                                        // Se combaciano le coordinate
                                        if(frogbullet[j].x >= crocodile[z].x - 25 && frogbullet[j].x <= crocodile[z].x + CROCO_W - 25){
                                            // Terminiamo il processo Proiettile
                                            kill(FrogBullet[j], SIGKILL);
                                            FrogBullet[j] = -1;
                                            // Scriviamo su Pipe per rendere il coccodrillo nuovamente buono
                                            write(PipeCommunicateCrocodile[z][1], &CrocodileContinue, sizeof(CrocodileContinue));
                                            // Vinciamo dei punti
                                            gameset->Point += 10;
                                        }
                                    }
                                    // Stessa cosa se il coccodrillo va da destra a sinistra
                                    else{
                                        if(frogbullet[j].x >= crocodile[z].x && frogbullet[j].x <= crocodile[z].x + CROCO_W){
                                            kill(FrogBullet[j], SIGKILL);
                                            FrogBullet[j] = -1;
                                            write(PipeCommunicateCrocodile[z][1], &CrocodileContinue, sizeof(CrocodileContinue));
                                            gameset->Point += 10;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // Aumento del valore dei coccodrilli per stare entro quelli del corso
            croco_start += MAX_CROCODILES;
        }

        // Collisione tra la rana e le piante
        // Se la coordinata Y corrisponde
        if(frog.y == PLANT_Y){
            // Iteriamo tra le piante
            for(size_t j = 0; j < N_PLANTS; j++){
                // Se la coordinata X corrisponde
                if(frog.x == plants[j].x){
                    // Se la pianta è attiva
                    if(plantsactive[j]){
                        // reset della situazione
                        Reset(PipeFrogBullet, FrogBullet, PipePlantsBullet, PlantBullet, PipeCrocodile, PipeCommunicateCrocodile, CrocodileProcess, PipeRiver, riveractive, River, PipePlant, TimerProcess, PipeGameTime, GameTime, win, winGame);
                        // Perdiamo una vita
                        gameset->LivesLeft--;
                        // Perdiamo dei punti
                        gameset->Point -= 5;
                        return;
                    }
                }
            }
        }

        //Collisione tra coccodrilli e rana
        // Se la rana si trova nel fiume
        if(frog.y <= 31 && frog.y >= 10){
            // Variabile per determinare se la rana è ancora viva
            bool FrogStillAlive = false;
            // Itera tra i coccodrilli
            for(size_t i = 0; i < MAX_CROCODILES * FLOWS; i++){
                // Se il coccodrillo è attivo
                if(CrocodileProcess[i] != -1){
                    // Se la rana si trova nelle stesse coordinate Y
                    if(frog.y == crocodile[i].y + 10){
                        // Se il coccodrillo va da sinistra a destra
                        if(crocodile[i].direction){
                            // Se la rana si trova nelle stesse coordinate X
                            if(frog.x >= crocodile[i].x - 25 - 5 && frog.x <= crocodile[i].x + (CROCO_W / 2) - 25){
                                // La rana è ancora viva
                                FrogStillAlive = true;
                                whatcroco = i;
                                // Terminiamo il ciclo
                                break;
                            }
                        }
                        //Stessa cosa se va da destra a sinistra
                        else{
                            if(frog.x >= crocodile[i].x + (CROCO_W / 2) && frog.x <= crocodile[i].x + CROCO_W + 5){
                                FrogStillAlive = true;
                                whatcroco = i;
                                break;
                            }
                        }
                    }
                }
            }
            // è possibile inserire da reset a retrun nei commenti e togliere mwvprintw() dai commenti per verificare il funzionamento del gioco senza giocare l'intera partita
            // Se la rana è morta
            if(!FrogStillAlive){
                // Reset della situazione
                Reset(PipeFrogBullet, FrogBullet, PipePlantsBullet, PlantBullet, PipeCrocodile, PipeCommunicateCrocodile, CrocodileProcess, PipeRiver, riveractive, River, PipePlant, TimerProcess, PipeGameTime, GameTime, win, winGame);
                // Perdiamo una vita
                gameset->LivesLeft--;
                // Perdiamo dei punti
                gameset->Point -= 5;
                return;
                //mvwprintw(winSidewalk, 0, 0, "%s", "Sei morto");
            }
            else{
                int frogCoord = 0;
                // Se il coccodrillo su cui la rana è sopra si muove
                if(Movement[whatcroco]){
                    // Se va verso destra
                    if(crocodile[whatcroco].direction){
                        // La rana si sposta insieme al coccodrilllo
                        frogCoord += OBJECT_W;
                    }
                    // Stessa cosa se va nella direzione opposta
                    else{
                        frogCoord -= OBJECT_W;   
                    }
                    // Scriviamo su pipe per rendere attivo il movimento
                    write(PipeCommunicateFrog, &frogCoord, sizeof(frogCoord));
                    // Disattivazione Movement
                    Movement[whatcroco] = false;
                }
                //mvwprintw(winSidewalk, 1, 0, "%s", "Sei vivo");
            }
        }

        // USCITA
        // Se termina il tempo
        if(gametime.timeLeft < 0 || gametime.barLengthTime < 0){
            // Reset della situazione
            Reset(PipeFrogBullet, FrogBullet, PipePlantsBullet, PlantBullet, PipeCrocodile, PipeCommunicateCrocodile, CrocodileProcess, PipeRiver, riveractive, River, PipePlant, TimerProcess, PipeGameTime, GameTime, win, winGame);
            // Perdiamo una vita
            gameset->LivesLeft--;
            return;
        }
        
        // Gestione della visualizzazione degli oggetti (colori diversi)
        // Visualizzazione degli oggetti decorativi del titolo, delle vite, e del tempo
        DrawDecorations(GENERAL_Y, (WIN_W - TITLE_W) / 2, TITLE_ID, winTitle);
        DrawDecorations(GENERAL_Y, WIN_X, LIVES_ID, winLives);
        DrawDecorations(GENERAL_Y, (WIN_W - TIMESLEFT_W) / 2, TIMESLEFT_ID, winLives);
        DrawDecorations(GENERAL_Y, POINTS_X, POINTS_ID, winLives);
        // Visualizzazione a schermo degli oggetti cuore (vite rimanenti)
        int heartX = HEART_X;
        for (size_t i = 0; i < gameset->LivesLeft; i++)
        {
            DrawDecorations(GENERAL_Y, heartX, HEART_ID, winLives);
            heartX += HEART_W;
            heartX += HEART_SEPARATOR;
        }
        // Visualizzazione a schermo deglla barra del tempo 
        wattron(winTime, COLOR_PAIR(9));
        for (int i = 0; i < gametime.barLengthTime; i++) {
            mvwprintw(winTime, 0, i, "|");
        }
        wattroff(winTime, COLOR_PAIR(9));
        // Visualizzazione a schermo del tempo rimanente
        DrawNumber(gametime.timeLeft, HUNDREDS_TIME_X, winLives);
        if(gameset->Point < 0){
            gameset->Point = 0;
        }
        // Visualizzazione a schermo dei punti
        DrawNumber(gameset->Point, HUNDREDS_POINT_X, winLives);
        

        // Visualizzazione a schermo dei coccodrilli attivi (blu buoni, rosso cattivi)
        for(size_t i = 0; i < MAX_CROCODILES * FLOWS; i++){
            // A seconda della direzione del coccodrillo, invia a DrawCrocodile() l'id differente
            if(CrocodileProcess[i] != -1){
                if(!crocodile[i].direction){
                    if(crocodile[i].type){
                        wattron(winRiver, COLOR_PAIR(4) | A_BOLD);
                        DrawCrocodile(crocodile[i].y, crocodile[i].x, GOODCROCOSX, winRiver);
                        wattroff(winRiver, COLOR_PAIR(4) | A_BOLD);
                    }
                    else{
                        wattron(winRiver, COLOR_PAIR(5) | A_BOLD);
                        DrawCrocodile(crocodile[i].y, crocodile[i].x, BADCROCOSX, winRiver);
                        wattron(winRiver, COLOR_PAIR(5) | A_BOLD);
                    }
                    
                }
                else{
                    if(crocodile[i].type){
                        wattron(winRiver, COLOR_PAIR(4) | A_BOLD);
                        DrawCrocodile(crocodile[i].y, crocodile[i].x, GOODCROCODX, winRiver);
                        wattroff(winRiver, COLOR_PAIR(4) | A_BOLD);
                    }
                    else{
                        wattron(winRiver, COLOR_PAIR(5) | A_BOLD);
                        DrawCrocodile(crocodile[i].y, crocodile[i].x, BADCROCODX, winRiver);
                        wattron(winRiver, COLOR_PAIR(5) | A_BOLD);
                    }
                }
            }
        }
        // Visualizzazione a schermo dei proiettili della rana
        for(size_t i = 0; i < MAX_BULLET_FROG; i++){
            if(FrogBullet[i] != -1){
                wattron(winGame, COLOR_PAIR(9));
                mvwprintw(winGame, frogbullet[i].y, frogbullet[i].x, "|");
                wattroff(winGame, COLOR_PAIR(9));
            }
        }
        // Visualizzazione a schermo dei proiettili delle piante
        for(size_t i = 0; i < MAX_BULLET_PLANT * N_PLANTS; i++){
            if(PlantBullet[i] != -1){
                wattron(winGame, COLOR_PAIR(7));
                mvwprintw(winGame, plantsbullet[i].y, plantsbullet[i].x, "|");
                wattroff(winGame, COLOR_PAIR(7));
            }
        }
        // Visualizzazione a schermo delle tane a seconda che siano attivi o disattivi
        wattron(winNest, COLOR_PAIR(6) | A_BOLD);
        for(size_t i = 0; i < N_NEST; i++){
            if(gameset->nestActive[i]){
                DrawObjects(GENERAL_Y, nest_x[i] - 4, NESTOPEN_ID, winNest);
            }
            else if(!gameset->nestActive[i]){
                DrawObjects(GENERAL_Y, nest_x[i] - 4, NESTCLOSED_ID, winNest);
            }
        }
        wattroff(winNest, COLOR_PAIR(6) | A_BOLD);
        // Chiamata alla funzione PlantsMovement per visualizzare a schermo le piante a seconda della posizione della Rana
        wattron(winGame, COLOR_PAIR(8) | A_BOLD);
        PlantsMovements(frog.x, plantsactive, plants, winGame);
        wattroff(winGame, COLOR_PAIR(8) | A_BOLD);
        // Visualizzazione a schermo della Rana
        DrawObjects(frog.y, frog.x, FROG_ID, winGame);

        

        // Attivazione dei background
        wbkgd(winShore, COLOR_PAIR(1));		
        wbkgd(winSidewalk, COLOR_PAIR(1));	
        wbkgd(winRiver, COLOR_PAIR(2));    
        wbkgd(winNest, COLOR_PAIR(3));
        
        // refresh() delle finestre
        wrefresh(winGame);
        wrefresh(win);
    }
}

// Scritta Hai Vinto
char YOUWIN[TITLE_H][YOUWIN_W + 1] = {
    "__   __           __        ___       ",
    "\\ \\ / /__  _   _  \\ \\      / (_)_ __  ",
    " \\ V / _ \\| | | |  \\ \\ /\\ / /| | '_ \\ ",
    "  | | (_) | |_| |   \\ V  V / | | | | |",
    "  |_|\\___/ \\__,_|    \\_/\\_/  |_|_| |_|"
};
// Scritta Hai Perso
char YOULOSE[TITLE_H][YOULOSE_W + 1] = {
    "__   __            _                   ",
    "\\ \\ / /__  _   _  | |    ___  ___  ___ ",
    " \\ V / _ \\| | | | | |   / _ \\/ __|/ _ \\",
    "  | | (_) | |_| | | |__| (_) \\__ \\  __/",
    "  |_|\\___/ \\__,_| |_____\\___/|___/\\___|"
};
