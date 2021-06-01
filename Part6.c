#define _CRT_SECURE_NO_WARNINGS
#include "Part1.h"
#include "Part2.h"
#include "Part3.h"
#include "Part4.h"
#include "Part5.h"


void freeChessPosList(chessPosList* lst);
int checkAndDisplayPathFromFile(char* file_name);
bool isNextPosValid(chessPosList* lst, chessPosCell* firstPos, char nextPosRow, char nextPosCol);
void insertDataToEndChessPosList(chessPosList* lst, char posLetter, char posNum);
void freeChessPosList(chessPosList* lst);
void insertNodeToEndChessPosList(chessPosList* lst, chessPosCell* newTail);


//void main() {
//
//	chessPosList lst;
//	chessPosCell cell6 = { {'E','1'},NULL };
//	chessPosCell cell5 = { {'A','4'},&cell6 };
//	chessPosCell cell4 = { {'H','5'},&cell5 };
//	chessPosCell cell3 = { {'D','8'},&cell4 };
//	chessPosCell cell2 = { {'H','5'},&cell3 };
//	chessPosCell cell1 = { {'A','4'},&cell2 };
//
//
//	lst.head = &cell1;
//	lst.tail = &cell6;
//	saveListToBinFile("file.bin", &lst);
//	checkAndDisplayPathFromFile("file.bin");
//
//}

chessPosCell* createNewChessPosListNode(char posLetter,char posNum, chessPosCell* next) {

	chessPosCell* output = malloc(sizeof(chessPosCell));
	checkMemoryAllocation(output);
	output->position[0] = posLetter;
	output->position[1] = posNum;
	output->next = next;

	return output;

}
int getListSize(chessPosList posList) {

	int counter = 0;
	chessPosCell* travers = posList.head;
	while (travers != NULL)
	{
		counter++;
		travers = travers->next;
	}
	return counter;
}

void makeEmptyChessPosList(chessPosList* posList) {

	posList->head = NULL;
	posList->tail = NULL;
}
int checkAndDisplayPathFromFile(char* file_name)
{
	int i;
	int row = 0, col = 0;
	short int size, validListSize, countPos = 0;
	char tempPosRow, tempPosCol;
	BYTE firstByte, secondByte, thirdByte;
	BYTE mask3bit = 0x07, mask2bit = 0x03, mask1bit = 0x01;

	FILE* binFile = fopen(file_name, "rb");

	if (binFile == NULL)
		return -1; /* file doesn't exist */

	fread(&size, sizeof(short int), 1, binFile);

	chessPosList posList;
	makeEmptyChessPosList(&posList);

	for (i = 0; i < size; i += 4)
	{
		fread(&firstByte, sizeof(BYTE), 1, binFile);

		row |= firstByte >> 5;

		col |= firstByte >> 2;
		col &= mask3bit;

		tempPosRow = row + 'A';
		tempPosCol = col + '1';
		countPos++;

		if (!isNextPosValid(&posList, posList.tail, tempPosRow, tempPosCol))
			return 1; /* if path isn't valid */

		row = 0;
		col = 0;
		if (fread(&secondByte, sizeof(BYTE), 1, binFile))
		{
			row |= (firstByte & mask2bit);
			//row &= mask2bit;
			row = row << 1;
			row |= secondByte >> 7;
			//row = row & mask1bit;

			col |= secondByte >> 4;
			col &= mask3bit;

			tempPosRow = row + 'A';
			tempPosCol = col + '1';
			countPos++;

			if (!isNextPosValid(&posList, posList.tail, tempPosRow, tempPosCol))
				return 1; /* if path isn't valid */
		}

		row = 0;
		col = 0;
		if (fread(&thirdByte, sizeof(BYTE), 1, binFile))
		{
			row |= secondByte >> 1;
			row &= mask3bit;

			col |= (secondByte & mask1bit);
			col = col << 2;
			col |= thirdByte >> 6;

			tempPosRow = row + 'A';
			tempPosCol = col + '1';
			countPos++;

			if (!isNextPosValid(&posList, posList.tail, tempPosRow, tempPosCol))
				return 1; /* if path isn't valid */

			row = 0;
			col = 0;
			if (countPos != size)
			{
				row |= thirdByte >> 3;
				row &= mask3bit;

				col |= (thirdByte & mask3bit);

				tempPosRow = row + 'A';
				tempPosCol = col + '1';
				countPos++;

				if (!isNextPosValid(&posList, posList.tail, tempPosRow, tempPosCol))
					return 1; /* if path isn't valid */
			}
		}

		row = 0;
		col = 0;
	}

	display(&posList); /* if path is valid */

	validListSize = getListSize(posList);

	if (validListSize == ROWS * COLS)
		return 2; /* if path is covering all board */
	else
		return 3; /* if path isn't covering all board */
}

bool isNextPosValid(chessPosList* lst, chessPosCell* firstPos, char nextPosRow, char nextPosCol)
{
	int i;
	int firstPosRow, firstPosCol, validRow, validCol, size;

	firstPosRow = firstPos->position[0] - 'A';
	firstPosCol = firstPos->position[1] - '1';

	if (firstPos == NULL)
	{
		insertDataToEndChessPosList(lst, nextPosRow, nextPosCol);
		return true;
	}

	chessPosArray*** chessBoard = validKnightMoves();
	size = chessBoard[firstPosRow][firstPosCol]->size;

	for (i = 0; i < size; i++)
	{
		validRow = chessBoard[firstPosRow][firstPosCol]->positions[i][0] - 'A';
		validCol = chessBoard[firstPosRow][firstPosCol]->positions[i][1] - '1';

		if ((nextPosRow - 'A') == validRow && (nextPosCol - '1') == validCol)
		{
			insertDataToEndChessPosList(lst, nextPosRow, nextPosCol);
			return true;
		}
	}

	freeChessPosList(lst);
	return false;
}

void insertDataToEndChessPosList(chessPosList* lst, char posLetter, char posNum)
{
	chessPosCell* newTail;
	newTail = createNewChessPosListNode(posLetter, posNum, NULL);
	insertNodeToEndChessPosList(lst, newTail);
}

void insertNodeToEndChessPosList(chessPosList* lst, chessPosCell* newTail)
{
	if (lst->head == NULL)
		lst->head = lst->tail = newTail;
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void freeChessPosList(chessPosList* lst)
{
	chessPosCell* curr = lst->head, * next;

	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}