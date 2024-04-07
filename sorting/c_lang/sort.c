#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define MAX 100

void merge_sort(int length, int array[length]);
void merge(int n1, int array1[n1], int n2, int array2[n2]);
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

void test(void (*algorithm)(int, int*)) {
  struct timeval start, stop;
  int len = 20000;//rand() % 15 + 1;
  int *arr = make_input(len);
  printf("unsorted:\n");
  yeet(len, arr);
  gettimeofday(&start, NULL);
  algorithm(len, arr);
  gettimeofday(&stop, NULL);
  printf("sorted:\n");
  yeet(len, arr);
  free(arr);
  printf("Sorting took %lu us.\n", stop.tv_usec - start.tv_usec);
}


int main(void) {
  printf("Initializing...\n");
  srand(time(NULL));
  printf("Testing Merge Sort:\n");
  test(merge_sort);
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
