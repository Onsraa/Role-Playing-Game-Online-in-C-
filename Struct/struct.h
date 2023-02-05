#ifndef STRUCT_H_
#define STRUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------DECLARATIONS------------------------------*/

/* CHARACTERS */
typedef struct Character Character;
typedef struct Bag Bag;
typedef struct Item Item;

typedef struct Gears Gears;
typedef struct Weapon Weapon;
typedef struct Armor Armor;

/* ELEMENT */
typedef struct Element Element;

/* SPELLS */
typedef struct Spell Spell;

typedef struct Offensive Offensive;
typedef struct Defensive Defensive;
typedef struct Heal Heal;

/* USERS */
typedef struct User User;

/* -------------------------------------------------------------------------*/

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

void initializeCharacter(User *user);

void chooseClass(User *user);

void addClass(User *user, int selection);

void warriorSelected(Character *character);

void rogueSelected(Character *character);

void archerSelected(Character *character);

void mageSelected(Character *character);

void characterStat(Character *character);

/* ELEMENT */

struct Element
{

    int type;
};

enum elements
{
    FIRE = 1,
    WATER = 2,
    PLANT = 3
};

enum compability
{
    EFFICIENT = 1,
    INEFFECTIVE = 2,
    NONE = 3
};

void initializeElement(Character *character, int element);

int compability(Element *first_element, Element *second_element);

char *numberToElementName(int number);

struct Spell
{

    char *spellName;
    char *description;
    char *valueFactor;
};

struct Offensive
{

    Spell *info;
    Element *element;

    int *damageValue;
    int cost;
};

struct Defensive
{

    Spell *info;
    Element *element;

    int defenseValue;
    int cost;
};

struct Heal
{

    Spell *info;
    Element *element;

    int healingValue;
    int cost;
};

struct User
{

    char *id;
    char *nickname;
    char *password;

    Character **characters; // Array of characters
    int nb_characters;
};

int createUser(char *nickname, char *password);  // Returns success or failure
int connectUser(char *nickname, char *password); // Returns success or failure

void changePassword(char id, char *password);

void userInfo(User *currentUser);

/* MOB */

typedef struct Mob Mob;

struct Mob{

    char *name;
    /*Basic stats*/
    int physicalPower;
    int magicPower;

    int maxHp;     // Static heal point
    int currentHp; // Dynamic heal point

    int maxMp;     // Static heal point
    int currentMp; // Dynamic mana point

    /*Progression*/
    int level;
};

#endif