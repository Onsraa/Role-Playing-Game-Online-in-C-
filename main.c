#include "./main.h"

int main(){

        User * me = malloc(sizeof(User));
        me->id = "m87KqduzxS";
        me->nickname = "Onsra";
        me->password = "Teddy123";
        me->nb_characters = 0;
        me->characters = NULL;

        chooseClass(me);

        pritnf("TEST GIT");
        
        exit(EXIT_SUCCESS);
}