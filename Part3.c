#include "Part1.h"
#include "Part2.h"
#include "Part3.h"






//void main() {
//	pathTree Tr;
//	chessPos A2 = { 'A','1' };
//
//
//	printf("---------MAIN------\n");
//
//
//		Tr = findAllPossibleKnightPaths(&A2);
//		treeNode* root = Tr.root; //A1
//		printTreeNode(root);
//		treeNode* FirstChild = root->next_possible_positions->next->node;
//	
//		printTreeNode(FirstChild); //B3
//		printTreeNode(FirstChild->next_possible_positions->next->next->node); //A5
//		printTreeNode(FirstChild->next_possible_positions->next->next->node->next_possible_positions->node); //C4
//		printTreeNode(FirstChild->next_possible_positions->next->next->node->next_possible_positions->node->next_possible_positions->node); // E5
//		printTreeNode(FirstChild->next_possible_positions->next->next->node->next_possible_positions->node->next_possible_positions->node->next_possible_positions->node); //D3
//		treeNode* d3 = FirstChild->next_possible_positions->next->next->node->next_possible_positions->node->next_possible_positions->node->next_possible_positions->node;
//		printTreeNode(d3->next_possible_positions->next->next->next->next->node); //E1
//		printTreeNode(d3->next_possible_positions->next->next->next->next->node->next_possible_positions->node); //C2
//
//}

pathTree findAllPossibleKnightPaths(chessPos* startingPosition) {
	/*
		Function recieves a pointer to chesspos and builds a Pathtree with
		all possible paths starting at the position "startingPosition" points to.
	*/

	pathTree ResTree; // create tree
	ResTree.root = NULL;
	int locations[ROWS*COLS]; // create an empty ROWSxCOLS array of zeros
	fill0(locations);
	chessPosArray*** Array;
	Array = validKnightMoves(); // calculate ALL possible knight from any position
	ResTree.root = MakeNewTreeNode(startingPosition); // create a node with the starting position and no children
	findAllPossibleKnightPathsRecursive(ResTree.root, locations,Array); // send root node to recursive function to build tree

	return ResTree;
}


void findAllPossibleKnightPathsRecursive(treeNode* cur_node, int* pos_arr, chessPosArray*** Array) {


	int temp[ROWS*COLS];
	if (count_valid_children(&cur_node->position, pos_arr,Array) == 0) 	//break condition
	{
		//if the node has no children that didn't appear in the path
		// next positions(Children list) point to NULL and return

		cur_node->next_possible_positions = NULL;
	}

	else {
		// if there are possible location to travel to still..
		int letter = TurnLetterToArrPos((cur_node->position)[0]); // turn letter to array number
		int digit = TurnDigitCharToArrPos((cur_node->position)[1]); // turn digit char to digit int
		int pos = letter * COLS + digit;
		pos_arr[pos] = 1;

		cur_node->next_possible_positions = addChildrenList(&cur_node->position, pos_arr,Array); //add walkable children nodes
		treeNodeListCell* traverse = cur_node->next_possible_positions; // point to start of list
		copyBoard(temp, pos_arr); // save copy of array

		while (traverse != NULL)
		{
			findAllPossibleKnightPathsRecursive(traverse->node, temp, Array); // send empty children to next call
			copyBoard(temp, pos_arr); // restore the array to how it was before previous call
			traverse = traverse->next;
		}
		

	}

}

void copyBoard(int arr[],int * copy) {
	for (int i = 0; i < ROWS*COLS; i++)
	{
		arr[i] = copy[i];
	}
}



int count_valid_children(chessPos* startingPosition, int* check_arr, chessPosArray*** Array) {
	// function takes a chesspos* int arr and chessPosArray***,
	// function return the amount of children that are valid to walk to based on Array and check_arr

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

	return counter;
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
	checkMemoryAllocation(node);
	node->position[0] = (*pos)[0];
	node->position[1] = (*pos)[1];
	node->next_possible_positions = malloc(sizeof(treeNodeListCell));
	return node;
}




treeNodeListCell* addChildrenList(chessPos* pos, int* arr, chessPosArray*** Array) {
	// Function takes a pointer to a chess position
	// Function Retruns a pointer to the first element in a linked list
	// the memebers of the linked list are the possible positons a knight can move to from
	// the position given as the function argument

	int unUsedCounter = 0;
	int i = 0;


	int counter = 0;
	int letter = TurnLetterToArrPos((*pos)[0]); // turn letter to array number
	int digit = TurnDigitCharToArrPos((*pos)[1]); // turn digit char to digit int
	int list_size = Array[letter][digit]->size; // how many possible locations
	chessPosArray* posArr = Array[letter][digit];



	treeNodeListCell* head = NULL;
	if (count_valid_children(pos,arr,Array) == 0)
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

	removeDuplicatesChildren(head);
	return head;
}



void printTreeNode(treeNode* node) {
	// function takes a pointer to a tree node
	// function prints the node and it's children
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


void removeDuplicatesChildren(treeNodeListCell* start)
{
	treeNodeListCell* ptr1, * ptr2, * dup;
	ptr1 = start;

	/* Pick elements one by one */
	while (ptr1 != NULL && ptr1->next != NULL)
	{

		ptr2 = ptr1;

		/* Compare the picked element with rest
		   of the elements */
		while (ptr2->next != NULL)
		{

			if (comparePositions(ptr1->node->position, ptr2->next->node->position))
			{
				/* sequence of steps is important here */
				dup = ptr2->next;
				ptr2->next = ptr2->next->next;

			}
			else {
				ptr2 = ptr2->next;
			}
		}
		ptr1 = ptr1->next;
	}
}

void fill0(int arr[]) {
	for (int i = 0; i < ROWS * COLS; i++)
	{
		arr[i] = 0;
	}
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



