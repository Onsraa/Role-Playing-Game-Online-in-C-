#include "../struct.h"

#define NB_WEAPONS 5

#define COMMON_DROP_RATE 44 // %
#define RARE_DROP_RATE  25// %
#define EPIC_DROP_RATE 20 // %
#define LEGENDARY_DROP_RATE 10 // %
#define DIVINE_DROP_RATE 1 // %

enum weapons {COMMON = 1, RARE = 2, EPIC = 3, LEGENDARY = 4, DIVINE = 5};

Weapon * generateWeapon(){

    srand(time(NULL));

    int drop_rate = rand() % 100;

    if(drop_rate <= DIVINE_DROP_RATE){
    
    }else if(drop_rate <= LEGENDARY_DROP_RATE){

    }else if(drop_rate <= EPIC_DROP_RATE){

    }else if(drop_rate <= RARE_DROP_RATE){

    }else{

    }
}

void dropStuff(Character *character, Mob *mob)
{
    
}

Weapon * divine(){
    
}
Weapon * legendary(){
    
}
Weapon * epic(){

}
Weapon * rare(){
    
}
Weapon * commun(){
    
}

Weapon * chooseWeapon(Character * character){

    system("clear");
    puts("\n");

    int nb_weapons = character->bag->nb_weapons;

    int answer;

    if(nb_weapons > 0){

        do{
            printf("Your weapons :");

            Weapon * current_weapon;

            Weapon * equipped_weapon = character->gears->weapon;

            for (int i = 0 ; i < nb_weapons ; i++){

                current_weapon = character->bag->weapons[i];

                if(current_weapon->id == equipped_weapon->id){
                    printf(COLOR_GREEN);
                }
                printf("%d : %s | %s\n" COLOR_RESET, i + 1, current_weapon->name, printRarity(current_weapon->rarity));
            }

            printf(COLOR_GREEN "\n* equipped weapon\n\n" COLOR_RESET);
            printf("0 - exit");


        }while(answer < 0 || answer > nb_weapons);

        if(answer == 0){
            //Leave
        }else{

            Weapon * choosed_weapon = character->bag->weapons[answer - 1];
            character->gears->weapon = choosed_weapon;
        }


    }else{
        printf(COLOR_RED "You have no weapon.\n" COLOR_RESET);
    }
}

char * printRarity(int rarity){

    switch(rarity){
        case DIVINE:
            return "Divine";
        case LEGENDARY:
            return "Legendary";
        case EPIC:
            return "Epic";
        case RARE:
            return "Rare";
        case COMMON:
            return "Common";
        
    }
}
