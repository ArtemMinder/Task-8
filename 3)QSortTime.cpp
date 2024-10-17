#include <iostream>
#include <vector>
#include <chrono>
#include "2)CustomQSort.cpp"


double measure_sort_time(std::vector<double>& unique_values) 
{

    const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    custom_qsort(unique_values.begin(), unique_values.end());
    const std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken for  custom sorting: " << duration << " microseconds" << std::endl;

    return duration;
}

void measure_parallel_sort_time(std::vector<double>& unique_values) 
{
    const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    parallel_qsort(unique_values.begin(), unique_values.end());
    const std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Time taken for parallel quicksort: " << duration << " microseconds\n";
}
