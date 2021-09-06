/*
 * cardCell.h
 *
 *  Created on: Feb 9, 2021
 *      Author: theresesmith
 */

#ifndef CARDCELL_H_
#define CARDCELL_H_

#include <stdbool.h>

typedef struct
{
	int row;
	int col;
	char letter;
	char digit;
	bool matched;
}cardCellContent;

#endif
