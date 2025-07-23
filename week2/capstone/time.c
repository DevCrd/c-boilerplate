#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000  // Try 1 million later!

// Bubble Sort
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-1-i; j++)
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

// Selection Sort
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[min])
                min = j;
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

// Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Utility
void fill_array(int arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 100000;
}

void copy_array(int src[], int dest[], int size) {
    for (int i = 0; i < size; i++)
        dest[i] = src[i];
}

int main() {
    int original[SIZE], arr1[SIZE], arr2[SIZE], arr3[SIZE];
    fill_array(original, SIZE);

    copy_array(original, arr1, SIZE);
    copy_array(original, arr2, SIZE);
    copy_array(original, arr3, SIZE);

    clock_t start, end;
    double time_taken;

    // Bubble Sort
    start = clock();
    bubble_sort(arr1, SIZE);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Bubble Sort Time: %.4f seconds\n", time_taken);

    // Selection Sort
    start = clock();
    selection_sort(arr2, SIZE);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Selection Sort Time: %.4f seconds\n", time_taken);

    // Merge Sort
    start = clock();
    merge_sort(arr3, 0, SIZE - 1);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Merge Sort Time: %.4f seconds\n", time_taken);

    return 0;
}