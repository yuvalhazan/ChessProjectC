#include "PseudoBoard.h"


int* copyPseudoBoard(int* arr) {
	int* output = (int*)malloc(ROWS * COLS * sizeof(int));
	int i, j;
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++)
			*(output + i * COLS + j) = *(arr + i * COLS + j);
	return output;
}

int* createEmptyPseudoBoard() {
	//Function allocates 64 bytes of memory for a board of ints
	// it fills the board with the values 0
	//returns a pointer to the board
	int* arr = (int*)malloc(ROWS * COLS * sizeof(int));
	int i, j;
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++)
			*(arr + i * COLS + j) = 0;
	return arr;
}

void print_pseudo_board(int* arr) {
	//Function takes 2D array gameBoard, int rows, int cols.
	//Function Prints The values of the array. (with some indexing to the lines)
	int i, j;
	printf("   "); //Visual
	for (i = 0; i < COLS; i++) {
		printf("%d    ", i + 1);//print column index's under 9
	}

	printf("\n");

	for (j = 0; j < ROWS; j++) {
		printf(" ");
		for (i = 0; i < COLS; i++) {
			if (i == COLS - 1) {
				printf("+----+");
			}
			else {
				printf("+----");
			}
		}

		printPseudoRow(j, arr);

	}
	printf(" ");
	for (i = 0; i < COLS; i++) {
		if (i == COLS - 1) {
			printf("+----+");
		}
		else {
			printf("+----");
		}
	}
}

void printPseudoRow(int rowIndext, int* arr) {
	// helper function for print_pseudo_board to print a row
	printf("\n");//Visual
	int i;
	int location;
	char letter = (int)('A' + rowIndext);

	printf("%c|", letter);

	for (i = 0; i < COLS; i++) {

		printf("  %d |", *(arr + rowIndext * COLS + i));

	}

	printf("\n");

}

void insertPosToPesudoBoard(int* arr, chessPos* pos) {

	int letter = TurnLetterToArrPos((*pos)[0]); // turn letter to array number
	int digit = TurnDigitCharToArrPos((*pos)[1]); // turn digit char to digit int
	*(arr + letter * COLS + digit) = 1;

}


bool inPseudoArray(int* arr, chessPos* pos) {

	int letter = TurnLetterToArrPos((*pos)[0]); // turn letter to array number
	int digit = TurnDigitCharToArrPos((*pos)[1]); // turn digit char to digit int
	if (*(arr + letter * COLS + digit) == 1)
	{
		return true;
	}
	else {
		return false;
	}
}