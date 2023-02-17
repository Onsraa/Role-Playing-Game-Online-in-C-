#include "../struct.h"

#define NB_WEAPONS 5

#define COMMON_DROP_RATE 44 // %
#define RARE_DROP_RATE  25// %
#define EPIC_DROP_RATE 20 // %
#define LEGENDARY_DROP_RATE 10 // %
#define DIVINE_DROP_RATE 1 // %

enum weapons {COMMON = 1, RARE = 2, EPIC = 3, LEGENDARY = 4, DIVINE = 5};

Weapon * generateWeapon(){

    srand(time(NULL));

    int drop_rate = rand() % 100;

    if(drop_rate <= DIVINE_DROP_RATE){
    
    }else if(drop_rate <= LEGENDARY_DROP_RATE){

    }else if(drop_rate <= EPIC_DROP_RATE){

    }else if(drop_rate <= RARE_DROP_RATE){

    }else{

    }
}

void dropStuff(Character *character, Mob *mob)
{
    
}

Weapon * divine(){
    
}
Weapon * legendary(){
    
}
Weapon * epic(){

}
Weapon * rare(){
    
}
Weapon * commun(){
    
}
