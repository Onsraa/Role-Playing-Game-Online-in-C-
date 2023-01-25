#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "classes.h"

enum classes
{
    WARRIOR = 1,
    ROGUE = 2,
    ARCHER = 3,
    MAGE = 4
};

void chooseClass(User *user)
{

    char **classes = {"Warrior", "Rogue", "Archer", "Mage"};
    int answer;

    do
    {
        system("clear");
        printf("What class do you choose ?");
        puts("\n");
        for (int i = 0; i < sizeof(classes); i++)
        {
            printf("%d - %s\n", i + 1, classes[i]);
        }
        puts("\n");
        scanf("%d", &answer);
    } while (answer < 1 || answer > sizeof(classes));

    user->characters = malloc(sizeof(Character));

    if(!user->characters){
        system("clear");
        printf("An error occurred while initializing the character.");
        exit(EXIT_FAILURE);
    }

    switch (answer)
    {
    case WARRIOR:
        addClass(user->characters, WARRIOR);

        break;

    case ROGUE:
        addClass(user->characters, ROGUE);
        break;

    case ARCHER:
        addClass(user->characters, ARCHER);
        break;

    case MAGE:
        addClass(user->characters, MAGE);
        break;
    }
};

void addClass(User *user, int selection)
{

    if(!user->characters){ // If no character has been created yet then you malloc first.
        user->characters = malloc(sizeof(Character *));
        user->nb_characters = 1;
    }else{
        user->nb_characters += 1;
        user->characters = realloc(user->characters, sizeof(Character *) * user->nb_characters);
    }

    Character *new_character = malloc(sizeof(Character));

    user->characters[user->nb_characters - 1] = new_character;

    if(!new_character){
        system("clear");
        printf("An error occurred while adding the class.");
        exit(EXIT_FAILURE);
    }

    new_character->level = 0;
    new_character->experience = 0;
    new_character->experienceNeededToLevelUp = 100;

    new_character->bag = NULL;

    switch (selection)
    {
    case WARRIOR:
        warriorSelected(new_character);
    case ROGUE:
        rogueSelected(new_character);
    case ARCHER:
        archerSelected(new_character);
    case MAGE:
        mageSelected(new_character);
    }
};

void warriorSelected(Character *character)
{
    character->className = "Warrior";
    character->physicalPower = 80;
    character->magicPower = 0;

    character->maxHp = 350;
    character->currentHp = character->maxHp;

    character->maxMp = 40;
    character->currentHp = character->maxMp;
};

void rogueSelected(Character *character)
{
    character->className = "Rogue";
    character->physicalPower = 200;
    character->magicPower = 0;

    character->maxHp = 150;
    character->currentHp = character->maxHp;

    character->maxMp = 30;
    character->currentHp = character->maxMp;
};

void archerSelected(Character *character)
{
    character->className = "Archer";
    character->physicalPower = 150;
    character->magicPower = 60;

    character->maxHp = 120;
    character->currentHp = character->maxHp;

    character->maxMp = 80;
    character->currentHp = character->maxMp;
};

void mageSelected(Character *character)
{
    character->className = "Mage";
    character->physicalPower = 0;
    character->magicPower = 200;

    character->maxHp = 110;
    character->currentHp = character->maxHp;

    character->maxMp = 120;
    character->currentHp = character->maxMp;
};
