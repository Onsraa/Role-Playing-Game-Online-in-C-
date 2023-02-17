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

        characterStats(me->characters[0]);

        giveSpells(me->characters[0]);

        showSpells(me->characters[0]);

        
        Mob * mob = generateMob(1);

        /*
        mobStats(mob);

        fight(me->characters[0], mob, 1, 1);

        */

        chooseWeapon(me->characters[0]);

        dropStuff(me->characters[0], mob);
        
        exit(EXIT_SUCCESS);
}