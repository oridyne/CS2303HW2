/*
 * space.h
 *
 *  Created on: Jan 27, 2020
 *      Author: Therese
 */

#ifndef SPACE_H_
#define SPACE_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "cardCell.h"

//typedef struct
//{
//	int row;
//	int col;
//	char letter;
//	char digit;
//	bool matched;
//}cardCellContent;

void initBoard(cardCellContent**, int);
void displayBoard(cardCellContent**, int);
bool setSpace(cardCellContent** theCardCell, int fRow, int fCol, int boardColSize, char sLetter, char sDigit);
cardCellContent** findSpace(cardCellContent** theCardCell, char sLetter, char sDigit, int boardColSize);
void genRandBoard(cardCellContent**, int);
bool checkBoard(cardCellContent**, int);
void deleteBoard(cardCellContent**, int);

#endif /* SPACE_H_ */
