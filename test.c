#include "Part1.h"
#include "Part2.h"



pathTree findAllPossibleKnightPaths(chessPos* startingPosition) {
	pathTree tr;
	tr.root = NULL;
	int arr[ROWS][COLS] = { {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}};
	tr.root = MakeNewTreeNode(startingPosition, NULL);
	findAllPossibleKnightPathsRec(tr.root, arr);
	return tr;
}

void findAllPossibleKnightPathsRec(treeNode* cur_node, int arr[COLS][ROWS]) {

	chessPosArray*** Array;
	Array = validKnightMoves();

	chessPosArray* possible_moves = Array[TurnLetterToArrPos(cur_node->position[0])][TurnDigitCharToArrPos(cur_node->position[1])];
	printAllPosInSquare(possible_moves);
	count_children_not_in_array(cur_node, arr);
}


int TurnLetterToArrPos(char letter) {
	// Function takes a char of a letter between A-H
	// Function Returns the coresponding number between 0-7 (for an array)
	return (int)letter - 65;
}

int TurnDigitCharToArrPos(char digit) {
	// Function takes a char of a digit between 1-8
	// Function Returns the coresponding number between 0-7(for an array)
	int x = digit - '0';
	return x - 1;
}

treeNode* MakeNewTreeNode(chessPos* pos,treeNodeListCell* next) {
	// Function takes a pointer to a chesspos
	// Function allocates memory for a tree node and puts the values from the pos
	// into the TreeNode position struct it then returns the pointer to the node

	treeNode* node = malloc(sizeof(treeNode));
	node->position[0] = (*pos)[0];
	node->position[1] = (*pos)[1];
	node->next_possible_positions = next;
	return node;
}

int count_children_not_in_array(treeNode* cur_node, int arr[COLS][ROWS]) {
	chessPosArray*** Array;
	Array = validKnightMoves();

	chessPosArray* possible_moves = Array[TurnLetterToArrPos(cur_node->position[0])][TurnDigitCharToArrPos(cur_node->position[1])];
	int arr_size = possible_moves->size;
	chessPos* cur_pos;
	int i;
	int letter;
	int digit;
	for (i = 0; i < arr_size; i++) {
		cur_pos = possible_moves->positions + i;
		letter = TurnLetterToArrPos(cur_pos[0]);
		digit = TurnDigitCharToArrPos(cur_pos[1]);
		printf("%d,%d",letter,digit);
	}
}