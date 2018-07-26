#include "MThreadPool.hpp"

int main()
{
	int i = 0;
	auto task = [&](){i++;};
	MThreadPool<decltype(task)> pool(task);

	return 0;
}
