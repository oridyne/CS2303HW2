/*
 * tests.c
 *
 *  Created on: Jul 4, 2019
 *      Author: Therese
 */

#include "tests.h"
#include "bingoBoard.h"
#include "cardCell.h"
#include "production.h"
#include "LinkedList.h"
#include <stdio.h>

bool tests()
{
	bool answer = false;
	bool ok1,ok2,ok3,ok4,ok5,ok6,ok7,ok8,ok9 = false;
	//test the functions that get used
	//order the tests from simplest first -- this produces building blocks for use in more complex tests
	//check how functions are used in production code, this gives clues about how to provide the arguments for the invocation
	ok1 = testReadFile();
	ok2 = testSetSpace();
	if(ok2) ok3 = testFindSpace();
    ok4 = testMakeLList();
    if(ok4) {
        ok5 = testEnqueue();
        ok6 = testPrintHistory();
    }
    ok7 = testGenBoardNoDupe();
    if(ok4) ok8 = testRemoveFromList();
    if(ok2) ok9 = testCheckBoard();
    answer = ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7 && ok8 && ok9;
	//answer = true;
	return answer;
}

bool testReadFile()
{
	puts("\nstarting testReadFile"); fflush(stdout);
	bool ok = true;

	cardCellContent** theBoardP = (cardCellContent**) malloc(5*5*sizeof(cardCellContent*));
	cardCellContent** nextSpace = theBoardP+1;
	printf("first is %x and second is %x \n", theBoardP, nextSpace);

	cardCellContent* where = (cardCellContent*) theBoardP;
	cardCellContent* whereNext = where+1;
	printf("first is %x and second is %x\n\n", where, whereNext);

	free(theBoardP);
	return ok;
}

bool testSetSpace() {
    puts("starting testSetSpace");
    bool ok = true;
    cardCellContent** theBoardP = (cardCellContent**) malloc(5*5*sizeof(cardCellContent*));
    genDefaultBoard(theBoardP, 5);
    // test check for bounds
    if(setSpace(theBoardP, 6, 5, 5, 'A', '0')) {
        puts("Out of bounds row check failed");
        ok = false;
    }
    if(setSpace(theBoardP,4,6,5, 'A', '0')) {
        puts("Out of bounds col check failed");
        ok = false;
    }
    char testLetter = 'R';
    char testDigit = '5';
    setSpace(theBoardP, 3, 4, 5, testLetter, testDigit);
    cardCellContent** currCell = theBoardP + 3 * 5 + 4;

    if((*currCell)->letter != testLetter && (*currCell)->digit != testDigit) {
        puts("Setting space test failed");
        ok = false;
    }
    deleteBoard(theBoardP, 5);

    if(ok) {
        puts("test setSpace passed\n");
    } else {
        puts("test setSpace failed\n");
    }
    return ok;
}

bool testFindSpace() {
    puts("starting testFindSpace");
    bool ok = true;
    cardCellContent** theBoardP = (cardCellContent**) malloc(5 * 5 * sizeof(cardCellContent*));
    genDefaultBoard(theBoardP,5);
    setSpace(theBoardP, 0, 4, 5, 'G', '7');
    setSpace(theBoardP, 3, 4, 5, 'O', '4');
    cardCellContent** matchP = findSpace(theBoardP, 'G', '7', 5);
    if((*matchP)->row != 0 && (*matchP)->col != 4) {
        ok = false;
    }
    deleteBoard(theBoardP, 5);
    if(ok)
    {
        puts("test findSpace did pass.\n");
    }
    else {
        puts("test findSpace did not pass.\n");
    }
    return ok;
}

bool testMakeLList()
{
	bool ok = true;
	puts("starting testMakeLList");fflush(stdout);
	//what are the criteria for success for make LList?
	//should be able to make one, add data to it, get the data back
	//test case 1:
	LLNode* theListP = makeEmptyLinkedList();
	if(theListP == NULL)
	{
		ok = false;
	}
	bool rightAnswer = true;
	bool answer = isEmpty(theListP);
	if(answer!=rightAnswer)
	{
		ok = false;
	}
	//test case 2:
    cardCellContent* newCell1 = initCardCell(0,0,'R','8');
    saveCardCellContent(theListP, newCell1);

    if(theListP->cardCell != newCell1) {
        ok = false;
    }

    cardCellContent* newCell2 = initCardCell(0, 0, 'A', '6');
    saveCardCellContent(theListP, newCell2);

    cardCellContent* newCell3 = initCardCell(0, 0, 'N', '4');
    saveCardCellContent(theListP, newCell3);

    if(getCardCellContent(theListP, 'A', '6') != newCell2) {
        ok = false;
    }

	if(ok)
	{
		puts("test make LList did pass.\n");
	}
	else {
        puts("test make LList did not pass.\n");
    }
	deleteList(theListP);

	return ok;
}

bool testEnqueue() {
    bool ok = true;
    puts("starting testEnqueue");

    LLNode* theListP = makeEmptyLinkedList();
    int nCalls = 25;
    for(int i = 0; i < nCalls; i++) {
		generateCall(theListP);
    }
    int count = 0;
    puts("Should have 25 in queue");
    LLNode* temp = theListP;
    while(temp != NULL) {
        count++;
        temp = (LLNode *) temp->next;
    }
    printf("Queue: %d\n", count);
    if(count != nCalls) {
        ok = false;
    }
    deleteList(theListP);
	if(ok) {
		puts("testEnqueue did pass.\n");
	} else {
		puts("testEnqueue did not pass.\n");
	}
	return ok;
}

// Never utilized this function in production
bool testRemoveFromList()
{
	bool ok = true;
    puts("starting testRemoveFromList");
    //cases:
	//1 list is empty:return same list
	//2 list is of length one, and item is present: return empty list
	//3 list is of length one, and item is not present: return same list
	//4 list is longer than one, item is present, at first location: return list starting at second element
	//5 list is longer than one, item is present, not at first location: return list with item removed
	//6 list is longer than one, item is not present: return same list
	LLNode* case1 = makeEmptyLinkedList();

	cardCellContent* cell1 = initCardCell(0,0,'A','1');
	LLNode* ans = removeFromList(case1, cell1);
	if((ans != case1) || (ans->cardCell != (cardCellContent*)0)) {
	    puts("case 1 failed");
	    ok = false;
	}
	saveCardCellContent(case1, cell1);

	//this is case2
	ans = removeFromList(case1, cell1);
	if((ans != case1) || (ans->cardCell != (cardCellContent*)0))
	{
		ok = false;
	}
	free(cell1);
	printf("testRemove case 2 with %d\n", ok); fflush(stdout);

	//now case 3
	cardCellContent* cell2 = initCardCell(0,1,'G','6');
	ans = removeFromList(case1, cell2);
	if(ans != case1)//this is only a partial check for list unchanged
	{
		ok = false;

	}
	printf("testRemove case 3 with %d\n", ok); fflush(stdout);
    free(cell2);
	deleteList(case1);

	// now case 4
    case1 = makeEmptyLinkedList();
	cell1 = initCardCell(0,0,'A','2');
	saveCardCellContent(case1, cell1);

	cell2 = initCardCell(0,1,'A','5');
	saveCardCellContent(case1, cell2);

	ans = removeFromList(case1, cell1);
	if(ans == case1)
	{
		ok = false;
	}
	case1 = ans;
	deleteList(case1);
	printf("testRemove case 4 with %d\n", ok); fflush(stdout);

	// now case 5
	case1 = makeEmptyLinkedList();
	cell1 = initCardCell(0,0,'A','4');
	saveCardCellContent(case1, cell1);
	cell2 = initCardCell(0,5,'G','5');
	saveCardCellContent(case1, cell2);
	puts("trying case 5");fflush(stdout);
	ans = removeFromList(case1, cell2);//ans should be equal to case1
	LLNode* theNext = (LLNode*) ans->next; //this is element where cell2 got attached
	cardCellContent* check = (cardCellContent*) 0;
	if (theNext)
	{
		check = theNext->cardCell; //this should be cell2, which should have been removed
	}
	printf("testRemove returned from case 5\n"); fflush(stdout);
	if((ans != case1) || (check != (cardCellContent*)0))//disquiet
	{
		ok = false;

	}
	printf("ans == case1 is %d\n", ans==case1);
    puts("below might not work because cell2 was free'd");
    printf("check != 0 is %d\n", check != (cardCellContent*)0);
	printf("testRemove case 5 with %d\n", ok); fflush(stdout);
    deleteList(case1);

	//now case 6
	case1 = makeEmptyLinkedList();
	cell1 = initCardCell(0,0,'B','2');
	saveCardCellContent(case1, cell1);
	cell2 = initCardCell(0,0,'Y','6');
	saveCardCellContent(case1, cell2);
	cardCellContent* another = initCardCell(0,4,'G','7');
	ans = removeFromList(case1, another);
	if((ans != case1)) {
		ok = false;
	}
	printf("testRemove case 6 with %d\n", ok); fflush(stdout);

    free(another);
	deleteList(case1);
    puts("");
	return ok;
}

bool testPrintHistory()
{
	bool ok = true;
    puts("starting testPrintHistory");
	LLNode* theListP = makeEmptyLinkedList();
    puts("Should display:");
    puts("Call history:\nA0 A1 A2 A3 A4 \nNumber of calls: 5\n");
	for(int i = 0; i < 5; i++) {
	    saveCardCellContent(theListP, initCardCell(0, i, 'A', '0' + i ));
	}
	printHistory(theListP);
	if(!getYesNo("Is this correct?")) {
	    ok = false;
    }
	deleteList(theListP);

	if(ok)
	{
		puts("test printHistory did pass.\n");
	}
	else
	{
		puts("test printHistory did not pass.\n");
	}
	return ok;
}

bool testGenBoardNoDupe() {
    bool ok = true;
    puts("starting testGenBoardNoDupe");
    cardCellContent** theBoardP = (cardCellContent**) malloc(5*5*sizeof(cardCellContent*));
    genRandBoard(theBoardP, 5);
    displayBoard(theBoardP, 5);
    if(!getYesNo("Are there any duplicate entries?")) {
        puts("testGenBoardNoDupe passed\n");
    } else {
        puts("testGenBoardNoDupe failed\n");
        ok = false;
    }
    deleteBoard(theBoardP, 5);

    return ok;
}

bool testCheckBoard() {
    bool ok = true;
    puts("starting testCheckBoard");
    cardCellContent** theBoardP = (cardCellContent**) malloc(5*5*sizeof(cardCellContent*));
    char testBoard[50] = {'W','3', 'R','7', 'B','3', 'Q','6', 'H','9', 'D','2', 'R','0', 'O','3', 'K','0', 'Y','2', 'I','1', 'D','7', 'S','2', 'M','9', 'W','2', 'R','9', 'S','3', 'Y','1', 'L','9', 'B','1', 'F','4', 'A','8', 'C','5', 'Y','3', 'E','1'};
    genDefaultBoard(theBoardP, 5);
    for(int i = 0; i < 5; i++) {
       for(int j = 0; j < 5; j++) {
           //printf("Combo: %c%c\n", testBoard[(i*10+j*2)], testBoard[i*10+j*2+1]);
           setSpace(theBoardP, i, j, 5, testBoard[i*10+j*2], testBoard[i*10+j*2+1]);
       }
    }
	puts("test board no bingo");
    // displayBoard(theBoardP,5);
	if(checkBoard(theBoardP, 5)){
		puts("test no bingo failed");
	    ok = false;
	}
	// set second row to marked horizontally
	for(int i = 0; i < 5; i++) {
		cardCellContent** currCell = theBoardP + 5 + i;
		(*currCell)->letter += 32;
	}
	puts("test bingo 2nd row");
	// displayBoard(theBoardP, 5);
	if(!checkBoard(theBoardP, 5)) {
	    puts("test bingo 2nd row failed");
		ok = false;
	}
	//reset row and set 2nd column to marked
	for(int i = 0; i < 5; i++) {
		cardCellContent** currCell = theBoardP + 5 + i;
		(*currCell)->letter -= 32;
		currCell = theBoardP + i * 5 + 1;
		(*currCell)->letter += 32;
	}
	puts("test bingo 2nd column");
	// displayBoard(theBoardP, 5);
	if(!checkBoard(theBoardP, 5)) {
	    puts("test bingo 2nd column failed");
		ok = false;
	}
	// reset column and set diagonal to marked
	for(int i = 0; i < 5; i++) {
		cardCellContent** currCell = theBoardP + i * 5 + 1;
		(*currCell)->letter -= 32;
		currCell = theBoardP + i * 5 + i;
		(*currCell)->letter += 32;
	}
	puts("test bingo diagonal");
	// displayBoard(theBoardP, 5);
	if(!checkBoard(theBoardP, 5)){
	    puts("test bingo diagonal failed");
		ok = false;
	}

	// test for case found in production testing
	puts("test with lowercase letters dispersed");
	char testBoard2[50] = {'Y', '5', 'X', '3', 'P', '6', 'i', '2', 'Y', '8', 'V', '8', 'P', '7', 'H', '1', 'a', '4', 'T', '8', 'F', '2', 't', '9', 'L', '1', 'G', '1', 'e', '8', 'R', '6', 'V', '1', 'O', '6', 'M', '5', 'N', '4', 'F', '0', 'A', '1', 'U', '0', 'l', '2', 'U', '3'};
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            setSpace(theBoardP, i, j, 5, testBoard2[i*10+j*2], testBoard2[i*10+j*2+1]);
        }
    }
    //displayBoard(theBoardP,5);
    if(checkBoard(theBoardP, 5)){
        puts("test lowercase dispersed no bingo failed");
        ok = false;
    }

    deleteBoard(theBoardP,5);
	if(ok) {
		puts("Test checkBoard passed\n");
	} else {
		puts("Test checkBoard failed\n");
	}
    return ok;
}

