//
// Created by Clarence Hirsch on 19/02/2023.
//


#ifndef ROLE_PLAYING_GAME_ONLINE_IN_C_SETTINGS_H
#define ROLE_PLAYING_GAME_ONLINE_IN_C_SETTINGS_H

//depreciated
void updateSettings( char* selectedDifficulty , char* selectedCombatMode , char* selectedDialogue);


void readSettings();
int getDifficulty();
void updateDifficulty(int newDifficulty);
int getCombatMode();
int getDialogueMode();
void updateDialogueSettings(int newDialog);
void updateCombatMode(int newCombatMode);
void printSettings();
int printDifficulty();
void difficultyMenu();
void menuSettings();






#endif //ROLE_PLAYING_GAME_ONLINE_IN_C_SETTINGS_H
