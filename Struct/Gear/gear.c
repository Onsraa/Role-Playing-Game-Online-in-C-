#include "../struct.h"

int generateRarity()
{

    int drop_rate = rand() % 100;

    if (drop_rate <= DIVINE_DROP_RATE)
    {
        return DIVINE;
    }
    else if (drop_rate <= LEGENDARY_DROP_RATE)
    {

        return LEGENDARY;
    }
    else if (drop_rate <= EPIC_DROP_RATE)
    {

        return EPIC;
    }
    else if (drop_rate <= RARE_DROP_RATE)
    {

        return RARE;
    }
    else
    {

        return COMMON;
    }
}

void dropStuff(Character *character, Mob *mob)
{
    puts("\n");

    int weapon_or_armor = (int)rand() % 3;
    int weapon_rarity = generateRarity();
    int armor_rarity = generateRarity();

    switch (weapon_or_armor)
    {
    case WEAPON:
        dropWeapon(character, weapon_rarity);
        break;
    case ARMOR:
        dropArmor(character, armor_rarity);
        break;
    case BOTH:
        dropBoth(character, weapon_rarity, armor_rarity);
        break;
    }
}

void dropBoth(Character *character, int weapon_rarity, int armor_rarity)
{

    printf("You just dropped both armor and weapon !\n\n");
    dropWeapon(character, weapon_rarity);
    dropArmor(character, armor_rarity);
};

void dropWeapon(Character *character, int weapon_rarity)
{

    char answer;

    Weapon *dropped_weapon = generateWeapon(weapon_rarity);

    do
    {

        printf("You dropped a weapon !\n\n" COLOR_GREEN_TERMINAL "The %s, [%d] | %s\n\n" COLOR_RESET_TERMINAL, dropped_weapon->name, dropped_weapon->bonus_damage, printRarity(dropped_weapon->rarity));
        printf("Do you want to add it in your bag ? (y)es - (n)o \n\n");

        if (scanf("%c", &answer) != 1)
        {
            while (fgetc(stdin) != '\n')
                ;
        };
    } while (answer != 'y' && answer != 'n');

    switch (answer)
    {
    case 'y':
        addWeapon(character, dropped_weapon);
        break;
    case 'n':
        free(dropped_weapon);
        break;
    }
};

void dropArmor(Character *character, int armor_rarity)
{

    char answer;

    Armor *dropped_armor = generateArmor(armor_rarity);

    do
    {

        printf("You dropped an armor !\n\n" COLOR_GREEN_TERMINAL "The %s, [%d] | %s\n\n" COLOR_RESET_TERMINAL, dropped_armor->name, dropped_armor->bonus_resistance, printRarity(dropped_armor->rarity));
        printf("Do you want to add it in your bag ? (y)es - (n)o \n\n");

        if (scanf("%c", &answer) != 1)
        {
            while (fgetc(stdin) != '\n')
                ;
        };
    } while (answer != 'y' && answer != 'n');

    switch (answer)
    {
    case 'y':
        addArmor(character, dropped_armor);
        break;
    case 'n':
        free(dropped_armor);
        break;
    }
};

void showBag(User *user, Character *character)
{

    if (!character)
    {
        system("clear");
        printf("Character not found\n");
        exit(EXIT_FAILURE);
    }

    if (!character->bag)
    {
        system("clear");
        printf("Bag not found\n");
        exit(EXIT_FAILURE);
    }

    if (!user->used_character)
    {

        char agree;

        do
        {
            system("clear");
            printf("Select a character first. (o)k\n\n");
            if (scanf("%c", &agree) != 1)
            {
                while (fgetc(stdin) != '\n')
                    ;
            };
        } while (agree != 'o');

        character_menu(user);
    }
    else
    {
        int answer;

        if (character->bag->nb_weapons == 0 && character->bag->nb_armors == 0)
        {
            do
            {
                system("clear");
                printf(COLOR_RED_TERMINAL "Bag is empty\n" COLOR_RESET_TERMINAL);
                puts(" ");

                printf("1 - Leave\n\n");

                if (scanf("%d", &answer) != 1)
                {
                    while (fgetc(stdin) != '\n')
                        ;
                };
            } while (answer != 1);

            switch (answer)
            {
            case 1:
                character_menu(user);
                break;
            }
        }
        else
        {
            do
            {
                if (!character->bag->nb_weapons == 0)
                {
                    printf("[");
                    for (int i = 0; i < character->bag->nb_weapons; i++)
                    {
                        printf("%s ", character->bag->weapons[i]->name);
                        if (i < character->bag->nb_weapons - 1)
                        {
                            printf(", ");
                        }
                    }
                    printf("]\n");
                }
                else
                {
                    printf(COLOR_RED_TERMINAL "\nYou don't have weapon.\n" COLOR_RESET_TERMINAL);
                }
                if (!character->bag->nb_armors == 0)
                {
                    printf("[");
                    for (int i = 0; i < character->bag->nb_armors; i++)
                    {
                        printf("%s ", character->bag->armors[i]->name);
                        if (i < character->bag->nb_armors - 1)
                        {
                            printf(", ");
                        }
                    }
                    printf("]\n");
                }
                else
                {
                    printf(COLOR_RED_TERMINAL "\nYou don't have armor.\n" COLOR_RESET_TERMINAL);
                }
                puts(" ");

                printf("1 - Check weapons\n");
                printf("2 - Check armors\n");
                printf("3 - Leave\n");

                if (scanf("%d", &answer) != 1)
                {
                    while (fgetc(stdin) != '\n')
                        ;
                };
            } while (answer != 1 && answer != 2 && answer != 3);

            switch (answer)
            {
            case 1:
                chooseWeapon(character);
                break;
            case 2:
                chooseArmor(character);
                break;
            case 3:
                character_menu(user);
                break;
            }
        }
    }
}

void cleanBag(Character *character)
{

    for (int i = 0; i < character->bag->nb_weapons; i++)
    {   
        free(character->bag->weapons[i]->element);
        character->bag->weapons[i]->element = NULL;
        free(character->bag->weapons[i]);
        character->bag->weapons[i] = NULL;
    }

    for (int i = 0; i < character->bag->nb_armors; i++)
    {
        free(character->bag->armors[i]->element);
        character->bag->armors[i]->element = NULL;
        free(character->bag->armors[i]);
        character->bag->armors[i]= NULL;
    }

    free(character->bag);
    character->bag = NULL;

}
void cleanGear(Character *character)
{

    free(character->gears->weapon);
    free(character->gears->armor);
    free(character->gears);

    character->gears->weapon = NULL;
    character->gears->armor = NULL;
    character->gears = NULL;
}