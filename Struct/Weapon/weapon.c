#include "../struct.h"

Weapon *generateWeapon(int rarity){

    switch(rarity){
        case DIVINE:
            return divineWeapon();
            break;
        case LEGENDARY:
            return legendaryWeapon();
            break;
        case EPIC:
            return epicWeapon();
            break;
        case RARE:
            return rareWeapon();
            break;
        case COMMON:
            return commonWeapon();
            break;
    }
}

Weapon *createWeapon(char *name, int bonus_damage, int rarity, int element)
{
    Weapon *weapon = malloc(sizeof(Weapon));
    weapon->name = name;
    weapon->bonus_damage = bonus_damage;
    weapon->rarity = rarity;
    weapon->element = malloc(sizeof(Element));
    weapon->element->type = element;
    return weapon;
}

Weapon *divineWeapon()
{
    return createWeapon("God's thunder", 999, DIVINE, FIRE);
}

Weapon *legendaryWeapon()
{
    return createWeapon("Wukong's staff", 120, LEGENDARY, PLANT);
}

Weapon *epicWeapon()
{
    return createWeapon("Axe of death", 80, EPIC, WATER);
}

Weapon *rareWeapon()
{
    return createWeapon("Wand of Potter", 40, RARE, FIRE);
}

Weapon *commonWeapon()
{

    return createWeapon("Wood stick", 10, COMMON, PLANT);
}

char *printRarity(int rarity)
{

    switch (rarity)
    {
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

Weapon *chooseWeapon(Character *character)
{

    system("clear");
    puts("\n");

    int nb_weapons = character->bag->nb_weapons;

    int answer;

    if (nb_weapons > 0)
    {

        do
        {
            printf("Your weapons :");

            Weapon *current_weapon;

            Weapon *equipped_weapon = character->gears->weapon;

            for (int i = 0; i < nb_weapons; i++)
            {

                current_weapon = character->bag->weapons[i];

                if (current_weapon->id == equipped_weapon->id)
                {
                    printf(COLOR_GREEN);
                }
                printf("%d : %s | %s\n" COLOR_RESET, i + 1, current_weapon->name, printRarity(current_weapon->rarity));
            }

            printf(COLOR_GREEN "\n* equipped weapon\n\n" COLOR_RESET);
            printf("0 - exit");

        } while (answer < 0 || answer > nb_weapons);

        if (answer == 0)
        {
            // Leave
        }
        else
        {

            Weapon *choosed_weapon = character->bag->weapons[answer - 1];
            character->gears->weapon = choosed_weapon;
        }
    }
    else
    {
        printf(COLOR_RED "You have no weapon.\n" COLOR_RESET);
    }
}