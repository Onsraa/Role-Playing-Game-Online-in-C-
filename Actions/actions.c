#include "../struct.h"

enum action {BASIC_ATTACK = 1, OFFENSIVE = 2, HEAL = 3};

enum gearState {EQUIPPED = 1, STORED = 0};

void fight(Character *character, Mob *mob, int auto_mode){

    int rounds = 0;

    while(character->isAlive && mob->isAlive){

        ++rounds;
    }
}

void players_turn(Character *character, Mob *mob, int dialogue){

    if(!character || !mob){
        system("clear");
        printf("Character or mob don't exist.");
        exit(EXIT_FAILURE);
    }

    int total_damage = character->physicalPower + character->magicalpower;

    if(character->gears && character->gears->weapon){ // Check if a weapon is equipped.
        switch(compatibility(character->element->type == character->gears->weapon->element->type)){ // Check element compatibility between weapon and character.
            case 1 : // Character's element is efficient against the weapon so it changes nothing.
                total_damage += character->gears->weapon->bonus_damage;
                break;
            case 2 : // Weapon's element is efficient against the character so it gives mallus.
                if(dialogue){
                    printf("The character struggles to handle a weapon of the opposite element, mallus !\n");
                }
                total_damage += character->gears->weapon->bonus_damage * 0.7;
                break;
            case 3 : // Same element weapon and character so bingo.
                if(dialogue){
                    printf("Compability between weapon and character, bonus damage !\n");
                }
                total_damage += character->gears->weapon->bonus_damage * 2;
                break;
        }
    }

    switch(fightAlgorithm(character, mob)){
        case 1 : // BASIC ATTACK
            mob->currentHp -= total_damage;

            if(dialogue){
                printf("You hit the %s for %d ! It has %d hp left.\n", mob->name, total_damage, mob->currentHp);
            }

            break;
        case 2 : // OFFENSIVE ATTACK

            if(character->spells[0]->valueFactor = STATIC){
                total_damage += character->spells[0]->value;
            }else{
                total_damage *= character->spells[0]->value;
            }

            mob->currentHp -= total_damage;
            
            if(dialogue){
                printf("You hit the %s for %d ! It has %d hp left.\n", mob->name, total_damage, mob->currentHp);
            }

            break : 
        case 3 : // HEALING 

            if(character->spells[1]->valueFactor = STATIC){
                total_damage += character->spells[0]->value;
            }else{
                total_damage *= character->spells[0]->value;
            }

            character->currentHp += total_damage;

            if(dialogue){
                printf("You healed yourself for %d !\nREMAINS HP : [%d/%d]\n", total_damage,character->currentHp, character->maxHp);
            }
            break;
    }
}

void mobs_turn(Mob *mob, Character * character, int dialogue){

    if(!character || !mob){
        system("clear");
        printf("Character or mob don't exist.");
        exit(EXIT_FAILURE);
    }

    int total_damage = mob->physicalPower + mob->magicalPower;

    if(dialogue){
        printf("The %s hits you for %d !\nREMAINS HP : [%d/%d]\n", mob->name, total_damage, character->currentHp, character->maxHp);
    }
    character->currentHp -= total_damage;
}

int fightAlgorithm(Character * character, Mob *mob){

    if(!character){
        printf("No character.");
        exit(EXIT_FAILURE);
    }

    int basic_attack_damage = character->attack_damage;

    Spell * offensive_spell = character->spells[0];
    Spell * healing_spell = character->spells[1];

    if(basic_attack_damage >= mob->currentHp){ // If the character only needs to hit once to kill the mob, then it returns the action.
        return BASIC_ATTACK;
    }

    if(character->currentMp >= offensive_spell->cost){
        if(offensive_spell->value >= mob->currentHp){
            return OFFENSIVE;
        }
        if(character->currentHp <= character->maxHp * 0.3){
            if(character->currentMp >= healing_spell->cost){
                return HEAL;
            }
        }
        return OFFFENSIVE;
    }
    return BASIC_ATTACK;
}

void dropStuff(Character *character, Mob * mob){

}