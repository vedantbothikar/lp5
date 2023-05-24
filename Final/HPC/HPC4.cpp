#include <iostream>
#include <cuda.h>
using namespace std;

__global__ void add(int *arr1_gpu, int *arr2_gpu, int *res_gpu, int size)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;

    if (index < size)
    {
        res_gpu[index] = arr1_gpu[index] + arr2_gpu[index];
    }
}

int main()
{

    int size;
    cin >> size;

    // declare arrays
    int *arr1_cpu = new int[size];
    int *arr2_cpu = new int[size];
    int *res_cpu = new int[size];

    // fill them with values
    for (int i = 0; i < size; i++)
    {
        arr1_cpu[i] = rand() % 100;
        arr2_cpu[i] = rand() % 100;
    }

    int *arr1_gpu, *arr2_gpu, *res_gpu;

    // allocate memory for arrays on GPU
    cudaMalloc((void **)&arr1_gpu, size * sizeof(int));
    cudaMalloc((void **)&arr2_gpu, size * sizeof(int));
    cudaMalloc((void **)&res_gpu, size * sizeof(int));

    // copy data from cpu to gpu
    cudaMemcpy(arr1__gpu, arr1_cpu, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(arr2_gpu, arr2_cpu, size * sizef(int), cudaMemcpyHpstToDevice);

    // add
    int blocksize = 256;
    int gridsize = (size + blocksize - 1) / blocksize;

    add<<<gridsize, blocksize>>>(arr1_gpu, arr2_gpu, res_gpu, size);

    // copy result back to cpu
    cudaMemcpy(res_cpu, res_gpu, size * sizeof(int), cudaMemcpyDeviceToHost);

    // print result
    for (int i = 0; i < size; i++)
    {
        cout << arr1_cpu[i] << " + " << arr2_cpu[i] << " = " << res_cpu[i] << endl;
    }

    // free memory
    cudaFree(arr1_gpu);
    cudaFree(arr2_gpu);
    cudaFree(res_gpu);

    delete[] arr1_cpu;
    delete[] arr2_cpu;
    delete[] res_cpu;

    return 0;
}