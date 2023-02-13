#include "../struct.h"

#define NB_MOBS 4

enum mobs {DRAGON = 1, GOBLIN = 2, TITAN = 3, GHOST = 4};
enum difficulty {EASY = 1, NORMAL = 2, HARD = 3};

Mob * generateMob(){

    Mob * generatedMob;

    srand(time(NULL));
    switch((int)(rand() % NB_MOBS + 1)){
        case GOBLIN:
            generatedMob = goblin();
            break;
        case TITAN:
            generatedMob = titan();
            break;
        case GHOST:
            generatedMob = ghost();
            break;
    };

    return generatedMob;
}

Mob * dragon(int difficulty){

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