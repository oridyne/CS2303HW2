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
	cardCellContent* cardCell;
}LLNode;

typedef struct
{
	cardCellContent* mp;
	LLNode* newQHead;
}backFromDQFIFO;

LLNode* makeEmptyLinkedList();
LLNode* removeFromList(LLNode* hp, cardCellContent* pP);
void saveCardCellContent(LLNode* lp, cardCellContent* mp);
cardCellContent* getCardCellContent(LLNode* lp, char gLetter, char gDigit);
bool isEmpty(LLNode* lp);
cardCellContent* dequeueLIFO(LLNode* lp);
backFromDQFIFO* dequeueFIFO(LLNode* lp);
void printHistory(LLNode* hp);
void deleteList(LLNode* hp);

#endif /* LINKEDLIST_H_ */
