#ifndef _part1_h
#define _part1_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef char chessPos[2];


typedef struct _chessPosArray {

    unsigned int size;
    chessPos* positions;
} chessPosArray;

#define ROWS 8 //  amount of rows
#define COLS 8 //  amount of columns



void printChessPos(chessPos* pos);
chessPosArray*** validKnightMoves();
chessPosArray* PositionsForSlot(int row, int col);
bool is_Valid_Location(int row, int col);
void insertPositionToArray(chessPos* ptr, char letter, char digit);
void checkMemoryAllocation(void* ptr);
chessPosArray*** createEmptyArr3dArr();
void printAllPosInSquare(chessPosArray* posArr);

#endif
