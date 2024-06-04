
# Frogger vs Plants in C 
## University of Cagliari - Applied Computer Science and Data Analytics course - Operating Sistem Exam

### Introduction
Creation of the **Frogger vs Plants** game, based on the famous *[Frogger](https://en.wikipedia.org/wiki/Frogger)* game.
Made using the C proramming language, there are two version: processes and threads.
In both version there are as many processes or threads as the game objects, in the processes version the communication between processes is managed by pipes, in the threads version the communication between threads is managed by some global variables.

### Linux Version 
This game is only playable on Linux, the following libraries are required: 
+ stdio.h
+ stdlib.h
+ string.h
+ stdbool.h
+ unistd.h
+ time.h
+ signal.h
+ sys/wait.h
+ sys/select.h

All these libraries are present in the system by default. In addition, these three must be downloaded:
+ ncurses.h - for the processes version
+ pthread.h - for the threads version
+ semaphore.h - for the threads version

To download ncurses.h you need to run the command
``` bash
sudo apt install libncurses5-dev
```
To download pthread.h and semaphore.h you need to run the command
```bash
sudo apt install libpthread-stubs0-dev
```
By checking the code you can notice the presence of comments in italian, they will be gradually translated in english for a better understanding (thanks for your understanding).
If something is unclear "Google is you friend" or better yet "ChatGPT is your friend", otherwise open a Issue.

### Makefile
In both versions is possible to compile the executable file *./a.out* using the command *"make all"*.
If you want to play the processes version, you need to download the directory *processes_version*, open it on Linux terminal and call the make command.
If you want to play the threads version, you need to download the directory *threads_version*, open it on Linux terminal and call the make command.
After that to run the game you need to call the executable file:
```bash
./a.out
```
Is it also possible to delete intermediate files and executable file using the command *"make clean"*

### Rules of the game
**DESCRIPTION OF THE PLAYING AREA**

The playing area is divided into 4 zones:
+ The starting zone, a piece of land where the frog can move
+ A river with 8 flows \(wich are randomly initialized for direction and time\) where there are crocodiles
+ A second piece of land where there are 3 evil plants
+ A nest zone

**HOW TO PLAY**

In the **Frogger vs Plants** game the player controls a frog \(using the directional arrows and the spacebar\), the goal is to reach the 5 nests avaliable and close them all without losing all the lives.
The player can reach the nest zone by crossing a river full of crocodiles, if the frog touches the water the player loses a life, therefore the player must use the crocodiles as rafts.
Those crocodiles are almost always good \(they can be recognized by their blue color\), but sometimes they cane become evil (red color), when this happens the player has little time to change crocodile before it sinks, causing the player to lose a life.
Beyond the river there is an area \(the second piece of land\) with 3 evil plants, which at random time intervals shoot projectiles; if those projectiles hit the frog, the player lose a life.
The player can shoot up to 2 projectiles per time, to defend themeself. These projectiles can do some things:
+ if a player's projectile hit a projectile from the plants, both are destroyed
+ if a player's projectile hit a plant, the plant is detroyed and disappear for a random amount of time
+ if a player's projectile hit a evil crocodile, the evil crocodile turns good again

**GAME MODES**

There is three games modes avaliable:
+ EASY
+ NORMAL
+ HARD \(realistically IMPOSSIBLE\)

In all the three modes the player has:
+ 3 lives
+ 2 bullets (that respawn when one collides or leaves the screen)

Things that change with the game mode:
+ Speed of crocodiles
+ Probability of creating crocodiles
+ Probability for the crocodiles to became evil
+ Probability for the projectiles from the plants to spawn
+ Time of the manche

The best mode is the normal.

### Score
**BONUS**

+ +5  if the player hit a projectile from the plants
+ +10 if the player hit a plant
+ +10 if the player hit a evil crocodile and he turns back good
+ +20 if the player close a nest

**MALUS**

+ -2  if the player hit a good crocodile
+ -5  if the player goes over a plant
+ -5  if the player goes into a closed nest
+ -5  if the player goes in the "nest zone" without closing a nest
+ -5  if the player gets hit by a projectiles from the plants 
+ -5  if the player goes into the water

The score is always over the zero, it can't became negative
2