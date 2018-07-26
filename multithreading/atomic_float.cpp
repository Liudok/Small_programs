#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

#pragma optimize("", off)

void add_mln_ints(std::atomic<int>& i)
{
	for (int k = 0; k < 1000000; ++k)
		i++;
}

void add_mln_floats(std::atomic<float>& fl)
{
	for (int k = 0; k < 1000000; ++k)
	{
		auto current = fl.load();
		while (!fl.compare_exchange_weak(current, current + 1))
			;
	}
}

int main()
{
	std::cout << "Using atomics to increment numbers million times in 2 threads\n\n";
	std::atomic<int> i {0};

	std::thread t1(add_mln_ints, std::ref(i));
	std::thread t2(add_mln_ints, std::ref(i));
	t1.join();
	t2.join();

	std::atomic<float> fl {0};

	std::thread t3(add_mln_floats, std::ref(fl));
	std::thread t4(add_mln_floats, std::ref(fl));
	t3.join();
	t4.join();

	std::cout << "int in 2 threads = " << i << std::endl;
	std::cout << "floats in 2 threads = " << fl << std::endl;

	return 0;
}