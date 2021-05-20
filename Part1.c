#include "Part1.h"
//void main(){
//
// chessPosArray*** Array;
// Array = validKnightMoves();
//
//
// printAllPosInSquare(Array[0][0]);
//}


chessPosArray*** validKnightMoves() {
    /*Function takes no arguments and returns a 2d-array of pointers.
    These pointers point to an array of possible Postisions for a knight to move to.*/

    chessPosArray*** Result = createEmptyArr3dArr(); //allocate memory for the array
    int i, j;


    for (i = 0; i < ROWS; i++) { //loop over an 8x8 board
        for (j = 0; j < COLS; j++) {
            *(Result[i] + j) = PositionsForSlot(i, j); //fill each position in the array with the values
        }
    }

    return Result;
}


chessPosArray*** createEmptyArr3dArr() {
    /*Function takes no arguments, the function then allocates memory for
    a 2d array of pointers to  a*Chessposarray */

    chessPosArray*** Result = (chessPosArray***)malloc(COLS * sizeof(chessPosArray**)); // allocate memory for the "columns"

    int count = 0;
    while (count < COLS)
    {
        Result[count] = (chessPosArray**)malloc(ROWS * sizeof(chessPosArray*)); // allocate memory for the "Rows"
        count++;
    }

    return Result;

}



chessPosArray* PositionsForSlot(int row, int col) {
    /*Function takes two integers row & col both between 0-7
      Function creates a chessPosArray and fills it with valid values
      based on row and col. The function returns the array in created.*/

    chessPosArray* pos_array = (chessPosArray*)malloc(sizeof(chessPosArray)); //allocate memory 
    checkMemoryAllocation(pos_array); // check allocation

    char letter = (char)(row + 65); // convert row int to a letter
    char digit = (char)(col + '1'); // convert col int to a digit

     //printf("for the position:(%c,%c)\n\n",letter,digit); //(FOR TESTING)


    int moves[] = // an array of values the knight can move in
    { 2,1,
      1,2,
      -1,2,
      -2,1,
      -2,-1,
      -1,-2,
      1,-2,
      2,-1 };

    int i;
    int counter = 0;

    pos_array->positions = (chessPos*)malloc(sizeof(chessPos) * 9); // allocate memory for the positions
    checkMemoryAllocation(pos_array->positions); // check allocation

    chessPos* ptr = pos_array->positions;

    for (i = 0; i < 15; i = i + 2) { // Test which moves are valid 
        if (is_Valid_Location(row + moves[i], col + moves[i + 1])) {

            char letter = (char)((row + moves[i]) + 65);
            char digit = (char)((col + moves[i + 1]) + '1');

            counter++;
            //printf("%c,%c valid move\n",letter,digit);

            insertPositionToArray(ptr, letter, digit); // if it's a valid move insert it to the array
            ptr++; // move pointer forward
        }
    }


    //pos_array->positions = (chessPos*) realloc(pos_array->positions, counter);
    pos_array->size = counter;


    return pos_array;
}

bool is_Valid_Location(int row, int col) {
    // Returns true if row number and column number
    // is in range

    return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLS);

}



void printAllPosInSquare(chessPosArray* posArr) {
    /*takes a pointer to a chessposArray and prints the
     positions the knight can move from this specific position*/

    int arr_size = posArr->size;
    int i;
    for (i = 0; i < arr_size; i++) {
        printChessPos(posArr->positions + i);
    }
}

void printChessPos(chessPos* ptr) {
    /*takes a pointer to a chesspos and prints the values*/
    if (ptr == NULL)
    {
        printf("Chess Position points to NULL");
    }
    else {
        printf("(%c,%c) ", (*ptr)[0], (*ptr)[1]);

    }
}



void insertPositionToArray(chessPos* ptr, char letter, char digit) {
    //takes pointer to a chess pos and two values.. puts them in the chess pos
    (*ptr)[0] = letter;
    (*ptr)[1] = digit;
}

void checkMemoryAllocation(void* ptr)
{
    //check if memory was successfully allocated
    if (ptr == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

