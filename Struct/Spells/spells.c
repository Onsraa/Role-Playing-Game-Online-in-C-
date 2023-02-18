#include "../struct.h"

enum spell
{
    OFFENSIVE = 1,
    HEAL = 2,
    PASSIVE = 3
}; // Passive spell is not implemented yet.

void showSpells(Character *character)
{

    if (!character)
    {
        printf("Character not found.\n");
        exit(EXIT_FAILURE);
    }
    
    printf("SPELLS : \n\n");

    for (int i = 0; i < NB_SPELLS; i++)
    {   
        printf("%d : %s | %s | [%d]\n", i + 1, character->spells[i]->spellName, character->spells[i]->description, character->spells[i]->cost);
    }
}

void giveSpells(Character *character)
{

    if (!character)
    {
        system("clear");
        printf("Error, character is not allocated.");
        exit(EXIT_FAILURE);
    }

    if (!character->spells)
    {
        character->spells = malloc(sizeof(Spell *) * 2); // Allocate memory for offensive and heal spells.
    }

    switch (character->classId)
    {

    case WARRIOR:
        warriorSpells(character);
        break;
    case ROGUE:
        rogueSpells(character);
        break;
    case ARCHER:
        archerSpells(character);
        break;
    case MAGE:
        mageSpells(character);
        break;
    }
}

Spell *generateSpell(char *spellName, char *description, int valueFactor, int value, int cost, int element)
{

    Spell *spell = malloc(sizeof(Spell));

    spell->spellName = spellName;
    spell->description = description;
    spell->valueFactor = valueFactor;
    spell->value = value;
    spell->cost = cost;

    spell->element = malloc(sizeof(Element));
    spell->element->type = element;

    return spell;
}

void warriorSpells(Character *character)
{ // OFFENSIVE and HEAL for WARRIOR

    character->spells[0] = generateSpell("Swing of Heaven", "Powerful swing.", STATIC, 70, 25, PLANT);
    character->spells[1] = generateSpell("Painless recovery", "Recover health slowly.", RATIO, 15, 40, PLANT);
}

void rogueSpells(Character *character)
{ // OFFENSIVE and HEAL for ROGUE

    character->spells[0] = generateSpell("Sneaky stap of the snake", "Shhhh.", RATIO, 40, 30, FIRE);
    character->spells[1] = generateSpell("Bandages of the poor guy", "Doesn't heal that much but it will do the job.", STATIC, 50, 10, PLANT);
}
void archerSpells(Character *character)
{ // OFFENSIVE and HEAL for ARCHER

    character->spells[0] = generateSpell("Rain of arrows", "Too much arrows.", STATIC, 110, 50, WATER);
    character->spells[1] = generateSpell("Second life", "Like a cat, he has many lives", RATIO, 70, 100, PLANT);
}
void mageSpells(Character *character)
{ // OFFENSIVE and HEAL for MAGE

    character->spells[0] = generateSpell("Mega giga extra fireball", "Strongest fireball in the world.", STATIC, 200, 70, FIRE);
    character->spells[1] = generateSpell("Pact with the devil", "Devil gives you more time to live so he can take your soul later.", STATIC, 140, 50, FIRE);
}

void cleanSpells(Character *character){

    for(int i = 0; i < NB_SPELLS; i++){
        free(character->spells[i]->spellName);
        free(character->spells[i]->description);
        free(character->spells[i]->element);
        free(character->spells[i]);
    }
}