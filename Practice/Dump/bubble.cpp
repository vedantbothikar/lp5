#include <iostream>
#include <omp.h>

using namespace std;

void bubble_sort_parallel(int arr[], int n) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
#pragma omp parallel for shared(arr) private(swapped)
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
    }
}

void bubble_sort_serial(int arr[], int n) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
    }
}

int main() {
    int arr[] = {5, 4, 3, 2, 1};
    int arr2[] = {5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    double start_time = omp_get_wtime();
    bubble_sort_serial(arr, n);
    double mid_time = omp_get_wtime();

    cout << "Time taken by serial Bubble sort: " << mid_time - start_time << " seconds" << endl;

    bubble_sort_parallel(arr2,n);

    double end_time = omp_get_wtime();

    cout << "Time taken by parallel Bubble sort: " << end_time - mid_time << " seconds" << endl;


    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
