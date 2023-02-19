#include "../struct.h"

void showAllCharacters(User *user){
    
    if(!user){
        system("clear");
        printf("No user\n");
        exit(EXIT_FAILURE);
    }

    if(!user->characters){
        system("clear");
        printf("Characters array is not allocated\n");
        exit(EXIT_FAILURE);
    }

    if(user->nb_characters > 0){
        printf("Your characters (Number of characters : %d): \n\n", user->nb_characters);
        for(int i = 0; i < user->nb_characters; i++){
            if(user->characters[i]->number == user->used_character){
                printf(COLOR_GREEN_TERMINAL);
            }
            printf("%d : %s [%d]\n" COLOR_RESET_TERMINAL, i + 1, user->characters[i]->className, user->characters[i]->level);
        }puts(" ");
        printf(COLOR_GREEN_TERMINAL "*current character used" COLOR_RESET_TERMINAL);
    }
}

void chooseCharacter(User * user){

    int choice;

    if(user->nb_characters > 0){
        do{
            system("clear");
            showAllCharacters(user);
            puts("\n");
            printf("Choose a character : ");

            if (scanf("%d", &choice) != 1)
            {
                while (fgetc(stdin) != '\n');
            };
        }while(choice < 1 || choice > user->nb_characters);

        user->used_character = choice;
    }else{
        do{
            system("clear");
            printf(COLOR_RED_TERMINAL "You have no character.\n\n" COLOR_RESET_TERMINAL);
            printf("Would you like to create a character? (y)es - (n)o\n\n");

            if (scanf("%c", &choice) != 1)
            {
                while (fgetc(stdin) != '\n');
            };
        }while(choice != 'y' && choice!= 'n');

        switch(choice){
            case 'y':
                initializeNewCharacter(user);
                break;
        }
    }

    character_menu(user);
}

void deleteCharacter(User * user){

    int choice;
    char verification;

    puts(" ");
    do{
        system("clear");
        showAllCharacters(user);
        puts("\n");
        printf("0 - Exit\n\n");
        printf("What character do you want to " COLOR_RED_TERMINAL "delete ?\n\n" COLOR_RESET_TERMINAL);
        if (scanf("%d", &choice) != 1)
        {
            while (fgetc(stdin) != '\n');
        };
    }while(choice < 0 || choice > user->nb_characters);

    system("clear");

    if(choice == 0){
        character_menu(user);
    }else{
        while(verification != 'y' && verification!= 'n'){
            system("clear");
            characterStats(user, user->characters[choice - 1]);
            printf("Are you sure you want to delete this character ? (y)es - (n)o\n\n");
            scanf("%c", &verification);
        };

        switch (verification){

        case 'y':
            cleanCharacter(user, user->characters[choice - 1]);
            break;
        case 'n':
            character_menu(user);
            break;
        }
    }

    character_menu(user);
}

void deleteAllCharacters(User * user){

    char verification;
    
    while(verification != 'y' && verification!= 'n'){
        system("clear");
        showAllCharacters(user);
        puts("\n");
        printf("Are you sure that you want to " COLOR_RED_TERMINAL "delete all the characters ? (y)es - (n)o\n\n" COLOR_RESET_TERMINAL);
        scanf("%c", &verification);
    };

    switch (verification){
    case 'y':
        for(int i = user->nb_characters - 1 ; i >= 0 ; i--){
            cleanCharacter(user, user->characters[i]);
        }
        break;
    case 'n':
        character_menu(user);
        break;
    }
}

void cleanCharacter(User * user, Character * character){

    int number = character->number;

    cleanBag(character);
    cleanGear(character);
    cleanSpells(character);
    
    free(character);
    character = NULL;

    if(number != user->nb_characters && user->nb_characters > 0){
        for(int i = number; i < user->nb_characters; i++){
            user->characters[i]->number--; // Decrease the number of all the characters after the one deleted.
            user->characters[i - 1] = user->characters[i]; // Decrease the position of all the characters after the one deleted.
        }
    }

    if(user->nb_characters == 0){
        user->used_character = 0;
    }else{
        if(user->used_character == number){ // If the character deleted is the current character, unequip it.
            user->used_character = 0;
        }
        else if(user->used_character > number){ // If the character deleted is not the used character and its position is lower, decrement the used_character so it equips the right character.
            user->used_character--;
        }
    }

    user->nb_characters--;
    user->characters = realloc(user->characters, sizeof(Character *) * user->nb_characters);
}

void initializeNewCharacter(User *user){
    
    free(user->characters);
    user->characters = malloc(sizeof(Character *));
    user->used_character = 1;
    chooseNewClass(user);
}

void chooseNewClass(User *user)
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
        printf("Your choice : ");
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

    character_menu(user);
    free(classes);
};

void checkStatus(User *user){
    
    int answer;
    system("clear");
    printf("Number of characters : %d\n", user->nb_characters);
    for(int i = 0 ; i < user->nb_characters; i++){
        printf("number : %d\n", user->characters[i]->number);
    }
    scanf("%d", &answer);
    if(answer == 1){
        character_menu(user);
    }
}

void addClass(User *user, int selection)
{

    if(!user->characters){
        user->characters = malloc(sizeof(Character *));
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

    new_character->isAlive = 1;

    new_character->level = 1;
    new_character->experience = 0;
    new_character->experienceNeededToLevelUp = XP_NEEDED;

    new_character->bag = malloc(sizeof(Bag));
    new_character->bag->weapons = malloc(sizeof(Weapon *));
    new_character->bag->armors = malloc(sizeof(Armor *));
    new_character->bag->nb_weapons = 0;
    new_character->bag->nb_armors = 0;
    
    new_character->gears = malloc(sizeof(Gears));
    new_character->gears->weapon = malloc(sizeof(Weapon));
    new_character->gears->armor = malloc(sizeof(Armor));

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

    new_character->number = user->nb_characters;
    
    user->characters[user->nb_characters - 1] = new_character;

    giveSpells(new_character);
};

void warriorSelected(Character *character)
{

    character->classId = WARRIOR;
    character->className = "Warrior";

    character->physicalPower = 80;
    character->magicalPower = 0;

    character->maxHp = 350;
    character->currentHp = character->maxHp;

    character->maxMp = 300;
    character->currentMp = character->maxMp;
};

void rogueSelected(Character *character)
{

    character->classId = ROGUE;
    character->className = "Rogue";

    character->physicalPower = 200;
    character->magicalPower = 0;

    character->maxHp = 150;
    character->currentHp = character->maxHp;

    character->maxMp = 300;
    character->currentMp = character->maxMp;
};

void archerSelected(Character *character)
{

    character->classId = ARCHER;
    character->className = "Archer";

    character->physicalPower = 150;
    character->magicalPower = 60;

    character->maxHp = 120;
    character->currentHp = character->maxHp;

    character->maxMp = 300;
    character->currentMp = character->maxMp;
};

void mageSelected(Character *character)
{

    character->classId = MAGE;
    character->className = "Mage";

    character->physicalPower = 0;
    character->magicalPower = 200;

    character->maxHp = 110;
    character->currentHp = character->maxHp;

    character->maxMp = 300;
    character->currentMp = character->maxMp;
};

void characterStats(User *user, Character *character){
    
    printf("Name : %s\n", character->className);

    printf("Physical Power : %d\n", character->physicalPower);
    printf("Magic Power : %d\n", character->magicalPower);

    showBars(character);
    
    printf("Level : %d\n", character->level);

    showSpells(character);

    printf("\n");
}

void showBars(Character *character){

    int currentHpBar = character->currentHp * BAR_LENGTH / character->maxHp;
    int currentMpBar = character->currentMp * BAR_LENGTH / character->maxMp;
    
    printf("HP (%d/%d) : ", character->currentHp, character->maxHp);
    printf("[");
    for(int i = 0 ; i < currentHpBar ; i++){
        printf("#");
    }
    for(int i = currentHpBar ; i < BAR_LENGTH ; i++){
        printf(".");
    }
    printf("]");
    puts(" ");
    printf("MP (%d/%d) : ", character->currentMp, character->maxMp);
    printf("[");
    for(int i = 0 ; i < currentMpBar ; i++){
        printf("#");
    }
    for(int i = currentMpBar ; i < BAR_LENGTH ; i++){
        printf(".");
    }
    printf("]");
    puts(" ");
}