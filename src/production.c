/*
 * production.c
 *
 *  Created on: Feb 6, 2021
 *      Author: theresesmith
 */

#include "production.h"

bool production(int argc, char *argv[]) {
    bool answer = true;
    int nCalls = -1;

    if (argc <= 1) //no interesting information
    {
        puts("Didn't find any arguments.");
        fflush(stdout);
        answer = false;
    } else //there is interesting information
    {
        printf("Found %d arguments.\n", argc);
        fflush(stdout);
        long aL = -1L;


        for (int i = 1; i < argc; i++) //don't want to read argv[0]
        {//argv[i] is a string
            //in this program our arguments are a filename followed by the max of rooms, followed by max of treasure
            switch (i) {
                case 1:

                    //this is the number of calls

                    aL = strtol(argv[i], NULL, 10);
                    nCalls = (int) aL;
                    if (nCalls < 0) {
                        answer = false;
                    }
                    printf("Number of calls is %d\n", nCalls);
                    fflush(stdout);
                    break;

                default:
                    puts("Unexpected argument count.");
                    fflush(stdout);
                    answer = false;
                    break;
            }//end of switch
        }//end of for loop on argument count
        puts("after reading arguments");
        fflush(stdout);

    }// end of command line arguments

    // Make the game play itself if you want to (makes testing less annoying)
    bool lazy = getYesNo("\nMake game play itself?");

    // initialize a linked list
    LLNode *theListP = makeEmptyLinkedList();

    // obtain space for bingo card
    cardCellContent **theBoardP = (cardCellContent **) malloc(5 * 5 * sizeof(cardCellContent *));
    srand(time(0));
    genRandBoard(theBoardP, 5);

    // displayCard
    puts("Your Board:");
    displayBoard(theBoardP, 5);
    puts("");
    bool win = false;
    // the caller is going call some random values
    for (int i = 0; i < nCalls; i++) {
        // get what caller calls
        // save result on linked list
        generateCall(theListP);
        // show/display the board
        if (!lazy) displayBoard(theBoardP, 5);
        // is it a match?
        // get current call
        LLNode *temp = theListP;
        char call[2] = {'A', '0'};
        // Get data from back of linked list
        while (temp != NULL) {
            if (temp->next == NULL) {
                call[0] = temp->cardCell->letter;
                call[1] = temp->cardCell->digit;
            }
            temp = (LLNode *) temp->next;
        }
        // check if call exists on board
        cardCellContent **matchCell = findSpace(theBoardP, call[0], call[1], 5);
        if (!lazy) {
            bool gotMatch = false;
            while(!gotMatch) {
                printf("Current Call: %c%c\n", call[0], call[1]);
                if (getYesNo("Is the call a match?")) {
                    int row = getDigit("What row is it in?", 6)-1;
                    int column = getDigit("What column is it in?", 6)-1;
                    if(matchCell != NULL && (*matchCell)->row == row && (*matchCell)->col == column) {
                            puts("Call is a match");
                            // set letter to lowercase
                            (*matchCell)->letter += 32;
                            gotMatch = true;
                    } else {
                        puts("Sorry. Call isn't a match\n");
                        displayBoard(theBoardP,5);
                    }
                } else {
                    gotMatch = true;
                }
            }
            puts("");
        } else {
            if (matchCell != NULL)(*matchCell)->letter += 32;
        }
        // did we win?
        if (checkBoard(theBoardP, 5)) {
            win = true;
            puts("You've won!");
            break;
        }
    }
    if (!win) {
        puts("You didn't win. Try again");
    }
    // printHistory
    if (nCalls > 0) {
        displayBoard(theBoardP, 5);
        printHistory(theListP);
    }
    // Free memory
    deleteList(theListP);
    deleteBoard(theBoardP, 5);
    return answer;
}

bool getYesNo(char *query) {
    bool answer = true; //so far
    char said = 'x';
    while ((said != 'y') && (said != 'n')) {
        printf("%s (y/n): ", query);
        fflush(stdout);
        scanf("%s", &said);
    }
    if (said == 'n') {
        answer = false;
    } else if (said == 'y') {
        answer = true;
    }
    return answer;
}

int getDigit(char *query, int upBound) {
    int inNum = 0;
    bool valid = false;
    while (!valid) {
        printf("%s: ", query);
        scanf("%1d", &inNum);
        fflush(stdout);
        if(inNum < upBound) {
            valid = true;
        }
    }
    return inNum;
}
