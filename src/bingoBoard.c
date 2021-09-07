/*
 * space.c
 *
 *  Created on: Jan 27, 2020
 *      Author: Therese
 */
#include "bingoBoard.h"

void genDefaultBoard(cardCellContent** theCardCell, int boardColSize)
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
        puts("setSpace: the input row & column have to be <= the board size");
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
            char rLetter = 'A';
            char rDigit = '0';
            bool duplicate = false;
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
            cardCellContent* x = initCardCell(row, col, rLetter, rDigit);
            cardCellContent** currCell = theCardCell + currIndex;
            *currCell = x;
        }
    }
}

bool checkBoard(cardCellContent** theCardCell, int boardColSize) {
    bool ans = false;
    int markCount[4] = {0,0,0,0};
    // Check Horizontal and Vertical
    for(int row = 0; row < boardColSize; row++) {
        // Horizontal check
        markCount[0] = 0;
        // Vertical check
        markCount[1] = 0;
        for (int col = 0; col <  boardColSize; ++col) {
            cardCellContent** currentCellHor = theCardCell + row * boardColSize + col;
            cardCellContent** currentCellVer = theCardCell + col * boardColSize + row;
            if((*currentCellHor)->letter >= 97) {
                markCount[0]++;
            }
            if((*currentCellVer)->letter >= 97) {
                markCount[1]++;
            }
            if(markCount[0] == 5) {
                printf("Bingo at row %d\n", row+1);
                ans = true;
            }
            if(markCount[1] == 5){
                printf("Bingo at column %d\n", row+1);
                ans = true;
            }
        }
        // Check diagonals
        cardCellContent** middleCell = theCardCell + (boardColSize/2)*boardColSize + (boardColSize/2);
        if((*middleCell)->letter >= 97 && !ans) {
            int backCount = ((boardColSize - 1) - row);
            cardCellContent** currCellDiagP = theCardCell + row * boardColSize + row;
            cardCellContent** currCellDiagN = theCardCell + row * boardColSize + backCount;
            if((*currCellDiagP)-> letter >= 97) {
                markCount[2]++;
            }
            if ((*currCellDiagN) -> letter >= 97) {
                markCount[3]++;
            }
            if(markCount[2] == 5 || markCount[3] == 5) {
                printf("Bingo on diagonal\n");
                ans = true;
            }
        }
        if(ans) break;
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

