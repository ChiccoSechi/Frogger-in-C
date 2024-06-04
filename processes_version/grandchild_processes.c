// Include l'header file grafica.h contenente tutti i #define, le strutture necessarie, le funzioni e le strutture char.
#include "grandchild_processes.h"

// Funzione per la gestione dei proiettili della rana
void FrogBulletFunction(int pipe, int y, int x) { 
    // Definizione struttura Proiettile  
    struct FrogBullet bullet;          
    // Inizializzazione coordinate 
    bullet.x = x;                   
    bullet.y = y;         
    // Processo Proiettile per la gestione della posizione (limitata allo schermo)
    while (bullet.y > 1) {
        // gestione del movimento verticale del proiettile
        bullet.y -= 1;              
        // Scrittura nella pipe delle coordinate del proiettile
        write(pipe, &bullet, sizeof(bullet));   
        // Leggero ritardo nel movimento del proiettile 
        usleep(200000);                   
    }
    // Segnale di terminazione
    bullet.y = -1; 
    // Scrittura nella pipe delle coordinate del proiettile        
    write(pipe, &bullet, sizeof(bullet));   
}
// Funzione per la gestione die proiettili delle piante
void PlantBulletFunction(int pipe, int y, int x) { 
    // Definizione struttura Proiettile  
    struct PlantBullet bullet;          
    // Inizializzazione coordinate 
    bullet.x = x;                   
    bullet.y = y;             

    // Processo Proiettile per la gestione della posizione (limitata allo schermo)
    while (bullet.y < 39) {
        // gestione del movimento verticale del proiettile
        bullet.y += 1;              
        // Scrittura nella pipe delle coordinate del proiettile
        write(pipe, &bullet, sizeof(bullet));   
        // Leggero ritardo nel movimento del proiettile (1s)
        sleep(1);                   
    }
    //Segnale di terminazione
    bullet.y = -1;
    // Scrittura nella pipe delle coordinate del proiettile        
    write(pipe, &bullet, sizeof(bullet));   
}
// Funzione per l agestione dei corsi d'acqua
void RiverFunction(int pipe, int rivertime, int difficulty){
    // Inizializzazione del seme randomicamente
    srand(time(NULL) + (getpid() ^  difficulty));
    // Inizializzazione della variabile booleana crcodile a false
    bool crocodile = false;
    // Definizione di una variabile probabilità
    int probabilità;
    // switch case basato sulla difficoltà per selezionare la probabilità
    switch (difficulty)
    {
    case EASY_ID:
        probabilità = 70;
        break;
    case NORMAL_ID:
        probabilità = 55;
        break;
    case HARD_ID:
        probabilità = 45;
        break;
    }
    // Ciclo while per la gestione del processo 
    while(true){
        // Gestione della probabilità di creazione del coccodrillo
        if(rand() % 100 <= probabilità){
            // Variabile coccodrillo attivata
            crocodile = true;
        }
        else{
            // Variabile coccodrillo disattivata
            crocodile = false;
        }
        // Scrittura su pipe della variabile
        write(pipe, &crocodile, sizeof(crocodile));
        // Variabile coccodrillo reimpostata su false
        crocodile = false;
        // Attesa di rivertime * 9, ovvero il tempo necessario che il coccodrillo precedentemente generato impiega per liberare la zona di stampa (basato sulla difficoltà)
        switch (difficulty)
        {
        case EASY_ID:
            sleep(rivertime * 9);
            break;
        case NORMAL_ID:
            sleep(rivertime * 9);
            break;
        case HARD_ID:
            for(size_t i = 0; i < 9; i++){
                usleep(rivertime * 100000);
            }
            break;
        }
    }
}
// Funzione per la gestione dei coccodrilli
void CrocodileFunction(int pipe, int y, int time_crocodile, bool direction, int ReadPipe, int difficulty){
    // Inizializzazione del seme randomicamente
    srand(time(NULL) + (getpid() ^  difficulty));
    // Inizializzazione struttura coccodrillo
    struct Crocodile crocodile;
    // inizializzazione della variabile tipologia a true
    crocodile.type = true; 
    // stessa cosa con la variabile continue
    bool CrocodileContinue = true;
    // inizializzazione variabile probabilità 
    int probabilità;
    // switch case basato sulla difficoltà per selezionare la probabilità
    switch (difficulty)
    {
    case EASY_ID:
        probabilità = 98;
        break;
    case NORMAL_ID:
        probabilità = 96;
        break;
    case HARD_ID: 
        probabilità = 94;
        break;        
    }
    // Se la direzione è true (da SX a DX)
    if(direction){ // da sx a dx
        // Inizializzazione coordinate Coccodrillo
        crocodile.x = 0;
        crocodile.y = y;
        // Inizializzazione direzione
        crocodile.direction = direction;
        // Ciclo per la gestione del movimento del coccodrillo (fino a che rimane nello schermo)
        while(crocodile.x <= WIN_W + 25 && CrocodileContinue){
            // Scrittura su Pipe della struttura coccodrillo
            write(pipe, &crocodile, sizeof(crocodile));
            // Leggero ritardo per la stampa
            switch (difficulty)
            {
            case EASY_ID:
                sleep(time_crocodile);
                break;
            case NORMAL_ID:
                sleep(time_crocodile);
                break;
            case HARD_ID:
                usleep(time_crocodile * 100000);
                break;
            }

            // Aumento della coordinata x (movimento), della larghezza della rana
            crocodile.x += OBJECT_W;
            // Possibilità del 5% che il coccodrillo diventi cattivo
            crocodile.type = (rand() % 100 >= probabilità) ? false : true;

            if(!crocodile.type){
                CrocodileContinue = false;
                for(size_t i = 0; i < OBJECT_W; i++)
                {
                    // Struttura di file descriptor per rendere la pipe non bloccante
                    fd_set readfds;
                    FD_ZERO(&readfds);
                    FD_SET(ReadPipe, &readfds);
                    int max_fd = ReadPipe;
                    struct timeval timeout;
                    timeout.tv_sec = 0;
                    timeout.tv_usec = 0;  
                    // chiamata alla funzione select
                    int ready = select(max_fd + 1, &readfds, NULL, NULL, &timeout);
                    if(ready == -1){
                        perror("Select Error");
                        exit(EXIT_FAILURE);
                    }
                    // Scrittura su Pipe della struttura coccodrillo
                    write(pipe, &crocodile, sizeof(crocodile));
                    // Se la pipe è disponibile ad essere letta
                    if(ready > 0 && FD_ISSET(ReadPipe, &readfds)){
                        read(ReadPipe, &CrocodileContinue, sizeof(CrocodileContinue));
                    }
                    // Se Crocodile continue è uguale a true il coccodrillo torna buono
                    if(CrocodileContinue){
                        crocodile.type = true;
                        break;
                    }
                    // Leggero ritardo per la stampa (basato sulla difficoltà)
                    switch (difficulty)
                    {
                    case EASY_ID:
                        sleep(time_crocodile);
                        break;
                    case NORMAL_ID:
                        sleep(time_crocodile);
                        break;
                    case HARD_ID:
                        usleep(time_crocodile * 100000);
                        break;
                    }
                    // Aumento della coordinata x (movimento), della larghezza della rana
                    crocodile.x += OBJECT_W;
                }
            }
        }

        // Uscita dal ciclo, segnale di terminazione 
        crocodile.y = -9999;
        // Scrittura su Pipe della struttura coccodrillo
        write(pipe, &crocodile, sizeof(crocodile));
    }
    // Se la direzione è false (da DX a SX)
    // Fa la stessa cosa
    else if(!direction){ // da dx a sx
        // Inizializzazione coordinate Coccodrillo
        crocodile.x = WIN_W - 5;
        crocodile.y = y;
        // Inizializzazione direzione
        crocodile.direction = direction;
        // Ciclo per la gestione del movimento del coccodrillo (fino a che rimane nello schermo)
        while(crocodile.x >= -25 && CrocodileContinue){
            // Scrittura su Pipe della struttura coccodrillo
            write(pipe, &crocodile, sizeof(crocodile));
            // Leggero ritardo per la stampa
            switch (difficulty)
            {
            case EASY_ID:
                sleep(time_crocodile);
                break;
            case NORMAL_ID:
                sleep(time_crocodile);
                break;
            case HARD_ID:
                usleep(time_crocodile * 100000);
                break;
            }
            // Diminuzione della coordinata x (movimento), della larghezza della rana
            crocodile.x -= OBJECT_W;
            // Possibilità del 15% che il coccodrillo diventi cattivo
            crocodile.type = (rand() % 100 >= probabilità) ? false : true;

            if(!crocodile.type){
                CrocodileContinue = false;
                for(size_t i = 0; i <= OBJECT_W; i++)
                {
                    fd_set readfds;
                    FD_ZERO(&readfds);
                    FD_SET(ReadPipe, &readfds);
                    int max_fd = ReadPipe;
                    struct timeval timeout;
                    timeout.tv_sec = 0;
                    timeout.tv_usec = 0;  // Timeout di 10 ms

                    int ready = select(max_fd + 1, &readfds, NULL, NULL, &timeout);
                    if(ready == -1){
                        perror("Select Error");
                        exit(EXIT_FAILURE);
                    }
                    // Scrittura su Pipe della struttura coccodrillo
                    write(pipe, &crocodile, sizeof(crocodile));

                    if(ready > 0 && FD_ISSET(ReadPipe, &readfds)){
                        read(ReadPipe, &CrocodileContinue, sizeof(CrocodileContinue));
                    }
                    if(CrocodileContinue){
                        crocodile.type = true;
                        break;
                    }

                    // Leggero ritardo per la stampa
                    switch (difficulty)
                    {
                    case EASY_ID:
                        sleep(time_crocodile);
                        break;
                    case NORMAL_ID:
                        sleep(time_crocodile);
                        break;
                    case HARD_ID:
                        usleep(time_crocodile * 100000);
                        break;
                    }
                    // Aumento della coordinata x (movimento), della larghezza della rana
                    crocodile.x -= OBJECT_W;  
                }
            }
        }
        
        // Uscita dal ciclo, segnale di terminazione 
        crocodile.y = -9999;
        // Scrittura su Pipe della struttura coccodrillo
        write(pipe, &crocodile, sizeof(crocodile));
    }
}

// Funzione per determinare il tempo di attesa di una pianta prima di ricomparire
void TimerFunction(int pipe, bool plantsactive){
    // inizializzazione rand()
    srand(time(NULL) ^ getpid());
    // tempo di attesa casuale
    int time = (rand() % 10) + 1;
    // finchè non finisce il timer la pianta rimane disattiva
    while (time > 0){
        write(pipe, &plantsactive, sizeof(plantsactive));
        time--;
        sleep(1);
    }
    // quando finisce il timer si riattiva la pianta
    plantsactive = true;
    write(pipe, &plantsactive, sizeof(plantsactive));
    
}

// Funzione per determinare il tempo rimanente e la lunghezza della barra del tempo
void GameTimeFunction(int pipe, int time){
    // definizione struttura tempo
    struct Time Time;
    // finchè il tempo non è 0
    for(size_t i = time; i >= 0; i--){
        // calcola la misura della lunghezza della barra
        Time.barLengthTime = (WIN_W - 1) * i / time;
        // tempo rimanente
        Time.timeLeft = i;
        // scrittura su pipe
        write(pipe, &Time, sizeof(Time));
        // attesa di un secondo
        sleep(1);
    }
    // segnale di terminazione
    Time.timeLeft = -1;
    Time.barLengthTime = -1;
    write(pipe, &Time, sizeof(Time));
}
