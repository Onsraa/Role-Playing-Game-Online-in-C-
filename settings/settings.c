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
