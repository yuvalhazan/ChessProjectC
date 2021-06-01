#ifndef _part5_h
#define _part5_h
#define _CRT_SECURE_NO_WARNINGS
#include "Part1.h"
#include "Part2.h"
#include "Part3.h"
#include "Part4.h"
#include<math.h>


typedef unsigned char Byte;
typedef unsigned char BYTE;

Byte* getBytesArr(chessPosList* pos_list, int len, int* p_size);
void updateIndexs(int nextEmptyBit, int* bitIndex, int* indexOfBytesArr, int* chessPosIndex);
Byte getByteFrom_chessPosList(int listLocation, int  type, chessPosList lst);
int listLen(chessPosList* list);
void saveListToBinFile(char* file_name, chessPosList* pos_list);
void checkAllocation(void* ptr);

#endif




