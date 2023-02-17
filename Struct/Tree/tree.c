#include "../struct.h"

#define REGENERATION_ZONE 6
#define STARTING_ZONE 5

enum zones {VOLCANO = 1, FOREST = 2, DUNGEON = 3, FALL = 4, HOSTS = 5, FOUNTAIN = 6}

void generateRandomZone(){


}

void fountain(Character * character){

    int answer;

    do{
        system("clear");
        printf("Do you want to regenerate your life points and your mana ?\n\n");
        printf("1 - Yes\n");
        printf("2 - No\n");
    }while(answer != 1 && answer != 2);

    switch(answer){
        case 1:
            character->currentHp += character->maxHp * 0.5;
            character->currentMp += character->maxMp;

            character->currentHp = (character->currentHp > character->maxHp) ? character->maxHp : character->currentHp;
            character->currentMp = (character->currentMp > character->maxMp) ? character->maxMp : character->currentMp;

            printf("You regenerate 50\% of your max hp and all your mp.");
            showBars(character);
            break;
        case 2:
            printf("Oh okay.. you're a tough one huh ?");
            break;
    }

}