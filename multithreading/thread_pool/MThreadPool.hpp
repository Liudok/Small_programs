#ifndef MTHREADPOOL_HPP
#define MTHREADPOOL_HPP

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <future>
#pragma optimize("", off)

template <typename T>
class MThreadPool
{
public:

	MThreadPool(std::function<T()>);
	~MThreadPool();
	bool m_stop_flag;
	std::future<T> Do(const std::function<T()> & i_func);
	std::vector<std::thread> m_pool;

private:
	std::queue<std::function<void(void)>> m_que;
	std::mutex m_mutex_tasks;
	std::mutex m_mutex_logs;
	std::condition_variable cond_var;
	void Loop();
};

template <typename T>
MThreadPool<T>::MThreadPool(std::function<T()>) {

}

template <typename T>
MThreadPool<T>::~MThreadPool() {

}

template <typename T>
void MThreadPool<T>::Loop()
{
	while (true)
	{
		std::unique_lock ul(m_mutex_tasks);
		cond_var.wait(ul, [](){return(!m_que.empty() || m_stop_flag);});
		if (m_stop_flag)
			break;
		else {
			m_que.front();
			m_que.pop();
			ul.unlock();
		}
	}
}

#endif