/*
 * LinkedList.c
 *
 *  Created on: Nov 4, 2019
 *      Author: Therese
 */


#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

bool isEmpty(LLNode* lp)
{
	bool ans = false;
	if(lp->cardCell == (cardCellContent*)0)
	{
		ans = true;
	}
	return ans;
}

LLNode* makeEmptyLinkedList()
{
	LLNode* lp = (LLNode*) malloc(sizeof(LLNode));
	lp->next = (struct LLNode*)0;
	lp->prev = (struct LLNode*)0;
	lp->cardCell = (cardCellContent*)0;

	return lp;
}

void saveCardCellContent(LLNode* lp, cardCellContent* mp)
{
	//if the list is empty, then make cardCell be mp
	//else traverse the list,
	//make a new list element
	//put mp in that
	//attach the new list element to the existing list
	if(isEmpty(lp))
	{
		lp->cardCell = mp;
	}
	else
	{
		LLNode* temp = lp;
		while(temp->next)
		{
			temp=(LLNode*)temp->next;
		}
		//now temp points to the last element

		//make a new element, attach mp to it, wire up the new element
		LLNode* newList = makeEmptyLinkedList();
		newList->cardCell = mp;
		temp->next = (struct LLNode*)newList;
		newList->prev = (struct LLNode*) temp;


	}
}

cardCellContent* dequeueLIFO(LLNode* lp)
{
	cardCellContent* cardCell = (cardCellContent*)0;
	if(isEmpty(lp))
	{
		puts("Trying to dequeue from empty.");
	}
	else
	{

		LLNode* temp = lp;
		while(temp->next)
		{
			temp=(LLNode*)temp->next;
		}
		//now temp points to the last element


		cardCell = temp->cardCell;
		temp->cardCell = (cardCellContent*)0;

		//remove the last, now empty, element
		if(temp->prev)
		{
			temp=(LLNode*)temp->prev;
			free(temp->next);

			temp->next = (struct LLNode*)0;
		}
		else
		{
			puts("Queue is now empty");
		}
		puts("returning from dequeue");fflush(stdout);
	}

	return cardCell;
}

backFromDQFIFO* dequeueFIFO(LLNode* lp)
{
	backFromDQFIFO* fp = (backFromDQFIFO*) malloc(sizeof(backFromDQFIFO));
	if(lp->next == (struct LLNode*)0)
	{
		//list of length 1 or 0
		fp->newQHead= lp;
	}
	else
	{
		fp->newQHead= (LLNode*) lp->next;
	}
	fp->mp= lp->cardCell;//all return values are set
	if(lp->next != (struct LLNode*)0)
	{
		//length list is >1
		free(lp);
	}

	return fp;
}

LLNode* removeFromList(LLNode* hP, cardCellContent* pP)
{
	LLNode* retHead = hP; //only changes if first element gets removed
	//find the cardCellContent
	//use the structure of a list, namely, list is empty or element followed by list
	if(!isEmpty(hP)) {
		//puts("list is not empty");fflush(stdout);
		LLNode* altHead = (LLNode*)hP->next;
		//find the item, if it is there
		LLNode* temp = hP;
		bool done = false;
		while((!done) && temp->next)
		{
			//are we there yet?
			if(temp->cardCell == pP)
			{
				done=true;
				//puts("found it 1");fflush(stdout);
			}
			else
			{
				temp=(LLNode*)temp->next;
			}
		}
		//either we are pointing to the correct element, or we are at the end, or both
		if((temp->cardCell) == pP)
		{
			//puts("found it 2");fflush(stdout);
			//found it, remove it
			//are we at the beginning?
			if(temp == hP)
			{  //found it at the first element
				//puts("found it at first element");fflush(stdout);
				//is the list of length 1?
				if(!(temp->next))
				{//if there is no next
					//remove cardCellContent, return empty list
					hP->cardCell = (cardCellContent*)0;
				}
				else //not of length 1
				{
//					puts("found it at first element of list with length > 1");fflush(stdout);
                    free(temp->cardCell);
					free(temp);
					altHead->prev=NULL;
					retHead = altHead;
				}
			}
			else //not found at first location in list
			{
//				puts("found it not at first element");fflush(stdout);
				//save the linkages
				//found element has a next
				//found element has a prev
				//participant before has a next
				//participant after has a prev
				LLNode* prevPart = (LLNode*) temp->prev;//non-zero because not at first element
				LLNode* nextPart = (LLNode*) temp->next;//could be zero, if found at last element
				prevPart->next = (struct LLNode*) nextPart;//RHS is 0 if at end

				//puts("after setting the next of the previous");fflush(stdout);
               // printf("Next is %p, %d\n", nextPart, (bool)nextPart);fflush(stdout);
				if((bool)nextPart)//don't need guarded block if element found at end of list
				{
					//puts("before setting the previous of the next");fflush(stdout);
					nextPart->prev = (struct LLNode*) prevPart;
				}
				//puts("after handling the  previous of the next");fflush(stdout);
                free(temp->cardCell);
                free(temp);
			}//end of not found at first location
		}//end of found it
		else
		{
			//didn't find it
			//puts("did not find it");fflush(stdout);
			//nothing to do
		}//end did not find it
	}
	//printf("Returning %p\n", retHead); fflush(stdout);
	return retHead;
}

// No memory leaks
void deleteList(LLNode* node) {
    LLNode* tmp;
    while (node != NULL) {
        tmp = node;
        node = (LLNode *) node->next;
        if(tmp->cardCell != NULL) {
            free(tmp->cardCell);
        }
        free(tmp);
    }
}

void printHistory(LLNode *hp) {
    printf("Call history: ");
    LLNode* currNode = hp;
    while(currNode != NULL) {
        printf("%c%c ",currNode->cardCell->letter,currNode->cardCell->digit);
        currNode = (LLNode *) currNode->next;
    }
    puts("");
}
