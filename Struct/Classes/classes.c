#include "../struct.h"

#define NB_CLASSES 4

enum classes
{
    WARRIOR = 1,
    ROGUE = 2,
    ARCHER = 3,
    MAGE = 4
};

void initializeCharacter(User *user){
    
    user->characters = malloc(sizeof(Character *));
    chooseClass(user);
}

void chooseClass(User *user)
{
    if(!user->characters){
        system("clear");
        printf("An error occurred while initializing the character.");
        exit(EXIT_FAILURE);
    }

    char **classes = malloc(sizeof(char *) * 4);

    classes[0] = "Warrior";
    classes[1] = "Rogue";
    classes[2] = "Archer";
    classes[3] = "Mage";

    int answer;

    do
    {
        system("clear");
        printf("What class do you choose ?");
        puts("\n");
        for (int i = 0; i < NB_CLASSES; i++)
        {
            printf("%d - %s\n", i + 1, classes[i]);
        }
        puts(" ");
        printf("Your choice: ");
        scanf("%d", &answer);
    } while (answer < 1 || answer > NB_CLASSES);

    switch (answer)
    {
    case WARRIOR:
        addClass(user, WARRIOR);
        break;

    case ROGUE:
        addClass(user, ROGUE);
        break;

    case ARCHER:
        addClass(user, ARCHER);
        break;

    case MAGE:
        addClass(user, MAGE);
        break;
    }
};

void addClass(User *user, int selection)
{

    if(!user->characters){
            system("clear");
            printf("An error occurred, the pointer to your characters doesn't exist.");
            exit(EXIT_FAILURE);
    }

    /* Update the size of the array of characters */
    user->nb_characters += 1;

    user->characters = realloc(user->characters, sizeof(Character*) * user->nb_characters);

    if(!user->characters){
            system("clear");
            printf("An error occurred while reallocating your characters array.");
            exit(EXIT_FAILURE);
    }

    Character *new_character = malloc(sizeof(Character));

    if(!new_character){
        system("clear");
        printf("An error occurred while allocating the character.");
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
        break;
    case ROGUE:
        rogueSelected(new_character);
        break;
    case ARCHER:
        archerSelected(new_character);
        break;
    case MAGE:
        mageSelected(new_character);
        break;
    }   
    user->characters[user->nb_characters - 1] = new_character;
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

void characterStat(Character *character){
    
    printf("Name: %s\n", character->className);

    printf("Physical Power: %d\n", character->physicalPower);
    printf("Magic Power: %d\n", character->magicPower);

    printf("HP: %d\n", character->currentHp);
    printf("MP: %d\n", character->currentMp);

    printf("Level: %d\n", character->level);

    printf("\n");
}