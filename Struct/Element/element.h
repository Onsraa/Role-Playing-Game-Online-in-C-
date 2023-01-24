#ifndef ELEMENT_H_
#define ELEMENT_H_
#include "../Classes/classes.h"

enum elements {FIRE = 1, WATER = 2, PLANT = 3};
enum compability {EFFICIENT = 1, INEFFECTIVE = 2, NONE = 3};

typedef struct Element Element;

struct Element {
    
    char * type;

};

void initializeElement(Character *character, int element);

int compability(Element * first_element, Element * second_element);

#endif