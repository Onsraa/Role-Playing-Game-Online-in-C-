#include "../struct.h"

Weapon *generateWeapon(char *name, int bonus_damage, int rarity, int element)
{

    Weapon *weapon = malloc(sizeof(Weapon));

    weapon->name = name;
    weapon->bonus_damage = bonus_damage;
    weapon->rarity = rarity;

    weapon->element = malloc(sizeof(Element));
    weapon->element->type = element;

    return weapon;
};

Weapon *divine(Character *character)
{

    return generateWeapon("God's thunder", 999, DIVINE, FIRE);
}

Weapon *legendary(Character *character)
{

    return generateWeapon("Wukong's staff", 120, LEGENDARY, PLANT);
}

Weapon *epic(Character *character)
{

    return generateWeapon("Axe of death", 80, EPIC, WATER);
}

Weapon *rare(Character *character)
{

    return generateWeapon("Wand of Potter", 40, RARE, FIRE);
}

Weapon *common()
{

    return generateWeapon("Wood stick", 10, COMMON, PLANT);
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
