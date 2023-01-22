#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./Struct/Users/users.h"

int main(){

        User * me = malloc(sizeof(User));
        me->id = "m87KqduzxS";
        me->nickname = "Onsra";
        me->password = "Teddy123";
        me->nb_characters = 0;
        me->characters = NULL;

        userInfo(me);

        exit(EXIT_SUCCESS);
}