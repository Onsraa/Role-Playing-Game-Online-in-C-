#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./Struct/struct.h"

int main(){

        User * me = malloc(sizeof(User));
        me->id = "m87KqduzxS";
        me->nickname = "Onsra";
        me->password = "Teddy123";
        me->nb_characters = 0;
        me->characters = NULL;

        initializeCharacter(me);
        
        system("clear");

        characterStat(me->characters[0]);

        exit(EXIT_SUCCESS);
}