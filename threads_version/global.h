// ifndef delle librerie per evitare una ripetizione
#ifndef LIBRERIE_H
#define LIBRERIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ncurses.h>
#include <pthread.h>
#include <semaphore.h>

#endif

#ifndef CONDIVISE_H
#define CONDIVISE_H

// Variabili di gioco
#define N_NEST 5            // Numero totale di tane
#define N_PLANTS 3          // Numero totale di piante
#define MAX_BULLET_FROG 2   // Numero massimo proiettili rana 
#define MAX_BULLET_PLANT 3  // Numero massimo proiettili pianta (Modalita NORMAL)
#define FLOWS 8             // Numero totali di flussi del fiume
#define MAX_CROCODILES 6    // Numero massimo di coccodrilli per corso (EASY - NORMAL)

// Dimensioni oggetti char
#define OBJECT_H 3          // Altezza generale oggetti di gioco
#define OBJECT_W 5          // Larghezza oggetti di gioco
#define WIN_W 260           // Larghezza finestra generale 

#endif

#ifndef GLOBAL_H
#define GLOBAL_H

// Struttura Rana
struct Frog{        
    short x, y;             // Coordinate
    bool bullet;            // Gestione proiettile (bool = true indica che il proiettile è stato sparato, bool = false invece il contrario)
};

extern struct Frog frog;

// Struttura flussi del fiume
struct River{
    bool active;            // fiume attivo o meno
    int time;               // velocità del fiume
    bool direction;         // direzione del fiume
};

extern struct River river[FLOWS];

// Struttura gestione partita
struct GameSet{
    bool nestActive[N_NEST];// Array di booleani per controllare se le tane sono Aperte o Chiuse (bool = true indica la tana aperta, bool = false il contrario)
    int LivesLeft;          // Vite rimanenti
    int Point;              // Punti della Manche
};

extern struct GameSet gameset;

// Struttura Proiettile Rana
struct FrogBullet{      
    short x, y;             // Coordinate
    bool active;            // Proiettile attivo o meno
};

extern struct FrogBullet frogbullet[MAX_BULLET_FROG];

//Struttura Proiettile Pianta
struct PlantBullet{
    short x, y;             // Coordinate
    bool active;            // Proiettile attivo o meno
};

extern struct PlantBullet plantbullet[MAX_BULLET_PLANT * N_PLANTS];

// Struttura Coccodrillo
struct Crocodile{
    int x, y;               // Coordinate
    bool direction;         // Direzione del Coccodrillo nel flusso del fiume (bool = true indica da Sinistra verso Destra, bool = false il contrario)
    bool type;              // Tipologia (bool = true indica che il Coccodrillo è Buono, bool = false il contrario)
    int time;               // Tempo di attesa
    bool active;            // Coccodrillo attivo o meno
};

extern struct Crocodile crocodile[MAX_CROCODILES * FLOWS];

// Struttura Pianta
struct Plant{
    short x, y;             // Coordinate e id (necessario al riconoscimento)
    bool bullet;            // Gestione proiettile (bool = true indica che il proiettile è stato sparato, bool = false invece il contrario)
    bool active;            // pianta attiva o meno
};

extern struct Plant plant[N_PLANTS];

// Struttura per la gestione del tempo
struct Time{
    int starttime;          // Tempo iniziale
    int barLengthTime;      // Lunghezza della barra del tempo rimanente per la manche
    int timeLeft;           // Tempo rimanente in secondi
};

extern struct Time gametime;

// Dichiarazione dei mutex
extern pthread_mutex_t mutex_frog;
extern pthread_mutex_t mutex_plant[N_PLANTS];
extern pthread_mutex_t mutex_frogbullet[MAX_BULLET_FROG];
extern pthread_mutex_t mutex_plantbullet[MAX_BULLET_PLANT * N_PLANTS];
extern pthread_mutex_t mutex_river[FLOWS];
extern pthread_mutex_t mutex_crocodile[MAX_CROCODILES * FLOWS];
extern pthread_mutex_t mutex_gametime;
extern sem_t sem_Game;

#endif 