//
// Created by nepla on 9/6/2021.
//

#ifndef REFERENCEHW2BINGO_CALLER_H
#define REFERENCEHW2BINGO_CALLER_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int number;
    char letter;
} bingoCombo;

bingoCombo generateRandomCombo();

#endif //REFERENCEHW2BINGO_CALLER_H
