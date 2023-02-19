#include "../struct.h"

Weapon *generateWeapon(int rarity)
{

    switch (rarity)
    {
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

void addWeapon(Character *character, Weapon *weapon)
{

    if (!character || !weapon)
    {
        system("clear");
        printf("Character or Weapon is NULL\n");
        exit(EXIT_FAILURE);
    }

    character->bag->nb_weapons++;

    weapon->id = character->bag->nb_weapons;

    if (!character->bag->weapons)
    {
        character->bag->weapons = malloc(sizeof(Weapon *));
    }
    else
    {
        character->bag->weapons = realloc(character->bag->weapons, sizeof(Weapon *) * character->bag->nb_weapons);
    }

    character->bag->weapons[character->bag->nb_weapons - 1] = weapon;
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

    int answer;
    int nb_weapons = character->bag->nb_weapons;

    Weapon *current_weapon = malloc(sizeof(Weapon));
    Weapon *equipped_weapon = NULL;

    if (nb_weapons > 0)
    {

        do
        {
            printf("Your weapons : \n\n");
            printf(COLOR_RED_TERMINAL "(To equip, enter the number | To unequip, enter the number of the current gear equipped)\n\n" COLOR_RESET_TERMINAL);

            if (character->gears->weapon)
            {
                equipped_weapon = character->gears->weapon;
            }

            for (int i = 0; i < nb_weapons; i++)
            {

                current_weapon = character->bag->weapons[i];

                if (equipped_weapon)
                {
                    if (current_weapon->id == equipped_weapon->id)
                        ;
                    {
                        printf(COLOR_GREEN_TERMINAL);
                    }
                }

                printf("%d : %s | %s\n" COLOR_RESET_TERMINAL, i + 1, current_weapon->name, printRarity(current_weapon->rarity));
            }

            printf(COLOR_GREEN_TERMINAL "\n* equipped weapon\n\n" COLOR_RESET_TERMINAL);
            printf("0 - exit\n\n");

            scanf("%d", &answer);

        } while (answer < 0 || answer > nb_weapons);

        if (answer == 0)
        {
            // Leave
        }
        else if (equipped_weapon)
        {
            if (character->bag->weapons[answer - 1]->id == equipped_weapon->id)
            {
                character->gears->weapon = NULL;
            }
            else
            {
                Weapon *choosed_weapon = character->bag->weapons[answer - 1];
                character->gears->weapon = choosed_weapon;
            }
        }
        else
        {
            Weapon *choosed_weapon = character->bag->weapons[answer - 1];
            character->gears->weapon = choosed_weapon;
        }
    }
    else
    {
        printf(COLOR_RED_TERMINAL "You have no weapon.\n" COLOR_RESET_TERMINAL);
    }
}