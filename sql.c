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

int connectUserToDataBase(User * currentUser){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    //N'utilisez pas notre serveur à mauvais escient svp. Merci <3
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
    printf("Enter your username: ");
    scanf("%s", username);


    printf("Enter your password: ");
    scanf("%s", userpassword);


    /* Check if user exists */
    sprintf(query, "SELECT * FROM Users WHERE username = '%s'", username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_store_result(conn);
    if(mysql_num_rows(res) == 0){
        /* Create the user */
        sprintf(query, "INSERT INTO Users (username, password) VALUES ('%s', '%s')",username, userpassword);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }else{
            printf("User created successfully\n");
            /* Get user data */
            sprintf(query, "SELECT * FROM Users WHERE username = '%s'", username);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
            }
            res = mysql_use_result(conn);
            row = mysql_fetch_row(res);
            currentUser->id = atoi(row[0]);
            currentUser->nickname = row[1];
            currentUser->password = row[2];
            currentUser->nb_characters = atoi(row[3]);
            mysql_free_result(res);
            return 2;                                         /// 2 = user created
        }
    }else{
        /* Check if the entered password match the one in the database */
        while ((row = mysql_fetch_row(res)) != NULL){
            if(strcmp(row[2], userpassword) == 0){
                printf("User is authenticated\n");
                /* Get user data */
                sprintf(query, "SELECT * FROM Users WHERE username = '%s'", username);
                if (mysql_query(conn, query)) {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    exit(1);
                }
                res = mysql_use_result(conn);
                row = mysql_fetch_row(res);
                currentUser->id = atoi(row[0]);
                currentUser->nickname = (char*)malloc(strlen(row[1])+1);
                strcpy(currentUser->nickname, row[1]);
                currentUser->password = (char*)malloc(strlen(row[2])+1);
                strcpy(currentUser->password, row[2]);
                currentUser->nb_characters = atoi(row[3]);
                mysql_free_result(res);
                return 1;                                     /// 1 = user authenticated
            }else{
                printf("Incorrect password\n");
                return 0;                                     /// 0 = user not authenticated password incorrect
            }
        }
    }

    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}











void sendUserInfoToDB(User *user) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "162.19.64.73";
    char *username = "clarence";
    char *password = "Respons11";
    char *database = "dbCproject";
    char query[1024];
    int i, j;
    int character_id;

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, username, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    /* Get the user_id generated by the previous query */
    sprintf(query, "SELECT id FROM Users WHERE nickname = '%s'", user->nickname);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    int user_id = atoi(row[0]);
    mysql_free_result(res);

    /* Send character information to database */
    for (i = 0; i < user->nb_characters; i++) {
        Character *character = user->characters[i];

        /*Send gear information to database */
        Gears *gears = character->gears;
        Armor *gearArmor = gears->armor;
        Weapon *gearWeapon = gears->weapon;

        /* Send Gear weapon information to database */
        sprintf(query, "INSERT INTO Weapons (name, bonus_damage, rarity, element) VALUES ('%s', %d, %d, %d)",
                gearWeapon->name, gearWeapon->bonus_damage, gearWeapon->rarity, gearWeapon->element->type);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        /* Get the Gear weapon_id generated by the previous query */
        sprintf(query, "SELECT LAST weapon_id FROM Weapons WHERE name = '%s'", gearWeapon->name);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        int gear_weapon_id = atoi(row[0]);
        mysql_free_result(res);


        /* Send Gear armor information to database */
        sprintf(query, "INSERT INTO Armors (name, bonus_resistance, rarity, element) VALUES ('%s', %d, %d, %d)",
                gearArmor->name, gearArmor->bonus_resistance, gearArmor->rarity, gearArmor->element->type);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        /* Get the Gear armor_id generated by the previous query */
        sprintf(query, "SELECT LAST armor_id FROM Armors WHERE name = '%s'", gearArmor->name);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        int gear_armor_id = atoi(row[0]);
        mysql_free_result(res);


        sprintf(query,
                "INSERT INTO Character (class_id, className, physicalPower, magicalPower, maxHp, currentHp, maxMp, currentMp, level, experience, experienceNeededToLevelUp, element, isAlive, user_id, nb_weapons, nb_armors, gear_weapon_id, gear_armor_id) VALUES ('%d', %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
                character->classId,character->className, character->physicalPower, character->magicalPower, character->maxHp,
                character->currentHp, character->maxMp, character->currentMp, character->level, character->experience,
                character->experienceNeededToLevelUp, character->element->type, character->isAlive, user_id,
                character->bag->nb_weapons, character->bag->nb_armors, gear_weapon_id, gear_armor_id);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        /* Get the character_id generated by the previous query */
        sprintf(query, "SELECT LAST character_id FROM Characters WHERE user_id = '%d'", user->id);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        character_id = atoi(row[0]);
        mysql_free_result(res);


        /*Send spells information to database */
        for (int k = 0; k < NB_SPELLS; ++k) {
            sprintf(query,
                    "INSERT INTO Spells (name, description, value_factor, value, cost, element, character_id) VALUES ('%s', '%s', %d, %d, %d, %d, %d)",
                    character->spells[k]->spellName, character->spells[k]->description,
                    character->spells[k]->valueFactor, character->spells[k]->value, character->spells[k]->cost,
                    character->spells[k]->element->type, character_id);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
            }
        }
        /*Send armor information to database */
        Bag *bag = character->bag;
        for (int k = 0; k < bag->nb_armors; ++k) {
            sprintf(query,
                    "INSERT INTO Armors (name, bonus_resistance, rarity, element, character_id) VALUES ('%s', %d, %d, %d, %d)",
                    bag->armors[k]->name, bag->armors[k]->bonus_resistance, bag->armors[k]->rarity,
                    bag->armors[k]->element->type, character_id);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
            }
        }
        /*Send weapon information to database */
        for (int k = 0; k < bag->nb_weapons; ++k) {
            sprintf(query,
                    "INSERT INTO Weapons (name, bonus_damage, rarity, element, character_id) VALUES ('%s', %d, %d, %d, %d)",
                    bag->weapons[k]->name, bag->weapons[k]->bonus_damage, bag->weapons[k]->rarity,
                    bag->weapons[k]->element->type, character_id);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
            }
        }
        free(character);
        free(gearWeapon);
        free(gearArmor);
        free(bag);
    }
    free(user);
    mysql_close(conn);
}








/* Get data from database */
void getDataFromDatabase(User *user){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "162.19.64.73";
    char *username = "clarence";
    char *password = "Respons11";
    char *database = "dbCproject";
    char query[1024];
    int i, j;
    int character_id;

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, username, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    /* Get characters data */
    /* Retrieve character information from database */
    sprintf(query, "SELECT * FROM Characters WHERE user_id = %d", user->id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    user->nb_characters = mysql_num_rows(res);
    user->characters = malloc(user->nb_characters * sizeof(Character *));
    i = 0;
    while ((row = mysql_fetch_row(res)) != NULL) {
        Character *character = malloc(sizeof(Character));
        character->element = malloc(sizeof(Element));
        Bag *bag = malloc(sizeof(Bag));

        character_id = atoi(row[0]);
        character->classId = atoi(row[1]);
        character->className = (char*)malloc(strlen(row[2])+1);
        strcpy(character->className, row[2]);
        character->physicalPower = atoi(row[3]);
        character->magicalPower = atoi(row[4]);
        character->maxHp = atoi(row[5]);
        character->currentHp = atoi(row[6]);
        character->maxMp = atoi(row[7]);
        character->currentMp = atoi(row[8]);
        character->level = atoi(row[9]);
        character->experience = atoi(row[10]);
        character->experienceNeededToLevelUp = atoi(row[11]);
        character->element->type = atoi(row[12]);
        character->isAlive = atoi(row[12]);
        bag->nb_weapons = atoi(row[13]);
        bag->nb_armors = atoi(row[14]);
        int gear_weapon_id = atoi(row[15]);
        int gear_armor_id = atoi(row[16]);



        user->characters[i] = character;

        /* Retrieve gear information from database */
        Gears *gears = malloc(sizeof(Gears));
        sprintf(query, "SELECT * FROM Weapons WHERE gear_weapon_id = %d", gear_weapon_id);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        MYSQL_RES *res_gear = mysql_use_result(conn);
        MYSQL_ROW row_gear = mysql_fetch_row(res_gear);
        if (row_gear != NULL) {
            gears->weapon = malloc(sizeof(Weapon));
            gears->weapon->name = malloc(strlen(row_gear[1])+1);
            strcpy(gears->weapon->name, row_gear[1]);
            gears->weapon->bonus_damage = atoi(row_gear[2]);
            gears->weapon->rarity = atoi(row_gear[3]);
            gears->weapon->element = malloc(sizeof(Element));
            gears->weapon->element->type = atoi(row_gear[4]);
        }
        mysql_free_result(res_gear);

        sprintf(query, "SELECT * FROM Armors WHERE gear_armor_id = %d", gear_armor_id);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        res_gear = mysql_use_result(conn);
        row_gear = mysql_fetch_row(res_gear);
        if (row_gear != NULL) {
            gears->armor = malloc(sizeof(Armor));
            gears->armor->name = malloc(strlen(row_gear[1])+1);
            strcpy(gears->armor->name, row_gear[1]);
            gears->armor->bonus_resistance = atoi(row_gear[2]);
            gears->armor->rarity = atoi(row_gear[3]);
            gears->armor->element = malloc(sizeof(Element));
            gears->armor->element->type = atoi(row_gear[4]);
        }
        mysql_free_result(res_gear);

        /* Retrieve bag information from database */
        sprintf(query, "SELECT * FROM Armors WHERE character_id = %d", character_id);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        MYSQL_RES *res_armor = mysql_use_result(conn);
        if (res_armor != NULL) {
            bag->armors = malloc(bag->nb_armors * sizeof(Armor *));
            j = 0;
            while ((row = mysql_fetch_row(res_armor)) != NULL && row[5] != NULL) {
                Armor *armor = malloc(sizeof(Armor));
                armor->element = malloc(sizeof(Element));
                armor->name = malloc(strlen(row[1])+1);
                strcpy(armor->name, row[1]);
                armor->bonus_resistance = atoi(row[2]);
                armor->rarity = atoi(row[3]);
                armor->element->type = atoi(row[4]);
                bag->armors[j] = armor;
                j++;
            }
        }
        mysql_free_result(res_armor);

        sprintf(query, "SELECT * FROM Weapons WHERE character_id = %d", character_id);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        MYSQL_RES *res_weapon = mysql_use_result(conn);
        if (res_weapon != NULL) {
            bag->weapons = malloc(bag->nb_weapons * sizeof(Weapon *));
            j = 0;
            while ((row = mysql_fetch_row(res_weapon)) != NULL && row[5] != NULL) {
                Weapon *weapon = malloc(sizeof(Weapon));
                weapon->element = malloc(sizeof(Element));
                weapon->name = malloc(strlen(row[1])+1);
                strcpy(weapon->name, row[1]);
                weapon->bonus_damage = atoi(row[2]);
                weapon->rarity = atoi(row[3]);
                weapon->element->type = atoi(row[4]);
                bag->weapons[j] = weapon;
                j++;
            }
        }
        mysql_free_result(res_weapon);

        /* Retrieve Spells information from database */
        sprintf(query, "SELECT * FROM Spells WHERE character_id = %d", character_id);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        MYSQL_RES *res_spells = mysql_use_result(conn);
        if (res_spells != NULL) {
            character->spells = malloc(NB_SPELLS * sizeof(Spell *));
            int k = 0;
            while ((row = mysql_fetch_row(res_spells)) != NULL && row[5] != NULL) {
                Spell *spell = malloc(sizeof(Spell));
                spell->element = malloc(sizeof(Element));
                spell->spellName = malloc(strlen(row[1])+1);
                strcpy(spell->spellName, row[1]);
                spell->description = malloc(strlen(row[2])+1);
                strcpy(spell->description, row[2]);
                spell->valueFactor = atoi(row[3]);
                spell->value = atoi(row[4]);
                spell->cost = atoi(row[5]);
                spell->element->type = atoi(row[6]);
                character->spells[k] = spell;
                k++;
            }
        }



    i++;
    }
}
