#include <iostream>
#include <omp.h>
using namespace std;

void bubble_serial(int *arr, int n)
{

    bool swapped = true;

    while (swapped)
    {
        swapped = false;

        for (int i = 0; i < n - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
    }
}

void bubble_parallel(int *arr, int n)
{

    bool swapped = true;

    while (swapped)
    {
        swapped = false;

#pragma omp parallel for shared(arr) private(swapped)
        for (int i = 0; i < n - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
    }
}

int main()
{

    int arr1[] = {5, 4, 3, 2, 1};
    int arr2[] = {5, 4, 3, 2, 1};

    int n = 5;

    double starttime = omp_get_wtime();
    bubble_serial(arr1, n);

    double endtime = omp_get_wtime();

    cout << "Time taken by serial Bubble sort: " << endtime - starttime << " seconds" << endl;

    bubble_parallel(arr2, n);
    double finalendtime = omp_get_wtime();

    cout << "Time taken by serial Bubble sort: " << finalendtime - endtime << " seconds" << endl;

    return 0;
}