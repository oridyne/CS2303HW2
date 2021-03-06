/*
 * production.h
 *
 *  Created on: Jul 4, 2019
 *      Author: Therese
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>//strncpy
#include <stdlib.h>//strtol
#include "bingoBoard.h"
#include "LinkedList.h"
#include "cardCell.h"
#include "caller.h"

#define FILENAMELENGTHALLOWANCE 50

bool production(int argc, char* argv[]);
bool getYesNo(char* query);
int getDigit(char* query, int upBound);

#endif /* PRODUCTION_H_ */
