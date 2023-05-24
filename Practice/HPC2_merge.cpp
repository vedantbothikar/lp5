#include <iostream>
#include <omp.h>
using namespace std;

void merge(int *arr, int *left, int size1, int *right, int size2)
{

    // pointers
    // i and j are for subarrays and k is for main arr
    int i = 0, j = 0, k = 0;

    while (i < size1 and j < size2)
    {

        if (left[i] < right[j])
        {
            arr[k] = left[i];
            i++;
            k++;
        }

        else
        {
            arr[k] = right[j];
            j++;
            k++;
        }
    }

    // insert all remaining elements
    while (i < size1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < size2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergesort_serial(int *arr1, int n)
{

    if (n > 1)
    {

        // Define left and right arrays and insert values in them
        int mid = n / 2;
        int *left = new int[mid];
        int *right = new int[n - mid];

        for (int i = 0; i < mid; i++)
        {
            left[i] = arr1[i];
        }

        for (int i = mid; i < n; i++)
        {
            right[i - mid] = arr1[i];
        }

        // sort left and right arrays
        mergesort_serial(left, mid);
        mergesort_serial(right, n - mid);

        // merge both arrays
        merge(arr1, left, mid, right, n - mid);

        delete[] left;
        delete[] right;
    }
}

void mergesort_parallel(int *arr2, int n)
{

    if (n > 1)
    {

        int mid = n / 2;

        int *left = new int[mid];
        int *right = new int[n - mid];

        // inserting values in left and right arrays
        for (int i = 0; i < mid; i++)
        {
            left[i] = arr2[i];
        }

        for (int i = mid; i < n; i++)
        {
            right[i - mid] = arr2[i];
        }

        // sort left and right arrays

#pragma omp task
        mergesort_parallel(left, mid);

#pragma omp task
        mergesort_parallel(right, n - mid);

        // merge arrays

#pragma omp taskwait
        merge(arr2, left, mid, right, n - mid);

        delete[] left;
        delete[] right;
    }
}

int main()
{

    int arr1[] = {5, 4, 3, 2, 1};
    int arr2[] = {5, 4, 3, 2, 1};
    int n = 5;

    double starttime = omp_get_wtime();

    mergesort_serial(arr1, n);

    double endtime = omp_get_wtime();

    cout << "Serial time: " << endtime - starttime << endl;

    mergesort_parallel(arr2, n);

    double finalendtime = omp_get_wtime();

    cout << "Parallel time: " << finalendtime - endtime << endl;

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr2[i] << " ";
    }
    cout << endl;

    return 0;
}