#include "../struct.h"
#define BAR_LENGTH 40
#define NB_MOBS 4
#define BOSS_POSITION 0

enum mobs {DRAGON = 0, GOBLIN = 1, TITAN = 2, GHOST = 3};
enum difficulty {EASY = 1, NORMAL = 2, HARD = 3};

Mob * generateMob(int difficulty){

    Mob * generatedMob = NULL;

    srand(time(NULL));

    int random;
    
    do{
        random = (int)(rand() % NB_MOBS);
    }while(random == BOSS_POSITION);


    switch(random){

        case DRAGON:
            generatedMob = dragon(difficulty);
            break;
        case GOBLIN:
            generatedMob = goblin(difficulty);
            break;
        case TITAN:
            generatedMob = titan(difficulty);
            break;
        case GHOST:
            generatedMob = ghost(difficulty);
            break;
    };

    return generatedMob;
}

Mob * dragon(int difficulty){ // Boss mob

    Mob * mob = malloc(sizeof(Mob));

    mob->name = "Dragon";
    mob->physicalPower = 200;
    mob->magicalPower = 200;

    mob->maxHp = 500;
    mob->currentHp = mob->maxHp;

    mob->level = difficulty;

    mob->isAlive = 1;

    return mob;
}

Mob * goblin(int difficulty){

    Mob * mob = malloc(sizeof(Mob));

    mob->name = "Goblin";
    mob->physicalPower = 50;
    mob->magicalPower = 20;

    mob->maxHp = 100;
    mob->currentHp = mob->maxHp;

    mob->level = difficulty;

    mob->isAlive = 1;

    return mob;
}

Mob * titan(int difficulty){

    Mob * mob = malloc(sizeof(Mob));

    mob->name = "Titan";
    mob->physicalPower = 110;
    mob->magicalPower = 50;

    mob->maxHp = 200;
    mob->currentHp = mob->maxHp;

    mob->level = difficulty;

    mob->isAlive = 1;

    return mob;
}

Mob * ghost(int difficulty){

    Mob * mob = malloc(sizeof(Mob));

    mob->name = "Ghost";
    mob->physicalPower = 50;
    mob->magicalPower = 80;

    mob->maxHp = 130;
    mob->currentHp = mob->maxHp;

    mob->level = difficulty;

    mob->isAlive = 1;

    return mob;
}

void mobStats(Mob * mob){

    printf("Name : %s\n", mob->name);

    printf("Physical Power : %d\n", mob->physicalPower);
    printf("Magic Power : %d\n", mob->magicalPower);

    int currentHpBar = mob->currentHp * BAR_LENGTH / mob->maxHp;
    
    printf("HP (%d/%d) : ", mob->currentHp, mob->maxHp);
    printf("[");
    for(int i = 0 ; i < currentHpBar ; i++){
        printf("#");
    }
    for(int i = currentHpBar ; i < BAR_LENGTH ; i++){
        printf(" ");
    }
    printf("]");
    puts(" ");

    printf("Level : %d\n", mob->level);

    printf("\n");
}