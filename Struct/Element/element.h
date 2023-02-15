#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../Classes/classes.h"

enum elements {FIRE = 1, WATER = 2, PLANT = 3};
enum compability {EFFICIENT = 1, INEFFECTIVE = 2, NONE = 3};

typedef struct Element Element;

struct Element {
    
    int type;

};

void initializeElement(Character *character, int element);

int compability(Element * first_element, Element * second_element);

char * numberToElementName(int number);

#endif