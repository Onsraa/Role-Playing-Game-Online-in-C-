#include "../struct.h"

Armor *generateArmor(int rarity)
{

    switch (rarity)
    {
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

void addArmor(Character *character, Armor *armor)
{

    if (!character || !armor)
    {
        system("clear");
        printf("Character or Armor is NULL\n");
        exit(EXIT_FAILURE);
    }

    character->bag->nb_armors++;
    armor->id = character->bag->nb_armors;

    if (!character->bag->armors)
    {
        character->bag->armors = malloc(sizeof(Armor *));
    }
    else
    {
        character->bag->armors = realloc(character->bag->armors, sizeof(Armor *) * character->bag->nb_armors);
    }

    character->bag->armors[character->bag->nb_armors - 1] = armor;
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

    int answer;
    int nb_armors = character->bag->nb_armors;

    Armor *current_armor = malloc(sizeof(Armor));
    Armor *equipped_armor = NULL;

    if (nb_armors > 0)
    {

        do
        {
            printf("Your armors : \n\n");

            if (character->gears->armor)
            {
                equipped_armor = character->gears->armor;
            }

            for (int i = 0; i < nb_armors; i++)
            {

                current_armor = character->bag->armors[i];

                if (equipped_armor)
                {
                    if (current_armor->id == equipped_armor->id)
                        ;
                    {
                        printf(COLOR_GREEN_TERMINAL);
                    }
                }

                printf("%d : %s | %s\n" COLOR_RESET_TERMINAL , i + 1, current_armor->name, printRarity(current_armor->rarity));
            }

            printf(COLOR_GREEN_TERMINAL "\n* equipped Armor\n\n" COLOR_RESET_TERMINAL);
            printf("0 - exit\n\n");

            scanf("%d", &answer);

        } while (answer < 0 || answer > nb_armors);

        if (answer == 0)
        {
            // Leave
        }else if(equipped_armor){
            if(character->bag->armors[answer - 1]->id == equipped_armor->id){
                character->gears->armor = NULL;
            }else{
                Armor *choosed_armor = character->bag->armors[answer - 1];
                character->gears->armor = choosed_armor;
            }
        }else{
            Armor *choosed_armor = character->bag->armors[answer - 1];
            character->gears->armor = choosed_armor;
        }
    }
    else
    {
        printf(COLOR_RED_TERMINAL "You have no armor.\n" COLOR_RESET_TERMINAL);
    }
}