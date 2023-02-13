#ifndef STRUCT_H_
#define STRUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

    /*Bag that contains equipments, weapons and armors*/
    Bag *bag;

    /*Equipment*/
    Gears *gears; // Define the gear equipped.

    /*State*/
    int isAlive;
};

struct Bag
{

    Weapon **weapons;
    Armor **armors;

    int nb_weapons;
    int nb_armors;
};

struct Gears
{

    Weapon *weapon;
    Armor *armor;
};

struct Weapon{

    char * name;
    int bonus_damage;
    
    Element * element;
};

struct Armor{

    char *name;
    int bonus_resistance;

    Element * element;
}

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

void initializeElement(Character *character, int element);

int compability(Element *first_element, Element *second_element);

char *numberToElementName(int number);

/* SPELLS */

struct Spell
{

    char *spellName;
    char *description;
    
    char *valueFactor;
    int value;

    int cost;
    int type;

    Element *element;

};

void showSpells(Character *character);

/* USERS */

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

    /*State*/
    int isAlive;
};

/* ACTIONS */

void fight(Character *character, Mob *mob, int auto_mode);

void hit(Character *character, Mob *mob);

#endif