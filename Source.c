#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#define N 10000

void ExchangeSort(int*);
void SelectionSort(int*);
void InsertionSort(int*);
void BubbleSort(int*);
void QuickSort(int*, int, int);
void MergeSort(int*, int, int);
void ShellSort(int*, int);
void CopyArray(int*, int*);
void RandomGenerate(int*);
int partition(int*, int, int);
void swap(int*, int, int);
int FindMax(int*, int);

int main()
{
	clock_t start, stop;
	int array[N] = { 0 };
	int copy[N] = { 0 };

	RandomGenerate(array);
	CopyArray(array, copy);

	start = clock();
	ExchangeSort(array);
	stop = clock();
	printf("Approx seconds, tenths, hundredths and milliseconds: %.3f\n", ((double)(stop - start) / CLOCKS_PER_SEC));

	CopyArray(copy, array);

	start = clock();
	SelectionSort(array);
	stop = clock();
	printf("Approx seconds, tenths, hundredths and milliseconds: %.3f\n", ((double)(stop - start) / CLOCKS_PER_SEC));

	CopyArray(copy, array);

	start = clock();
	InsertionSort(array);
	stop = clock();
	printf("Approx seconds, tenths, hundredths and milliseconds: %.3f\n", ((double)(stop - start) / CLOCKS_PER_SEC));

	CopyArray(copy, array);

	start = clock();
	BubbleSort(array);
	stop = clock();
	printf("Approx seconds, tenths, hundredths and milliseconds: %.3f\n", ((double)(stop - start) / CLOCKS_PER_SEC));

	CopyArray(copy, array);

	start = clock();
	ShellSort(array, N);
	stop = clock();
	printf("Approx seconds, tenths, hundredths and milliseconds: %.3f\n", ((double)(stop - start) / CLOCKS_PER_SEC));

	CopyArray(copy, array);

	start = clock();
	QuickSort(array, 0, N - 1);
	stop = clock();
	printf("Approx seconds, tenths, hundredths and milliseconds: %.3f\n", ((double)(stop - start) / CLOCKS_PER_SEC));

	CopyArray(copy, array);

	start = clock();
	MergeSort(array, 0, N - 1);
	stop = clock();
	printf("Approx seconds, tenths, hundredths and milliseconds: %.3f\n", ((double)(stop - start) / CLOCKS_PER_SEC));

	return 0;
}

void CopyArray(int* source, int* destination)
{
	int i = 0;
	for (i = 0; i < N; i++)
	{
		destination[i] = source[i];
	}

}

void RandomGenerate(int* array)
{
	int i = 0;
	time_t t;
	srand((unsigned)time(&t));
	for (i = 0; i < N; i++)
	{
		array[i] = rand();
	}
}

void ExchangeSort(int* array)
{
	int i, j, temp;
	for (i = 0; i < N - 1; i++)
	{
		for (j = i + 1; j < N; j++)
		{
			if (array[i] > array[j])
			{
				swap(array, j, i);
			}
		}
	}
}

void SelectionSort(int* array)
{
	int i, max;
	for (i = 0; i < N; i++)
	{
		max = FindMax(array, i);
		swap(array, max, (N - 1 - i));
	}
}

void BubbleSort(int* array)
{
	int i, j;
	for (i = 0; i < N - 1; i++)
	{
		for (j = 0 + 1; j < N; j++)
		{
			if (array[i] > array[j])
			{
				swap(array, j, i);
			}
		}
	}
}

int FindMax(int* array, int high)
{
	int i, index;
	index = high;
	for (i = high; i < N; i++)
	{
		if (array[i] > array[index])
			index = i;
	}
	return index;
}

void swap(int* array, int p1, int p2)
{
	int temp;
	temp = array[p2];
	array[p2] = array[p1];
	array[p1] = temp;
}

void InsertionSort(int* array)
{
	int i, key, j;
	for (i = 1; i < N; i++)
	{
		key = array[i];
		j = i - 1;

		while (j >= 0 && array[j] > key)
		{
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = key;
	}
}

int partition(int array[], int low, int high) {

	// Initialize pivot to be the first element
	int p = array[low];
	int i = low;
	int j = high;

	while (i < j) {

		// Find the first element greater than
		// the pivot (from starting)
		while (array[i] <= p && i <= high - 1) {
			i++;
		}

		// Find the first element smaller than
		// the pivot (from last)
		while (array[j] > p && j >= low + 1) {
			j--;
		}
		if (i < j) {
			swap(array, i, j);
		}
	}
	swap(array, low, j);
	return j;
}


void QuickSort(int array[], int low, int high) {
	if (low < high) {

		// call partition function to find Partition Index
		int pi = partition(array, low, high);

		// Recursively call quickSort() for left and right
		// half based on Partition Index
		QuickSort(array, low, pi - 1);
		QuickSort(array, pi + 1, high);
	}
}

void ShellSort(int a[], int b)
{
	/* Rearranging the elements of array at n/2, n/4, ..., 1 intervals */
	for (int interval = b / 2; interval > 0; interval /= 2)
	{
		for (int i = interval; i < b; i += 1)
		{
			/* store a[i] to the tempvar variable and make the ith position empty */
			int tempvar = a[i];
			int j;
			for (j = i; j >= interval && a[j - interval] > tempvar; j -= interval)
				a[j] = a[j - interval];

			// put tempvar which is a[i] in its correct position  
			a[j] = tempvar;
		}
	}
	return 0;
}

void Merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	int L[(N / 2) + 1], R[N / 2];

	// Copy data to temp arrays L[] and R[]
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back into arr[l..r
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[],
	// if there are any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[],
	// if there are any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void MergeSort(int arr[], int l, int r)
{
	if (l < r) {
		int m = l + (r - l) / 2;

		// Sort first and second halves
		MergeSort(arr, l, m);
		MergeSort(arr, m + 1, r);

		Merge(arr, l, m, r);
	}
}
