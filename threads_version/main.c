// include delle librerie necessarie
#include "main.h"
#include "menu.h"
#include "threads.h"
#include "graphics.h"
#include "global.h"



// Definizione delle finestre globali
WINDOW  *winEnd;

// Funzione main (inizio del programma)
int main(){
    //Gestione lunghezze schermo con print di avviso e per vedere le dimensioni in quel momento 
    int x, y;
    initscr();
    do{
        getmaxyx(stdscr, y, x);
        clear();
      	mvprintw((y/2)-1, (x/2)-strlen("Ridimensionare lo schermo"), "Ridimensionare lo schermo");
        mvprintw(y/2, (x/2)-strlen("y=nn x=nn "), "y=%d x=%d", y, x);	  
    if(x>=262 && x<=280){
        	break;
        }
    }while(getch());
    clear();
    endwin();

    // Chiamata alla funzione StartGame (si occupa di iniziare la partita)
    StartGame();
    // Termina il programma
    return 0;
}
// Funzione che si occupa di inizializzare il menu di gioco, riceve la scelta del giocatore e seleziona la difficoltà corretta
void StartGame(){
    // Inizializzazione schermo e ncurses
    // Inizializzazione visualizzazione colori
    // Disabilitazione degli input utente
    // Disabilitazione del cursore
    // Attivazione di ricevimento degli input senza attesa del carattere ENTER
    // Abilitazione lettura dei tasti speciali
    initscr(); start_color(); noecho(); curs_set(FALSE); cbreak(); keypad(stdscr, TRUE);

    // Inizializzazione delle tane a true (aperte)
    for(size_t i = 0; i < N_NEST; i++){
        gameset.nestActive[i] = true;
    }
    // Inizializzazione delle vite
    gameset.LivesLeft = STARTLIVES;
    // inizializzazione dei punti
    gameset.Point = 0;
    // Inizializzazione coordinate centrali dello schermo 
    int center_y = LINES / 2, center_x  = COLS / 2;
    // Definizioni coppie di colori
    init_pair(1, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    // Definizione finestre centrate rispetto allo schermo
    winMenu = newwin(WINMENU_H, WINMENU_W, center_y - (WINMENU_H / 2), center_x - (WINMENU_W / 2));
    winLevel = newwin(WINLEVEL_H, WINMENU_W, center_y - (WINLEVEL_H / 2), center_x - (WINMENU_W / 2));
    // Attivazione background per le finestre
    wbkgd(winMenu, COLOR_PAIR(1));
    wbkgd(winLevel, COLOR_PAIR(1));
    // Inizializzazione variabile difficulty, chiamata alla funzione MenuFunction() che restituisce la scelta dell'utente
    difficulty = MenuFunction();
    // Eliminazione finestre dopo averne terminato l'utilizzo
    delwin(winMenu);
    delwin(winLevel);
    // Terminazione ncurses e chiusura schermo
    endwin();

    if(difficulty == EXITLEVEL){
        return;
    }
    else{
        Match();
    }
}
// funzione Match per l'inizializzazione delle variabili dei mutex e dei thread, chiama la funzione campo
void Match (){
    // Chiamata alla funzione srand() per l'inizializzazione del seme randomico
    srand(time(NULL));
    // Inizializzazione schermo e ncurses
    // Inizializzazione visualizzazione colori
    // Disabilitazione degli input utente
    // Disabilitazione del cursore
    // Attivazione di ricevimento degli input senza attesa del carattere ENTER
    // Abilitazione lettura dei tasti speciali
    initscr(); start_color(); noecho(); curs_set(FALSE); cbreak(); keypad(stdscr, TRUE);
    // inizializzazione di whatcroco a -1 per evitare errori
    whatcroco = -1;

    // inizializzazione MUTEX con gestione dell'errore

    if(pthread_mutex_init(&mutex_frog, NULL) != 0){
        perror("Mutex Error");
        exit(EXIT_FAILURE);
    }

    for(size_t i = 0; i < N_PLANTS; i++){
        if(pthread_mutex_init(&mutex_plant[i], NULL)!= 0){
            perror("Mutex Error");
            exit(EXIT_FAILURE);
        }
    }

    for(size_t i = 0; i < MAX_BULLET_FROG; i++){
        if(pthread_mutex_init(&mutex_frogbullet[i], NULL)!= 0){
            perror("Mutex Error");
            exit(EXIT_FAILURE);
        }
    }

    for(size_t i = 0; i < MAX_BULLET_PLANT * N_PLANTS; i++){
        if(pthread_mutex_init(&mutex_plantbullet[i], NULL)!= 0){
            perror("Mutex Error");
            exit(EXIT_FAILURE);
        }
    }

    for(size_t i = 0; i < FLOWS; i++){
        if(pthread_mutex_init(&mutex_river[i], NULL) != 0){
            perror("Mutex Error");
            exit(EXIT_FAILURE);
        }
    }

    for(size_t i = 0; i < MAX_CROCODILES * FLOWS; i++){
        if(pthread_mutex_init(&mutex_crocodile[i], NULL)!= 0){
            perror("Mutex Error");
            exit(EXIT_FAILURE);
        }
    }

    if(pthread_mutex_init(&mutex_gametime, NULL) != 0){
        perror("Mutex Error");
        exit(EXIT_FAILURE);
    }

    // inizializzazione SEMAFORO con gestione dell'errore

    if(sem_init(&sem_Game, 0, 1) != 0){
        perror("Semaphore Error");
        exit(EXIT_FAILURE);
    }

    // inizializzazione VARIABILI GLOBALI

    // rana
    frog.x = STARTFROG_X;                        
    frog.y = STARTFROG_Y;
    frog.bullet = false;     

    // piante
    for(size_t i = 0; i < N_PLANTS; i++){

        plant[i].active = true;

        switch (i)
        {  
        case 0:
            plant[i].x = PLANT1_X;
            plant[i].y = PLANT_Y;
            break;
        case 1:
            plant[i].x = PLANT2_X;
            plant[i].y = PLANT_Y;
            break;
        case 2:
            plant[i].x = PLANT3_X;
            plant[i].y = PLANT_Y;
            break;
        }
    }

    // proiettili rana e piante inizializzati a false
    for(size_t i = 0; i < MAX_BULLET_FROG; i++){
        frogbullet[i].active = false;
    }

    for(size_t i = 0 ; i < MAX_BULLET_PLANT * N_PLANTS; i++){
        plantbullet[i].active = false;
    }

    // fiume inizializzato sulla base della difficoltà
    switch(difficulty)
    {
    case EASY_ID:
        for(size_t i = 0; i < FLOWS; i++){
            river[i].active = false;
            river[i].direction = (rand() % 101 < 50) ? false : true;
            river[i].time = (rand() % 5 + 1);
        }
        break;
    case NORMAL_ID:
        for(size_t i = 0; i < FLOWS; i++){
            river[i].active = false;
            river[i].direction = (rand() % 101 < 50) ? false : true;
            river[i].time = (rand() % 3 + 1);
        }
        break;
    case HARD_ID:
        for(size_t i = 0; i < FLOWS; i++){
            river[i].active = false;
            river[i].direction = (rand() % 101 < 50) ? false : true;
            river[i].time = (rand() % 10 + 1);
        }
        break;
    }

    // crocodile inizializzati a false
    for(size_t i = 0; i < MAX_CROCODILES * FLOWS; i++){
        crocodile[i].active = false;
    }
    
    // definizione THREAD e chiamata alle funzioni con gestione dell'errore

    pthread_t ThreadFrog, ThreadPlant[N_PLANTS], ThreadRiver[FLOWS];

    if(pthread_create(&ThreadFrog, NULL, &FrogFunction, NULL) != 0){
        perror("Thread Error");
        exit(EXIT_FAILURE);
    }

    for(size_t i = 0; i < N_PLANTS; i++){
        if(pthread_create(&ThreadPlant[i], NULL, &PlantFunction, &i)!= 0){
            perror("Thread Error");
            exit(EXIT_FAILURE);
        }
        // piccolo ritardo per evitare errori con gli indici
        usleep(5000);
    }

    for(size_t i = 0; i < FLOWS; i++){
        if(pthread_create(&ThreadRiver[i], NULL, &RiverFunction, &i)!= 0){
            perror("Thread Error");
            exit(EXIT_FAILURE);
        }
        // piccolo ritardo per evitare errori con gli indici
        usleep(5000);
    }
    
    // chiamata alla funzione padre (gestione grafica e generazione thread)
    FatherFunction();
    
    // Chiamata a pthread_cancel sui thread
    if (pthread_cancel(ThreadFrog) != 0) {
        perror("Errore nella cancellazione del thread Frog");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < N_PLANTS; i++) {
        if (pthread_cancel(ThreadPlant[i]) != 0) {
            perror("Errore nella cancellazione del thread Plant");
            exit(EXIT_FAILURE);
        }
    }

    for(size_t i = 0; i < FLOWS; i++){
        if (pthread_cancel(ThreadRiver[i])!= 0) {
            perror("Errore nella cancellazione del thread River");
            exit(EXIT_FAILURE);
        }
    }

    // Chiusura del mutex per la rana
    if(pthread_mutex_destroy(&mutex_frog) != 0){
        perror("Mutex Destroy Error");
        exit(EXIT_FAILURE);
    }
    
    // Chiusura dei mutex per le piante
    for (size_t i = 0; i < N_PLANTS; i++) {
        if(pthread_mutex_destroy(&mutex_plant[i]) != 0){
            perror("Mutex Destroy Error");
            exit(EXIT_FAILURE);
        }
    }
    
    // Chiusura dei mutex per i proiettili della rana
    for (size_t i = 0; i < MAX_BULLET_FROG; i++) {
        if(pthread_mutex_destroy(&mutex_frogbullet[i]) != 0){
            perror("Mutex Destroy Error");
            exit(EXIT_FAILURE);
        }
    }
    
    // Chiusura dei mutex per i proiettili delle piante
    for (size_t i = 0; i < MAX_BULLET_PLANT * N_PLANTS; i++) {
        if(pthread_mutex_destroy(&mutex_plantbullet[i]) != 0){
            perror("Mutex Destroy Error");
            exit(EXIT_FAILURE);
        }
    }
    
    // Chiusura dei mutex per il fiume
    for (size_t i = 0; i < FLOWS; i++) {
        if(pthread_mutex_destroy(&mutex_river[i]) != 0){
            perror("Mutex Destroy Error");
            exit(EXIT_FAILURE);
        }
    }
    
    // Chiusura dei mutex per i coccodrilli
    for (size_t i = 0; i < MAX_CROCODILES * FLOWS; i++) {
        if(pthread_mutex_destroy(&mutex_crocodile[i]) != 0){
            perror("Mutex Destroy Error");
            exit(EXIT_FAILURE);
        }
    }
    
    // Chiusura del mutex per il tempo di gioco
    if(pthread_mutex_destroy(&mutex_gametime) != 0){
        perror("Mutex Destroy Error");
        exit(EXIT_FAILURE);
    }
    
    // Chiusura del semaforo
    if(sem_destroy(&sem_Game) != 0){
        perror("Semaphore Destroy Error");
        exit(EXIT_FAILURE);
    }

    // pulizia finestra
    clear();
    // Definizione delle coordinate al centro dello schermo
    int center_y = LINES / 2, center_x  = COLS / 2;
    // Se le vite rimanenti sono maggiori di 0
    if(gameset.LivesLeft > 0){
        // Inizializzazione variabile booleana per controllare se le tane sono chiuse o aperte
        bool allNestAreFalse = true;
        for (size_t i = 0; i < N_NEST; i++) {
            // Se una tana è aperta
            if (gameset.nestActive[i]) {
                // è falso che tutte le tane sono chiuse
                allNestAreFalse = false;
                // Uscita dal ciclo
                break;
            }
        }
        // Se tutte le tane sono chiuse (VITTORIA)
        if(allNestAreFalse){
            // refresh() dello schermo per attivare le modifiche
            refresh();
            // Inizializzazione coppia di colori
            init_pair(1, COLOR_BLACK, COLOR_MAGENTA);
            // Creazione finestra WINEND (centrata rispetto allo schermo) per la stampa finale
            winEnd = newwin(WINEND_H, WINEND_W, center_y - (WINEND_H / 2), center_x - (WINEND_W / 2));
            // Attivazione dello sfondo
            wbkgd(winEnd, COLOR_PAIR(1));
            // Attivazione dei bordi
            box(winEnd, ACS_VLINE, ACS_HLINE);
            // Ciclo for per gestire la stampa della scritta HAI VINTO centrata rispetto allo schermo
            for(size_t i = 0; i < TITLE_H; i++){
                mvwprintw(winEnd, WINEND_Y + i, (WINEND_W - YOUWIN_W) / 2, "%s", YOUWIN[i]);
            }
            // Se i punti sono minori di zero li riportiamo a zero (non si considerano i punteggi negativi)
            if(gameset.Point < 0){
                gameset.Point = 0;
            }
            // Print dello score ottenuto e della richiesta di premere il tasto ENTER (in realta va bene un tasto qualsiasi) per andare avanti
            mvwprintw(winEnd, WINEND_SCORE_Y, (WINEND_W - 10) / 2, "Score: %d", gameset.Point);
            mvwprintw(winEnd, WINEND_SCORE_Y + 2, (WINEND_W - 11) / 2, "%s", "Press Enter");
            // refresh() della finestra WINEND per rendere visibili le modifiche
            wrefresh(winEnd);
            // Funzione getch nella finestra WINEND necessaria per bloccare la finestra finchè l'utente non preme invio
            wgetch(winEnd);
            // Eliminazione della finestra winEnd per liberare la memoria
            delwin(winEnd);
            // Chiusura ncurses
            endwin();
            // Chiamata alla funzione StartGame con argomento gameset per riniziare il gioco
            StartGame(gameset);
        }
        // Se invece ci sono ancora tane aperte e le vite sono maggiori di zero si continua
        else{
            // Chiusura ncurses
            endwin();
            // Chiamata alla funzione Easy con argomento gameset per iniziare un nuovo match
            Match();
        }
        
    }
    // Se invece le vite rimanenti sono inferiori o uguali a zero (SCONFITTA)
    else if(gameset.LivesLeft <= 0){
        // refresh() dello schermo per attivare le modifiche
        refresh();
        // Inizializzazione coppia di colori
        init_pair(1, COLOR_BLACK, COLOR_MAGENTA);
        // Creazione finestra WINEND (centrata rispetto allo schermo) per la stampa finale
        winEnd = newwin(WINEND_H, WINEND_W, center_y - (WINEND_H / 2), center_x - (WINEND_W / 2));
        // Attivazione dello sfondo
        wbkgd(winEnd, COLOR_PAIR(1));
        // Attivazione dei bordi
        box(winEnd, ACS_VLINE, ACS_HLINE);
        // Ciclo for per gestire la stampa della scritta HAI PERSO centrata rispetto allo schermo
        for(size_t i = 0; i < TITLE_H; i++){
            mvwprintw(winEnd, WINEND_Y + i, (WINEND_W - YOULOSE_W) / 2, "%s", YOULOSE[i]);
        }
        // Se i punti sono minori di zero li riportiamo a zero (non si considerano i punteggi negativi)
        if(gameset.Point < 0){
            gameset.Point = 0;
        }
        // Print dello score ottenuto e della richiesta di premere il tasto ENTER (in realta va bene un tasto qualsiasi) per andare avanti
        mvwprintw(winEnd, WINEND_SCORE_Y, (WINEND_W - 10) / 2, "Score: %d", gameset.Point);
        mvwprintw(winEnd, WINEND_SCORE_Y + 2, (WINEND_W - 11) / 2, "%s", "Press Enter");
        // refresh() della finestra WINEND per rendere visibili le modifiche
        wrefresh(winEnd);
        // Funzione getch nella finestra WINEND necessaria per bloccare la finestra finchè l'utente non preme invio
        wgetch(winEnd);
        // Eliminazione della finestra per liberare la memoria
        delwin(winEnd);
        // Chiusura ncurses
        endwin();
        // Chiamata alla funzione StartGame con argomento gameset per riniziare il gioco
        StartGame(gameset);
    }
}

void FatherFunction(){
    // Chiamata alla funzione Color() che si occupa della creazione delle coppie di colori
    Color();
    // Inizializzazione variabili WINDOW
    WINDOW *win, *winTitle, *winLives, *winTime, *winGame, *winNest, *winShore, *winRiver, *winSidewalk;

    // Array di interi contenente le coordinate delle tane (utile per avere un codice più pulito successivamente)
    int nest_x[N_NEST] = {NEST1_X, NEST2_X, NEST3_X, NEST4_X, NEST5_X};
    // definizione dei thread
    pthread_t ThreadFrogBullet[MAX_BULLET_FROG], ThreadPlantBullet[MAX_BULLET_PLANT * N_PLANTS], ThreadCrocodile[MAX_CROCODILES * FLOWS];
    pthread_t ThreadGameTime;
    
    // definizione del tempo sulla base della difficoltà
    switch (difficulty)
    {
    case EASY_ID:
        gametime.starttime = TIME_E;
        break;
    case NORMAL_ID:
        gametime.starttime = TIME_N;
        break;
    case HARD_ID:
        gametime.starttime = TIME_H;
        break;

    }

    // thread per la gestione del tempo
    if(pthread_create(&ThreadGameTime, NULL, &GameTimeFunction, NULL) != 0){
        perror("Thread Error");
        exit(EXIT_FAILURE);
    }

    // inizio funzione padre
    while(1){
        // attesa del semaforo
        sem_wait(&sem_Game);

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
    

        // CREAZIONE THREAD

        // Proiettili Rana
        // cerca di bloccare il mutex, se ci riesce disattiva la variabile bullet della rana, successivamente itera tra i proiettili disponibili,
        // se lo trova, iniziliazza il proiettile e lo attiva, crea il thread chiamando la funzione FrogBullet ed esce dal ciclo
        if(pthread_mutex_trylock(&mutex_frog) == 0){
            if(frog.bullet){
                frog.bullet = false;
                pthread_mutex_unlock(&mutex_frog);
                for(size_t i = 0; i < MAX_BULLET_FROG; i++){
                    if(pthread_mutex_trylock(&mutex_frogbullet[i]) == 0){
                        if(!frogbullet[i].active){
                            frogbullet[i].x = frog.x + 2;
                            frogbullet[i].y = frog.y;
                            frogbullet[i].active = true;
                            pthread_mutex_unlock(&mutex_frogbullet[i]);
                            if(pthread_create(&ThreadFrogBullet[i], NULL, &FrogBulletFunction, &i)!= 0){
                                perror("Thread Error");
                                exit(EXIT_FAILURE);
                            }

                            break;
                        }
                        else{
                            pthread_mutex_unlock(&mutex_frogbullet[i]);
                        }
                    }
                }
            }
            else{
                pthread_mutex_unlock(&mutex_frog);
            }
        }
        

        // Proiettili Piante
        // itera tra le piante, cerca di bloccare il mutex, se ci riesce disattiva la variabile bullet della pianta, itera tra i proiettili disponibili 
        // e se trova un proiettile disponibile lo inzializza e crea il thread con la funzione PlantBullet
        for(size_t i = 0; i < N_PLANTS; i++){
            if(pthread_mutex_trylock(&mutex_plant[i]) == 0){
                if(plant[i].bullet){
                    plant[i].bullet = false;
                    pthread_mutex_unlock(&mutex_plant[i]);
                    for(size_t j = i * MAX_BULLET_PLANT ; j < MAX_BULLET_PLANT * (i + 1); j++){
                        if(pthread_mutex_trylock(&mutex_plantbullet[j]) == 0){
                            if(!plantbullet[j].active){
                                plantbullet[j].x = plant[i].x + 2;
                                plantbullet[j].y = plant[i].y + 2;
                                plantbullet[j].active = true;
                                pthread_mutex_unlock(&mutex_plantbullet[j]);
                                if(pthread_create(&ThreadPlantBullet[j], NULL, &PlantBulletFunction, &j)!= 0){
                                    perror("Thread Error");
                                    exit(EXIT_FAILURE);
                                }
                                usleep(5000);

                                break;
                            }
                            else{
                                pthread_mutex_unlock(&mutex_plantbullet[j]);
                            }
                        }
                    }
                }
                else{
                    pthread_mutex_unlock(&mutex_plant[i]);
                }
            }
        }

        // coccodrilli
        // itera tra i flussi, cerca di bloccare il mutex, se un flusso è attivo, lo disattiva e itera tra i coccodrilli per cercarne uno disponibile
        // se lo trova lo inizializza e crea il thread chiamando la funzione CrocodileFunction
        for(size_t i = 0; i < FLOWS; i++){
            if(pthread_mutex_trylock(&mutex_river[i]) == 0){
                if(river[i].active){
                    river[i].active = false;
                    pthread_mutex_unlock(&mutex_river[i]);
                    for(size_t j = i * MAX_CROCODILES; j < MAX_CROCODILES * (i + 1); j++){
                        if(pthread_mutex_trylock(&mutex_crocodile[j]) == 0){
                            if(!crocodile[j].active){
                                if(river[i].direction){crocodile[j].x = 0;}
                                else{crocodile[j].x = WIN_W - 5;}
                                crocodile[j].y = i * 3;
                                crocodile[j].direction = river[i].direction;
                                crocodile[j].type = true;
                                crocodile[j].time = river[i].time;
                                crocodile[j].active = true;
                                pthread_mutex_unlock(&mutex_crocodile[j]);
                                if(pthread_create(&ThreadCrocodile[j], NULL, &CrocodileFunction, &j) != 0){
                                    perror("Thread Error");
                                    exit(EXIT_FAILURE);
                                }
                                usleep(5000);
                                break;
                            }
                            else{
                                pthread_mutex_unlock(&mutex_crocodile[j]);
                            }
                        }
                    }
                }
                else{
                    pthread_mutex_unlock(&mutex_river[i]);
                }
            }
        }

        // COLLISIONI
        
        // tra proiettili rana e proiettili pianta
        // Itera tra i proiettili della rana e i proiettili delle piante, se trova una corrispondenza tra le coordinate disattiva i proiettili
        for(size_t i = 0; i < MAX_BULLET_FROG; i++){
            for(size_t j = 0; j < MAX_BULLET_PLANT * N_PLANTS; j++){
                if(frogbullet[i].active && plantbullet[j].active){
                    if(frogbullet[i].x == plantbullet[j].x && frogbullet[i].y == plantbullet[j].y){
                        pthread_mutex_lock(&mutex_frogbullet[i]);
                        pthread_mutex_lock(&mutex_plantbullet[j]);
                        frogbullet[i].active = false;
                        plantbullet[j].active = false;
                        pthread_mutex_unlock(&mutex_plantbullet[j]);
                        pthread_mutex_unlock(&mutex_frogbullet[i]);

                        gameset.Point += 5;
                    }
                }
            }
        }

        // tra proiettili rana e pianta
        // itera tra i proiettili della rana e le piante, se trova una corrispondenza tra le coordinate disattiva la pianta e il proiettile (la pianta scompare)
        for(size_t i = 0; i < MAX_BULLET_FROG; i++){
            for(size_t j = 0; j < N_PLANTS; j++){
                if(frogbullet[i].active && plant[j].active){
                    if(frogbullet[i].x == plant[j].x + 2 && frogbullet[i].y == plant[j].y + 2){
                        pthread_mutex_lock(&mutex_frogbullet[i]);
                        pthread_mutex_lock(&mutex_plant[j]);
                        frogbullet[i].active = false;
                        plant[j].active = false;
                        pthread_mutex_unlock(&mutex_plant[j]);
                        pthread_mutex_unlock(&mutex_frogbullet[i]);

                        gameset.Point += 10;
                    }
                }
            }
        }
        
        // tra rana e piante
        // se la rana si trova nelle coordinate di una delle piante muore
        for(size_t i = 0; i < N_PLANTS; i++){
            if(frog.y == PLANT_Y && frog.x == plant[i].x && plant[i].active){
                gameset.Point -= 5;
                gameset.LivesLeft--;
                Reset(ThreadFrogBullet, ThreadPlantBullet, ThreadGameTime, ThreadCrocodile, winGame, win);
                return;
            }
        }

        // tra rana e tane
        // controlla che la rana sia arrivata in una delle tane, se la tana è aperta la chiude, se la tana è chiusa si perde una vita, se non entra in una tana perde una vita
        if(frog.y == LIMITFROG_UP){
            for(size_t i = 0; i < N_NEST; i++){
                if(frog.x == nest_x[i]){
                    if(gameset.nestActive[i]){
                        gameset.nestActive[i] = false;
                        gameset.Point += 20;
                        Reset(ThreadFrogBullet, ThreadPlantBullet, ThreadGameTime, ThreadCrocodile, winGame, win);
                        return;
                    }
                    else{
                        gameset.Point -= 5;
                        gameset.LivesLeft--;
                        Reset(ThreadFrogBullet, ThreadPlantBullet, ThreadGameTime, ThreadCrocodile, winGame, win);
                        return;
                    }
                }    
            }
            gameset.Point -= 5;
            gameset.LivesLeft--;
            Reset(ThreadFrogBullet, ThreadPlantBullet, ThreadGameTime, ThreadCrocodile, winGame, win);
            return;
            
        }
        
        // tra proiettili piante e rana
        // itera tra i proiettili delle piante, controlla le coordinate, se combaciano la rana muore
        for (size_t i = 0; i < MAX_BULLET_PLANT * N_PLANTS; i++) {
            if (frog.x + 2 == plantbullet[i].x && plantbullet[i].y >= frog.y && plantbullet[i].y < frog.y + OBJECT_H && plantbullet[i].active) {
                // Collisione tra rana e proiettile pianta
                gameset.LivesLeft--;
                gameset.Point -= 5;
                Reset(ThreadFrogBullet, ThreadPlantBullet, ThreadGameTime, ThreadCrocodile, winGame, win);
                return;
            }
        }

        int flow = 0;
        // tra proiettili rana e coccodrilli
        // itera tra le coordinate y dei flussi, itera tra i proiettili rana e (se attivi) itera tra i coccodrilli, se le coordinate corrispondono possono accadere due cose:
        // se il coccodrillo è buono il proiettile viene distrutto, se è cattivo il proiettile viene distrutto e il coccodrillo torna buono
        for(size_t i = 11; i <= 32 ; i += OBJECT_H){
            for(size_t j = 0; j < MAX_BULLET_FROG; j++){
                if(frogbullet[j].active && frogbullet[j].y == i){
                    for(size_t k = flow * MAX_CROCODILES; k < MAX_CROCODILES * (flow + 1); k++){
                        if(crocodile[k].active){
                            if(crocodile[k].type){
                                if(crocodile[k].direction){
                                    if(frogbullet[j].x >= crocodile[k].x -25 && frogbullet[j].x <= crocodile[k].x + CROCO_W - 25){
                                        pthread_mutex_lock(&mutex_frogbullet[j]);
                                        frogbullet[j].active = false;
                                        pthread_mutex_unlock(&mutex_frogbullet[j]);
                                        gameset.Point -= 2;
                                    }
                                }
                                else{
                                    if(frogbullet[j].x >= crocodile[k].x && frogbullet[j].x <= crocodile[k].x + CROCO_W){
                                        pthread_mutex_lock(&mutex_frogbullet[j]);
                                        frogbullet[j].active = false;
                                        pthread_mutex_unlock(&mutex_frogbullet[j]);
                                        gameset.Point -= 2;
                                    }
                                }
                            }
                            else{
                                if(crocodile[k].direction){
                                    if(frogbullet[j].x >= crocodile[k].x -25 && frogbullet[j].x <= crocodile[k].x + CROCO_W - 25){
                                        pthread_mutex_lock(&mutex_frogbullet[j]);
                                        frogbullet[j].active = false;
                                        pthread_mutex_unlock(&mutex_frogbullet[j]);
                                        pthread_mutex_lock(&mutex_crocodile[k]);
                                        crocodile[k].type = true;
                                        pthread_mutex_unlock(&mutex_crocodile[k]);
                                        gameset.Point += 10;
                                    }
                                }
                                else{
                                    if(frogbullet[j].x >= crocodile[k].x && frogbullet[j].x <= crocodile[k].x + CROCO_W){
                                        pthread_mutex_lock(&mutex_frogbullet[j]);
                                        frogbullet[j].active = false;
                                        pthread_mutex_unlock(&mutex_frogbullet[j]);
                                        pthread_mutex_lock(&mutex_crocodile[k]);
                                        crocodile[k].type = true;
                                        pthread_mutex_unlock(&mutex_crocodile[k]);
                                        gameset.Point += 10;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            flow++;
        }

        // tra rana e coccodrilli
        // verifica che la rana sia all'interno del fiume e sopra un coccodrillo, salva il coccodrillo su cui è sopra per gestire il movimento,
        // se non è sopra nessun coccodrillo l arana muore
        if(frog.y >= 10 && frog.y <= 31){
            bool FrogStillAlive = false;
            for(size_t i = 0; i < MAX_CROCODILES * FLOWS; i++){
                if(crocodile[i].active && frog.y == crocodile[i].y + 10){
                    if(crocodile[i].direction){
                        if(frog.x >= crocodile[i].x -25 && frog.x <= crocodile[i].x + (CROCO_W/2) - 25){
                            FrogStillAlive = true;
                            whatcroco = i;
                            break;
                        }
                    }    
                    else{
                        if(frog.x >= crocodile[i].x + (CROCO_W/2) && frog.x <= crocodile[i].x + CROCO_W){
                            FrogStillAlive = true;
                            whatcroco = i;
                            break;
                        }
                    }                
                }
            }
            if(!FrogStillAlive){
                whatcroco = -1;
                gameset.Point -= 5;
                gameset.LivesLeft--;
                Reset(ThreadFrogBullet, ThreadPlantBullet, ThreadGameTime, ThreadCrocodile, winGame, win);
                return;
            }
        }

        // se il tempo si azzera si perde
        if(gametime.timeLeft <= 0){
            gameset.LivesLeft--;
            Reset(ThreadFrogBullet, ThreadPlantBullet, ThreadGameTime, ThreadCrocodile, winGame, win);
            return;
        }

        
        // PRINT
        mvwprintw(winSidewalk, 4, 0, "%d", whatcroco);

        // Gestione della visualizzazione degli oggetti (colori diversi)
        // Visualizzazione degli oggetti decorativi del titolo, delle vite, e del tempo
        DrawDecorations(GENERAL_Y, (WIN_W - TITLE_W) / 2, TITLE_ID, winTitle);
        DrawDecorations(GENERAL_Y, WIN_X, LIVES_ID, winLives);
        DrawDecorations(GENERAL_Y, (WIN_W - TIMESLEFT_W) / 2, TIMESLEFT_ID, winLives);
        DrawDecorations(GENERAL_Y, POINTS_X, POINTS_ID, winLives);
        // Visualizzazione a schermo degli oggetti cuore (vite rimanenti)
        int heartX = HEART_X;
        for (size_t i = 0; i < gameset.LivesLeft; i++)
        {
            DrawDecorations(GENERAL_Y, heartX, HEART_ID, winLives);
            heartX += HEART_W;
            heartX += HEART_SEPARATOR;
        }

        // stampa barra del tempo
        pthread_mutex_lock(&mutex_gametime);
        wattron(winTime, COLOR_PAIR(9));
        for (int i = 0; i < gametime.barLengthTime; i++) {
            mvwprintw(winTime, 0, i, "|");
        }
        wattroff(winTime, COLOR_PAIR(9));

        // Stampa del tempo rimanente
        DrawNumber(gametime.timeLeft, HUNDREDS_TIME_X, winLives);

        if(gameset.Point < 0){
            gameset.Point = 0;
        }
        // stampa dei punti
        DrawNumber(gameset.Point, HUNDREDS_POINT_X,winLives);
        pthread_mutex_unlock(&mutex_gametime);

        // stampa dei coccodrilli (buoni o cattivi)
        for(size_t i = 0; i < MAX_CROCODILES * FLOWS; i++){
            pthread_mutex_lock(&mutex_crocodile[i]);
            if(crocodile[i].active){
                if(crocodile[i].direction){
                    if(crocodile[i].type){
                        wattron(winRiver, COLOR_PAIR(4) | A_BOLD);
                        DrawCrocodile(crocodile[i].y, crocodile[i].x, GOODCROCODX, winRiver);
                        wattroff(winRiver, COLOR_PAIR(4) | A_BOLD);
                    }
                    else{
                        wattron(winRiver, COLOR_PAIR(5) | A_BOLD);
                        DrawCrocodile(crocodile[i].y, crocodile[i].x, BADCROCODX, winRiver);
                        wattroff(winRiver, COLOR_PAIR(5) | A_BOLD);
                    }
                }
                else{
                    if(crocodile[i].type){
                        wattron(winRiver, COLOR_PAIR(4) | A_BOLD);
                        DrawCrocodile(crocodile[i].y, crocodile[i].x, GOODCROCOSX, winRiver);
                        wattroff(winRiver, COLOR_PAIR(4) | A_BOLD);
                    }
                    else{
                        wattron(winRiver, COLOR_PAIR(5) | A_BOLD);
                        DrawCrocodile(crocodile[i].y, crocodile[i].x, BADCROCOSX, winRiver);
                        wattroff(winRiver, COLOR_PAIR(5) | A_BOLD);
                    }
                }
            }
            pthread_mutex_unlock(&mutex_crocodile[i]);
        }

        // stampa dei proiettili della rana
        for(size_t i = 0; i < MAX_BULLET_FROG; i++){
            pthread_mutex_lock(&mutex_frogbullet[i]);
            if(frogbullet[i].active == true){
                wattron(winGame, COLOR_PAIR(9));
                mvwprintw(winGame, frogbullet[i].y, frogbullet[i].x, "|");
                wattroff(winGame, COLOR_PAIR(9));
            }
            pthread_mutex_unlock(&mutex_frogbullet[i]);
        }

        // stampa dei proiettili delle piante
        for(size_t i = 0; i < MAX_BULLET_PLANT * N_PLANTS; i++){
            pthread_mutex_lock(&mutex_plantbullet[i]);
            if(plantbullet[i].active == true){
                wattron(winGame, COLOR_PAIR(7));
                mvwprintw(winGame, plantbullet[i].y, plantbullet[i].x, "|");
                wattroff(winGame, COLOR_PAIR(7));
            }
            pthread_mutex_unlock(&mutex_plantbullet[i]);
        }

        // Visualizzazione a schermo delle tane a seconda che siano attivi o disattivi
        wattron(winNest, COLOR_PAIR(6) | A_BOLD);
        for(size_t i = 0; i < N_NEST; i++){
            if(gameset.nestActive[i]){
                DrawObjects(GENERAL_Y, nest_x[i] - 4, NESTOPEN_ID, winNest);
            }
            else if(!gameset.nestActive[i]){
                DrawObjects(GENERAL_Y, nest_x[i] - 4, NESTCLOSED_ID, winNest);
            }
        }
        wattroff(winNest, COLOR_PAIR(6) | A_BOLD);

        // chiamata alla funzione per la stampa delle piante
        pthread_mutex_lock(&mutex_frog);
        wattron(winGame, COLOR_PAIR(8) | A_BOLD);
        PlantsMovements(frog.x, winGame);
        wattroff(winGame, COLOR_PAIR(8) | A_BOLD);
        pthread_mutex_unlock(&mutex_frog);

        // stampa della rana
        pthread_mutex_lock(&mutex_frog);
        DrawObjects(frog.y, frog.x, FROG_ID, winGame);
        pthread_mutex_unlock(&mutex_frog);

        // Attivazione dei background
        wbkgd(winShore, COLOR_PAIR(1));		
        wbkgd(winSidewalk, COLOR_PAIR(1));	
        wbkgd(winRiver, COLOR_PAIR(2));    
        wbkgd(winNest, COLOR_PAIR(3));
    
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





