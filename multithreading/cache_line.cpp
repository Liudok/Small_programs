#include <iostream>
#include <vector>

int main()
{
	auto size = 1000;
	std::vector<int> v(size * size, 0);

	std::cout << "Iterating through 2-dimension array:\n\n";

    auto t1 = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < size; ++i)
		for (auto j = 0; j < size; ++j)
    		v[i * size + j] = 1;
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Duration of operations by line = " << std::chrono::duration<double, std::milli>(t2 - t1).count() << std::endl;


	t1 = std::chrono::high_resolution_clock::now();
	for (auto i = 0; i < size; ++i)
		for (auto j = 0; j < size; ++j)
			v[j * size + i] = 1;
	t2 = std::chrono::high_resolution_clock::now();
	std::cout << "Duration of operations by column = " << std::chrono::duration<double, std::milli>(t2 - t1).count() << std::endl;

	return 0;
}