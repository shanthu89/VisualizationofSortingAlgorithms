#include <sys/resource.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Function to copy array locally from the given Input array for each sort.
int *CopytoArray(int *inputArray, int len) {
	int *b = malloc(len * sizeof(int));
	int i;
		for (i = 0; i <= len - 1; i++) {
		b[i] = inputArray[i];

	}
	return b;
}

//Swap Function to swap numbers.
int swap(int *array ,int copyTo,int copyFrom)
{
		//printf("Swapping %d, %d\n", copyTo, copyFrom);
		int temp;
		temp=array[copyTo];
		array[copyTo]=array[copyFrom];
		array[copyFrom]=temp;
		PrintOutputArray(array,30);
		return 0;
}

//Print Function to print result
int PrintOutputArray(int *a, int len) {
	int i;
	return 1;
	for (i = 0; i < len; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}

//Bubble Sort Function
int BubbleSort(int *inputArray, int len) {
	int *array = CopytoArray(&inputArray[0], len);
	int count = 0,swapCount=0;
	int i, j;
	int postionToFill;
	for (j = 0; j < len; j++) {
		postionToFill = len - j - 1;
		//printf("Position filled:%d  ", postionToFill);
		//int numIfs = 0;
		for (i = 0; i < postionToFill; i++) {
			count++;
			//numIfs++;
			if (array[i] > array[i + 1]) {
				swapCount++;
				swap(array,i,i+1);
			}
			//printf("loop:%d ", a[i]);
		}
		//printf("numIfs:%d \n", numIfs);
	}
	//printf("\nBubble Sort\n");
	printf("swapCount:%d\n", swapCount);
	//printf("Sorted array: ");
	PrintOutputArray(array, len);
	free(array);
	return 0;
}

//Insertion Sort Function
int InsertionSort(int *inputArray, int len) {
	int *array = CopytoArray(&inputArray[0], len);
	//printf("Input array\n");
	//PrintOutputArray(array, len);
	//printf("\n");
	int i, j, count = 0,swapCount=0;
	for (i = 0; i < len; i++) {
		j = i;
		while (j > 0) {
			if(array[j] > array[j - 1]) {
				break;
			}
			count++;
			if (array[j] != array[j-1]) {
				swapCount++;
				swap(array,j,j-1);
			}
			j--;
		}
	}
	//printf("\nInsertion Sort\n");
	printf("swapCount:%d \n", swapCount);
	//printf("Sorted array: ");
	PrintOutputArray(array, len);
	free(array);
	return 0;

}

//Selection Sort Function
int SelectionSort(int *inputArray, int len) {
	int *array = CopytoArray(inputArray, len);
	int i, j,count=0,swapCount=0;
	int minIndex;
	for (i = 0; i < len; i++) {
		minIndex = i;
		for (j = i + 1; j < len; j++) {
			count++;
			if (array[minIndex] > array[j]) {
				minIndex = j;
			}
		}
		if(minIndex!=i){
			swapCount++;
			swap(array,i,minIndex);
		}
		PrintOutputArray(array, len);
	}
	//printf("\nSelection Sort\n");
	printf("swapCount:%d \n", swapCount);
	//printf("Sorted array: ");
	PrintOutputArray(array, len);
	free(array);
	return 0;
}

int mergeSortInversions = 0;
//Merge sort helper function to merge arrays after splitting and sorting
void MergeSortInternal(int *array, int left, int right, const int length) {
	if (left >= right) {
		return;
	}
	//printf("left: %d, right: %d\n", left, right);
	int mid=(left+right)/2;
	MergeSortInternal(array, left, mid, length);
	MergeSortInternal(array, mid+1, right, length);

	//printf("Merging.. ");
	//PrintOutputArray(array+left, mid-left+1);
	//PrintOutputArray(array+mid+1, right-mid);
	//printf(".. \n");
	//int *outputTemp = malloc(sizeof(int) * (right-left+1));
	int* outputTemp = CopytoArray(array, length);
	int i = left;
	int j = mid+1;
	int outputIndex = left;
	for (outputIndex = left; outputIndex < right+1/*-left+1*/; outputIndex++)
	{
		if (i > mid) {
			// left array over
			outputTemp[outputIndex] = array[j++];
		}
		else if (j > right) {
			//printf("Elements in right array: %d\n", right-mid-1);
			mergeSortInversions += (j-mid-1);
			// right array over
			outputTemp[outputIndex] = array[i++];
		}
		else if (array[i] <= array[j]) {
			mergeSortInversions += (j-mid-1);
			outputTemp[outputIndex] = array[i++];
		} else {
			outputTemp[outputIndex] = array[j++];
		}
		//PrintOutputArray(outputTemp, /*right-left+1*/ length);
	}

	//PrintOutputArray(&outputTemp[0], right-left+1);
	int k;
	for (i=left; i<=right; i++, k++)
	{
		array[i] = outputTemp[i];
	}
	PrintOutputArray(array, length);

}
//Merge sort function
int MergeSort(int* inputArray, int len) {
	int *array = CopytoArray(inputArray, len);
	mergeSortInversions = 0;
	//PrintOutputArray(array, len);
	MergeSortInternal(array, 0, len-1, len);


	//printf("\nMerge Sort\n");
	printf("swapCount:%d \n", mergeSortInversions);
	//printf("Sorted array: ");
	//PrintOutputArray(array, len);
	free(array);
	return 0;
}



int quickSortSwapCount = 0;
// Quick sort helper function that partition array and returns pivot position
int QuickSortPartition(int* array, int left, int right) {
	if (left >= right) {
		return left;
	}
	int pivotNum = array[left];
	int i=left+1;
	int j=right;
	while (i<=j) {
		while (i<=j && array[i] <= pivotNum) i++;
		while (i<=j && array[j] > pivotNum) j--;
		if (i<j) {

			if (array[i] != array[j]) {
				quickSortSwapCount++;
				swap(array, i, j);
			}
		}
	}
	if (i-1 != left)
	{
		if (array[i-1] != array[left])
		{
			swap(array, i-1, left);
			quickSortSwapCount++;
		}
	}
	return i-1;
}
//Actual Quick sort function - recursive
int QuickSortInternal (int* array, int left, int right) {
	if (left >= right) {
		return 0;
	}
	int pivot = QuickSortPartition(array, left, right);
	QuickSortInternal(array, left, pivot-1);
	QuickSortInternal(array, pivot+1, right);
	return 0;
}
//Wrapper around Quick sort function for memory management
int QuickSort(int* inputArray, int len) {
	int *array = CopytoArray(inputArray, len);
	quickSortSwapCount = 0;
	QuickSortInternal(array, 0, len-1);
	//printf("\nQuick Sort\n");
	printf("swapCount:%d \n", quickSortSwapCount);
	//printf("Sorted array: ");
	PrintOutputArray(array, len);
	free(array);
	return 0;
}

//Function to read the input elements from file.
int *GetinputArray(char* filename, int inputSize){
	FILE *fp;
	int *a = malloc(inputSize * sizeof(int));
	//int a[inputSize];
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error reading fileL %s\n", filename);
		exit(0);
	}
	int i = 0, j = 0;
	int completed = 0;
	while (j<inputSize) {
		completed = fscanf(fp, "%d", &i);
		if (completed == EOF){
			break;
		}
		a[j] = i;
		j++;
	}
	fclose(fp);
	return a;
}

// Count inversions. Brute force
int sortednessPercent(const int* array, int len)
{
    long double inversions = 0;
    int i, j;
    for (i=0; i<len; i++) {
        for (j=i+1; j<len; j++) {
            if (array[i] > array[j])
                inversions++;
        }
    }
    long double normalizationFactor = 1.0 * len * (len-1) / 2;  //normalizing the inversion count calculated to value between 0 to 1.
    return 100*(1- (1.0 * inversions)/normalizationFactor);     // calculating sortedness in percentage 
}

//Function to run all sorts with various sortedness measure
void runAllSorts(int* inputArray, int inputSize, int sortedness)

{
	printf("BubbleSort\n");
	BubbleSort(inputArray, inputSize);
	printf("InsertionSort\n");
	InsertionSort(inputArray, inputSize);
	printf("SelectionSort\n");
	SelectionSort(inputArray, inputSize);
	printf("MergeSort\n");
	MergeSort(inputArray, inputSize);
	printf("QuickSort\n");
	QuickSort(inputArray, inputSize);

/*	clock_t begin, end; // to measure time
	struct rusage begin_usage, end_usage; // to measure heap memory usage

	getrusage(RUSAGE_SELF,&begin_usage); //Function for memory usage calculation
	BubbleSort(inputArray, inputSize);
	end = clock();                        //Clock to measure execution time of functions
	double bubbleSortTime = (double)(end - begin);
	getrusage(RUSAGE_SELF,&end_usage);
	long bubbleMem = end_usage.ru_maxrss - begin_usage.ru_maxrss;

	begin = clock();
	getrusage(RUSAGE_SELF,&begin_usage);
	InsertionSort(inputArray, inputSize);
	end = clock();
	double insertionSortTime = (double)(end - begin);
	getrusage(RUSAGE_SELF,&end_usage);
	long insertionMem = end_usage.ru_maxrss - begin_usage.ru_maxrss;

	getrusage(RUSAGE_SELF,&begin_usage);
	begin = clock();
	SelectionSort(inputArray, inputSize);
	end = clock();
	double selectionSortTime = (double)(end - begin);
	getrusage(RUSAGE_SELF,&end_usage);
	long selectionMem = end_usage.ru_maxrss - begin_usage.ru_maxrss;

	getrusage(RUSAGE_SELF,&begin_usage);
	begin = clock();
	MergeSort(inputArray, inputSize);
	end = clock();
	double mergeSortTime = (double) (end - begin);
	getrusage(RUSAGE_SELF,&end_usage);
	long mergeMem = end_usage.ru_maxrss - begin_usage.ru_maxrss;

	getrusage(RUSAGE_SELF,&begin_usage);
	begin = clock();
	QuickSort(inputArray, inputSize);
	end = clock();
	double quickSortTime = (double) (end - begin);// / CLOCKS_PER_SEC;
	getrusage(RUSAGE_SELF,&end_usage);
	long quickMem = end_usage.ru_maxrss - begin_usage.ru_maxrss;


	printf("%d,%d,%.f,%.f,%.f,%.f,%.f\n",inputSize, sortedness, 
			bubbleSortTime/1000, 
			insertionSortTime/1000, 
			selectionSortTime/1000, 
			mergeSortTime/1000,
			quickSortTime/1000);


	printf("%d,%d,%ld,%ld,%ld,%ld,%ld\n",inputSize, sortedness, 
			bubbleMem, 
			insertionMem, 
			selectionMem, 
			mergeMem,
			quickMem);*/
}
//Function to run all sorts with different dataset sizes
void runWithVaryingInputSize(int* inputArray, int maxLength, int sortedness)
{
	//int inputSizes[] = {15};//{50, 100, 1000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000};
	//int count = sizeof(inputSizes)/sizeof(int);

	int i;
	//for (i = 0; i < count; i++)
	{
		//int inputSize = inputSizes[i];
		runAllSorts(inputArray, /*inputSize*/maxLength, sortedness);
	}
}

void runWithVaryingSortedness(int* inputArray, int inputSize)
{
	// sort initially before adjusting sortedness
	QuickSortInternal(inputArray, 0, inputSize-1);

	int iterationLimit = 10;
	int iterationCount = 0;
	int swapMultiplier = inputSize/iterationLimit/2;
	for (iterationCount = 0; iterationCount < iterationLimit+1; iterationCount++)
	{
		//int sortedness = sortednessPercent(inputArray, inputSize);
		//printf("Sortedness percent: %d\n", sortedness);
		runAllSorts(inputArray, inputSize, -3);

		// Shuffling array
		int m=0;
		for (m=0; m<swapMultiplier; m++) {
			int i1 = (iterationCount * swapMultiplier)+m;
			int j1 = inputSize-((iterationCount*swapMultiplier)+m+1);
			swap(inputArray, i1, j1);
		}
	}
}

int main(int argc, char **argv) {

	if (argc != 3) {
		printf("Please supply file name and input size. \n Usage: Sort.exe C:\\DummyPath\\data.txt 1000");
		return -1;
	}
	char* filename = argv[1];

	int inputSize=atoi(argv[2]);
	//int inputSize=100000;

	int *inputArray=GetinputArray(filename, inputSize);
	//int originalSortedness = sortednessPercent(inputArray, inputSize);
	//printf("Original sortedness: %d\n", originalSortedness);
	//runWithVaryingSortedness(inputArray, inputSize);
	runWithVaryingInputSize(inputArray, inputSize, 0);//, originalSortedness);
	return 0;
	free(inputArray);
}


