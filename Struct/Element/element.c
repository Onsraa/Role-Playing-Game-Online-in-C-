#include "../struct.h"

void initializeElement(Character *character, int element)
{

    character->element = malloc(sizeof(Element));
    character->element->type = element;
}

int compability(Element *first_element, Element *second_element)
{

    switch (first_element->type == second_element->type)
    {
    case 1:
        return NONE;
    case 0:
        if (first_element->type == FIRE)
        {
            if (second_element->type == PLANT)
            {
                return EFFICIENT;
            }
            else
            {
                return INEFFECTIVE;
            }
        }
        else if (first_element->type == WATER)
        {
            if (second_element->type == FIRE)
            {
                return EFFICIENT;
            }
            else
            {
                return INEFFECTIVE;
            }
        }
        else
        {
            if (second_element->type == WATER)
            {
                return EFFICIENT;
            }
            else
            {
                return INEFFECTIVE;
            }
        }
    }
}

char * numberToElementName(int number){

    switch(number){
        case FIRE : 
            return "fire";
        case WATER : 
            return "water";
        case PLANT : 
            return "plant";
    }
}