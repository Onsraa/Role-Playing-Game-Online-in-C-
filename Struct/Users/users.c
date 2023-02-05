#include "../struct.h"

void userInfo(User * currentUser){

    system("clear");
    printf("\n|----------------------------------------------------------------|\n\n");
    printf("\tnickname: %s\n", currentUser->nickname);
    printf("\tpassword: %c", currentUser->password[0]);
    for(int i = 1 ; i < strlen(currentUser->password); i++){
        printf("*");
    }
    printf("\n\n|----------------------------------------------------------------|\n");
}