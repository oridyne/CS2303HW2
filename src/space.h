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
#include "cardCell.h"

//typedef struct
//{
//	int row;
//	int col;
//	char letter;
//	char digit;
//	bool matched;
//}cardCellContent;

void initSpace(cardCellContent**, int);
void displaySpace(cardCellContent**, int);

#endif /* SPACE_H_ */
