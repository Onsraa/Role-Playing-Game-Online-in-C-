#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include "../Struct/struct.h"

void readSettings(){
    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;
    struct json_object *settings;
    struct json_object *color;
    struct json_object *difficulty;
    struct json_object *combat_mode;
    struct json_object *dialogue;

    fp = fopen("settings.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "settings", &settings);
    json_object_object_get_ex(settings, "color", &color);
    json_object_object_get_ex(settings, "difficulty", &difficulty);
    json_object_object_get_ex(settings, "combat_mode", &combat_mode);
    json_object_object_get_ex(settings, "dialogue", &dialogue);

    printf("Color: %s\n", json_object_get_string(color));
    printf("Difficulty: %s\n", json_object_get_string(difficulty));
    printf("Combat Mode: %s\n", json_object_get_string(combat_mode));
    printf("Dialogue: %s\n", json_object_get_string(dialogue));

}

int getDifficulty(){
    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;
    struct json_object *settings;
    struct json_object *difficulty;
    struct json_object *combat_mode;
    struct json_object *dialogue;

    fp = fopen("settings.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "settings", &settings);
    json_object_object_get_ex(settings, "difficulty", &difficulty);
    json_object_object_get_ex(settings, "combat_mode", &combat_mode);
    json_object_object_get_ex(settings, "dialogue", &dialogue);

    return json_object_get_int(difficulty);

}

void updateDifficulty(int newDifficulty){
    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;
    struct json_object *settings;
    struct json_object *difficulty;
    struct json_object *combat_mode;
    struct json_object *dialogue;

    fp = fopen("settings.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);

    //get the settings object
    json_object_object_get_ex(parsed_json, "settings", &settings);

    //get the difficulty object and update it with the new value
    json_object_object_get_ex(settings, "difficulty", &difficulty);
    json_object_set_int(difficulty, newDifficulty);

    //write the new json to the file
    fp = fopen("settings.json", "w");
    fprintf(fp, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
    fclose(fp);

}


int getCombatMode(){

    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;
    struct json_object *settings;
    struct json_object *difficulty;
    struct json_object *combat_mode;
    struct json_object *dialogue;

    fp = fopen("settings.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "settings", &settings);
    json_object_object_get_ex(settings, "difficulty", &difficulty);
    json_object_object_get_ex(settings, "combat_mode", &combat_mode);
    json_object_object_get_ex(settings, "dialogue", &dialogue);

    return json_object_get_int(combat_mode);
}


int getDialogueMode(){
    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;
    struct json_object *settings;
    struct json_object *difficulty;
    struct json_object *combat_mode;
    struct json_object *dialogue;

    fp = fopen("settings.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "settings", &settings);
    json_object_object_get_ex(settings, "difficulty", &difficulty);
    json_object_object_get_ex(settings, "combat_mode", &combat_mode);
    json_object_object_get_ex(settings, "dialogue", &dialogue);

    return json_object_get_int(dialogue);

}



void updateDialogueSettings(int newDialog) {
    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;
    struct json_object *settings;
    struct json_object *dialogue;

    // Open the file and read its contents into a buffer
    fp = fopen("settings.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    // Parse the JSON data
    parsed_json = json_tokener_parse(buffer);

    // Get the "settings" object
    json_object_object_get_ex(parsed_json, "settings", &settings);

    // Get the "dialogue" field and update it with the new value
    json_object_object_get_ex(settings, "dialogue", &dialogue);
    json_object_set_int(dialogue, newDialog);

    // Write the updated JSON data back to the file
    fp = fopen("settings.json", "w");
    fprintf(fp, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
    fclose(fp);
}

void updateCombatMode(int newCombatMode) {
    const char *filename = "settings.json";
    const char *field = "combat_mode";

    // Open the file and read its contents into a buffer
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open %s for reading\n", filename);
        exit(1);
    }
    char buffer[1024];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), fp);
    if (bytesRead == 0) {
        fprintf(stderr, "Failed to read from %s\n", filename);
        fclose(fp);
        exit(1);
    }
    fclose(fp);

    // Parse the JSON data
    struct json_object *parsed_json = json_tokener_parse(buffer);

    // Update the field
    struct json_object *combatModeObj = json_object_new_int(newCombatMode);
    json_object_object_add(json_object_object_get(parsed_json, "settings"), field, combatModeObj);

    // Write the updated JSON data back to the file
    fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open %s for writing\n", filename);
        exit(1);
    }
    fprintf(fp, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
    fclose(fp);
}


void updateSettings( char* selectedDifficulty , char* selectedCombatMode , char* selectedDialogue) {
    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;
    struct json_object *settings;

    struct json_object *difficulty;
    struct json_object *combat_mode;
    struct json_object *dialogue;

    fp = fopen("settings.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "settings", &settings);
    json_object_object_get_ex(settings, "difficulty", &difficulty);
    json_object_object_get_ex(settings, "combat_mode", &combat_mode);
    json_object_object_get_ex(settings, "dialogue", &dialogue);

    // update the values
    json_object_set_string(difficulty, selectedDifficulty);
    json_object_set_string(combat_mode, selectedCombatMode);
    json_object_set_string(dialogue, selectedDialogue);

    // write the updated values back to the file
    fp = fopen("settings.json", "w");
    fprintf(fp, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
    fclose(fp);
}

void printSettings(){
    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;
    struct json_object *settings;
    struct json_object *difficulty;
    struct json_object *combat_mode;
    struct json_object *dialogue;
    char * combatModeStatus;
    char * dialogueStatus;
    char * difficultyStatus;

    fp = fopen("settings.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "settings", &settings);
    json_object_object_get_ex(settings, "difficulty", &difficulty);
    json_object_object_get_ex(settings, "combat_mode", &combat_mode);
    json_object_object_get_ex(settings, "dialogue", &dialogue);


    if (json_object_get_int(difficulty) == 1){
        difficultyStatus = "FACILE";
    } else if (json_object_get_int(difficulty) == 2){
        difficultyStatus = "MOYEN";
    } else {
        difficultyStatus = "DIFFICILE";
    }

    if (json_object_get_int(combat_mode) == 1){
        combatModeStatus = "ON";
    } else {
        combatModeStatus = "OFF";
    }
    if (json_object_get_int(dialogue) == 1){
        dialogueStatus = "ON";
    } else {
        dialogueStatus = "OFF";
    }
    printf("\n\n\n");
    printf("****** SETTINGS: ******\n");
    printf("1 -- Mode de combat: %s\n", combatModeStatus);
    printf("2 -- Dialogue: %s\n", dialogueStatus);
    printf("3 -- Difficulté: %s\n\n", difficultyStatus);
    printf("0 -- Retour\n");
    printf("***********************\n");
}

int printDifficulty(){
    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;
    struct json_object *settings;
    struct json_object *difficulty;
    struct json_object *combat_mode;
    struct json_object *dialogue;
    char * combatModeStatus;
    char * dialogueStatus;
    char * difficultyStatus;

    fp = fopen("settings.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "settings", &settings);
    json_object_object_get_ex(settings, "difficulty", &difficulty);
    json_object_object_get_ex(settings, "combat_mode", &combat_mode);
    json_object_object_get_ex(settings, "dialogue", &dialogue);
    printf("\n");
    printf("****** DIFFICULTY: ******\n");
    if (json_object_get_int(difficulty) == 1){
        printf("1 -- Facile (actuel)\n");
    } else {
        printf("1 -- Facile\n");
    }
    if (json_object_get_int(difficulty) == 2){
        printf("2 -- Moyen (actuel)\n");
    } else {
        printf("2 -- Moyen\n");
    }
    if (json_object_get_int(difficulty) == 3){
        printf("3 -- Difficile (actuel)\n\n");
    } else {
        printf("3 -- Difficile\n\n");
    }
    printf("0 -- Retour\n");
    printf("*************************\n");
    return json_object_get_int(difficulty);
}

void difficultyMenu(){
    int actualDifficulty;
    actualDifficulty = printDifficulty();
    int choice;
    char * confirm2 = malloc(sizeof(char) * 5);
    scanf("%d", &choice);
    while (choice < 0 || choice > 3){
        printf("\n\n\nChoix invalide, veuillez réessayer\n");
        printDifficulty();
        scanf("%d", &choice);
    }
    while (choice == actualDifficulty){
        printf("\n\n\nVous êtes déja sur cette difficulté, veuillez en choisir une autre\n");
        printDifficulty();
        scanf("%d", &choice);
    }
    switch (choice) {
        case 1:
            printf("Voulez-vous vraiment changer la difficulté en FACILE ? (y = Oui, n = Non)\n");
            scanf("%s", confirm2);
            while (strcmp(confirm2, "y") != 0 && strcmp(confirm2, "n") != 0){
                printf("Voulez-vous vraiment changer la difficulté en FACILE ?     ATTENTION->(y = Oui, n = Non)\n");
                scanf("%s", confirm2);
            }
            if (strcmp(confirm2, "y") == 0) {
                updateDifficulty(1);
                printf("\n|||||||La difficulté est maintenant en FACILE ! |||||||\n");
            }else {
                difficultyMenu();
            }
            break;
        case 2:
            printf("Voulez-vous vraiment changer la difficulté en MOYEN ? (y = Oui, n = Non)\n");
            scanf("%s", confirm2);
            while (strcmp(confirm2, "y") != 0 && strcmp(confirm2, "n") != 0){
                printf("Voulez-vous vraiment changer la difficulté en MOYEN ?     ATTENTION->(y = Oui, n = Non)\n");
                scanf("%s", confirm2);
            }
            if (strcmp(confirm2, "y") == 0) {
                updateDifficulty(2);
                printf("\n||||||| La difficulté est maintenant en MOYEN ! |||||||\n");
            }else {
                difficultyMenu();
            }
            break;
        case 3:
            printf("Voulez-vous vraiment changer la difficulté en DIFFICILE ? (y = Oui, n = Non)\n");
            scanf("%s", confirm2);
            while (strcmp(confirm2, "y") != 0 && strcmp(confirm2, "n") != 0){
                printf("Voulez-vous vraiment changer la difficulté en DIFFICILE ?     ATTENTION->(y = Oui, n = Non)\n");
                scanf("%s", confirm2);
            }
            if (strcmp(confirm2, "y") == 0) {
                updateDifficulty(3);
                printf("\n|||||||La difficulté est maintenant en DIFFICILE ! |||||||\n");
            }else {
                difficultyMenu();
            }
            break;
        case 0:
            break;
    }
    free(confirm2);
}

void menuSettings(User * user){
    int choice;
    char *confirm = malloc(sizeof(char) * 5);
    int difficulty;

    system("clear");
    printSettings();
    scanf("%d", &choice);
    switch(choice){
        case 0:
            main_menu(user);
            break;
        case 1:
            if (getCombatMode() == 1){
                printf("Voulez-vous vraiment désactiver le mode de combat ? (y = Oui, n = Non)\n");
                scanf("%s", confirm);
                while (strcmp(confirm, "y") != 0 && strcmp(confirm, "n") != 0){
                    printf("Voulez-vous vraiment désactiver le mode de combat ?     ATTENTION->(y = Oui, n = Non)\n");
                    scanf("%s", confirm);
                }
                if (strcmp(confirm, "y") == 0) {
                    updateCombatMode(0);
                    printf("Le mode de combat est maintenant désactivé !\n");
                }
            } else {
                printf("Voulez-vous vraiment activer le mode de combat ? (y = Oui, n = Non)\n");
                scanf("%s", confirm);
                while (strcmp(confirm, "y") != 0 && strcmp(confirm, "n") != 0){
                    printf("Voulez-vous vraiment activer le mode de combat ?     ATTENTION->(y = Oui, n = Non)\n");
                    scanf("%s", confirm);
                }
                if (strcmp(confirm, "y") == 0) {
                    updateCombatMode(1);
                    printf("Le mode de combat est maintenant actif !\n");
                }
            }
            menuSettings(user);
            break;
        case 2:
            if (getDialogueMode() == 1){
                printf("Voulez-vous vraiment désactiver le dialogue ? (y = Oui, n = Non)\n");
                scanf("%s", confirm);
                while (strcmp(confirm, "y") != 0 && strcmp(confirm, "n") != 0){
                    printf("Voulez-vous vraiment désactiver le dialogue ?     ATTENTION->(y = Oui, n = Non)\n");
                    scanf("%s", confirm);
                }
                if (strcmp(confirm, "y") == 0) {
                    updateDialogueSettings(0);
                    printf("Le dialogue est maintenant désactivé !\n");
                }
            } else {
                printf("Voulez-vous vraiment activer le dialogue ? (y = Oui, n = Non)\n");
                scanf("%s", confirm);
                while (strcmp(confirm, "y") != 0 && strcmp(confirm, "n") != 0){
                    printf("Voulez-vous vraiment activer le dialogue ?     ATTENTION->(y = Oui, n = Non)\n");
                    scanf("%s", confirm);
                }
                if (strcmp(confirm, "y") == 0) {
                    updateDialogueSettings(1);
                    printf("Le dialogue est maintenant actif !\n");
                }
            }
            menuSettings(user);
            break;
        case 3:
            difficultyMenu();
            menuSettings(user);
            break;
        default:
            printf("Choix invalide\n");
            menuSettings(user);
            break;
    }

    free(confirm);
}