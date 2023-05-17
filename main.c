/**
 *	@name 		main.c
 *	@date 		5/15/2023
 *	@author 	Steve Corral
 *	@UIN 		674006479
 *	@class 		CS 211
 *	@Semester	Summer 2023
 *
 *
 *	@brief 		This program takes in integer values, and puts them into a dynamic array.
 *				Then the dynamic array is copied into a second array. This second array will
 *				then be sorted using the quicksort algorithm. Afterwards, the orignal dynamic
 *				array and the sorted array are checked to see how many values match. Finally,
 *				we check to see if the target value is in the array, and if it is then we also
 *				check if it is in a correctly sorted position. If it is, then we print out the
 *				first matching position of the target value.
 */

#include <stdlib.h>
#include <stdio.h>

/***
 * @brief 			copies the values from the orginal array into a new one
 *
 * @param fromArray is the original array with values
 * @param toArray 	is the new empty array
 * @param size 		is the size of the array
 */
void copyArray(int fromArray[], int toArray[], int size)
{
	for (int i = 0; i < size; i++)
	{
		toArray[i] = fromArray[i];
	}
}

/***
 * @brief 		This will swap the values of a and b
 *
 * @param a 	is the first value
 * @param b 	is the second value
 */
void swapValues(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/***
 * @brief 		This will move all the values that are larger than the pivot
 * 				to the right, and all the smaller values to the left
 *
 * @param array will be the sorted array that we are using
 * @param low 	will be the lowest index in the array, which would be 0
 * @param high 	will be the highest index, which will change depending on the
 * 				level in the recursion of quicksort() we're at
 *
 * @return int 	will return the position of the pivot after all the swapping
 */
int partition(int array[], int low, int high)
{
	int pivot = array[low]; // Places the pivot on index 0, or left-most index

	int afterPivot = high; // this will be for the numbers higher than the current
						   // pivot

	for (int i = high; i > low; i--)
	{

		if (array[i] > pivot)
		{
			swapValues(&array[i], &array[afterPivot]);
			afterPivot--;
		}
	}
	swapValues(&array[low], &array[afterPivot]);
	return afterPivot;
}

/***
 * @brief 		This algorithm will use recursion in order to sort the array.
 * 				It will first partition the array, so the pivot is in the correct
 * 				position. Then it will go into two recursive calls, the first one
 * 				will partition everything to the left of the pivot, and the second
 * 				will do the same but for the right of the pivot. Once all these
 * 				partitions are done, then the array will be sorted.
 *
 * @param array the array that we want to sort
 * @param low 	this will be the lowest index in the array at first, however will
 * 				change as we go deeper in the recursive call
 * @param high 	this will be the highest index in the array at frst, but will
 * 				change as we go deeper in the recursive call
 */
void quickSort(int array[], int low, int high)
{
	if (low < high)
	{
		int pivotLocation = partition(array, low, high);

		quickSort(array, low, pivotLocation - 1);
		quickSort(array, pivotLocation + 1, high);
	}
}

/***
 * @brief 				counts the amount of values in the two arrays which match
 *
 * @param dynamicArray	this is the orignal unsorted array
 * @param sortedArray	this is the new sorted array
 * @param size			this is the size of both arrays
 *
 * @return int			will return the count
 */
int countMatches(int *dynamicArray, int *sortedArray, int size)
{
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		if (*(dynamicArray + i) == *(sortedArray + i))
		{
			count++;
		}
	}

	return count;
}

/**
 * @brief 				Determines wheter the target array is: in the list and in the
 * 						correctly sorted position; in the list but not in the correct
 * 						position; or not in the list at all.
 *
 * @param dynamicArray 	this is the original unsorted array
 * @param sortedArray 	this is the new sorted array
 * @param size 			this is the size of both arrays
 * @param target 		this is the target value
 * @param nfound 		this is the count for the amount of times the target appears
 * 						in the list
 * @param index 		this is the index for the correctly sorted position of the
 * 						target
 * @return int 			will return 1, 0, or -1 depending on the nfound and index
 */
int findInList(int *dynamicArray, int *sortedArray, int size, int target, int *nfound, int *index)
{
	int indexMatchCount = 0;

	for (int i = 0; i < size; i++)
	{
		if (*(sortedArray + i) == target)
		{
			(*nfound)++;

			if (*(sortedArray + i) == *(dynamicArray + i) && indexMatchCount == 0)
			{
				(*index) = i + 1;
				indexMatchCount++;
			}
		}
	}

	if (*index > -1)
	{
		return 1;
	}
	else if (*nfound > 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int main(void)
{

	int val, *dynamicArray = NULL, allocatedMemory = 100, sizeOfArray = 0;

	/* allocating memory for dynamic array with initial size of 100 */
	dynamicArray = (int *)malloc(allocatedMemory * sizeof(int));

	/* Prompt the user for input */
	printf("Enter in a list of numbers to be stored in a dynamic array.\n");
	printf("End the list with the terminal value of -999\n");

	/* loop until the user enters -999 */
	scanf("%d", &val);
	while (val != -999)
	{
		sizeOfArray += 1;

		/* Stores the value in the array */
		dynamicArray[sizeOfArray - 1] = val;

		/* Double the array size whenever more space is needed. */
		if (sizeOfArray == allocatedMemory)
		{
			int i, *tempArray = dynamicArray;

			allocatedMemory = allocatedMemory * 2;
			dynamicArray = (int *)malloc(allocatedMemory * sizeof(int));

			for (i = 0; i < sizeOfArray; i++)
			{
				*(dynamicArray + i) = *(tempArray + i);
			}

			free(tempArray);
			tempArray = NULL;
		}

		/* get next value */
		scanf("%d", &val);
	}

	/* Call function to copy over the values from original array to the new array */
	int sortedArray[sizeOfArray];
	copyArray(dynamicArray, sortedArray, sizeOfArray);

	/* Call function to sort one of the arrays. */
	quickSort(sortedArray, 0, sizeOfArray - 1);

	/* Call function to count matches, and report results. */
	int numMatches = countMatches(dynamicArray, sortedArray, sizeOfArray);
	printf("\nNumbers already in sorted order = %d / %d = %.1f%%\n\n", numMatches, sizeOfArray, (((float)numMatches / sizeOfArray) * 100));

	/* Now check target numbers to see if they are in the list and where. */
	/* loop until the user enters -999 */
	printf("Enter in a list of numbers to search for.  \n");
	printf("End the list with a terminal value of -999\n");

	scanf("%d", &val);
	while (val != -999)
	{
		/* call function to perform target search operation */
		int index = -1, nfound = 0, result = findInList(dynamicArray, sortedArray, sizeOfArray, val, &nfound, &index);
		/* print out info about the target search results  */
		printf("Target: %d = ", val);

		if (result == 1)
		{
			printf("Present %d time(s) and in order. First match at position %d.", nfound, index);
		}
		else if (result == 0)
		{
			printf("Present %d time(s) but not in order.", nfound);
		}
		else
		{
			printf("Not even in the list!");
		}

		printf("\n");
		/* get next value */
		scanf("%d", &val);
	}

	/* Final results could be printed here, such as the total # found, etc. */
	printf("Good bye\n");

	return 0;
}
