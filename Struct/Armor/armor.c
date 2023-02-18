#include "../struct.h"

Armor *generateArmor(int rarity){

    switch(rarity){
        case DIVINE:
            return divineArmor();
            break;
        case LEGENDARY:
            return legendaryArmor();
            break;
        case EPIC:
            return epicArmor();
            break;
        case RARE:
            return rareArmor();
            break;
        case COMMON:
            return commonArmor();
            break;
    }
}

Armor *createArmor(char *name, int bonus_resistance, int rarity, int element)
{
    Armor *armor = malloc(sizeof(Armor));
    armor->name = name;
    armor->bonus_resistance = bonus_resistance;
    armor->rarity = rarity;
    armor->element = malloc(sizeof(Element));
    armor->element->type = element;
    return armor;
}

Armor *divineArmor()
{
    return createArmor("Belzebub's skins", 666, DIVINE, FIRE);
}

Armor *legendaryArmor()
{
    return createArmor("Ancient dragon skin", 80, LEGENDARY, FIRE);
}

Armor *epicArmor()
{
    return createArmor("Shadow cape", 50, EPIC, WATER);
}

Armor *rareArmor()
{
    return createArmor("Ninja tortle's shell", 20, RARE, PLANT);
}

Armor *commonArmor()
{

    return createArmor("Silver chestplate", 10, COMMON, PLANT);
}

Armor *chooseArmor(Character *character)
{

    system("clear");
    puts("\n");

    int nb_armors = character->bag->nb_armors;

    int answer;

    if (nb_armors > 0)
    {

        do
        {
            printf("Your Armors :");

            Armor *current_armor;

            Armor *equipped_armor = character->gears->armor;

            for (int i = 0; i < nb_armors; i++)
            {

                current_armor = character->bag->armors[i];

                if (current_armor->id == equipped_armor->id)
                {
                    printf(COLOR_GREEN);
                }
                printf("%d : %s | %s\n" COLOR_RESET, i + 1, current_armor->name, printRarity(current_armor->rarity));
            }

            printf(COLOR_GREEN "\n* equipped Armor\n\n" COLOR_RESET);
            printf("0 - exit");

        } while (answer < 0 || answer > nb_armors);

        if (answer == 0)
        {
            // Leave
        }
        else
        {

            Armor *choosed_armor = character->bag->armors[answer - 1];
            character->gears->armor = choosed_armor;
        }
    }
    else
    {
        printf(COLOR_RED "You have no Armor.\n" COLOR_RESET);
    }
}