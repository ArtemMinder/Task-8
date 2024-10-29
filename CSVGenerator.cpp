#include <iostream>
#include <fstream>  
#include <vector>
#include <tuple>   
#include <string>

void create_csv(const std::string& filename, const std::string& sort_name, std::vector<int> num_elements, std::vector<long long> time_taken)
{

    std::ifstream f(filename, std::ios::app);
    if (f.peek() == std::ifstream::traits_type::eof())
    {
        f.close();
        std::ofstream file(filename, std::ios::app);
        file << "," << num_elements[0] << "," << num_elements[1] << "," << num_elements[2] << "," << num_elements[3] << "\n";
    }
    f.close();

    std::ofstream file(filename, std::ios::app);

    if (file.is_open()) 
    {
        file << sort_name<<",";

        for (int i = 0; i <= time_taken.size()-1; i++)
        {
            file <<time_taken[i]<<",";
        }
        
        file << "\n";

        file.close();
        std::cout << "CSV file updated successfully: " << filename << std::endl;
    }
    else 
    {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}