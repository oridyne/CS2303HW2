/*
 * tests.c
 *
 *  Created on: Jul 4, 2019
 *      Author: Therese
 */

#include "tests.h"
#include "production.h"
#include "LinkedList.h"


bool tests()
{
	bool answer = false;

	//test the functions that get used
	//order the tests from simplest first -- this produces building blocks for use in more complex tests
	//check how functions are used in production code, this gives clues about how to provide the arguments for the invocation
	bool ok1 = testReadFile();
	bool ok3 = testMakeLList();
	bool ok4 = testEnqueue();
	bool ok5 = testPrintHistory();
	answer = ok1 && ok3 && ok4 && ok5;
	//answer = true;
	return answer;
}

bool testReadFile()
{
	puts("starting testReadFile"); fflush(stdout);
	bool ok = true;

//	cardCellContent** theSpaceP = (cardCellContent**) malloc(5*5*sizeof(cardCellContent*));
//	cardCellContent** nextSpace = theSpaceP+1;
//	printf("first is %x and second is %x \n", theSpaceP, nextSpace);
//
//	cardCellContent* where = (cardCellContent*) theSpaceP;
//	cardCellContent* whereNext = where+1;
//	printf("first is %x and second is %x\n", where, whereNext);






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
	if(ok)
	{
		puts("test make LList did pass.");
	}
	else
	{
		puts("test make LList did not pass.");
	}

	return ok;
}
bool testEnqueue()
{
	bool ok = true;
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
//	cardCellContent* pay1 = (cardCellContent*) malloc(sizeof(Room));
//	pay1->roomNumber = 1;
//	LLNode* ans = removeFromList(case1, pay1);
//	if((ans != case1) || (ans->payP != (cardCellContent*)0))
//	{
//		ok = false;
//
//	}
//	printf("testRemove case 1 with %d\n", ok); fflush(stdout);
//	savecardCellContent(case1, pay1);
//	//this is case2
//	ans = removeFromList(case1, pay1);
//	if((ans != case1) || (ans->payP != (cardCellContent*)0))
//	{
//		ok = false;
//
//	}
//	printf("testRemove case 2 with %d\n", ok); fflush(stdout);
//	//now case 3
//	cardCellContent* pay3 = (cardCellContent*) malloc(sizeof(Room));
//	pay3->roomNumber = 3;
//	ans = removeFromList(case1, pay3);
//	if(ans != case1)//this is only a partial check for list unchanged
//	{
//		ok = false;
//
//	}
//	printf("testRemove case 3 with %d\n", ok); fflush(stdout);
//	//now case 4
//	case1 = makeEmptyLinkedList();
//	pay1 = (cardCellContent*) malloc(sizeof(Room));
//	pay1->roomNumber = 1;
//	savecardCellContent(case1, pay1);
//	pay3 = (cardCellContent*) malloc(sizeof(Room));
//	pay3->roomNumber = 3;
//	savecardCellContent(case1, pay3);
//	ans = removeFromList(case1, pay1);
//
//	if(ans == case1)
//	{
//		ok = false;
//
//	}
//	printf("testRemove case 4 with %d\n", ok); fflush(stdout);
//	//now case 5
//	case1 = makeEmptyLinkedList();
//	pay1 = (cardCellContent*) malloc(sizeof(Room));
//	pay1->roomNumber = 1;
//	savecardCellContent(case1, pay1);
//	pay3 = (cardCellContent*) malloc(sizeof(Room));
//	pay3->roomNumber = 3;
//	savecardCellContent(case1, pay3);
//	//puts("trying case 5");fflush(stdout);
//	ans = removeFromList(case1, pay3);//ans should be equal to case1
//	LLNode* theNext = (LLNode*) ans->next; //this is element where pay3 got attached
//	cardCellContent* check = (cardCellContent*) 0;
//	if (theNext)
//	{
//		check = theNext->payP; //this should be pay3, which should have been removed
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
//	pay1 = (cardCellContent*) malloc(sizeof(Room));
//	pay1->roomNumber = 1;
//	savecardCellContent(case1, pay1);
//	pay3 = (cardCellContent*) malloc(sizeof(Room));
//	pay3->roomNumber = 3;
//	savecardCellContent(case1, pay3);
//	cardCellContent* another = (cardCellContent*) malloc(sizeof(Room));
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


