#include "Part5.h"


/////assist func to #5///////


void checkAllocation(void* ptr)
{
	//check if memory was successfully allocated
	if (ptr == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(1);
	}
}
/*need to connect "check allocation" func to "getBytesArr" */
Byte* getBytesArr(chessPosList* pos_list, int len, int* p_size) {

	int type = 0, bitIndex, indexOfBytesArr, chessPosIndex, diff; // type define`s if row or col.
	// bytesArrSize := compute the amount of bytes required.
	int bytesArrSize = (int)((len * 6) / 8) + ((len * 6) % 8 == 0 ? 0 : 1);
	Byte* bytesArr = (Byte*)calloc(bytesArrSize, sizeof(Byte));
	Byte inputMask = 0x7; // mask: 0000 0111
	checkAllocation(bytesArr);

	for (int nextEmptyBit = 0; nextEmptyBit < len * 6; nextEmptyBit += 3) {
		updateIndexs(nextEmptyBit, &bitIndex, &indexOfBytesArr, &chessPosIndex);
		diff = (type == 0 ? 'A' : 1);
		Byte temp = getByteFrom_chessPosList(chessPosIndex, type, *pos_list);
		temp -= diff;
		Byte input = temp & inputMask;
		if (bitIndex >= 2)
			bytesArr[indexOfBytesArr] |= (input << (bitIndex - 2));
		else {
			temp = (input >> (2 - bitIndex));
			bytesArr[indexOfBytesArr] |= temp;
			temp = (input << (6 + bitIndex));
			bytesArr[indexOfBytesArr + 1] |= temp;
		}
		type = (type == 1 ? 0 : 1);
	}

	*p_size = bytesArrSize;
	return bytesArr;
}

void updateIndexs(int nextEmptyBit, int* bitIndex, int* indexOfBytesArr, int* chessPosIndex) {

	*bitIndex = 7 - (nextEmptyBit % 8); // index of bit inside byte ( 0 is the less significant )
	*indexOfBytesArr = nextEmptyBit / 8;
	*chessPosIndex = nextEmptyBit / 6; // each chessPos use 6 bits
}

Byte getByteFrom_chessPosList(int listLocation, int  type, chessPosList lst) {

	chessPosCell* current = lst.head;
	int i = 0;

	while (i < listLocation) {
		current = current->next;
		i++;
	}

	return lst.head->position[type];

}

/*assist func to #5 but add to list file*/
int listLen(chessPosList* list) {

	int count = 0;
	chessPosCell* current = list->head;

	while (current != NULL) {
		current = current->next;
		count++;
	}

	return count;
}

//////////submit func #5////////
void saveListToBinFile(char* file_name, chessPosList* pos_list) {

	FILE* data = fopen(file_name, "wb");
	checkAllocation(data);

	int size = 0;
	short int len = listLen(pos_list);
	Byte* bytesArr = getBytesArr(pos_list, len, &size);

	fwrite(&len, sizeof(short int), 1, data);
	fwrite(bytesArr, sizeof(Byte), size, data);

	free(bytesArr);
	fclose(data);
}

