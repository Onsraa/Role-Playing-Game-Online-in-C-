#include "./Struct/struct.h"
#include "./sql.h"
#include "./Settings/settings.h"

int main(){

        srand(time(NULL));

        //startingMenu();

        //Connexion

        //connectUserToDataBase();

      
        User * me = malloc(sizeof(User));
        /*
        me->id = 1;
        me->nickname = "Teddy";
        me->password = "Teddy123";
        me->nb_characters = 0;
        me->characters = NULL;
        */

        connectUserToDataBase(me);

        introduction(me);

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

        free(me);
        exit(EXIT_SUCCESS);
}