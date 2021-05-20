#ifndef _part3_h
#define _part3_h
#include "Part1.h"
#include "Part2.h"

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	chessPos position;
	treeNodeListCell* next_possible_positions; /* list of locations*/
} treeNode;

typedef struct _treeNodeListCell {

	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;


typedef struct _pathTree {
	treeNode* root;
} pathTree;


void findAllPossibleKnightPathsRecursive(treeNode* cur_node, int* pos_arr);
pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
int TurnLetterToArrPos(char letter);
int TurnDigitCharToArrPos(char digit);
treeNode* MakeNewTreeNode(chessPos* pos);
treeNodeListCell* addChildrenList(chessPos* pos,int* arr);
void printTreeNode(treeNode* node);
treeNode* createIntersection(chessPos* pos, int* pos_arr);
bool has_no_valid_children(chessPos* startingPosition, int* check_arr);
int count_valid_children(chessPos* startingPosition, int* check_arr);


#endif
