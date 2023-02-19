#include "../struct.h"

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

Mob * createMob(char * mobName, int phyisicalPower, int magicalPower, int hp, int difficulty){

    Mob * mob = malloc(sizeof(Mob));

    mob->name = mobName;
    mob->physicalPower = phyisicalPower * difficulty;
    mob->magicalPower = magicalPower * difficulty;

    mob->maxHp = hp * difficulty;
    mob->currentHp = mob->maxHp;

    mob->level = difficulty;

    mob->isAlive = 1;

    return mob;
}

Mob * dragon(int difficulty){ // Boss mob

    return createMob("Dragon", 190, 100, 3000, difficulty);
}

Mob * goblin(int difficulty){

    return createMob("Goblin", 30, 0, 100, difficulty);
}

Mob * titan(int difficulty){

    return createMob("Titan", 80, 10, 500, difficulty);
}

Mob * ghost(int difficulty){
    
    return createMob("Ghost", 50, 50, 300, difficulty);
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