#include "global.h"

struct Frog frog;
struct River river[FLOWS];
struct GameSet gameset;
struct FrogBullet frogbullet[MAX_BULLET_FROG];
struct PlantBullet plantbullet[MAX_BULLET_PLANT * N_PLANTS];
struct Crocodile crocodile[MAX_CROCODILES * FLOWS];
struct Plant plant[N_PLANTS];
struct Time gametime;

// Dichiarazione dei mutex
pthread_mutex_t mutex_frog;
pthread_mutex_t mutex_plant[N_PLANTS];
pthread_mutex_t mutex_frogbullet[MAX_BULLET_FROG];
pthread_mutex_t mutex_plantbullet[MAX_BULLET_PLANT * N_PLANTS];
pthread_mutex_t mutex_river[FLOWS];
pthread_mutex_t mutex_crocodile[MAX_CROCODILES * FLOWS];
pthread_mutex_t mutex_gametime;
sem_t sem_Game;