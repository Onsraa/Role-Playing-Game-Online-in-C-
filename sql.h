#ifndef ROLE_PLAYING_GAME_ONLINE_IN_C_SQL_H
#define ROLE_PLAYING_GAME_ONLINE_IN_C_SQL_H

#include <mysql.h>

void finish_with_error(MYSQL *con);

int connectUserToDataBase(User * currentUser);

void sendUserInfoToDB(User * user);

void getDataFromDatabase(User * user);


#endif //ROLE_PLAYING_GAME_ONLINE_IN_C_SQL_H