#ifndef _Pboard_h
#define _Pboard_h
#include "Part1.h"
#include "Part2.h"
#include "Part2.h"

int* createEmptyPseudoBoard();
void insertPosToPesudoBoard(int* arr, chessPos* pos);
void printPseudoRow(int rowIndext, int* arr);
void print_pseudo_board(int* arr);
bool inPseudoArray(int* arr, chessPos* pos);
int* copyPseudoBoard(int* arr);

#endif