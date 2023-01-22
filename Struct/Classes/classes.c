#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "classes.h"

enum classes {WARRIOR = 1, ROGUE = 2, ARCHER = 3, MAGE = 4};

void initializeClass(User *user, int selection){
    
    Character *new_character = malloc(sizeof(Character));
    
    new_character->level = 0;
    new_character->experience = 0;
    new_character->experienceNeededToLevelUp = 100;

    new_character->bag = NULL;

    switch(selection){
        case WARRIOR : 
            warriorSelected(new_character);
        case ROGUE : 
            rogueSelected(new_character);
        case ARCHER : 
            archerSelected(new_character);
        case MAGE : 
            mageSelected(new_character);
    }    
};

void warriorSelected(Character *character){
    character->className = "Warrior";
    character->physicalPower = 80;
    character->magicPower = 0;

    character->maxHp = 350;
    character->currentHp = character->maxHp;
    
    character->maxMp = 40;
    character->currentHp = character->maxMp;
};

void rogueSelected(Character *character){
    character->className = "Rogue";
    character->physicalPower = 200;
    character->magicPower = 0;

    character->maxHp = 150;
    character->currentHp = character->maxHp;
    
    character->maxMp = 30;
    character->currentHp = character->maxMp;
};

void archerSelected(Character *character){
    character->className = "Archer";
    character->physicalPower = 150;
    character->magicPower = 60;

    character->maxHp = 120;
    character->currentHp = character->maxHp;
    
    character->maxMp = 80;
    character->currentHp = character->maxMp;
};

void mageSelected(Character *character){
    character->className = "Mage";
    character->physicalPower = 0;
    character->magicPower = 200;

    character->maxHp = 110;
    character->currentHp = character->maxHp;
    
    character->maxMp = 120;
    character->currentHp = character->maxMp;
};