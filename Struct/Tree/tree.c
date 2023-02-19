#include "../struct.h"

/*ZONES*/
/*

#define STARTING_ZONE 1
#define REGENERATION_ZONE 2
#define NB_STAGES 10
#define NB_WAYS 3
#define NB_ZONES 6

enum zones
{
    HOSTS = 1,
    FOUNTAIN = 2,
    DUNGEON = 3,
    FALL = 4,
    VOLCANO = 5,
    FOREST = 6
};
*/

StartZone * initializeFirstZone(){

    StartZone * start_zone = malloc(sizeof(StartZone));
    
    start_zone->nb_stages = NB_STAGES;

    start_zone->first = malloc(sizeof(Zone));
    start_zone->first->zoneName = HOSTS;
    start_zone->first->difficulty = 0;
    start_zone->first->mob = NULL;

    return start_zone;
}

void generateMap(User *user, Character * character, Zone * zone, int difficulty, int auto_mode, int dialogue){

    int answer;
    int nb_stages = NB_STAGES;

    do{
        system("clear");
        puts(" ");
        printf(COLOR_GREEN_TERMINAL "Generating random zones..\n" COLOR_RESET_TERMINAL);
        printf ("1 - Continue");
    }while(answer != 1);

    StartZone * start_zone = initializeFirstZone();

    Zone * current_zone = start_zone->first;

    while(nb_stages > 0){

        current_zone->left_way = generateRandomZone(difficulty);
        current_zone->right_way = generateRandomZone(difficulty);
        
        int answer;

        do{
            system("clear");
            printf("You have two ways in front of you. Which one do you take ?\n\n");
            printf("1 - %s\n", printZoneName(current_zone->left_way));
            printf("2 - %s\n", printZoneName(current_zone->left_way));
            
            scanf("%d", &answer);
        }while(answer!= 1 && answer!= 2);

        switch(answer){
            case 1:
                current_zone = current_zone->left_way;
                break;
            case 2:
                current_zone = current_zone->right_way;
                break;
        }

        actionZone(user, character, current_zone, auto_mode, dialogue);

        nb_stages--;
    }
}

Zone * generateRandomZone(int difficulty){

    int random_map = rand() % NB_ZONES + 1;

    return createZone(random_map, difficulty);
}

Zone * createZone(int zoneName, int difficulty){

    Zone * zone = malloc(sizeof(Zone));

    if(zoneName != HOSTS || zoneName != FOUNTAIN){
        zone->mob = generateMob(difficulty);
    }else{
        zone->mob = NULL;
    }

    zone->left_way = malloc(sizeof(Zone));
    zone->right_way = malloc(sizeof(Zone));

    return zone;
}

char * printZoneName(Zone * zone){

    switch(zone->zoneName){
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

void actionZone(User *user, Character * character, Zone * zone, int auto_mode, int dialogue){

    switch(zone->zoneName){
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

void hosts(User *user, Character * character){

    int answer;
    do{
        system("clear");
        puts(" ");
        printf("You are in the host " COLOR_GREEN_TERMINAL"zone. Nothing much happens.\n\n");
        printf("1 - Continue ?\n");
        printf("2 - Quit the dungeon\n\n");

        scanf("%d", &answer);
    }while(answer == 1 || answer == 2);

    switch(answer){
        case 2:
            character_menu(user);
            break;
    }
}

void fountain(Character * character){

    int answer;

    do{
        system("clear");
        printf("Do you want to regenerate your life points and your mana ?\n\n");
        printf("1 - Yes\n");
        printf("2 - No\n");
    }while(answer != 1 && answer != 2);

    system("clear");

    switch(answer){
        case 1:
            character->currentHp += character->maxHp * 0.5;
            character->currentMp += character->maxMp;

            character->currentHp = (character->currentHp > character->maxHp) ? character->maxHp : character->currentHp;
            character->currentMp = (character->currentMp > character->maxMp) ? character->maxMp : character->currentMp;

            printf("You regenerated 50\% of your max hp and all your mp.");
            showBars(character);
            break;
        case 2:
            printf("Oh okay.. you're a tough one huh ?");
            break;
    }
}