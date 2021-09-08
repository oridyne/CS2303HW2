/*
 * cardCell.c
 *
 *  Created on: Feb 9, 2021
 *      Author: theresesmith
 */

#include "cardCell.h"

// Simplifies making new cardCell
cardCellContent* initCardCell(int nRow, int nCol, char nLetter, char nDigit) {
    cardCellContent* newCell = (cardCellContent*) malloc(sizeof(cardCellContent));
    newCell->row = nRow;
    newCell->col = nCol;
    newCell->letter = nLetter;
    newCell->digit = nDigit;
    newCell->matched = false;
    return newCell;
}
