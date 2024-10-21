#include <iostream>
#include <fstream>  
#include <vector>
#include <tuple>   
#include <string>


void create_csv(const std::string& filename, const std::string& sort_name, int num_elements, long long time_taken) 
{
    static std::vector<std::tuple<std::string, int, long long>> sorting_data;
    sorting_data.emplace_back(sort_name, time_taken, num_elements);

    std::ofstream file(filename);

    if (file.is_open()) 
    {
        file << "Sorting Algorithm, Time (microseconds)/" << num_elements << " elements\n";  
        for (const auto& data : sorting_data) 
        {
            file << std::get<0>(data) << "," << std::get<1>(data) << "\n";
        }

        file.close();
        std::cout << "CSV file updated successfully: " << filename << std::endl;
    }
    else 
    {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}