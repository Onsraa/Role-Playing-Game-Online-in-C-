#include "../struct.h"
#define NB_SPELLS 3

enum spell = {DEFAULT = 1, OFFENSIVE = 2, HEAL = 3, PASSIVE = 4} // Passive spell is not implemented yet.

void showSpells(Character *character){

    if(!character){
        printf("Character not found.\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0 ; i < NB_SPELLS ; i++){
        printf("%d : %s [%d]\n", i+1, character->spells[i].spellName, character->spells[i].cost);
    }
}