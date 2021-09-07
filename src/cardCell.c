/*
 * cardCell.c
 *
 *  Created on: Feb 9, 2021
 *      Author: theresesmith
 */

#include "cardCell.h"
#include "LinkedList.h"

cardCellContent* initCardCell(int nRow, int nCol, char nLetter, char nDigit) {
    cardCellContent* newCell = (cardCellContent*) malloc(sizeof(cardCellContent));
    newCell->row = nRow;
    newCell->col = nCol;
    newCell->letter = nLetter;
    newCell->digit = nDigit;
    newCell->matched = false;
    return newCell;
}

char generateRandomDigit() {
    return '0' + (rand() % (9 + 1));
}

char generateRandomLetter() {
    return 'A' + (rand() % 26);
}

void generateCall(LLNode* lp) {
    bool duplicate = false;
    char rLetter = 'A';
    char rDigit = '0';
    do {
        rDigit = generateRandomDigit();
        rLetter = generateRandomLetter();
        duplicate = false;
        LLNode* temp = lp;
        while(temp != NULL && !duplicate && temp->cardCell != NULL) {
            if(rDigit == temp->cardCell->digit && rLetter == temp->cardCell->letter) {
                duplicate = true;
            }
            temp = (LLNode *) temp->next;
        }
    } while (duplicate);
    cardCellContent* newCell = initCardCell(0,0,rLetter,rDigit);
    saveCardCellContent(lp, newCell);
    printf("Current Call: %c%c\n", rLetter, rDigit);
} 
