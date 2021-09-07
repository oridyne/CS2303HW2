/*
 * cardCell.h
 *
 *  Created on: Feb 9, 2021
 *      Author: theresesmith
 */

#ifndef CARDCELL_H_
#define CARDCELL_H_

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
	int row;
	int col;
	char letter;
	char digit;
	bool matched;
}cardCellContent;

cardCellContent* initCardCell(int nRow, int nCol, char nLetter, char nDigit);
// "Caller" Functions
char generateRandomDigit();
char generateRandomLetter();
bool isMarked(cardCellContent cardCell);

#endif
