#ifndef USERS_H_
#define USERS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../Classes/classes.h"

typedef struct User User;

struct User
{

    char *id;
    char *nickname;
    char *password;

    Character **characters; // Array of characters
    int nb_characters;
};

int createUser(char * nickname, char * password); // Returns success or failure
int connectUser(char * nickname, char * password); // Returns success or failure

void changePassword(char id, char * password);

void userInfo(User * currentUser);

#endif