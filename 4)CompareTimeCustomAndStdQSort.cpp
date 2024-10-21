#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

double measure_custom_qsort_time(std::vector<double>& unique_values);

void measure_std_sort_time(std::vector<double>& unique_values)
{
    const std::chrono::time_point<std::chrono::steady_clock> start_std = std::chrono::steady_clock::now();
    std::sort(unique_values.begin(), unique_values.end());
    const std::chrono::time_point<std::chrono::steady_clock> end_std = std::chrono::steady_clock::now();
    double duration_std = std::chrono::duration_cast<std::chrono::microseconds>(end_std - start_std).count();
    std::cout << "Time taken for std::sort: " << duration_std << " microseconds" << std::endl;
    double duration_custom = measure_custom_qsort_time(unique_values);

    if (duration_std < duration_custom) 
    {
        std::cout << "std::sort is faster." << std::endl;
    }
    else if (duration_std > duration_custom) 
    {
        std::cout << "custom_qsort is faster." << std::endl;
    }
    else 
    {
        std::cout << "Both sorting methods took the same amount of time." << std::endl;
    }
}
