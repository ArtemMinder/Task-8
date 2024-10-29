#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include "2)CustomQSort.cpp"

void create_csv(const std::string& filename, const std::string& sort_name, std::vector<int> num_elements, std::vector<long long> time_taken);

void measure_std_qsort_time(std::vector<std::vector<double>>& values, std::vector<int> number_of_values)
{
    std::vector<long long> durations;
    for (int i = 0; i < number_of_values.size(); i++)
    {
        const std::chrono::time_point<std::chrono::steady_clock> start_std = std::chrono::steady_clock::now();
        std::sort(values[i].begin(), values[i].end());
        const std::chrono::time_point<std::chrono::steady_clock> end_std = std::chrono::steady_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::microseconds>(end_std - start_std).count();
        std::cout << "Time taken for  std::qsort: " << duration << " microseconds" << std::endl;
        durations.push_back(duration);
    }
    create_csv("sorting_times.csv", "STD Quicksort", number_of_values, durations);
}

std::vector<long long> measure_custom_qsort_time(std::vector<std::vector<double>>& values, std::vector<int> number_of_values)
{

    std::vector<long long> durations;
    for (int i = 0; i < number_of_values.size(); i++)
    {
        const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
        custom_qsort(values[i].begin(), values[i].end());
        const std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Time taken for  custom quicksort: " << duration << " microseconds" << std::endl;
        durations.push_back(duration);
    }
    create_csv("sorting_times.csv", "Custom Quicksort", number_of_values, durations);

    return durations;
}

void measure_parallel_sort_time(std::vector<std::vector<double>>& values, std::vector<int> number_of_values)
{
    std::vector<long long> durations;
    for (int i = 0; i < number_of_values.size(); i++)
    {
        const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
        sort_with_affinity(values[i].begin(), values[i].end());
        const std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Time taken for parallel quicksort: " << duration << " microseconds\n";
        durations.push_back(duration);
    }
    create_csv("sorting_times.csv", "8-Thread Quicksort", number_of_values, durations);
}
