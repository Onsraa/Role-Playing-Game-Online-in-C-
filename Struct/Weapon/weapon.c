#include "../struct.h"

#define NB_WEAPONS 4

enum weapons {COMMON = 1, RARE = 2, EPIC = 3, LEGENDARY = 4};

int generateWeapon(){

    srand(time(NULL));
    return (int)(rand() % NB_WEAPONS + 1);
}