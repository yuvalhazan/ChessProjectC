#include "Part7.h"

void print_menu();
chessPos* get_knight_pos();
void program_loop();

void main() {

    program_loop();
}

chessPos* get_knight_pos() {

    char letter, digit;
    chessPos* pos = malloc(sizeof(chessPos));
    checkMemoryAllocation(pos);
    getchar();
    printf("Enter Letter ('A','B','C'...)\n");
    letter = getchar();
    getchar();
    printf("Enter Digit ('1','2','3'...)\n");

    digit = getchar();

    *pos[0] = letter;
    (*pos)[1] = digit;
    printf("You chose the position: ");
    printChessPos(pos);
    return pos;
}

void print_menu() {

    printf("1. Enter a knight's starting position\n");
    printf("2. Create all possible knight paths\n");
    printf("3. Find a knight path covering all board\n");
    printf("4. Save knight path covering all board to file\n");
    printf("5. Load and display path from file\n");
    printf("6. Exit\n");
}

void program_loop() {

    pathTree Tr;
    Tr.root = NULL;
    char choice;
    chessPos* pos = NULL;
    chessPosList* path = NULL;
    print_menu();
    choice = getchar();
    while (true)
    {
        if (choice == '1')
        {
            pos = get_knight_pos();
        }
        else if (choice == '2') {
            if (pos == NULL)
            {
                printf("You have to enter a position first!\n");
            }
            else {
                Tr = findAllPossibleKnightPaths(pos);
            }
        }
        else if (choice == '3') {
            if (pos == NULL)
            {
                printf("You have to enter a position first!\n");
            }
            else if (Tr.root != NULL)
            {
                path = findKnightPathCoveringAllBoard(&Tr);
            }
            else {
                Tr = findAllPossibleKnightPaths(pos);
                path = findKnightPathCoveringAllBoard(&Tr);
            }
        }
        else if (choice == '4') {
            printf("Not implemented yet!\n");
            break;
        }
        else if (choice == '5') {
            printf("Not implemented yet!\n");
            break;
        }
        else if (choice == '6') {
            printf("Exiting program thank you for using!\n");
            break;
        }
        else {
            printf("please enter a valid choice\n");
        }
        choice = getchar();
    }
    return;
}