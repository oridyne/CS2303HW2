/*
 * space.c
 *
 *  Created on: Jan 27, 2020
 *      Author: Therese
 */
#include "bingoBoard.h"

void initBoard(cardCellContent** theCardCell, int boardColSize)
{
	for(int row = 0; row < boardColSize; row++)
	{
		for(int col = 0; col < boardColSize; col++)
		{
		    cardCellContent* x = initCardCell(row, col, 'A', '0');
			cardCellContent** thatCellP = theCardCell + row*boardColSize + col;
			*thatCellP = x; //put its address into bingo card space
		}
	}
}

void displayBoard(cardCellContent** theCardCell, int boardColSize)
{
	for(int row = 0; row < boardColSize; row++)
	{
		for(int col = 0; col < boardColSize; col++)
		{
			cardCellContent** thatCellP = theCardCell + row*boardColSize + col;
			char let = (*thatCellP)->letter;
			char digit = (*thatCellP)->digit;
			printf("|%c%c", let, digit);
		}
		printf("|\n");
	}
}

bool setSpace(cardCellContent** theCardCell, int fRow, int fCol, int boardColSize, char sLetter, char sDigit) {
    if(fRow > boardColSize || fCol > boardColSize) {
        puts("setSpace failed: the input row & column have to be <= the board size");
        return false;
    }
    cardCellContent** currCell = theCardCell + fRow * boardColSize + fCol;
    (*currCell)->letter = sLetter;
    (*currCell)->digit = sDigit;
    return true;
}

cardCellContent** findSpace(cardCellContent **theCardCell, char sLetter, char sDigit, int boardColSize) {
    cardCellContent** retCell = NULL;
    for(int row = 0; row<boardColSize; row++) {
        for (int col = 0; col < boardColSize; col++) {
           cardCellContent** currCell = theCardCell + row * boardColSize + col;
           if((*currCell)->letter == sLetter && (*currCell)->digit == sDigit) {
               retCell = currCell;
           }
        }
    }
    return retCell;
}

void genRandBoard(cardCellContent** theCardCell, int boardColSize) {
    for(int row = 0; row < boardColSize; row++) {
        for(int col = 0; col < boardColSize; col++) {
            int currIndex = row * boardColSize + col;
            cardCellContent** currCell = theCardCell + currIndex;
            bool duplicate = false;
            char rLetter = 'A';
            char rDigit = '0';
            do {
                rDigit = generateRandomDigit();
                rLetter = generateRandomLetter();
                duplicate = false;
                for(int i = 0; i < row * boardColSize + col; i++) {
                    cardCellContent** testCell = theCardCell + i;
                    if(rDigit == (*testCell)->digit && rLetter == (*testCell)->letter) {
                        duplicate = true;
                    }
                }
            } while (duplicate);
            (*currCell)->digit = rDigit;
            (*currCell)->letter = rLetter;
        }
    }
}

bool checkBoard(cardCellContent** theCardCell, int boardColSize) {
    bool ans = false;
    int markCount[2] = {0, 0};
    //check hor and vert
    for(int row = 0; row < boardColSize; row++) {
        for (int col = 0; col <  boardColSize; ++col) {
            cardCellContent** currentCellHor = theCardCell + row * boardColSize + col;
            cardCellContent** currentCellVer = theCardCell + col*boardColSize + row;
            if((*currentCellHor)->letter >= 97) {
                markCount[0]++;
            } else if((*currentCellVer)->letter >= 97) {
                markCount[1]++;
            }
        }
        if(markCount[0] == 5 || markCount[1] == 5) {
            ans = true;
            break;
        }
    }

    cardCellContent** middleCell = theCardCell + (boardColSize/2)*boardColSize + (boardColSize/2);
    if((*middleCell)->letter >= 97) {
        if(!ans) {
            markCount[0] = 0;
            markCount[1] = 0;
            for (int row = 0; row < boardColSize; ++row) {
                cardCellContent** currCellDP = theCardCell + row * boardColSize + row;
                int backCount = ((boardColSize - 1) - row);
                cardCellContent** currCellDN = theCardCell + backCount * boardColSize + backCount;
                if((*currCellDP)-> letter >= 97) {
                    markCount[0]++;
                } else if ((*currCellDN) -> letter >= 97) {
                    markCount[1]++;
                }
            }
        }
    }

    return ans;
}

// Make sure no memory leaks
void deleteBoard(cardCellContent** theCardCell, int boardColSize) {
    for(int row = 0; row < boardColSize; row++) {
        for(int col = 0; col < boardColSize; col++) {
            cardCellContent** thatCellP = theCardCell + row * boardColSize + col;
            free(*thatCellP);
        }
    }
    free(theCardCell);
}

