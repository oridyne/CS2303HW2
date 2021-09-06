//
// Created by Noah Plasse on 9/6/2021.
//

#include "caller.h"

bingoCombo generateRandomCombo(){
    bingoCombo newCombo;
    newCombo.number = (rand() % (9 + 1));
    newCombo.letter = 'A' + (rand() % 26);
    return newCombo;
}