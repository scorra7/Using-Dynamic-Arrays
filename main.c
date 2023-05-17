/*  proj1Base.c

	Written 5/15/2023 by Steve Corral for CS 211, Summer 2023
	
	This program . . . 
	
	TODO:  Update this comment, including file name adjustment as needed
*/

#include <stdlib.h>
#include <stdio.h>


void copyArray(int fromArray[], int toArray[], int size) {
	for (int i = 0; i < size; i++) {
		toArray[i] = fromArray[i];
	}
}

// This will swap values a to values b, and vice versa
void swapValues(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
// This will partition the array from the pivot
int partition(int array[], int low, int high)
{
    int pivot = array[low]; // Places the pivot on index 0, or left-most index

    int afterPivot = high;
    for (int i = high; i > low; i--) {

        if (array[i] > pivot) {
            swapValues(&array[i], &array[afterPivot]);
			afterPivot--;
		}
    }
    swapValues(&array[low], &array[afterPivot]);
    return afterPivot;
}
 

void quickSort(int array[], int low, int high)
{
    if (low < high) {
        int pivotLocation = partition(array, low, high);

        quickSort(array, low, pivotLocation - 1);
        quickSort(array, pivotLocation + 1, high);
    }
}


int countMatches(int dynamicArray[], int sortedArray[], int size) {
	int count = 0;

	for (int i = 0; i < size; i++) {
		if (dynamicArray[i] == sortedArray[i]) {
			count++;
		}
	}

	return count;
}


int main( void ) {

	int val, *dynamicArray = NULL, allocatedMemory = 100, sizeOfArray = 0;
	
	/* allocating memory for dynamic array with initial size of 100 */
	dynamicArray = (int *) malloc(allocatedMemory * sizeof( int ) );

	/* Prompt the user for input */
	printf( "Enter in a list of numbers to be stored in a dynamic array.\n" );
	printf( "End the list with the terminal value of -999\n" );
	
	/* loop until the user enters -999 */
	scanf( "%d", &val );
	while( val != -999 ) {
		sizeOfArray += 1;

		/* Stores the value in the array */
		dynamicArray[sizeOfArray - 1] = val;

		/* Double the array size whenever more space is needed. */
		if (sizeOfArray == allocatedMemory) {
			int i, *tempArray = dynamicArray;

			allocatedMemory = allocatedMemory * 2;
			dynamicArray = (int*) malloc(allocatedMemory * sizeof(int));

			for (i = 0; i < sizeOfArray; i++) {
				dynamicArray[i] = tempArray[i];
			}

			free(tempArray);
			tempArray = NULL;
		}
		
		/* get next value */
		scanf( "%d", &val );
	}

	
	/* Creates a new array that will be used for sorting, and copies over the values from dynamicArray to the new array */
	int sortedArray[sizeOfArray];
	copyArray(dynamicArray, sortedArray, sizeOfArray);

	/* Call function to sort one of the arrays. */
	quickSort(sortedArray, 0, sizeOfArray - 1);

	/* Call function to count matches, and report results. */
	int numMatches = countMatches(dynamicArray, sortedArray, sizeOfArray);
	printf("Numbers already in sorted order = %d / %d = %.1f%%\n", numMatches, sizeOfArray, (((float)numMatches / sizeOfArray) * 100));
	
	/* Now check target numbers to see if they are in the list and where. */
	
	/* loop until the user enters -999 */
	printf( "Enter in a list of numbers to search for.  \n" );
	printf( "End the list with a terminal value of -999\n" );
	
	scanf( "%d", &val );	
	while( val != -999 ) {
		/* call function to perform target search operation */
		
		/* print out info about the target search results  */
		
		/* get next value */
		scanf( "%d", &val );
	}
	
	/* Final results could be printed here, such as the total # found, etc. */
	printf( "Good bye\n" );
	
	return 0;
} 
