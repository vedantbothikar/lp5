#include <iostream>
#include <omp.h>

using namespace std;

void merge(int arr[], int left[], int left_size, int right[], int right_size) {
    int i = 0, j = 0, k = 0;
    while (i < left_size && j < right_size) {
        if (left[i] < right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < left_size) {
        arr[k++] = left[i++];
    }
    while (j < right_size) {
        arr[k++] = right[j++];
    }
}

void merge_sort_parallel(int arr[], int n) {
    if (n > 1) {
        int mid = n / 2;
        int *left = new int[mid];
        int *right = new int[n - mid];
        for (int i = 0; i < mid; i++) {
            left[i] = arr[i];
        }
        for (int i = mid; i < n; i++) {
            right[i - mid] = arr[i];
        }

#pragma omp task
        merge_sort_parallel(left, mid);

#pragma omp task
        merge_sort_parallel(right, n - mid);

#pragma omp taskwait
        merge(arr, left, mid, right, n - mid);

        delete[] left;
        delete[] right;
    }
}

void merge_sort_serial(int arr[], int n) {
    if (n > 1) {
        int mid = n / 2;
        int *left = new int[mid];
        int *right = new int[n - mid];
        for (int i = 0; i < mid; i++) {
            left[i] = arr[i];
        }
        for (int i = mid; i < n; i++) {
            right[i - mid] = arr[i];
        }

        merge_sort_serial(left, mid);

        merge_sort_serial(right, n - mid);

        merge(arr, left, mid, right, n - mid);

        delete[] left;
        delete[] right;
    }
}

int main() {
    int arr[] = {5, 4, 3, 2, 1};
    int arr2[] = {5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    double start_time = omp_get_wtime();
    merge_sort_serial(arr2, n);

    double mid_time = omp_get_wtime();

    cout << "Time taken by serial Merge sort: " << mid_time - start_time << " seconds" << endl;


#pragma omp parallel
#pragma omp single
    merge_sort_parallel(arr, n);

    double end_time = omp_get_wtime();

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Time taken by parallel Merge sort: " << end_time - mid_time << " seconds" << endl;

    return 0;
}
