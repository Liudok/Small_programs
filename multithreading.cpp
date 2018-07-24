#include <iostream>
#include <vector>
#include <thread>
#include <cmath>

template<typename it, typename T, typename F>
T sum_func(it it_b, it it_e, T init, size_t thread_num, F func)
{

	std::vector<std::thread> t(thread_num);
	int k = 0;
	int vec_part = (it_e - it_b)/ thread_num;
	std::vector<double> results(thread_num);
	auto accum = [&](auto start, auto end, auto ret){
		for(start; start != end; ++start)
		{
			ret += func(*start);
		}
	};
	while (k < thread_num)
	{
		int res = 0;
		t[k] = std::thread(&accum, it_b + (k * vec_part), it_b + ((k + 1) * vec_part), &res);
		results[k] = res;
		k++;
	}

	double ret = 0;
	for (int i = 0; i < thread_num; ++i)
	{
		ret += results[i];
		t[i].join();

	}
	return ret;
} 

int main()

{
	  int size = 100;
	  std::vector<double> v(size);
	  for (int i = 0; i < size; ++i)
	  {
			v[i] = (rand() % 20);
	  }
	   for (auto it = v.begin(); it != v.end(); ++it)
	  {
			std::cout <<*it<<std::endl;
	  }

	  auto func = [](double a){return sqrt(a);};
	  std::cout << int cores = std::thread::hardware_concurrency() << std::endl;
	  double res = sum_func(v.begin(), v.end(), (double)0.0, cores, func);
	  std::cout << res << std::endl;
}

