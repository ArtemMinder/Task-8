#include <iostream>
#include <vector>
#include "2)CustomQSort.cpp"

std::vector <double> generate_unique_doubles(double min, double max, size_t num_values);
double measure_custom_qsort_time(std::vector<double>& unique_values);
void measure_std_qsort_time(std::vector<double>& unique_values);
void measure_parallel_sort_time(std::vector<double>& unique_values);

int main() 
{
	// Define the range and the number of unique values
	double min = 1.0;
	double max = 10.0;
	size_t num_values = 1000000;

	//1)Generate unique values ​​of double format
	generate_unique_doubles(min, max, num_values);

	//2)Sort the values and print them
	std::vector<double> unique_values = generate_unique_doubles(min, max, num_values);
	sort_and_print_doubles(unique_values.begin(), unique_values.end());

	//3)Measure std qsort time
	measure_std_qsort_time(unique_values);

	//4)Measure custom qsort time
	measure_custom_qsort_time(unique_values);

	//5)Sorting in 8-thread mode (IntelCore i7-6700HQ)
	parallel_qsort(unique_values.begin(), unique_values.end());

	//6)Printing in 8-thread qsort mode 
	sort_and_print_doubles_parallel(unique_values.begin(), unique_values.end());

	//7) Measure 8-thread qsort time
	measure_parallel_sort_time(unique_values);

	return 0;
}
