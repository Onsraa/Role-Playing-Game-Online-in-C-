#include "Struct/struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void connectToDataBase(){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "162.19.64.73";
    char *user = "clarence";
    char *password = "Respons11";
    char *database = "dbCproject";
    char query[300];

    char username[50];
    char userpassword[255];


    conn = mysql_init(NULL);

    if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)){
        finish_with_error(conn);
    }

    if(mysql_query(conn, "show tables")){
        finish_with_error(conn);
    }

    res = mysql_store_result(conn);

    printf("MySQL Tables in mysql database:\n");

    while((row = mysql_fetch_row(res)) != NULL){
        printf("%s \n", row[0]);
    }

    printf("Enter your username: ");
    scanf("%s", username);


    printf("Enter your password: ");
    scanf("%s", userpassword);


    /* Check if user exists */
    sprintf(query, "SELECT * FROM users WHERE username = '%s'", username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_store_result(conn);
    if(mysql_num_rows(res) == 0){
        /* Create the user */
        sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')",username, userpassword);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }else{
            printf("User created successfully\n");
        }
    }else{
        /* Check if the entered password match the one in the database */
        while ((row = mysql_fetch_row(res)) != NULL){
            if(strcmp(row[2], userpassword) == 0){
                printf("User is authenticated\n");
            }else{
                printf("Incorrect password\n");
            }
        }
    }


    mysql_free_result(res);
    mysql_close(conn);
}

void sendUserInfoToDB(User *user) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "server_name";
    char *username = "username";
    char *password = "password";
    char *database = "database_name";
    char query[1024];
    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, username, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    /* Send character information to database */
    int i;
    for (i = 0; i < user->nb_characters; i++) {
        Character *character = user->characters[i];
        sprintf(query, "INSERT INTO Characters (className, physicalPower, magicPower, maxHp, currentHp, maxMp, currentMp, level, experience, experienceNeededToLevelUp, elementType, user_id) VALUES ('%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s)",
                character->className, character->physicalPower, character->magicPower,
                character->maxHp, character->currentHp, character->maxMp, character->currentMp,
                character->level, character->experience, character->experienceNeededToLevelUp,
                character->element->type, user->id);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }

        /* Get the last inserted character id */
        int characterId = mysql_insert_id(conn);

        /* Send spell information to database */
        for (int j = 0; j < character->nb_spells; j++) {
            Spell *spell = character->spells[j];
            sprintf(query, "INSERT INTO Spells (spellName, description, valueFactor, characterId) VALUES ('%s', '%s', '%s', '%d')",
                    spell->spellName, spell->description, spell->valueFactor, characterId);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
            }
        }

        /* Send bag information to database */
        Bag *bag = character->bag;
        for (int j = 0; j < bag->nb_items; j++) {
            Item *item = bag->items[j];
            sprintf(query, "INSERT INTO Items (itemName, quantity) VALUES ('%s', '%d')",
                    item->name, item->quantity);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
            }
        }

        /* Send gear information to database */
        Gears *gears = character->bag->gear;
        sprintf(query, "INSERT INTO Gears (weaponName, armorName) VALUES ('%s', '%s')",
                gears->weapon->name, gears->armor->name);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }

        /* Send each item information to database */
        for (int i = 0; i < bag->nb_items; i++) {
            sprintf(query, "INSERT INTO Items (itemName, quantity, gearId) VALUES ('%s', '%d', '%d')",
                    bag->items[i]->name, bag->items[i]->quantity, gearId);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
            }
        }

        /* Get the last inserted character id */
        int characterId = mysql_insert_id(conn);

        /* Update the foreign key of the character in the User table */
        sprintf(query, "UPDATE User SET characterId = '%d' WHERE id = '%s'", characterId, user->id);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
    }

    /* Close the connection */
    mysql_close(conn);
}