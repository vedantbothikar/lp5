#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

using namespace std;

int main()
{
    std::vector<int> numbers = {10, 5, 7, 15, 3, 9, 12, 8};

    // Serial Operations
    int min_val_serial = numbers[0];
    int max_val_serial = numbers[0];
    int sum_serial = 0;

    double start_time_serial = omp_get_wtime();

    // Calculate min, max, sum and average serially
    for (int i = 0; i < numbers.size(); i++)
    {
        min_val_serial = std::min(min_val_serial, numbers[i]);
        max_val_serial = std::max(max_val_serial, numbers[i]);
        sum_serial += numbers[i];
    }

    double average_serial = static_cast<double>(sum_serial) / numbers.size();

    double end_time_serial = omp_get_wtime();

    // Printing results
    std::cout << "Serial Results:" << std::endl;
    std::cout << "Minimum value: " << min_val_serial << std::endl;
    std::cout << "Maximum value: " << max_val_serial << std::endl;
    std::cout << "Sum: " << sum_serial << std::endl;
    std::cout << "Average: " << average_serial << std::endl;
    cout << "Time taken for serial operations: " << (end_time_serial - start_time_serial) << " seconds" << endl;

    // Parallel Operations
    int min_val_parallel = numbers[0];
    int max_val_parallel = numbers[0];
    int sum_parallel = 0;

    double start_time_parallel = omp_get_wtime();

    // The below command is changed due to prettier formatting, which is why I have added this same line in comment below without any formatting
    // #pragma omp parallel for reduction(min: min_val_parallel) reduction(max: max_val_parallel) reduction(+: sum_parallel)

#pragma omp parallel for reduction(min                                                           \
                                   : min_val_parallel) reduction(max                             \
                                                                 : max_val_parallel) reduction(+ \
                                                                                               : sum_parallel)

    for (int i = 0; i < numbers.size(); i++)
    {
        min_val_parallel = std::min(min_val_parallel, numbers[i]);
        max_val_parallel = std::max(max_val_parallel, numbers[i]);
        sum_parallel += numbers[i];
    }

    double average_parallel = static_cast<double>(sum_parallel) / numbers.size();

    double end_time_parallel = omp_get_wtime();

    std::cout << "\nParallel Results:" << std::endl;
    std::cout << "Minimum value: " << min_val_parallel << std::endl;
    std::cout << "Maximum value: " << max_val_parallel << std::endl;
    std::cout << "Sum: " << sum_parallel << std::endl;
    std::cout << "Average: " << average_parallel << std::endl;
    cout << "Time taken for serial operations: " << (end_time_parallel - start_time_parallel) << " seconds" << endl;

    return 0;
}
