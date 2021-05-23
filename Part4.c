#include "Part3.h"
#include "PseudoBoard.h"
void find(treeNode* root, int level, int* maxLevel);

//void main() {
//
//    pathTree Tr;
//    chessPos A2 = { 'C','3' };
//    
//    
//    printf("---------MAIN------\n");
//    
//    
//    Tr = findAllPossibleKnightPaths(&A2);
//    treeNode* root = Tr.root;
//    int max = -1;
//    find(root, 0, &max);
//    printf("max: %d", max);
//}

//chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree) {
//
//}


void find(treeNode* root, int level, int* maxLevel)
{
    level++;
    if (root != NULL)
    {
        treeNodeListCell* traverse = root->next_possible_positions; // point to start of list
        
        while (traverse != NULL)

        {
            find(traverse->node, level, maxLevel);

            traverse = traverse->next;
        }
        
        // Update level and resue
        if (level > *maxLevel)
        {
            
            *maxLevel = level;

        }
    }
}