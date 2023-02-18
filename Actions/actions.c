#include "../Struct/struct.h"

enum action
{
    BASIC_ATTACK = 1,
    OFFENSIVE = 2,
    HEAL = 3
};

enum gearState
{
    EQUIPPED = 1,
    STORED = 0
};

void gainXp(Character *character, Mob *mob){

    int xp_gained = XP_GAINED * mob->level;

    printf("You gained %d XP\n\n", xp_gained);

    character->experience += xp_gained;

    if(character->experience >= character->experienceNeededToLevelUp){
        levelUp(character);
    }
}

void levelUp(Character *character){

    character->experience = 0;
    character->experienceNeededToLevelUp *= 1.5;
    character->level++;

    printf("You leveled up ! You are now level %d\n\n", character->level);
}

void fight(Character *character, Mob *mob, int auto_mode, int dialogue)
{

    system("clear");
    int rounds = 0;
    puts(" ");
    printf("##########################################");
    puts(" ");
    printf("\tFight: %s VS %s", character->className, mob->name);
    puts(" ");
    printf("##########################################");

    puts(" ");
    switch (auto_mode)
    {
    case 0:

        break;
    case 1:
        while (character->isAlive && mob->isAlive)
        {   
            puts(" ");
            printf("\tROUND N°%d\n\n", rounds);
            switch (rounds % 2)
            {
            case 0:
                players_turn(character, mob, dialogue);
                break;
            case 1:
                mobs_turn(mob, character, dialogue);
                break;
            }
            showFightStates(character, mob);
            regenerateMana(character);
            printf("--------------------------------------------------------------\n");
            ++rounds;
        }
        break;
    }

    if(character->isAlive){
        printf("You won against the %s !", mob->name);
        gainXp(character, mob);
        dropStuff(character, mob);
    }else{
        printf("You died against the %s.", mob->name);
    }
    puts(" ");
}

void players_turn(Character *character, Mob *mob, int dialogue)
{

    if (!character || !mob)
    {
        system("clear");
        printf("Character or mob don't exist.");
        exit(EXIT_FAILURE);
    }

    int total_damage = character->physicalPower + character->magicalPower;

    if (character->gears && character->gears->weapon)
    { // Check if a weapon is equipped.
        switch (compability(character->element, character->gears->weapon->element))
        { // Check element compability between weapon and character.

        case 1: // Character's element is efficient against the weapon so it changes nothing.
            total_damage += character->gears->weapon->bonus_damage;
            break;
        case 2: // Weapon's element is efficient against the character so it gives mallus.
            if (dialogue)
            {
                printf("The character struggles to handle a weapon of the opposite element : mallus !\n");
            }
            total_damage += character->gears->weapon->bonus_damage * 0.7;
            break;
        case 3: // Same element weapon and character so bingo.
            if (dialogue)
            {
                printf("Compability between weapon and character : bonus damage !\n");
            }
            total_damage += character->gears->weapon->bonus_damage * 2;
            break;
        }
    }

    Spell *offensive_spell = character->spells[0];
    Spell *healing_spell = character->spells[1];

    switch (fightAlgorithm(character, mob))
    {
    case 1: // BASIC ATTACK
        mob->currentHp -= total_damage;

        if (dialogue)
        {
            printf("You hit the %s for %d with your basic attack !\n", mob->name, total_damage);
        }

        break;
    case 2: // OFFENSIVE ATTACK

        character->currentMp -= character->spells[0]->cost;

        if(character->currentMp < 0){
           character->currentMp = 0; 
        }

        if (character->spells[0]->valueFactor = STATIC)
        {
            total_damage += offensive_spell->value;
        }
        else
        {
            total_damage *= offensive_spell->value;
        }

        mob->currentHp -= total_damage;

        if (dialogue)
        {
            printf("You used your offensive spell ! The %s, it hits for %d !\n", offensive_spell->spellName, total_damage);
        }

        break;
    case 3: // HEALING

        character->currentMp -= character->spells[1]->cost;

        if(character->currentMp < 0){
           character->currentMp = 0; 
        }

        if (character->spells[1]->valueFactor = STATIC)
        {
            total_damage += healing_spell->value;
        }
        else
        {
            total_damage *= healing_spell->value;
        }

        character->currentHp += total_damage;

        if (dialogue)
        {
            printf("You healed yourself for %d with the %s !\n\n", total_damage, healing_spell->spellName);
        }
        break;
    }

    if(mob->currentHp <= 0){
        mob->isAlive = 0;
    }
}

void mobs_turn(Mob *mob, Character *character, int dialogue)
{

    if (!character || !mob)
    {
        system("clear");
        printf("Character or mob don't exist.");
        exit(EXIT_FAILURE);
    }

    int total_damage = mob->physicalPower + mob->magicalPower;

    if (dialogue)
    {
        printf("The %s hits you for %d !\n", mob->name, total_damage, character->currentHp, character->maxHp);
    }
    character->currentHp -= total_damage;

    if(character->currentHp <= 0){
        character->isAlive = 0;
    }
}

int fightAlgorithm(Character *character, Mob *mob)
{

    if (!character)
    {
        printf("No character.");
        exit(EXIT_FAILURE);
    }

    int isLow = (character->currentHp <= character->maxHp * 0.3) ? 1 : 0; // State to know if the character is low in hp or not (>30% hp).

    int basic_attack_damage = character->physicalPower + character->magicalPower;

    if (basic_attack_damage >= mob->currentHp)
    { // If the character only needs to hit once to kill the mob, then it returns the action.
        return BASIC_ATTACK;
    }

    Spell *offensive_spell = character->spells[0];
    Spell *healing_spell = character->spells[1];

    switch (isLow)
    {
    case 0:
        if (character->currentMp >= offensive_spell->cost)
        { // Check if we have enough mana to cast an offensive.
            return OFFENSIVE;
        }
        break;
    case 1:
        if (character->currentMp >= healing_spell->cost)
        { // Check if we have enough mana to cast a heal.
            return HEAL;
        }
        break;
    }

    return BASIC_ATTACK;
}

void showFightStates(Character *character, Mob *mob){

    printf("You :\n");
    showBars(character);
    puts(" ");
    printf("The %s : \n", mob->name);

    int currentHpBar = mob->currentHp * BAR_LENGTH / mob->maxHp;
    
    printf("HP (%d/%d) : ", mob->currentHp, mob->maxHp);
    printf("[");
    for(int i = 0 ; i < currentHpBar ; i++){
        printf("#");
    }
    for(int i = currentHpBar ; i < BAR_LENGTH ; i++){
        printf(" ");
    }
    printf("]");
    puts(" ");
}

void regenerateMana(Character * character){

    character->currentMp *= MANA_REGEN_RATIO;

    if(character->currentMp > character->maxMp){
        character->currentMp = character->maxMp;
    }
}

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

    switch(weapon_or_armor){
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

void dropBoth(Character *character, int weapon_rarity, int armor_rarity){
    
    printf("You just dropped both armor and weapon !\n\n");
    dropWeapon(character, weapon_rarity);
    dropArmor(character, armor_rarity);
};

void dropWeapon(Character *character, int weapon_rarity){

    char answer;

    Weapon * dropped_weapon = generateWeapon(weapon_rarity);

    do{

        printf("You dropped a weapon !\n\n" COLOR_GREEN_TERMINAL  "The %s, [%d] | %s\n\n" COLOR_RESET_TERMINAL , dropped_weapon->name, dropped_weapon->bonus_damage, printRarity(dropped_weapon->rarity));
        printf("Do you want to add it in your bag ? (y)es - (n)o \n\n");

        if (scanf("%c", &answer) != 1)
		{
			while (fgetc(stdin) != '\n');
		};
    }while(answer != 'y' && answer != 'n');

    switch(answer){
        case 'y':
            addWeapon(character, dropped_weapon);
            break;
        case 'n':
            free(dropped_weapon);
            break;
    }

};

void dropArmor(Character *character, int armor_rarity){

    char answer;

    Armor * dropped_armor = generateArmor(armor_rarity);

    do{

        printf("You dropped an armor !\n\n" COLOR_GREEN_TERMINAL  "The %s, [%d] | %s\n\n" COLOR_RESET_TERMINAL , dropped_armor->name, dropped_armor->bonus_resistance, printRarity(dropped_armor->rarity));
        printf("Do you want to add it in your bag ? (y)es - (n)o \n\n");
        
        if (scanf("%c", &answer) != 1)
		{
			while (fgetc(stdin) != '\n');
		};
    }while(answer != 'y' && answer != 'n');

    switch(answer){
        case 'y':
            addArmor(character, dropped_armor);
            break;
        case 'n':
            free(dropped_armor);
            break;
    }
};
