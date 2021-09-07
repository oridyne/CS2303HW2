#!/usr/bin/env bash

calls=0

if [[ -n $1 ]]; then
    calls=$1
fi

make clean && make && ./build/BingoHW2 $calls

