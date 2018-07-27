#include <iostream>
#include <vector>
#include <thread>
#include <cmath>

template<typename it, typename T, typename F>
T sum_func_one_thread(it it_b, it it_e, T init, F &func)
{
	double ret = init;
	for(it begin = it_b; begin != it_e; ++begin)
	{
		ret += func(*begin);
	}
	return ret;
}


template<typename it, typename T, typename F>
T sum_func(it it_b, it it_e, T init, size_t thread_num, F &func)
{

	std::vector<std::thread> t(thread_num);

	int vec_part = (it_e - it_b)/ thread_num;
	std::cout << "Each thread will process " << vec_part << " elements of vector" << std::endl;
	std::vector<double> results(thread_num, 0);

	int k = 0;
	it start = it_b;
	it end = it_b;

	while (k < thread_num)
	{
		start = it_b + (k * vec_part);
		end = it_b + ((k + 1) * vec_part);

		t[k] = std::thread([&results, &func, k, start, end](){
			double sum_inside = 0;
			for(it begin = start; begin != end; ++begin)
			{
				sum_inside += func(*begin);
			}
			results[k] = sum_inside;
		});

		k++;
	}

	double ret = init;
	for (int i = 0; i < thread_num; ++i)
	{
		t[i].join();
		ret += results[i];
	}
	return ret;
} 

int main()

{
	int size = 1000;
	std::vector<double> v(size);

	for (int i = 0; i < size; ++i)
	{
		v[i] = (rand() % 20);
	}

	for (auto it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it <<std::endl;
	}

	auto func = [](double a){return sqrt(a);};
	int cores = std::thread::hardware_concurrency();
	std::cout << "Amount of threads = " << cores << std::endl;

	auto t1 = std::chrono::high_resolution_clock::now();
	double res = sum_func(v.begin(), v.end(), (double)0.0, cores, func);
	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << "\nDuration of operation  with threads = " << std::chrono::duration<double, std::milli>(t2 - t1).count() << std::endl;


	std::cout << "Result: " << res << std::endl;

	t1 = std::chrono::high_resolution_clock::now();
	res = sum_func_one_thread(v.begin(), v.end(), (double)0.0, func);
	t2 = std::chrono::high_resolution_clock::now();
	std::cout << "\nDuration of operation  without threads = " << std::chrono::duration<double, std::milli>(t2 - t1).count() << std::endl;

	std::cout << "Result: " << res << std::endl;

	return 0;
}
