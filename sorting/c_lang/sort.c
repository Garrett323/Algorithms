#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define MAX 100

void merge_sort(int length, int array[length]);
void merge(int n1, int array1[n1], int n2, int array2[n2]);
void quick_sort(int n, int array[n]);
void yeet(int n, int* arr) {
  printf("{");
  for (int i = 0; i < n - 1; i++) {
    printf("%d, ", arr[i]);
  }
  printf("%d}\n", arr[n-1]);
}

int* make_input(int len) {
  int *arr = (int*)malloc(len*sizeof(int));
  for (int i = 0; i < len; i++) {
    arr[i] = rand() % MAX;
  }
  return arr;
}

void seperate() {
  for (int i=0; i<80; i++) {
    printf("*");
  }
  printf("\n\n");
}

void test(void (*algorithm)(int, int*), int len, int show) {
  seperate();
  struct timeval start, stop;
  int *arr = make_input(len);
  printf("unsorted:\n");
  if (show) yeet(len, arr);
  gettimeofday(&start, NULL);
  algorithm(len, arr);
  gettimeofday(&stop, NULL);
  printf("sorted:\n");
  if (show) yeet(len, arr);
  free(arr);
  printf("Sorting took %lu us.\n", stop.tv_usec - start.tv_usec);
  seperate();
}


int main(void) {
  int n = 300;
  printf("Initializing...\n");
  srand(time(NULL));
  printf("Testing Merge Sort:\n");
  test(merge_sort, n, 1);
  printf("Testing Quick Sort:\n");
  test(quick_sort, n, 1);
  return 0;
}

/* ATTENTION!
*  This implementation of merge sort is highly unsafe!
*  Splitting an array like this can result in segmentation faults when not handled properly!
*  I choose to do it like this because it is an interesting way to implement this algorithm 
*  and its quite fast!
*/
void merge_sort(int length, int array[length]) {
  if (length <= 1) return;
  merge_sort(length/2, array);
  merge_sort((length + 1)/2, &array[length/2]);
  merge(length/2, array, (length + 1)/2, &array[length/2]);
} 

void merge(int n1, int array1[n1], int n2, int array2[n2]) {
  int n = n1 + n2;
  int sorted[n];
  int i = 0, j = 0;
  for (int k = 0; k < n; k++) {
    if (j >= n2 || (i < n1 && array1[i] < array2[j])) {
      sorted[k] = array1[i++];
    }
    else {
      sorted[k] = array2[j++];
    }
  }
  for (int i = 0; i < n; i++) {
    array1[i] = sorted[i];
  }
}

void swap(int i, int j, int* array) {
  int temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

void quick_sort(int n, int array[n]) {
  if (n <= 1) {
    return;
  }
  int pivot = array[0];
  int lesser = 1, equal = 0;
  for (int i=1; i<n; i++) {
    if (array[i] < pivot) {
      swap(i, lesser++, array);
    } 
    else if (array[i] == pivot) {
      equal++;
    }
  }
  int l = lesser - 1;
  int r = n - lesser - equal;
  swap(0, lesser - 1, array);
  quick_sort(l, array);
  quick_sort(r, array + lesser + equal);
}
