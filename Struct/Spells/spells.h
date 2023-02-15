#ifndef SPELLS_H_
#define SPELLS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../Element/element.h"

typedef struct Spell Spell;

typedef struct Offensive Offensive;
typedef struct Defensive Defensive;
typedef struct Heal Heal;

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

#endif
