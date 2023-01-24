#ifndef CLASSES_H_
#define CLASSES_H_
#include "../Element/element.h"
#include "../Spells/spells.h"
#include "../Users/users.h"

typedef struct Character Character;

typedef struct Bag Bag;
typedef struct Item Item;

typedef struct Gears Gears;
typedef struct Weapon Weapon;
typedef struct Armor Armor;


struct Character
{

    char *className;

    /*Basic stats*/
    int physicalPower;
    int magicPower;

    int maxHp;     // Static heal point
    int currentHp; // Dynamic heal point

    int maxMp;     // Static heal point
    int currentMp; // Dynamic mana point


    /*Progression*/
    int level;
    int experience;
    int experienceNeededToLevelUp; 

    /*Faculties*/
    Element *element; // Define the element
    Spell *spells;    // Array of spell

    /*Bag that contains equipments and items*/
    Bag *bag;

    /*Equipment*/
};

struct Bag
{

    Item **items;
    Gears *gears;
};

struct Gears
{

    Weapon *weapon;
    Armor *armor;
};

void chooseClass();

void addClass(User *user, int selection);

void warriorSelected(Character *character);

void rogueSelected(Character *character);

void archerSelected(Character *character);

void mageSelected(Character *character);

#endif
