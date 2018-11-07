#include <stdio.h>
#include <assert.h>
#include <limits.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void percolate_down(int *arr, int i, int n) {
    int tmp = arr[i];
    while (2 * i + 1 < n) {
        int child = 2 * i + 1;
        if (child != n - 1 && arr[child + 1] > arr[child])
            child++;
        if (tmp >= arr[child])
            break;

        arr[i] = arr[child];
        i = child;
    }
    arr[i] = tmp;
}

void heap_sort(int *arr, int n) {
    // build heap
    for (int i = n / 2; i >= 0; i--)
        percolate_down(arr, i, n);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]); // delete max
        percolate_down(arr, 0, i);
    }
}

void print_arr(int *arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void test_sort() {
    int arr[] = {1};
    heap_sort(arr, sizeof(arr) / sizeof(int));
    print_arr(arr, sizeof(arr) / sizeof(int));
    int arr2[] = {1, 0};
    heap_sort(arr2, sizeof(arr2) / sizeof(int));
    print_arr(arr2, sizeof(arr2) / sizeof(int));
    int arr3[] = {2, 1, 0};
    heap_sort(arr3, sizeof(arr3) / sizeof(int));
    print_arr(arr3, sizeof(arr3) / sizeof(int));
    int arr4[] = {9, 6, 2, 3, 1, 2};
    heap_sort(arr4, sizeof(arr4) / sizeof(int));
    print_arr(arr4, sizeof(arr4) / sizeof(int));
    int arr5[] = {2, 2, 2};
    heap_sort(arr5, sizeof(arr5) / sizeof(int));
    print_arr(arr5, sizeof(arr5) / sizeof(int));
}

int main() {
    test_sort();
}
