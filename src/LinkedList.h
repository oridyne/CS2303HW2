/*
 * LinkedList.h
 *
 *  Created on: Nov 4, 2019
 *      Author: Therese
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdbool.h>
#include "cardCell.h"

struct LLNode;
typedef struct
{
	struct LLNode* next;
	struct LLNode* prev;
	cardCellContent* payP;
}LLNode;

typedef struct
{
	cardCellContent* mp;
	LLNode* newQHead;
}backFromDQFIFO;

LLNode* makeEmptyLinkedList();
LLNode* removeFromList(LLNode* hp, cardCellContent* pP);
void savecardCellContent(LLNode* lp, cardCellContent* mp);
bool isEmpty(LLNode* lp);
cardCellContent* dequeueLIFO(LLNode* lp);
backFromDQFIFO* dequeueFIFO(LLNode* lp);
void printHistory(LLNode* hp);

#endif /* LINKEDLIST_H_ */
