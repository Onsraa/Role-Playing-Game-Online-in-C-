#include "../struct.h"

enum action {BASIC_ATTACK = 1, OFFENSIVE = 2, HEAL = 3};

enum gearState {EQUIPPED = 1, STORED = 0};

void fight(Character *character, Mob *mob, int auto_mode){

    int rounds = 0;

    while(character->isAlive && mob->isAlive){

        ++rounds;
    }
}

void player_hits(Character *character, Mob *mob){

    if(!character || !mob){
        system("clear");
        printf("Character or mob don't exist.");
        exit(EXIT_FAILURE);
    }

    float total_damage;

    if(character->bag){
        for(int gear = 0 ; gear < character->bag->nb_gear ; gear++){
            
        }
    }


}

void player_heals(Character *character){
    
}

void mob_hits(Mob *mob, Character * character){

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