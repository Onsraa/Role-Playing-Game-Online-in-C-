//
// Created by Clarence Hirsch on 19/02/2023.
//

#ifndef ROLE_PLAYING_GAME_ONLINE_IN_C_SQL_H
#define ROLE_PLAYING_GAME_ONLINE_IN_C_SQL_H

#include <mysql.h>

void finish_with_error(MYSQL *con);

int connectUserToDatabase(User * user);

void sendUserInfoToDB(User * user);

void getDataFromDatabase(User * user);


#endif //ROLE_PLAYING_GAME_ONLINE_IN_C_SQL_H
