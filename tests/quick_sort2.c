void insertion_sort(int *arr, int n) {
    int inserted, j;
    for (int i = 1; i < n; i++) {
        inserted = arr[i];
        for (j = i; j > 0 && arr[j - 1] > inserted; j--)
            arr[j] = arr[j - 1];
        arr[j] = inserted;
    }
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int median3(int *arr, int left, int right) {
    int center = left + (right - left) / 2;
    if (arr[left] > arr[center])
        swap(&arr[left], &arr[center]);
    if (arr[center] > arr[right])
        swap(&arr[center], &arr[right]);
    if (arr[left] > arr[center])
        swap(&arr[left], &arr[center]);
    swap(&arr[center], &arr[right - 1]);
    return arr[right - 1];
}

void q_sort(int *arr, int left, int right) {
    if (CUTOFF > right - left) {
        insertion_sort(arr, right - left + 1);
        return;
    }

    int pivot = median3(arr, left, right);
    int i, j;
    for (i = left + 1, j = right - 2;; i++, j--)
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i >= j)
            break;

        swap(&arr[i], &arr[j]);
    }
    swap(&arr[i], &arr[right - 1]);

    q_sort(arr, left, i - 1);
    q_sort(arr, i + 1, right);
}

void quick_sort(int *arr, int n) {
    q_sort(arr, 0, n - 1);
}
