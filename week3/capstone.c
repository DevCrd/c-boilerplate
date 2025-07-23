#include <stdio.h>

// Function to sort the array using Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to perform Binary Search
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == target)
            return mid; // Found at index mid
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    
    return -1; // Not found
}

int main() {
    int n;

    // Step 1: Get number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    // Step 2: Get elements from the user
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Step 3: Sort the array
    bubbleSort(arr, n);

    // Step 4: Display sorted array
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Step 5: Ask user for a number to search
    int target;
    printf("Enter a number to search for: ");
    scanf("%d", &target);

    // Step 6: Search for the number
    int result = binarySearch(arr, n, target);

    // Step 7: Show result
    if (result != -1) {
        printf("Found %d at index %d (0-based index).\n", target, result);
    } else {
        printf("%d not found in the array.\n", target);
    }

    return 0;
}
