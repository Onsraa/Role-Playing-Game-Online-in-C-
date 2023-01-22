#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int main(){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "162.19.64.73";
    char *user = "clarence";
    char *password = "Respons11";
    char *database = "dbCproject";

    conn = mysql_init(NULL);

    if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)){
        finish_with_error(conn);
    }

    if(mysql_query(conn, "show tables")){
        finish_with_error(conn);
    }

    res = mysql_use_result(conn);

    printf("MySQL Tables in mysql database:\n");

    while((row = mysql_fetch_row(res)) != NULL){
        printf("%s \n", row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);
}


