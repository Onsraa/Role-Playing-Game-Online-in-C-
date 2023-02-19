#include "./Struct/struct.h"
#include "sql.h"

int main(){

        User * me = malloc(sizeof(User));

        //Conected user to the database
        connectUserToDatabase(me);

        initializeCharacter(me);
        
        system("clear");

        characterStats(me->characters[0]);

        giveSpells(me->characters[0]);

        showSpells(me->characters[0]);

        Mob * mob = generateMob(1);

        mobStats(mob);

        fight(me->characters[0], mob, 1, 1);

        exit(EXIT_SUCCESS);
}