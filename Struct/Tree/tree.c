#include "../struct.h"

StartZone *initializeFirstZone()
{

    StartZone *start_zone = malloc(sizeof(StartZone));

    start_zone->nb_stages = NB_STAGES;

    start_zone->first = malloc(sizeof(Zone));
    start_zone->first->zoneName = HOSTS;
    start_zone->first->difficulty = 0;
    start_zone->first->mob = NULL;

    return start_zone;
}

void generateMap(User *user, Character *character, int difficulty, int auto_mode, int dialogue)
{

    int answer;
    int nb_stages = NB_STAGES;

    do
    {
        system("clear");
        puts(" ");
        printf(COLOR_GREEN_TERMINAL "Generating random zones..\n\n" COLOR_RESET_TERMINAL);
        printf("1 - Continue\n\n");
        scanf("%d", &answer);
    } while (answer != 1);

    StartZone *start_zone = initializeFirstZone();

    Zone *current_zone = start_zone->first;

    while (nb_stages > 0)
    {
        if(character->isAlive == 1){
            current_zone->left_way = generateRandomZone(difficulty);
        do
        {
            current_zone->right_way = generateRandomZone(difficulty);
        } while (current_zone->left_way->zoneName == current_zone->right_way->zoneName);

        int answer;

        do
        {
            system("clear");
            printf("You have two ways in front of you. Which one do you take ?\n\n");
            printf("1 - %s\n", printZoneName(current_zone->left_way));
            printf("2 - %s\n\n", printZoneName(current_zone->right_way));

            scanf("%d", &answer);
        } while (answer != 1 && answer != 2);

        switch (answer)
        {
        case 1:
            current_zone = current_zone->left_way;
            break;
        case 2:
            current_zone = current_zone->right_way;
            break;
        }

        actionZone(user, character, current_zone, auto_mode, dialogue);

        nb_stages--;

        }else{
            resetCharacter(character);
            main_menu(user);
        }
    }

    system("clear");

    char final_answer;

    do{
        printf("WOW ! Very impressive...\n\n");
        printf("You just completed %d stages in a row without dying.\n");
        printf("You maybe deserve to fight the best of the best.\n\n");
        printf("Are you ready ? (y/n)\n\n");

        if (scanf("%c", &final_answer) != 1)
        {
            while (fgetc(stdin) != '\n');
        };
    }while(final_answer == 'y' || final_answer == 'n');

    system("clear");

    switch(final_answer){
        case 'y':
            printf("Good, now you're gonna fight the %s Dragon !");
            fight(character, dragon(difficulty), auto_mode, dialogue);
    }

    resetCharacter(character);
}

Zone *generateRandomZone(int difficulty)
{

    int random_map = rand() % NB_ZONES + 1;

    return createZone(random_map, difficulty);
}

Zone *createZone(int zoneName, int difficulty)
{

    Zone *zone = malloc(sizeof(Zone));

    zone->zoneName = zoneName;

    if (zoneName != HOSTS || zoneName != FOUNTAIN)
    {
        zone->mob = generateMob(difficulty);
    }
    else
    {
        zone->mob = NULL;
    }

    zone->left_way = malloc(sizeof(Zone));
    zone->right_way = malloc(sizeof(Zone));

    return zone;
}

char *printZoneName(Zone *zone)
{

    switch (zone->zoneName)
    {
    case HOSTS:
        return "Hosts";
    case FOUNTAIN:
        return "Fountain";
    case DUNGEON:
        return "Dungeon";
    case FALL:
        return "Fall";
    case VOLCANO:
        return "Volcano";
    case FOREST:
        return "Forest";
    }

    return NULL;
}

void actionZone(User *user, Character *character, Zone *zone, int auto_mode, int dialogue)
{

    switch (zone->zoneName)
    {
    case HOSTS:
        hosts(user, character);
        break;
    case FOUNTAIN:
        fountain(character);
        break;
    default:
        fight(character, zone->mob, auto_mode, dialogue);
        break;
    }
}

void hosts(User *user, Character *character)
{

    int answer;
    do
    {
        system("clear");
        printf("You are in the host " COLOR_GREEN_TERMINAL "zone" COLOR_RESET_TERMINAL ". Nothing much happens.\n\n");
        printf("1 - Continue ?\n");
        printf("2 - Quit the dungeon\n\n");

        if (scanf("%d", &answer) != 1)
        {
            while (fgetc(stdin) != '\n')
                ;
        };
    } while (answer != 1 && answer != 2);

    switch (answer)
    {
    case 2:
        main_menu(user);
        break;
    }
}

void fountain(Character *character)
{

    int answer;

    do
    {
        system("clear");
        printf("Do you want to regenerate your life points and your mana ?\n\n");
        printf("1 - Yes\n");
        printf("2 - No\n\n");
        if (scanf("%d", &answer) != 1)
        {
            while (fgetc(stdin) != '\n')
                ;
        };
    } while (answer != 1 && answer != 2);

    switch (answer)
    {
    case 1:
        character->currentHp += character->maxHp * 0.5;
        character->currentMp += character->maxMp;

        character->currentHp = (character->currentHp > character->maxHp) ? character->maxHp : character->currentHp;
        character->currentMp = (character->currentMp > character->maxMp) ? character->maxMp : character->currentMp;

        answer = 0;

        do
        {
            system("clear");
            printf("You regenerated 50 percents of your max hp and all your mp.\n\n");
            showBars(character);
            puts("\n");
            printf("1 - Continue\n\n");
            if (scanf("%d", &answer) != 1)
            {
                while (fgetc(stdin) != '\n')
                    ;
            };
        } while (answer != 1);
        break;
    case 2:
        printf("Oh okay.. you're a tough one huh ?");
        break;
    }
}