#ifndef STRUCT_H_
#define STRUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ------------------------------GLOBAL VALUES------------------------------*/

/*COLORS*/
#define COLOR_RESET "\x1b[0m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"

/*INTERFACES*/
#define BAR_LENGTH 40

/*CLASSES-CHARACTERS*/
#define NB_CLASSES 4

enum classes
{
    WARRIOR = 1,
    ROGUE = 2,
    ARCHER = 3,
    MAGE = 4
};

/*ELEMENTS*/

enum elements
{
    FIRE = 1,
    WATER = 2,
    PLANT = 3
};

/*SPELLS*/
#define NB_SPELLS 2

/*MOBS*/
#define NB_MOBS 4
#define BOSS_POSITION 0

/*ACTION*/
#define MANA_REGEN_RATIO 1.2

/*BAGS, STUFFS, DROPS, GEARS*/
#define NB_WEAPONS 5

#define COMMON_DROP_RATE 44    // %
#define RARE_DROP_RATE 25      // %
#define EPIC_DROP_RATE 20      // %
#define LEGENDARY_DROP_RATE 10 // %
#define DIVINE_DROP_RATE 1     // %

enum weapon_or_armor
{
    WEAPON = 0,
    ARMOR = 1,
    BOTH = 2
};

enum rarity
{
    COMMON = 1,
    RARE = 2,
    EPIC = 3,
    LEGENDARY = 4,
    DIVINE = 5
};

/*ZONES*/

#define REGENERATION_ZONE 6
#define STARTING_ZONE 5

enum zones
{
    VOLCANO = 1,
    FOREST = 2,
    DUNGEON = 3,
    FALL = 4,
    HOSTS = 5,
    FOUNTAIN = 6
};

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

/* MOBS */
typedef struct Mob Mob;

/* -------------------------------------------------------------------------*/

struct Character
{

    int classId; // Determine the class number.

    char *className;

    /*Basic stats*/
    int physicalPower;
    int magicalPower;

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
    Spell **spells;   // Array of spells

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

char *printRarity(int rarity);
void dropStuff(Character *character, Mob *mob);

/*WEAPONS*/
struct Weapon
{

    int id;

    char *name;

    int bonus_damage;

    int rarity;

    Element *element;
};

Weapon *generateWeapon(int rarity);
Weapon *chooseWeapon(Character *character);

Weapon *divineWeapon();
Weapon *legendaryWeapon();
Weapon *epicWeapon();
Weapon *rareWeapon();
Weapon *commonWeapon();

/*ARMORS*/
struct Armor
{

    int id;

    char *name;

    int bonus_resistance;

    int rarity;

    Element *element;
};

Armor *generateArmor(int rarity);
Armor *chooseArmor(Character *character);

Armor *divineArmor();
Armor *legendaryArmor();
Armor *epicArmor();
Armor *rareArmor();
Armor *commonArmor();

void dropBoth(Character *character, int weapon_rarity, int armor_rarity);
void dropWeapon(Character *character, int weapon_rarity);
void dropArmor(Character *character, int armor_rarity);

void initializeCharacter(User *user);

void chooseClass(User *user);

void addClass(User *user, int selection);

void warriorSelected(Character *character);

void rogueSelected(Character *character);

void archerSelected(Character *character);

void mageSelected(Character *character);

void characterStats(Character *character);

void showBars(Character *character);

/* ELEMENT */

struct Element
{

    int type;
};

void initializeElement(Character *character, int element);

int compability(Element *first_element, Element *second_element);

char *numberToElementName(int number);

/* SPELLS */

enum spellFactor
{
    STATIC = 1,
    RATIO = 2
};

struct Spell
{

    char *spellName;
    char *description;

    int valueFactor;
    int value;

    int cost;

    Element *element;
};

void giveSpells(Character *character);
void showSpells(Character *character);

Spell *generateSpell(char *spellName, char *description, int valueFactor, int value, int cost, int element);

void warriorSpells(Character *character);
void rogueSpells(Character *character);
void archerSpells(Character *character);
void mageSpells(Character *character);

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

struct Mob
{

    char *name;

    /*Basic stats*/
    int physicalPower;
    int magicalPower;

    int maxHp;     // Static heal point
    int currentHp; // Dynamic heal point

    /*Progression*/
    int level;

    /*State*/
    int isAlive;
};

Mob *generateMob(int difficulty);

Mob *dragon(int difficulty);
Mob *goblin(int difficulty);
Mob *titan(int difficulty);
Mob *ghost(int difficulty);

void mobStats(Mob *mob);

/* ACTIONS */

void fight(Character *character, Mob *mob, int auto_mode, int dialogue);
void showFightStates(Character *character, Mob *mob);

int fightAlgorithm(Character *character, Mob *mob);

void players_turn(Character *character, Mob *mob, int dialogue);
void mobs_turn(Mob *mob, Character *character, int dialogue);

void regenerateMana(Character *character);
#endif