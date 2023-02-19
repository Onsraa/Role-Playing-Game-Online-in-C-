#include "./Struct/struct.h"
#include "sql.h"

int main(){

        srand(time(NULL));

        //startingMenu();

        //Connexion

        //connectUserToDataBase();

        User * me = malloc(sizeof(User));

        //Conected user to the database
        connectUserToDatabase(me);

        initializeCharacter(me);
        
        system("clear");

        /*
        initializeNewCharacter(me);
        chooseNewClass(me);

        showAllCharacters(me);

        exit(1);

        Mob * mob = generateMob(1);

        fight(me->characters[0], mob, 1, 1);

        chooseWeapon(me->characters[0]);
        chooseWeapon(me->characters[0]);
        */

        exit(EXIT_SUCCESS);
}