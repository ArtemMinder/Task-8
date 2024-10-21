#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <mutex>
#include <windows.h>
#include <condition_variable>

// Custom quicksort implementation using iterators
template <typename RandomIt>
void custom_qsort(RandomIt first, RandomIt last)
{
	if (first >= last || std::distance(first, last) <= 1) return;

	RandomIt left = first;
	RandomIt right = last - 1;
	auto pivot = *(first + (last - first) / 2);

	while (left <= right)
	{
		// Move left iterator until we find an element greater than or equal to the pivot
		while (left <= right && *left < pivot)
		{
			++left;
		}
		// Move right iterator until we find an element less than or equal to the pivot
		while (left <= right && *right > pivot)
		{
			--right;
		}
		// If left and right haven't crossed, swap the elements
		if (left <= right)
		{
			std::swap(*left, *right);
			++left;
			--right;
		}
	}

	// Recursively sort the two partitions
	if (first < right) custom_qsort(first, right + 1);  // Sort the left partition
	if (left < last) custom_qsort(left, last);          // Sort the right partition
}
// Function to sort and print the values using iterators
template <typename RandomIt>
void sort_and_print_doubles(RandomIt first, RandomIt last)
{
	custom_qsort(first, last);

	// Print sorted values
	std::cout << "Sorted values:\n";
	for (RandomIt it = first; it != last; ++it)
	{
		std::cout << *it << '\n';
	}
}

// Function to merge sorted subarrays
template <typename RandomIt>
void merge_sections(RandomIt first, RandomIt last, size_t num_sections)
{
	size_t section_size = std::distance(first, last) / num_sections;

	for (size_t i = 1; i < num_sections; ++i)
	{
		std::inplace_merge(first, first + section_size * i, first + section_size * (i + 1));
	}
}

// Parallel quicksort using 8 threads
template <typename RandomIt>
void parallel_qsort(RandomIt first, RandomIt last)
{
	size_t length = std::distance(first, last);

	if (length < 2) return;

	size_t num_threads = 8;
	size_t chunk_size = length / num_threads;
	std::vector<std::thread> threads;

	std::mutex mtx;
	std::condition_variable cv;
	int completed_threads = 0;

	for (size_t i = 0; i < num_threads; ++i)
	{
		RandomIt chunk_start = first + i * chunk_size;
		RandomIt chunk_end = (i == num_threads - 1) ? last : chunk_start + chunk_size;

		threads.emplace_back([chunk_start, chunk_end, &mtx, &cv, &completed_threads]()
			{
				custom_qsort(chunk_start, chunk_end);

				std::lock_guard<std::mutex> lock(mtx);
				completed_threads++;
				cv.notify_one();
			});
	}


	{
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [&completed_threads, num_threads]() { return completed_threads == num_threads; });
	}

	merge_sections(first, last, num_threads);

	for (auto& thread : threads)
	{
		thread.join();
	}
}

template <typename RandomIt>
void sort_and_print_doubles_parallel(RandomIt first, RandomIt last)
{
	parallel_qsort(first, last);

	std::cout << "Sorted values using parallel quicksort:\n";
	for (RandomIt it = first; it != last; ++it)
	{
		std::cout << *it << '\n';
	}
	std::cout << std::endl;
}


inline void set_thread_affinity(int core_id) 
{
	HANDLE thread = GetCurrentThread(); 
	DWORD_PTR mask = 1 << core_id;       
	SetThreadAffinityMask(thread, mask);
}

template <typename RandomIt>
void parallel_sort(RandomIt start, RandomIt end, int core_id) 
{
	set_thread_affinity(core_id);
	std::sort(start, end);
}

template <typename RandomIt>
void sort_with_affinity(RandomIt first, RandomIt last)
{
	const int num_threads = 8;
	std::vector<std::thread> threads;
	size_t chunk_size = std::distance(first, last) / num_threads;

	for (int i = 0; i < num_threads; ++i)
	{
		auto start = first + i * chunk_size; 
		auto next = (i == num_threads - 1) ? last : start + chunk_size;

		threads.emplace_back(parallel_sort<RandomIt>, start, next, i); 
	}

	for (auto& t : threads) 
	{
		t.join();
	}

	std::sort(first, last);
}