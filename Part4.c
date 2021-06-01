#include "Part4.h"



//void main() {
//
//    pathTree Tr;
//    chessPos A2 = { 'A','1' };
//    chessPosList* ls;
//
//    
//    printf("---------MAIN------\n");
//    
//    
//    Tr = findAllPossibleKnightPaths(&A2);
//    ls = findKnightPathCoveringAllBoard(&Tr);
//    printFullKnightPath(ls);
//}

void printFullKnightPath(chessPosList* ls) {
    chessPosCell* traverse;
    if (ls == NULL)
    {
        printf("The path does not exist\n");
        return;
    }
    traverse = ls->head;
    int i = 1;
    printf("--Start--\n");
    while (traverse != NULL)
    {
        printChessPos(traverse->position);
        if (traverse->next == NULL)
        {
            printf("\n--END--\n");
        }
        else if (i%5 == 0)
        {
            printf("->\n");
        }
        else {
            printf("->");
        }
        traverse = traverse->next;
        i++;
    }

}

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree) {
    // function takes a pointer to PathTree
    // function checks if there is a path in the tree from the root that covers the entire board
    // if yes return pointer to the list of position else return NULL

    chessPosList* ls;
    int max_level;
    chessPosCell* traverse;
    ls = malloc(sizeof(chessPosList));
    ls->head = findKnightPathCoveringAllBoardHelper(path_tree->root, 1, &max_level);
    if (max_level < COLS*ROWS)
    {
        // if the biggest path in the tree is less than ROWS*COLS it isn't a full path return NULL
        return NULL;
    }
    traverse = ls->head; // point to start of list
    while (traverse->next != NULL)
    {
        traverse  = traverse->next;
    }
    ls->tail = traverse;

    return ls;

}

chessPosCell* findKnightPathCoveringAllBoardHelper(treeNode* cur_node,int level,int * maxLevel) {

    level++;
    chessPosCell* cell = malloc(sizeof(chessPosCell));
    int child_amt, max = -1;
    chessPosCell** arr;

    if (cur_node->next_possible_positions == NULL)
    {
        cell->position[0] = cur_node->position[0];
        cell->position[1] = cur_node->position[1];
        cell->next = NULL;
        return cell;
    }

    treeNodeListCell* traverse = cur_node->next_possible_positions; // point to start of list
    child_amt = CountChildrenInNode(traverse);
    arr = malloc(sizeof(chessPosCell*) * child_amt);
    for (int i = 0; i < child_amt; i++)
    {
        arr[i] = malloc(sizeof(chessPosCell));
        arr[i]->position[0] = cur_node->position[0];
        arr[i]->position[1] = cur_node->position[1];
        arr[i]->next = findKnightPathCoveringAllBoardHelper(traverse->node, level,maxLevel);
        traverse = traverse->next;
    }
    for (int i = 0; i < child_amt; i++)
    {

        if (len_list(arr[i]) > max){
            max = len_list(arr[i]);
            cell = arr[i];
        }

    }
    if (level > *maxLevel){
        *maxLevel = level;
    }
    
    return cell;

}


int len_list(chessPosCell* cell) {
    // function takes a pointer to chessPosCell
    // funtion counts how many items linked until NULL

    int counter = 0;
    while (cell != NULL)
    {
        counter++;
        cell = cell->next;
    }
    return counter;
}

int CountChildrenInNode(treeNodeListCell* traverse) {
    // function takes a pointer to treeNodeListCell
    // funtion counts how many items linked until NULL
    int counter = 0;
    while (traverse != NULL)
    {
        counter++;
        traverse = traverse->next;
    }
    return counter;

}

