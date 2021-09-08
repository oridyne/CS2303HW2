//
// Created by nepla on 9/7/2021.
//

#include "caller.h"

char generateRandomDigit() {
    return '0' + (rand() % (9 + 1));
}

char generateRandomLetter() {
    return 'A' + (rand() % 26);
}

// Generates call and adds it to linkedList
void generateCall(LLNode* lp) {
    bool duplicate = false;
    char rLetter;
    char rDigit;
    do {
        rDigit = generateRandomDigit();
        rLetter = generateRandomLetter();
        duplicate = false;
        // Check if combo exists in list already
        // If it does, regenerate random combo
        if(getCardCellContent(lp, rLetter, rDigit) != NULL) {
            duplicate = true;
        };
    } while (duplicate);
    cardCellContent* newCell = initCardCell(0,0,rLetter,rDigit);
    saveCardCellContent(lp, newCell);
}
