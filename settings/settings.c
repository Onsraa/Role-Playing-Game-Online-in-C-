#include <stdio.h>
#include <json-c/json.h>

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


int getCombatMode(){
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

    return json_object_get_int(combat_mode);

}


int getDialogueMode(){
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


void updateSettings(char* selectedColor , char* selectedDifficulty , char* selectedCombatMode , char* selectedDialogue) {
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

    // update the values
    json_object_set_string(color, selectedColor);
    json_object_set_string(difficulty, selectedDifficulty);
    json_object_set_string(combat_mode, selectedCombatMode);
    json_object_set_string(dialogue, selectedDialogue);

    // write the updated values back to the file
    fp = fopen("settings.json", "w");
    fprintf(fp, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
    fclose(fp);
}
