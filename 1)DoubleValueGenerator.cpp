#include <iostream>
#include <random>
#include <set>

// Function to generate and print a set of unique double values
std::vector<double> generate_unique_doubles(double min, double max, size_t num_values) 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<double> unique_values;

    // Ask the user to choose a distribution
    std::cout << "Choose a distribution to generate unique values:\n";
    std::cout << "1. Uniform distribution\n";
    std::cout << "2. Normal distribution\n";
    std::cout << "3. Exponential distribution\n";
    std::cout << "4. Lognormal distribution\n";
    std::cout << "5. Cauchy distribution\n";
    int distribution_choice;
    std::cin >> distribution_choice;

    // Distribution selection logic
    switch (distribution_choice) 
    {
    case 1: 
    {
        // Uniform distribution
        std::uniform_real_distribution<> dist(min, max);
        while (unique_values.size() < num_values) 
        {
            double value = dist(gen);
            unique_values.push_back(value);
        }
        break;
    }
    case 2: 
    {
        // Normal distribution (Gaussian)
        double mean = (min + max) / 2.0;
        double stddev = (max - min) / 6.0; // Standard deviation
        std::normal_distribution<> dist(mean, stddev);
        while (unique_values.size() < num_values)
        {
            double value = dist(gen);
            if (value >= min && value <= max) 
            {
                unique_values.push_back(value);
            }
        }
        break;
    }
    case 3: 
    {
        // Exponential distribution
        std::exponential_distribution<> dist(1.0 / ((max - min) / 2.0));
        while (unique_values.size() < num_values) 
        {
            double value = dist(gen) + min;
            if (value <= max) 
            {
                unique_values.push_back(value);
            }
        }
        break;
    }
    case 4: {
        // Lognormal distribution
        double mean = (min + max) / 2.0;
        double stddev = (max - min) / 6.0;
        std::lognormal_distribution<> dist(mean, stddev);
        while (unique_values.size() < num_values) 
        {
            double value = dist(gen);
            if (value >= min && value <= max)
            {
                unique_values.push_back(value);
            }
        }
        break;
    }
    case 5: {
        // Cauchy distribution
        double median = (min + max) / 2.0;
        double scale = (max - min) / 4.0;
        std::cauchy_distribution<> dist(median, scale);
        while (unique_values.size() < num_values) 
        {
            double value = dist(gen);
            if (value >= min && value <= max) 
            {
                unique_values.push_back(value);
            }
        }
        break;
    }
    default:
        std::cerr << "Invalid distribution choice!\n";
        break;
    }

    // Output the result
    std::cout << "Unique values:\n";
    for (const double& val : unique_values) 
    {
        std::cout << val << '\n';
    }

    return std::vector<double>(unique_values.begin(), unique_values.end());
}