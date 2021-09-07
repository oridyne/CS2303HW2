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

	//test the functions that get used
	//order the tests from simplest first -- this produces building blocks for use in more complex tests
	//check how functions are used in production code, this gives clues about how to provide the arguments for the invocation
	bool ok1 = testReadFile();
	bool ok2 = testSetSpace();
	bool ok3 = testMakeLList();
	bool ok4 = testEnqueue();
	bool ok5 = testPrintHistory();
	bool ok6 = testGenBoardNoDupe();
	bool ok7 = testRemoveFromList();
	bool ok8 = testCheckBoard();
	answer = ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7 && ok8;
	//answer = true;
	return answer;
}

bool testReadFile()
{
	puts("starting testReadFile"); fflush(stdout);
	bool ok = true;

	cardCellContent** theSpaceP = (cardCellContent**) malloc(5*5*sizeof(cardCellContent*));
	cardCellContent** nextSpace = theSpaceP+1;
	printf("first is %x and second is %x \n", theSpaceP, nextSpace);

	cardCellContent* where = (cardCellContent*) theSpaceP;
	cardCellContent* whereNext = where+1;
	printf("first is %x and second is %x\n", where, whereNext);

	free(theSpaceP);
	return ok;
}

bool testSetSpace() {
    bool ok = true;
    cardCellContent** theSpaceP = (cardCellContent**) malloc(5*5*sizeof(cardCellContent*));
    initBoard(theSpaceP, 5);
    // test check for bounds
    if(!setSpace(theSpaceP, 6, 5, 5, 'A', '0')) {
        puts("Out of bounds row check passed");
    }
    if(!setSpace(theSpaceP,4,6,5, 'A', '0')) {
        puts("Out of bounds col check passed");
    }
    char testLetter = 'R';
    char testDigit = '5';
    setSpace(theSpaceP, 3, 4, 5, testLetter, testDigit);
    cardCellContent** currCell = theSpaceP + 3 * 5 + 4;
    if((*currCell)->letter == testLetter && (*currCell)->digit == testDigit) {
        puts("setting space test passed");
    } else {
        puts("setting space test passed");
        ok = false;
    }
    deleteBoard(theSpaceP, 5);
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
	//TODO more test cases here
    cardCellContent* cell1 = initCardCell(0,0,'R','8');
    saveCardCellContent(theListP, cell1);

    if(theListP->cardCell != cell1) {
        ok = false;
    }

	if(ok)
	{
		puts("test make LList did pass.");
	}
	else {
        puts("test make LList did not pass.");
    }
	deleteList(theListP);

	return ok;
}

bool testEnqueue() {
    bool ok = true;
    int nCalls = 25;
    LLNode* theListP = makeEmptyLinkedList();
    for(int i = 0; i<nCalls; i++) {
		generateCall(theListP);
        /* bool duplicate = false; */
        /* char rLetter = 'A'; */
        /* char rDigit = '0'; */
        /* do { */
        /*     rDigit = generateRandomDigit(); */
        /*     rLetter = generateRandomLetter(); */
        /*     duplicate = false; */
        /*     LLNode* temp = theListP; */
        /*     while(temp != NULL && !duplicate && temp->cardCell != NULL) { */
        /*         if(rDigit == temp->cardCell->digit && rLetter == temp->cardCell->letter) { */
        /*             duplicate = true; */
        /*         } */
        /*         temp = (LLNode *) temp->next; */
        /*     } */
        /* } while (duplicate); */
        /* cardCellContent* newCell = initCardCell(0,0,rLetter,rDigit); */
        /* saveCardCellContent(theListP, newCell); */
    }
    printHistory(theListP);

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
	if(ok)
	{
		puts("testEnqueue did pass.");
	}
	else
	{
		puts("testEnqueue did not pass.");
	}
	return ok;
}

bool testRemoveFromList()
{
	bool ok = true;
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
//	case1 = makeEmptyLinkedList();
//	cell1 = (cardCellContent*) malloc(sizeof(cardCellContent));
//	cell1->roomNumber = 1;
//	saveCardCellContent(case1, cell1);
//	cell2 = (cardCellContent*) malloc(sizeof(cardCellContent));
//	cell2->roomNumber = 3;
//	saveCardCellContent(case1, cell2);
//	//puts("trying case 5");fflush(stdout);
//	ans = removeFromList(case1, cell2);//ans should be equal to case1
//	LLNode* theNext = (LLNode*) ans->next; //this is element where cell2 got attached
//	cardCellContent* check = (cardCellContent*) 0;
//	if (theNext)
//	{
//		check = theNext->cardCell; //this should be cell2, which should have been removed
//	}
//	//printf("testRemove returned from case 5\n"); fflush(stdout);
//	if((ans != case1) || (check != (cardCellContent*)0))//disquiet
//	{
//		ok = false;
//
//	}
//	//printf("ans == case1 is %d\n", ans==case1);
//	//printf("check != 0 is %d\n", check != (cardCellContent*)0);
//	printf("testRemove case 5 with %d\n", ok); fflush(stdout);
//	//now case 6
//	case1 = makeEmptyLinkedList();
//	cell1 = (cardCellContent*) malloc(sizeof(cardCellContent));
//	cell1->roomNumber = 1;
//	saveCardCellContent(case1, cell1);
//	cell2 = (cardCellContent*) malloc(sizeof(cardCellContent));
//	cell2->roomNumber = 3;
//	saveCardCellContent(case1, cell2);
//	cardCellContent* another = (cardCellContent*) malloc(sizeof(cardCellContent));
//	another->roomNumber=2;
//	ans = removeFromList(case1, another);
//	if((ans != case1))
//	{
//		ok = false;
//
//	}
//	printf("testRemove case 6 with %d\n", ok); fflush(stdout);
	return ok;
}

bool testPrintHistory()
{
	bool ok = true;
	LLNode* theListP = makeEmptyLinkedList();
    puts("Should display:");
    puts("Call history: A0 A1 A2 A3 A4 \n");
	for(int i = 0; i < 5; i++) {
	    saveCardCellContent(theListP, initCardCell(0, i, 'A', '0' + i ));
	}
	printHistory(theListP);
	if(getYesNo("Is this correct?")) {
	    puts("testPrintHistory passed");
	} else {
	    puts("testPrintHistory failed");
	    ok = false;
    }
	deleteList(theListP);

	if(ok)
	{
		puts("testprintHistory did pass.");
	}
	else
	{
		puts("testprintHistory did not pass.");
	}
	return ok;
}

bool testGenBoardNoDupe() {
    bool ok = true;
    cardCellContent** theSpaceP = (cardCellContent**) malloc(5*5*sizeof(cardCellContent*));
    initBoard(theSpaceP, 5);
    genRandBoard(theSpaceP, 5);
    displayBoard(theSpaceP, 5);
    if(!getYesNo("Are there any duplicate entries?")) {
        puts("testGenBoardNoDupe passed");
    } else {
        puts("testGenBoardNoDupe failed");
        ok = false;
    }
    deleteBoard(theSpaceP, 5);

    return ok;
}

bool testCheckBoard() {
    bool ok = true;
    cardCellContent** theSpaceP = (cardCellContent**) malloc(5*5*sizeof(cardCellContent*));
    char testBoard[50] = {'W','3', 'R','7', 'B','3', 'Q','6', 'H','9', 'D','2', 'R','0', 'O','3', 'K','0', 'Y','2', 'I','1', 'D','7', 'S','2', 'M','9', 'W','2', 'R','9', 'S','3', 'Y','1', 'L','9', 'B','1', 'F','4', 'A','8', 'C','5', 'Y','3', 'E','1'};
    initBoard(theSpaceP, 5);
    for(int i = 0; i < 5; i++) {
       for(int j = 0; j < 5; j++) {
           //printf("Combo: %c%c\n", testBoard[(i*10+j*2)], testBoard[i*10+j*2+1]);
           setSpace(theSpaceP, i, j, 5, testBoard[i*10+j*2], testBoard[i*10+j*2+1]);
       }
    }
	puts("test board no match");
    displayBoard(theSpaceP,5);
	if(checkBoard(theSpaceP, 5)){
		ok = false;
	}
	// set second row to marked horizontally
	for(int i = 0; i < 5; i++) {
		cardCellContent** currCell = theSpaceP + 5 + i;
		(*currCell)->letter += 32;
	}
	puts("test board match 2nd row horizontal");
	displayBoard(theSpaceP, 5);
	if(!checkBoard(theSpaceP, 5)) {
		ok = false;
	}
	//reset row and set 2nd column to marked
	for(int i = 0; i < 5; i++) {
		cardCellContent** currCell = theSpaceP + 5 + i;
		(*currCell)->letter -= 32;
		currCell = theSpaceP + i * 5 + 1;
		(*currCell)->letter += 32;
	}
	puts("test board match 2nd column vertical");
	displayBoard(theSpaceP, 5);
	if(!checkBoard(theSpaceP, 5)) {
		ok = false;
	}
	// reset column and set diagonal to marked
	for(int i = 0; i < 5; i++) {
		cardCellContent** currCell = theSpaceP + i * 5 + 1;
		(*currCell)->letter -= 32;
		currCell = theSpaceP + i * 5 + i;
		(*currCell)->letter += 32;
	}
	puts("test board match diagonal");
	displayBoard(theSpaceP, 5);
	if(!checkBoard(theSpaceP, 5)){
		ok = false;
	}
    deleteBoard(theSpaceP,5);

	if(ok) {
		puts("Test checkBoard passed");
	} else {
		puts("Test checkBoard failed");
	}
    return ok;
}

