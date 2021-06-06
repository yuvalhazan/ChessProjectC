#include "Part7.h"



void main() {

    program_loop();
}


chessPos* get_knight_pos() {

    char letter, digit;
    bool validInput = false;
    chessPos* pos = malloc(sizeof(chessPos));
    checkMemoryAllocation(pos);
    

    while (validInput == false)
    {
        getchar();
        printf("Enter Letter ('A','B','C'...)\n");

        letter = getchar();

        getchar();
        printf("Enter Digit ('1','2','3'...)\n");

        digit = getchar();

        *pos[0] = letter;
        (*pos)[1] = digit;

        if (letter >= 'A' && letter <= 'A' +ROWS && digit >= '1' && digit <= '1' + ROWS)
        /*checking valid input*/
        {
            validInput = true;
        }
       
    }
    printf("You chose the position: ");
    printChessPos(pos);
    printf("\n");
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

char* getFileName() {
    /* Function takes nothing*/
    /* takes accepts from user a string of unknown length */
    char* str;
    int logSize = 0, phySize = 1;
    char c;

    str = (char*)malloc(sizeof(char) * phySize);
    checkMemoryAllocation(str);
    c = getchar();

    while (c != '\n')
    {
        if (logSize == phySize)
        {
            phySize *= 2;
            str = (char*)realloc(str, sizeof(char) * phySize);
        }

        str[logSize] = c;
        logSize++;
        c = getchar();
    }

    str = (char*)realloc(str, sizeof(char) * (logSize + 1));
    str[logSize] = '\0';

    return str;
}

void program_loop() {

    pathTree Tr;
    Tr.root = NULL;
    char choice;
    char* fileName;
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
                printf("Created a tree of all possible knight paths succesfully!\n");
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
            if (pos == NULL)
            {
                printf("You have to enter a position first!\n");
            }
            else
            {
                printFullKnightPath(path);
                saveListToBinFile("test.bin", path);
            }


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
            printf("please enter a valid choice from the menu \n");
        }
        choice = getchar();
    }
    return;
}