#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include "2)CustomQSort.cpp"

void create_csv(const std::string& filename, const std::string& sort_name, int num_elements, long long time_taken);

void measure_std_qsort_time(std::vector<double>& unique_values)
{

    const std::chrono::time_point<std::chrono::steady_clock> start_std = std::chrono::steady_clock::now();
    std::sort(unique_values.begin(), unique_values.end());
    const std::chrono::time_point<std::chrono::steady_clock> end_std = std::chrono::steady_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::microseconds>(end_std - start_std).count();
    std::cout << "Time taken for  std::qsort: " << duration << " microseconds" << std::endl;

    create_csv("sorting_times.csv", "STD Quicksort", unique_values.size(), duration);
}

double measure_custom_qsort_time(std::vector<double>& unique_values) 
{

    const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    custom_qsort(unique_values.begin(), unique_values.end());
    const std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken for  custom quicksort: " << duration << " microseconds" << std::endl;

    create_csv("sorting_times.csv", "Custom Quicksort", unique_values.size(), duration);

    return duration;
}

void measure_parallel_sort_time(std::vector<double>& unique_values) 
{
    const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    sort_with_affinity(unique_values.begin(), unique_values.end());
    const std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken for parallel quicksort: " << duration << " microseconds\n";

    create_csv("sorting_times.csv", "8-Thread Quicksort", unique_values.size(), duration);
}
