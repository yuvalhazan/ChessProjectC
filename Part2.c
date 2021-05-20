#include "Part1.h"
#include "Part2.h"


//void main(){
//
//    chessPosList lst;
//    chessPosCell cell6= {{'E','1'},NULL};
//    chessPosCell cell5= {{'A','4'},&cell6};
//    chessPosCell cell4= {{'H','5'},&cell5};
//    chessPosCell cell3= {{'D','8'},&cell4};
//    chessPosCell cell2= {{'H','5'},&cell3};
//    chessPosCell cell1 = {{'A','4'},&cell2};
//
//
//    lst.head = &cell1;
//    lst.tail = &cell6;
//
//    display(&lst);
//
//}

void print_game_board(int rows, int cols, chessPosList* lst) {
    //Function takes 2D array gameBoard, int rows, int cols.
    //Function Prints The values of the array. (with some indexing to the lines)
    int i, j;
    printf("   "); //Visual
    for (i = 0; i < cols; i++) {
        printf("%d    ", i + 1);//print column index's under 9
    }

    printf("\n");

    for (j = 0; j < rows; j++) {
        printf(" ");
        for (i = 0; i < cols; i++) {
            if (i == cols - 1) {
                printf("+----+");
            }
            else {
                printf("+----");
            }
        }

        printRow(j, lst);

    }
    printf(" ");
    for (i = 0; i < cols; i++) {
        if (i == cols - 1) {
            printf("+----+");
        }
        else {
            printf("+----");
        }
    }
}
bool listHasInRow(chessPosList* lst, char row) {

    chessPosCell* ptr = lst->head;
    while (ptr != NULL) {
        if (ptr->position[0] == row) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

bool listHasCell(chessPosList* lst, char letter, char col, int* loc) {

    chessPosCell* ptr = lst->head;
    int counter = 1;
    while (ptr != NULL) {
        if (ptr->position[0] == letter && ptr->position[1] == (char)col + '0') {
            *loc = counter;
            return true;
        }
        ptr = ptr->next;
        counter++;
    }
    return false;
}



void printRow(int rowIndext, chessPosList* lst) {
    printf("\n");//Visual
    int i;
    int location;
    char letter = (int)('A' + rowIndext);
    if (listHasInRow(lst, letter)) {
        printf("%c|", letter);

        for (i = 0; i < COLS; i++) {
            if (listHasCell(lst, letter, i + 1, &location)) {
                printf("  %d |", location);
            }
            else {
                printf("    |");
            }
        }

        printf("\n");
    }
    else { //print blank row
        printf("%c|", letter);
        for (i = 0; i < COLS; i++) {
            printf("    |");
        }
        printf("\n");
    }



}

void display(chessPosList* lst) {
    /*Function recieves a pointer to a linked list of ChessPos's
    The Function Removes Duplicates and Prints the Positions
    In a ChessBoard Indexed by their location in the list*/

    removeDuplicates(lst->head);

    print_game_board(ROWS, COLS, lst);

}

void removeDuplicates(chessPosCell* start)
{
    chessPosCell* ptr1, * ptr2, * dup;
    ptr1 = start;

    /* Pick elements one by one */
    while (ptr1 != NULL && ptr1->next != NULL)
    {

        ptr2 = ptr1;

        /* Compare the picked element with rest
           of the elements */
        while (ptr2->next != NULL)
        {

            if (comparePositions(ptr1->position, ptr2->next->position))
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

bool comparePositions(chessPos pos1, chessPos pos2) {

    return (pos1[0] == pos2[0] && pos1[1] == pos2[1]);

}




