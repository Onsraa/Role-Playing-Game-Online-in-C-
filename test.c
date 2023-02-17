#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_MOBS 4
#define BOSS_POSITION 2

enum mobs {DRAGON = 0, GOBLIN = 1, TITAN = 2, GHOST = 3};
enum difficulty {EASY = 1, NORMAL = 2, HARD = 3};

void generateMob(){

    srand(time(NULL));

    int random;
    
    do{
        random = (int)(rand() % (NB_MOBS));
    }while(random == BOSS_POSITION);

    system("clear");
    printf("Random : %d", random);
    puts(" ");
    switch(random){
        
        case GOBLIN:
            printf("GOBLIN");            
            break;
        case TITAN:
            printf("TITAN");            break;
        case GHOST:
            printf("GHOST");
            break;
    };
}

int main(){

    generateMob();
}