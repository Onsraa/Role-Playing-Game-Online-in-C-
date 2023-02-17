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
