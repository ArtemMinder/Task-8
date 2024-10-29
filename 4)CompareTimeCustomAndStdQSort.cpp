#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>

std::vector<long long> measure_custom_qsort_time(std::vector<std::vector<double>>& values, std::vector<int> number_of_values);

void measure_std_sort_time(std::vector<std::vector<double>>& values, std::vector<int> number_of_values)
{
    std::vector<double> durations;
        for (int i = 0; i <= number_of_values.size() - 1; i++)
        {
            const std::chrono::time_point<std::chrono::steady_clock> start_std = std::chrono::steady_clock::now();
            std::sort(values[i].begin(), values[i].end());
            const std::chrono::time_point<std::chrono::steady_clock> end_std = std::chrono::steady_clock::now();
            double duration_std = std::chrono::duration_cast<std::chrono::microseconds>(end_std - start_std).count();
            std::cout << "Time taken for std::sort: " << duration_std << " microseconds" << std::endl;
            durations.push_back(duration_std);
        }

        long long average_std_duration = std::accumulate(durations.begin(), durations.end(), 0.0) / durations.size();

        std::vector<long long> custom_qsort = measure_custom_qsort_time(values, number_of_values);

        long long average_custom_duration = std::accumulate(custom_qsort.begin(), custom_qsort.end(), 0.0) / custom_qsort.size();

    if (average_std_duration < average_custom_duration)
    {
        std::cout << "std::sort is faster." << std::endl;
    }
    else if (average_std_duration > average_custom_duration)
    {
        std::cout << "custom_qsort is faster." << std::endl;
    }
    else 
    {
        std::cout << "Both sorting methods took the same amount of time." << std::endl;
    }
}
