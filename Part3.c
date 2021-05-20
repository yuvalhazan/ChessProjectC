#include "Part1.h"
#include "Part2.h"
#include "Part3.h"
#include "PseudoBoard.h"






//void main() {
//	pathTree Tr;
//	chessPos A2 = { 'A','2' };
//
//
//	printf("---------MAIN------\n");
//
//
//	Tr = findAllPossibleKnightPaths(&A2);
//	treeNode* root = Tr.root;
//	printTreeNode(root);
//	treeNode* FirstChild = root->next_possible_positions->node;
//	treeNode* SecondChild = root->next_possible_positions->next->node;
//	treeNode* ThirdChild = root->next_possible_positions->next->next->node;
//	printTreeNode(FirstChild);
//	printTreeNode(FirstChild->next_possible_positions->node);
//	printTreeNode(FirstChild->next_possible_positions->node->next_possible_positions->node);
//}

pathTree findAllPossibleKnightPaths(chessPos* startingPosition) {
	/*
		Function recieves a pointer to chesspos and builds a Pathtree with
		all possible paths starting at the position "startingPosition" points to.
	*/

	pathTree ResTree; // create tree
	ResTree.root = NULL;
	int* locations = createEmptyPseudoBoard(); // create an empty 8X8 array of zeros
	ResTree.root = MakeNewTreeNode(startingPosition); // create a node with the starting position and no children
	findAllPossibleKnightPathsRecursive(ResTree.root, locations); // send root node to recursive function to build tree

	return ResTree;
}


void findAllPossibleKnightPathsRecursive(treeNode* cur_node, int* pos_arr) {




	int* temp;
	if (count_valid_children(&cur_node->position, pos_arr) == 0) 	//break condition
	{
		//if the node has no children that didn't appear in the path
		// next positions(Children list) point to NULL and return

		cur_node->next_possible_positions = NULL;
		return;
	}

	else {
		// if there are possible location to travel to still..

		insertPosToPesudoBoard(pos_arr, &cur_node->position); // put cur position in visited positions array

		cur_node->next_possible_positions = addChildrenList(&cur_node->position, pos_arr); //add unused children

		treeNodeListCell* traverse = cur_node->next_possible_positions; // point to start of list

		temp = copyPseudoBoard(pos_arr); // create copy of array to send to next recursive call
		while (traverse != NULL)

		{
			findAllPossibleKnightPathsRecursive(&traverse->node->position, temp);
			traverse = traverse->next;
		}
		free(temp);

	}





}




int count_valid_children(chessPos* startingPosition, int* check_arr) {
	chessPosArray*** Array;
	Array = validKnightMoves(); // calculate ALL possible knight from any position

	int counter = 0;
	int letter = TurnLetterToArrPos((*startingPosition)[0]); // turn letter to array number
	int digit = TurnDigitCharToArrPos((*startingPosition)[1]); // turn digit char to digit int
	int list_size = Array[letter][digit]->size; // how many possible locations
	chessPosArray* posArr = Array[letter][digit];

	for (int i = 0; i < list_size; i++)
	{
		if (!inPseudoArray(check_arr, posArr->positions + i))
		{
			counter++;
		}
	}
	free(Array);
	return counter;
}
bool has_no_valid_children(chessPos* startingPosition, int* check_arr) {
	//function takes a chesspos pointer and a pseudo array 
	// function checks if there are legitemate positions for the kingt based on the check_arr

	chessPosArray*** Array;
	Array = validKnightMoves(); // calculate ALL possible knight from any position

	int unUsedCounter = 0;
	int letter = TurnLetterToArrPos((*startingPosition)[0]); // turn letter to array number
	int digit = TurnDigitCharToArrPos((*startingPosition)[1]); // turn digit char to digit int
	int list_size = Array[letter][digit]->size; // how many possible locations
	chessPosArray* posArr = Array[letter][digit];

	for (int i = 0; i < list_size; i++)
	{
		if (inPseudoArray(check_arr, posArr->positions + i))
		{
			continue;
		}
		else {
			return false;
		}
	}
	return true;
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


treeNode* MakeNewTreeNode(chessPos* pos) {
	// Function takes a pointer to a chesspos
	// Function allocates memory for a tree node and puts the values from the pos
	// into the TreeNode position struct it then returns the pointer to the node
	treeNode* node = malloc(sizeof(treeNode));
	node->position[0] = (*pos)[0];
	node->position[1] = (*pos)[1];
	return node;
}

treeNode* createIntersection(chessPos* pos,int* pos_arr) {
	// funtion takes a pointer to a chesspos
	// Function allocates memory and fills the pos values into the node
	// Function adds to the node a list of next possible positions for the knight

	treeNode* node = MakeNewTreeNode(pos);

	insertPosToPesudoBoard(pos_arr, pos);
	node->next_possible_positions = addChildrenList(pos, pos_arr);

	return node;
}



treeNodeListCell* addChildrenList(chessPos* pos, int* arr) {
	// Function takes a pointer to a chess position
	// Function Retruns a pointer to the first element in a linked list
	// the memebers of the linked list are the possible positons a knight can move to from
	// the position given as the function argument

	chessPosArray*** Array;
	Array = validKnightMoves(); // calculate ALL possible knight from any position

	int unUsedCounter = 0;
	int i = 0;
	int letter = TurnLetterToArrPos((*pos)[0]); // turn letter to array number
	int digit = TurnDigitCharToArrPos((*pos)[1]); // turn digit char to digit int
	int list_size = Array[letter][digit]->size; // how many possible locations
	chessPosArray* posArr = Array[letter][digit]; // array of possible locations from position

	treeNodeListCell* head = NULL;
	if (has_no_valid_children(pos,arr))
	{
		return NULL;
	}

	while (inPseudoArray(arr,posArr->positions+ i))
	{
		i++;
	}
	treeNodeListCell* temp = malloc(sizeof(treeNodeListCell));
	temp->node = MakeNewTreeNode(posArr->positions + i);
	temp->next = NULL;

	head = temp;
	if (i == 0)
	{
		i = 1;
	}
	for (i; i < list_size; i++)
	{
		if (inPseudoArray(arr, posArr->positions + i))
		{
			continue;
		}
		else {

			treeNodeListCell* temp2 = malloc(sizeof(treeNodeListCell));
			temp->next = temp2;
			temp2->node = MakeNewTreeNode(posArr->positions + i);
			temp2->next = NULL;
			temp = temp2;
		}

	}


	return head;
}



void printTreeNode(treeNode* node) {
	if (node == NULL)
	{
		printf("points to NULL\n");
		return;
	}
	printf("the node position is:");
	printChessPos(&node->position);
	printf("\n");
	treeNodeListCell* traverse = node->next_possible_positions;
	printf("	children:\n");
	while (traverse != NULL)
	{
		printChessPos(&traverse->node->position);
		traverse = traverse->next;
	}
	printf("\n");
}









