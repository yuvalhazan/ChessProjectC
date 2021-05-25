#ifndef _part4_h
#define _part4_h

#include "Part3.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
chessPosCell* findKnightPathCoveringAllBoardHelper(treeNode* cur_node, int level, int* maxLevel);
int CountChildrenInNode(treeNodeListCell* traverse);
int len_list(chessPosCell* cell);
void printFullKnightPath(chessPosList* ls);

#endif