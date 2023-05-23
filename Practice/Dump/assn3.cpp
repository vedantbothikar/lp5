#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

int main() {
    std::vector<int> numbers = {10, 5, 7, 15, 3, 9, 12, 8};

    // Serial Operations
    int min_val_serial = numbers[0];
    int max_val_serial = numbers[0];
    int sum_serial = 0;

    auto start_serial = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numbers.size(); i++) {
        min_val_serial = std::min(min_val_serial, numbers[i]);
        max_val_serial = std::max(max_val_serial, numbers[i]);
        sum_serial += numbers[i];
    }

    double average_serial = static_cast<double>(sum_serial) / numbers.size();

    auto end_serial = std::chrono::high_resolution_clock::now();
    auto duration_serial = std::chrono::duration_cast<std::chrono::microseconds>(end_serial - start_serial);

    std::cout << "Serial Results:" << std::endl;
    std::cout << "Minimum value: " << min_val_serial << std::endl;
    std::cout << "Maximum value: " << max_val_serial << std::endl;
    std::cout << "Sum: " << sum_serial << std::endl;
    std::cout << "Average: " << average_serial << std::endl;
    std::cout << "Serial Execution Time: " << duration_serial.count() << " microseconds" << std::endl;

    // Parallel Operations
    int min_val_parallel = numbers[0];
    int max_val_parallel = numbers[0];
    int sum_parallel = 0;

    auto start_parallel = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for reduction(min:min_val_parallel) reduction(max:max_val_parallel) reduction(+:sum_parallel)
    for (int i = 0; i < numbers.size(); i++) {
        min_val_parallel = std::min(min_val_parallel, numbers[i]);
        max_val_parallel = std::max(max_val_parallel, numbers[i]);
        sum_parallel += numbers[i];
    }

    double average_parallel = static_cast<double>(sum_parallel) / numbers.size();

    auto end_parallel = std::chrono::high_resolution_clock::now();
    auto duration_parallel = std::chrono::duration_cast<std::chrono::microseconds>(end_parallel - start_parallel);

    std::cout << "\nParallel Results:" << std::endl;
    std::cout << "Minimum value: " << min_val_parallel << std::endl;
    std::cout << "Maximum value: " << max_val_parallel << std::endl;
    std::cout << "Sum: " << sum_parallel << std::endl;
    std::cout << "Average: " << average_parallel << std::endl;
    std::cout << "Parallel Execution Time: " << duration_parallel.count() << " microseconds" << std::endl;

    return 0;
}
