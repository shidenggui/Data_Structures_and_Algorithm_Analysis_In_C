#include <stdio.h>
#include <assert.h>
#include <limits.h>
#define CUTOFF 15

void insertion_sort(int *arr, int left, int right) {
    int inserted, j;
    for (int i = left + 1; i <= right; i++) {
        inserted = arr[i];
        for (j = i; j > left && inserted < arr[j - 1]; j--)
            arr[j] = arr[j - 1];
        arr[j] = inserted;
    }
}
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int median3(int *arr, int left, int right) {
    int center = left + (right - left) / 2;
    if (arr[left] > arr[center])
        swap(&arr[left], &arr[center]);
    if (arr[right] > arr[center])
        swap(&arr[right], &arr[center]);
    if (arr[left] > arr[right])
        swap(&arr[left], &arr[right]);
    return arr[center];
}

void qsort(int *arr, int left, int right) {
    if (CUTOFF > left - right) {
        insertion_sort(arr, left, right);
        return;
    }

    int pivot = median3(arr, left, right);
    int i = left + 1;
    int j = right - 1;
    while(i < j) {
        while (arr[i] < pivot) i++;
        while (arr[j] < pivot) j--;
        if (i >= j)
            break;

        swap(&arr[i], &arr[j]);
        i++;
        j--;
    }
    swap(&arr[j], &arr[right]);
    qsort(arr, left, j - 1);
    qsort(arr, j + 1, right);
}
void quick_sort(int *arr, int n) {
    qsort(arr, 0, n - 1);
}

void print_arr(int *arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void test_sort() {
    int arr[] = {1};
    quick_sort(arr, sizeof(arr) / sizeof(int));
    print_arr(arr, sizeof(arr) / sizeof(int));
    int arr2[] = {1, 0};
    quick_sort(arr2, sizeof(arr2) / sizeof(int));
    print_arr(arr2, sizeof(arr2) / sizeof(int));
    int arr3[] = {2, 1, 0};
    quick_sort(arr3, sizeof(arr3) / sizeof(int));
    print_arr(arr3, sizeof(arr3) / sizeof(int));
    int arr4[] = {9, 6, 2, 3, 1, 2};
    quick_sort(arr4, sizeof(arr4) / sizeof(int));
    print_arr(arr4, sizeof(arr4) / sizeof(int));
    int arr5[] = {2, 2, 2};
    quick_sort(arr5, sizeof(arr5) / sizeof(int));
    print_arr(arr5, sizeof(arr5) / sizeof(int));
}

int main() {
    test_sort();
}
