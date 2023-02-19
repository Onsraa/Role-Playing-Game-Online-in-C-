#include "./Struct/struct.h"
#include "./sql.h"
#include "./Settings/settings.h"

int main(){

        srand(time(NULL));

        User * me = malloc(sizeof(User));

        introduction(me);

        free(me);
        
        exit(EXIT_SUCCESS);
}