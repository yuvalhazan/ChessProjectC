#ifndef _part2_h
#define _part2_h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Part1.h"



typedef struct _chessPosCell {
    chessPos position;
    struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList {
    chessPosCell* head;
    chessPosCell* tail;

} chessPosList;










void checkMemoryAllocation(void* ptr);
void display(chessPosList* lst);
bool comparePositions(chessPos pos1, chessPos pos2);
void removeDuplicates(chessPosCell* start);
void print_game_board(int rows, int cols, chessPosList* lst);
void printRow(int rowIndext, chessPosList* lst);
bool listHasCell(chessPosList* lst, char letter, char col, int* loc);

#endif
