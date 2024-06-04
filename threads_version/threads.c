#include "threads.h"
#include "global.h"

// variabili globali per gestire la difficoltà e il coccodrillo su cui si trova la rana
int difficulty, whatcroco;

// Funzione per la gestione della rana
void *FrogFunction(void* arg){
    // Variabile per la scelta dell'utente
    int ch;        
    // Processo Rana per la gestione della posizione
    while(1){

        // Chiamata alla funzione getch() per il recupero dell'input utente
        ch = getch();  

        // Apertura del mutex per scrivere
        pthread_mutex_lock(&mutex_frog);
        // Gestione dei pulsanti
        switch (ch){
            // Caso tasto direzionale verso l'alto (decremento posizione Y della rana)
            case KEY_UP:
                if(frog.y > LIMITFROG_UP) frog.y -= OBJECT_H;   // diminuzione posizione della rana 
                break;
            // Caso tasto direzionale verso il basso (incremento posizione Y della rana)
            case KEY_DOWN:
                if(frog.y < LIMITFROG_DOWN) frog.y += OBJECT_H; // aumento posizione della rana
                break;
            // Caso tasto direzionale verso sinistra (decremento posizione X della rana)
            case KEY_LEFT:
                if(frog.x > LIMITFROG_LEFT) frog.x -= OBJECT_W; // diminuzione posizione della rana
                break;
            // Caso tasto direzionale verso destra (incremento posizione X della rana)
            case KEY_RIGHT:
                if(frog.x < LIMITFROG_RIGHT) frog.x += OBJECT_W;// aumento posizione della rana
                break;
            // Caso tasto spazio (attivazione proiettile)
            case KEY_SPACE:
                // attivazione proiettile
                frog.bullet = true;
                break;
        } 
        // Attivo il semaforo
        sem_post(&sem_Game);
        // Chiusura del mutex
        pthread_mutex_unlock(&mutex_frog);
    }
    // Chiusura thread
    pthread_exit(NULL);
}

// Funzione per la gestione delle piante
void *PlantFunction(void* arg){
    // Salvataggio dell'argomento salvato
    size_t id = *((size_t*)arg); 
    // definizione variabile probabilità
    int probabilità;
    // switch case per la scelta della probabilità sulla base della difficoltà
    switch (difficulty)
    {
    case EASY_ID:
        probabilità = 20;
        break;
    case NORMAL_ID:
        probabilità = 30;
        break;
    case HARD_ID:
        probabilità = 40;
        break;
    }
    // Processo Pianta per la gestione del proiettile
    while (1) {
        // apertura mutex
        pthread_mutex_lock(&mutex_plant[id]);
        // Impostazione del valore bullet a true basato sulla probabilità
        if(rand() % 100 <= probabilità && !plant[id].bullet) {
            plant[id].bullet = true;
            // attivazione semaforo
            sem_post(&sem_Game);
        }
        // chiusura mutex
        pthread_mutex_unlock(&mutex_plant[id]);
        
        // Leggero ritardo 
        sleep(4); 
        // se la pianta viene disattivata imposta un timer casuale tra 1 e 10 secondi
        if(!plant[id].active){
            int time = (rand() % 10) + 1;
            sleep(time);
            pthread_mutex_lock(&mutex_plant[id]);
            plant[id].active = true;
            pthread_mutex_unlock(&mutex_plant[id]);
        }
    }
    // chiusura thread
    pthread_exit(NULL);
}
// Funzione per la gestione dei fiumi
void *RiverFunction(void* arg){
    // salvataggio argomento passato alla funzione
    size_t id = *((size_t*)arg);

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
    // funzione per il fiume
    while(1){
        // apertura mutex
        pthread_mutex_lock(&mutex_river[id]);
        // attivazione del fiume sulla base della probabilità
        if(rand() % 100 <= probabilità && !river[id].active){
            river[id].active = true;
            // attivazione semaforo
            sem_post(&sem_Game);
        }
        // chiusura mutex
        pthread_mutex_unlock(&mutex_river[id]);
        // attesa sulla base della difficoltà
        switch (difficulty)
        {
        case EASY_ID:
            sleep(river[id].time * 7);
            break;
        case NORMAL_ID:
            sleep(river[id].time * 7);
            break;
        case HARD_ID:
            usleep(river[id].time * 700000);
            break;
        }
        
    }
    // chiusura thread
    pthread_exit(NULL);
}
// funzione proiettile rana
void *FrogBulletFunction(void* arg){
    // salvataggio argomento
    size_t id = *((size_t*)arg);
    // processo attivo finchè in gioco o se il proiettile è attivo
    while(frogbullet[id].y > 1 && frogbullet[id].active){
        // apertura mutex e diminuzione della coordinata
        pthread_mutex_lock(&mutex_frogbullet[id]);
        frogbullet[id].y--;
        // chiusura mutex
        pthread_mutex_unlock(&mutex_frogbullet[id]);
        // attivazione semaforo
        sem_post(&sem_Game);
        // attesa
        usleep(500000);
    }
    // apertura e chiusura del mutex, disattivazione proiettile e chiusura thread
    pthread_mutex_lock(&mutex_frogbullet[id]);
    frogbullet[id].active = false;
    pthread_mutex_unlock(&mutex_frogbullet[id]);
    pthread_exit(NULL);
}
// funzione per la gestione del proiettile della pianta
void *PlantBulletFunction(void* arg){
    // salvataggio argomento
    size_t id = *((size_t*)arg);
    // processo attivo finchè in gioco o se il proiettile è attivo
    while(plantbullet[id].y < 39 && plantbullet[id].active){
        // apertura e chiusura del mutex, diminuzione della coordinata
        pthread_mutex_lock(&mutex_plantbullet[id]);
        plantbullet[id].y++;
        pthread_mutex_unlock(&mutex_plantbullet[id]);
        // attivazione semaforo
        sem_post(&sem_Game);
        // attesa
        sleep(1);
    }
    // apertura e chiusura del mutex, disattivazione proiettile e chiusura thread
    pthread_mutex_lock(&mutex_plantbullet[id]);
    plantbullet[id].active = false;
    pthread_mutex_unlock(&mutex_plantbullet[id]);
    pthread_exit(NULL);
}

// funzione per la gestione del coccodrillo
void *CrocodileFunction(void *arg){
    // salvataggio argomento
    size_t id = *((size_t*)arg);
    // variabile probabilità
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
    // se la direzione è true (da sx a dx)
    if(crocodile[id].direction){
        // finchè è in gioco e il coccodrillo è buono
        while(crocodile[id].x <= WIN_W + 25 && crocodile[id].type){
            // apertura e chiusura mutex con incremento della coordinata
            pthread_mutex_lock(&mutex_crocodile[id]);
            crocodile[id].x += OBJECT_W;
            pthread_mutex_unlock(&mutex_crocodile[id]);
            // se il coccodrillo è lo stesso su cui è la rana si spostano insieme
            if(id == whatcroco){
                if(frog.x < LIMITFROG_RIGHT) frog.x += OBJECT_W;
            }
            // attivazione semaforo
            sem_post(&sem_Game);
            // switch basato sulla difficoltà per l'attesa
            switch (difficulty)
            {
            case EASY_ID:
                sleep(crocodile[id].time);
                break;
            case NORMAL_ID:
                sleep(crocodile[id].time);
                break;
            case HARD_ID:
                usleep(crocodile[id].time * 100000);
                break;
            }
            // apertura e chiusura del mutex, possibilità del coccodrillo di diventare cattivo
            pthread_mutex_lock(&mutex_crocodile[id]);
            crocodile[id].type = (rand() % 100 >= probabilità) ? false : true;
            pthread_mutex_unlock(&mutex_crocodile[id]);
            // se è cattivo
            if(!crocodile[id].type){
                // si muove di 5 movimenti prima di sparire (il resto è identico a quando era buono)
                for(size_t i = 0; i < OBJECT_W; i++){
                    pthread_mutex_lock(&mutex_crocodile[id]);
                    crocodile[id].x += OBJECT_W;
                    pthread_mutex_unlock(&mutex_crocodile[id]);

                    if(id == whatcroco){
                        if(frog.x < LIMITFROG_RIGHT) frog.x += OBJECT_W;
                    }

                    sem_post(&sem_Game);

                    switch (difficulty)
                    {
                    case EASY_ID:
                        sleep(crocodile[id].time);
                        break;
                    case NORMAL_ID:
                        sleep(crocodile[id].time);
                        break;
                    case HARD_ID:
                        usleep(crocodile[id].time * 100000);
                        break;
                    }
                    // se il coccodrillo torna buono si ritorna nel while
                    if(crocodile[id].type){
                        break;
                    }
                }
            }
        }
        // apertura e chiusura del mutex, disattivazione coccodrillo e chiusura thread
        pthread_mutex_lock(&mutex_crocodile[id]);
        crocodile[id].active = false;
        pthread_mutex_unlock(&mutex_crocodile[id]);
        pthread_exit(NULL);
    }
    // stessa cosa nella direzione opposta
    else{
        while(crocodile[id].x >= -25 && crocodile[id].type){
            pthread_mutex_lock(&mutex_crocodile[id]);
            crocodile[id].x -= OBJECT_W;
            pthread_mutex_unlock(&mutex_crocodile[id]);

            if(id == whatcroco){
                if(frog.x > LIMITFROG_LEFT) frog.x -= OBJECT_W;
            }

            sem_post(&sem_Game);

            switch (difficulty)
            {
            case EASY_ID:
                sleep(crocodile[id].time);
                break;
            case NORMAL_ID:
                sleep(crocodile[id].time);
                break;
            case HARD_ID:
                usleep(crocodile[id].time * 100000);
                break;
            }

            pthread_mutex_lock(&mutex_crocodile[id]);
            crocodile[id].type = (rand() % 100 >= probabilità) ? false : true;
            pthread_mutex_unlock(&mutex_crocodile[id]);

            if(!crocodile[id].type){
                for(size_t i = 0; i < OBJECT_W; i++){
                    pthread_mutex_lock(&mutex_crocodile[id]);
                    crocodile[id].x -= OBJECT_W;
                    pthread_mutex_unlock(&mutex_crocodile[id]);

                    if(id == whatcroco){
                        if(frog.x > LIMITFROG_LEFT) frog.x -= OBJECT_W;
                    }

                    sem_post(&sem_Game);

                    switch (difficulty)
                    {
                    case EASY_ID:
                        sleep(crocodile[id].time);
                        break;
                    case NORMAL_ID:
                        sleep(crocodile[id].time);
                        break;
                    case HARD_ID:
                        usleep(crocodile[id].time * 100000);
                        break;
                    }

                    if(crocodile[id].type){
                        break;
                    }
                }
            }
        }
        pthread_mutex_lock(&mutex_crocodile[id]);
        crocodile[id].active = false;
        pthread_mutex_unlock(&mutex_crocodile[id]);
        pthread_exit(NULL);
    }
}
// funzione per la gestione del tempo
void *GameTimeFunction(void *arg) {
    // finchè il tempo è maggiore di 0
    while (gametime.starttime >= 0) {
        // apertura mutex
        pthread_mutex_lock(&mutex_gametime);
        // stampa della barra sulla base del tempo deciso dalla difficoltà
        switch (difficulty)
        {
        case EASY_ID:
            gametime.barLengthTime = (WIN_W - 1) * gametime.starttime / TIME_E; // Aggiornamento barra del tempo
            break;
        case NORMAL_ID:
            gametime.barLengthTime = (WIN_W - 1) * gametime.starttime / TIME_N; // Aggiornamento barra del tempo
            break;
        case HARD_ID:
            gametime.barLengthTime = (WIN_W - 1) * gametime.starttime / TIME_H; // Aggiornamento barra del tempo
            break;
        }
        gametime.timeLeft = gametime.starttime;
        pthread_mutex_unlock(&mutex_gametime);
        // attivazione semaforo
        sem_post(&sem_Game);
        // attesa
        sleep(1);
        // decremento per il tempo
        gametime.starttime--;
    }
    // uscita dal thread
    pthread_exit(NULL);
}

