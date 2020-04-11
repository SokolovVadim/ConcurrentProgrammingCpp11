#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <deque>

int factorial(int N)
{
	int res(1);
	for(int i(N); i > 1; --i)
		res *= i;
	std::cout << "Result is: " << res << std::endl;
	return res;
}

std::deque<std::packaged_task<int()> > task_q;
std::mutex mu;
std::condition_variable cond;

void thread_1(){
	std::packaged_task<int()> t;
	{
		std::unique_lock<std::mutex> locker(mu);
		cond.wait(locker, [](){return !task_q.empty();});
		t = std::move(task_q.front());
		task_q.pop_front();
	}
	t();
}


int main()
{
	std::thread t1(thread_1);
	std::packaged_task<int()> task(std::bind(factorial, 6));
	std::future<int> fu = task.get_future();
	{
		std::lock_guard<std::mutex> locker(mu);
		task_q.push_back(std::move(task));
	}
	cond.notify_one();

	std::cout << fu.get() << std::endl;
	
	t1.join();
	
	return 0;
}
